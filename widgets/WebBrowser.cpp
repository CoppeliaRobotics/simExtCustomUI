#include "WebBrowser.h"

#include "XMLUtils.h"

#include "UIProxy.h"

#include <QWebEngineView>

WebBrowser::WebBrowser()
    : Widget("webbrowser")
{
}

WebBrowser::~WebBrowser()
{
}

void WebBrowser::parse(Widget *parent, std::map<int, Widget*>& widgets, tinyxml2::XMLElement *e)
{
    Widget::parse(parent, widgets, e);

    url = xmlutils::getAttrStr(e, "url", "");

    onLoadProgress = xmlutils::getAttrStr(e, "on-load-progress", "");
}

QWidget * WebBrowser::createQtWidget(Proxy *proxy, UIProxy *uiproxy, QWidget *parent)
{
    QWebEngineView *view = new QWebEngineView(parent);
    view->setEnabled(enabled);
    view->setVisible(visible);
    view->setStyleSheet(QString::fromStdString(style));
    if(url != "")
        view->load(QString::fromStdString(url));
    QObject::connect(view, &QWebEngineView::loadProgress, uiproxy, &UIProxy::onLoadProgress);
    setQWidget(view);
    setProxy(proxy);
    return view;
}

void WebBrowser::loadUrl(std::string url)
{
    static_cast<QWebEngineView*>(getQWidget())->load(QString::fromStdString(url));
}

