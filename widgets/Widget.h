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
protected:
    static int nextId;
    static std::map<int, Widget *> widgets;
    static std::map<QWidget *, Widget *> widgetByQWidget;

    int id;

    QWidget *qwidget;

    Proxy *proxy;

    Widget();

public:
    virtual ~Widget();

    virtual bool parse(tinyxml2::XMLElement *e, std::vector<std::string>& errors);
    virtual QWidget * createQtWidget(Proxy *proxy, UIProxy *uiproxy, QWidget *parent) = 0;

    inline QWidget * getQWidget() {return qwidget;}

    template<typename T>
    static Widget * tryParse(tinyxml2::XMLElement *e, std::vector<std::string>& errors);
    static Widget * parseAny(tinyxml2::XMLElement *e, std::vector<std::string>& errors);

    static Widget * byId(int id);
    static Widget * byQWidget(QWidget *w);

    virtual const char * name();

    std::string str();

#ifdef DEBUG
    static void dumpTables();
#endif

    friend class UIFunctions;
    friend class UIProxy;
    friend class Window;
};

#endif // WIDGET_H_INCLUDED

