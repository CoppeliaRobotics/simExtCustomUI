#ifndef WEBBROWSER_H_INCLUDED
#define WEBBROWSER_H_INCLUDED

#include <vector>
#include <string>

#include <QWidget>

#include "tinyxml2.h"

class Proxy;
class UIProxy;

#include "Widget.h"
#include "Event.h"

class WebBrowser : public Widget
{
protected:
    std::string url;
    std::string onLoadProgress;

public:
    WebBrowser();
    virtual ~WebBrowser();

    void parse(Widget *parent, std::map<int, Widget*>& widgets, tinyxml2::XMLElement *e);
    QWidget * createQtWidget(Proxy *proxy, UIProxy *uiproxy, QWidget *parent);

    void loadUrl(std::string url);

    friend class UIFunctions;
};

#endif // WEBBROWSER_H_INCLUDED

