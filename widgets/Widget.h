#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include <vector>
#include <map>
#include <string>

#include <QWidget>

#include "tinyxml2.h"

class Proxy;
class UIProxy;

class Widget
{
private:
    QWidget *qwidget;
    Proxy *proxy;
    const std::string widgetClass;

protected:
    static int nextId;
    static std::map<int, Widget *> widgets;
    static std::map<QWidget *, Widget *> widgetByQWidget;

    int id;

    Widget(std::string widgetClass);

    void setQWidget(QWidget *qwidget);
    void setProxy(Proxy *proxy);

public:
    virtual ~Widget();

    virtual void parse(tinyxml2::XMLElement *e);
    virtual QWidget * createQtWidget(Proxy *proxy, UIProxy *uiproxy, QWidget *parent) = 0;

    inline QWidget * getQWidget() {return qwidget;}

    template<typename T>
    static T * parse1(tinyxml2::XMLElement *e);
    static Widget * parseAny(tinyxml2::XMLElement *e);

    static Widget * byId(int id);
    static Widget * byQWidget(QWidget *w);

    std::string str();

#ifdef DEBUG
    static void dumpTables();
#endif

    friend class UIFunctions;
    friend class UIProxy;
    friend class Window;
};

#endif // WIDGET_H_INCLUDED

