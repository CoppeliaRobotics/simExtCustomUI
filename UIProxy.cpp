#include "UIProxy.h"
#include "debug.h"
#include "widgets/Widget.h"

#include <QThread>
#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QLabel>

#include "stubs.h"

using namespace tinyxml2;

// UIProxy is a singleton

UIProxy *UIProxy::instance = NULL;

UIProxy::UIProxy(QObject *parent)
    : QObject(parent)
{
}

UIProxy::~UIProxy()
{
    UIProxy::instance = NULL;
}

UIProxy * UIProxy::getInstance(QObject *parent)
{
    if(!UIProxy::instance)
    {
        UIProxy::instance = new UIProxy(parent);

        DBG << "UIProxy constructed in thread " << QThread::currentThreadId() << std::endl;

        uiThread();
    }
    return UIProxy::instance;
}

void UIProxy::destroyInstance()
{
    if(UIProxy::instance)
        delete UIProxy::instance;
}

void UIProxy::onCreate(Proxy *proxy)
{
    proxy->createQtWidget(this);
}

// The following slots are directly connected to Qt Widgets' signals.
// Here we look up the sender to find the corresponding Widget object,
// and emit a signal with the Widget object pointer.
//
// That signal will be connected to a slot in UIFunctions, such
// that the callback is called from the SIM thread.

void UIProxy::onButtonClick()
{
    QWidget *qwidget = dynamic_cast<QWidget*>(sender());
    if(qwidget)
    {
        Widget *widget = Widget::byQWidget(qwidget);
        if(widget)
        {
            emit buttonClick(widget);
        }
    }
}

void UIProxy::onValueChange(int value)
{
    QWidget *qwidget = dynamic_cast<QWidget*>(sender());
    if(qwidget)
    {
        Widget *widget = Widget::byQWidget(qwidget);
        if(widget)
        {
            emit valueChange(widget, value);
        }
    }
}

void UIProxy::onValueChange(QString value)
{
    QWidget *qwidget = dynamic_cast<QWidget*>(sender());
    if(qwidget)
    {
        Widget *widget = Widget::byQWidget(qwidget);
        if(widget)
        {
            emit valueChange(widget, value);
        }
    }
}

void UIProxy::onEditingFinished()
{
    QWidget *qwidget = dynamic_cast<QWidget*>(sender());

    if(qwidget)
    {
        Widget *widget = Widget::byQWidget(qwidget);

        if(widget)
        {
            emit editingFinished(widget);
        }
    }
}

// The following slots are wrappers for functions called from SIM thread
// which should instead execute in the UI thread.

void UIProxy::onDestroy(Proxy *proxy)
{
    DBG << "proxy=" << (void*)proxy << std::endl;

    if(!proxy) return;
    if(!proxy->ui) return;
    if(!proxy->ui->qwidget) return;

    proxy->ui->qwidget->deleteLater();
}

void UIProxy::onShowWindow(Window *window)
{
    DBG << "window=" << (void*)window << std::endl;

    if(!window) return;

    window->show();
}

void UIProxy::onHideWindow(Window *window)
{
    DBG << "window=" << (void*)window << std::endl;

    if(!window) return;

    window->hide();
}

void UIProxy::onSetImage(Image *image, const char *data, int w, int h)
{
    DBG << "image=" << (void*)image << ", data=" << (void*)data << ", w=" << w << ", h=" << h << std::endl;

    if(!image) return;
    if(!data) return;

    QImage::Format format = QImage::Format_RGB888;
    int bpp = 3; // bytes per pixel
    QPixmap pixmap = QPixmap::fromImage(QImage((unsigned char *)data, w, h, bpp * w, format));
    simReleaseBufferE((char *)data); // XXX: simReleaseBuffer should accept a const pointer
    QLabel *label = static_cast<QLabel*>(image->qwidget);
    label->setPixmap(pixmap);
    label->resize(pixmap.size());
}

void UIProxy::onSceneChange(Window *window, int oldSceneID, int newSceneID)
{
    DBG << "window=" << (void*)window << ", oldSceneID=" << oldSceneID << ", newSceneID" << newSceneID << std::endl;

    if(!window) return;

    window->onSceneChange(oldSceneID, newSceneID);
}

void UIProxy::onSetEnabled(Widget *widget, bool enabled)
{
    DBG << "widget=" << (void*)widget << ", enabled=" << enabled << std::endl;

    if(!widget) return;

    widget->getQWidget()->setEnabled(enabled);
}

