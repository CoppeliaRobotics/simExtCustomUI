QT += core gui widgets printsupport webenginewidgets

TARGET = v_repExtCustomUI
TEMPLATE = lib

DEFINES -= UNICODE
DEFINES += QT_COMPIL
CONFIG += shared debug_and_release
INCLUDEPATH += "../include"
INCLUDEPATH += "external/QCustomPlot-2.0.0-beta"
INCLUDEPATH += "external/QDataflowCanvas"

*-msvc* {
	QMAKE_CXXFLAGS += -O2
	QMAKE_CXXFLAGS += -W3
}
*-g++*|*clang* {
	QMAKE_CXXFLAGS += -O3
	QMAKE_CFLAGS += -O3
        QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-unused-parameter
        QMAKE_CXXFLAGS_WARN_OFF = -Wall -Wno-unused-parameter
}

win32 {
    DEFINES += WIN_VREP
    DEFINES += NOMINMAX
    DEFINES += strcasecmp=_stricmp
    INCLUDEPATH += "c:/local/boost_1_62_0"
}

macx {
    QMAKE_MAC_SDK = macosx10.12
    DEFINES += MAC_VREP
    INCLUDEPATH += "/usr/local/Cellar/boost/1.63.0/include/"
}

unix:!macx {
    DEFINES += LIN_VREP
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

stubs_h.target = stubs.h
stubs_h.output = stubs.h
stubs_h.input = callbacks.xml
stubs_h.commands = python -m v_repStubsGen -H stubs.h callbacks.xml
QMAKE_EXTRA_TARGETS += stubs_h
PRE_TARGETDEPS += stubs.h

stubs_cpp.target = stubs.cpp
stubs_cpp.output = stubs.cpp
stubs_cpp.input = callbacks.xml
stubs_cpp.commands = python -m v_repStubsGen -C stubs.cpp callbacks.xml
QMAKE_EXTRA_TARGETS += stubs_cpp
PRE_TARGETDEPS += stubs.cpp

reference_html.target = reference.html
reference_html.output = reference.html
reference_html.input = callbacks.xml
reference_html.commands = xsltproc --path \"$$PWD/\" -o reference.html callbacks.xsl callbacks.xml
QMAKE_EXTRA_TARGETS += reference_html
PRE_TARGETDEPS += reference.html

widgets_html.target = widgets.html
widgets_html.output = widgets.html
widgets_html.input = widgets.xml
widgets_html.commands = xsltproc --path \"$$PWD/\" -o widgets.html widgets.xsl widgets.xml
QMAKE_EXTRA_TARGETS += widgets_html
PRE_TARGETDEPS += widgets.html

UI_lua.target = UI.lua
UI_lua.output = UI.lua
UI_lua.input = callbacks.xml
UI_lua.commands = python \"$$PWD/generate_aliases.py\" UI.lua
QMAKE_EXTRA_TARGETS += UI_lua
PRE_TARGETDEPS += UI.lua

HEADERS += \
    debug.h \
    signal_spy.h \
    plugin.h \
    v_repExtCustomUI.h \
    ../include/v_repLib.h \
    stubs.h \
    UIFunctions.h \
    UIProxy.h \
    widgets/Button.h \
    widgets/Checkbox.h \
    widgets/Combobox.h \
    widgets/Dataflow.h \
    widgets/Edit.h \
    widgets/Event.h \
    widgets/Group.h \
    widgets/HSlider.h \
    widgets/Image.h \
    widgets/Label.h \
    widgets/LayoutWidget.h \
    widgets/Plot.h \
    widgets/Progressbar.h \
    widgets/Radiobutton.h \
    widgets/Slider.h \
    widgets/Spinbox.h \
    widgets/Table.h \
    widgets/Tabs.h \
    widgets/Tree.h \
    widgets/VSlider.h \
    widgets/WebBrowser.h \
    widgets/Widget.h \
    widgets/Window.h \
    widgets/all.h \
    LuaCallbackFunction.h \
    Proxy.h \
    XMLUtils.h \
    tinyxml2.h \
    external/QCustomPlot-2.0.0-beta/qcustomplot.h \
    external/QDataflowCanvas/qdataflowmodel.h \
    external/QDataflowCanvas/qdataflowcanvas.h

SOURCES += \
    debug.cpp \
    signal_spy.cpp \
    v_repExtCustomUI.cpp \
    ../common/v_repLib.cpp \
    stubs.cpp \
    UIFunctions.cpp \
    UIProxy.cpp \
    widgets/Button.cpp \
    widgets/Checkbox.cpp \
    widgets/Combobox.cpp \
    widgets/Dataflow.cpp \
    widgets/Edit.cpp \
    widgets/Event.cpp \
    widgets/Group.cpp \
    widgets/HSlider.cpp \
    widgets/Image.cpp \
    widgets/Label.cpp \
    widgets/LayoutWidget.cpp \
    widgets/Plot.cpp \
    widgets/Progressbar.cpp \
    widgets/Radiobutton.cpp \
    widgets/Slider.cpp \
    widgets/Spinbox.cpp \
    widgets/Table.cpp \
    widgets/Tabs.cpp \
    widgets/Tree.cpp \
    widgets/VSlider.cpp \
    widgets/WebBrowser.cpp \
    widgets/Widget.cpp \
    widgets/Window.cpp \
    LuaCallbackFunction.cpp \
    Proxy.cpp \
    XMLUtils.cpp \
    tinyxml2.cpp \
    external/QCustomPlot-2.0.0-beta/qcustomplot.cpp \
    external/QDataflowCanvas/qdataflowmodel.cpp \
    external/QDataflowCanvas/qdataflowcanvas.cpp


