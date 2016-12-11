#include "WebView.h"

#include "XMLUtils.h"

#include "UIProxy.h"

#include <QWebEngineView>

WebView::WebView()
    : Widget("webview"), width(300), height(200)
{
}

WebView::~WebView()
{
}

void WebView::parse(Widget *parent, std::map<int, Widget*>& widgets, tinyxml2::XMLElement *e)
{
    Widget::parse(parent, widgets, e);

    url = xmlutils::getAttrStr(e, "url", "about:blank");

    width = xmlutils::getAttrInt(e, "width", width);

    height = xmlutils::getAttrInt(e, "height", height);
}

QWidget * WebView::createQtWidget(Proxy *proxy, UIProxy *uiproxy, QWidget *parent)
{
    QWebEngineView *view = new QWebEngineView(parent);
    view->setEnabled(enabled);
    view->setVisible(visible);
    view->setStyleSheet(QString::fromStdString(style));
    view->setUrl(QUrl(QString::fromStdString(url)));
    view->resize(width, height);
    setQWidget(view);
    setProxy(proxy);
    return view;
}

