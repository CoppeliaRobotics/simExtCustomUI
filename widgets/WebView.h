#ifndef WEBVIEW_H_INCLUDED
#define WEBVIEW_H_INCLUDED

#include <vector>
#include <string>

#include <QWidget>

#include "tinyxml2.h"

class Proxy;
class UIProxy;

#include "Widget.h"
#include "Event.h"

class WebView : public Widget
{
protected:
    std::string url;

    int width, height;

public:
    WebView();
    virtual ~WebView();

    void parse(Widget *parent, std::map<int, Widget*>& widgets, tinyxml2::XMLElement *e);
    QWidget * createQtWidget(Proxy *proxy, UIProxy *uiproxy, QWidget *parent);

    friend class UIFunctions;
};

#endif // WEBVIEW_H_INCLUDED

