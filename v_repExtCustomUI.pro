QT += core gui widgets printsupport

TARGET = v_repExtCustomUI
TEMPLATE = lib

DEFINES -= UNICODE
DEFINES += QT_COMPIL
CONFIG += shared debug_and_release
INCLUDEPATH += "../include"
INCLUDEPATH += "external/QCustomPlot-2.0.0-beta"
INCLUDEPATH += "external/QDataflowCanvas"
INCLUDEPATH += "external"
INCLUDEPATH += "generated"

*-msvc* {
	QMAKE_CXXFLAGS += -O2
	QMAKE_CXXFLAGS += -W3
}
*-g++*|*clang* {
        CONFIG(debug, debug|release){
            QMAKE_CXXFLAGS += -g
            QMAKE_CFLAGS += -g
        } else {
            QMAKE_CXXFLAGS += -O3
            QMAKE_CFLAGS += -O3
        }
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

generated.target = $$PWD/generated
generated.output = $$PWD/generated
generated.commands = $(MKDIR) $$PWD/generated
QMAKE_EXTRA_TARGETS += generated
PRE_TARGETDEPS += $$PWD/generated

stubs_h.target = generated/stubs.h
stubs_h.output = generated/stubs.h
stubs_h.input = callbacks.xml
stubs_h.commands = python \"$$PWD/external/v_repStubsGen/main.py\" -H generated/stubs.h callbacks.xml
QMAKE_EXTRA_TARGETS += stubs_h
PRE_TARGETDEPS += generated/stubs.h

stubs_cpp.target = generated/stubs.cpp
stubs_cpp.output = generated/stubs.cpp
stubs_cpp.input = callbacks.xml
stubs_cpp.commands = python \"$$PWD/external/v_repStubsGen/main.py\" -C generated/stubs.cpp callbacks.xml
QMAKE_EXTRA_TARGETS += stubs_cpp
PRE_TARGETDEPS += generated/stubs.cpp

lua_xml.target = generated/lua.xml
lua_xml.output = generated/lua.xml
lua_xml.input = simExtCustomUI.lua
lua_xml.commands = python \"$$PWD/external/v_repStubsGen/lua_to_xml.py\" simExtCustomUI.lua generated/lua.xml
QMAKE_EXTRA_TARGETS += lua_xml
PRE_TARGETDEPS += generated/lua.xml

reference_xml.target = generated/reference.xml
reference_xml.output = generated/reference.xml
reference_xml.input = callbacks.xml generated/lua.xml
reference_xml.commands = python \"$$PWD/external/v_repStubsGen/merge_xml.py\" callbacks.xml generated/lua.xml generated/reference.xml
QMAKE_EXTRA_TARGETS += reference_xml
PRE_TARGETDEPS += generated/reference.xml

reference_html.target = generated/reference.html
reference_html.output = generated/reference.html
reference_html.input = generated/reference.xml
reference_html.commands = xsltproc --path \"$$PWD/\" -o generated/reference.html \"$$PWD/external/v_repStubsGen/xsl/reference.xsl\" generated/reference.xml
QMAKE_EXTRA_TARGETS += reference_html
PRE_TARGETDEPS += generated/reference.html

lua_calltips_cpp.target = generated/lua_calltips.cpp
lua_calltips_cpp.output = generated/lua_calltips.cpp
lua_calltips_cpp.input = simExtCustomUI.lua \"$$PWD/external/v_repStubsGen/generate_lua_calltips.py\"
lua_calltips_cpp.commands = python \"$$PWD/external/v_repStubsGen/generate_lua_calltips.py\" CustomUI UI \"$$PWD/simExtCustomUI.lua\" \"$$PWD/generated/lua_calltips.cpp\"
QMAKE_EXTRA_TARGETS += lua_calltips_cpp
PRE_TARGETDEPS += generated/lua_calltips.cpp

notepadplusplus_xml.target = generated/np++.xml
notepadplusplus_xml.output = generated/np++.xml
notepadplusplus_xml.input = generated/reference.xml
notepadplusplus_xml.commands = python \"$$PWD/external/v_repStubsGen/generate_notepadplusplus_xml.py\" \"$$PWD/generated/reference.xml\" \"$$PWD/generated/np++.xml\"
QMAKE_EXTRA_TARGETS += notepadplusplus_xml
PRE_TARGETDEPS += generated/np++.xml

notepadplusplus_txt.target = generated/np++.txt
notepadplusplus_txt.output = generated/np++.txt
notepadplusplus_txt.input = generated/reference.xml
notepadplusplus_txt.commands = python \"$$PWD/external/v_repStubsGen/generate_notepadplusplus_txt.py\" \"$$PWD/generated/reference.xml\" \"$$PWD/generated/np++.txt\"
QMAKE_EXTRA_TARGETS += notepadplusplus_txt
PRE_TARGETDEPS += generated/np++.txt

widgets_html.target = generated/widgets.html
widgets_html.output = generated/widgets.html
widgets_html.input = widgets.xml
widgets_html.commands = xsltproc --path \"$$PWD/\" -o generated/widgets.html widgets.xsl widgets.xml
QMAKE_EXTRA_TARGETS += widgets_html
PRE_TARGETDEPS += generated/widgets.html

HEADERS += \
    debug.h \
    signal_spy.h \
    plugin.h \
    v_repExtCustomUI.h \
    ../include/v_repLib.h \
    generated/stubs.h \
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
    widgets/TextBrowser.h \
    widgets/Tree.h \
    widgets/VSlider.h \
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
    generated/stubs.cpp \
    generated/lua_calltips.cpp \
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
    widgets/TextBrowser.cpp \
    widgets/Tree.cpp \
    widgets/VSlider.cpp \
    widgets/Widget.cpp \
    widgets/Window.cpp \
    LuaCallbackFunction.cpp \
    Proxy.cpp \
    XMLUtils.cpp \
    tinyxml2.cpp \
    external/QCustomPlot-2.0.0-beta/qcustomplot.cpp \
    external/QDataflowCanvas/qdataflowmodel.cpp \
    external/QDataflowCanvas/qdataflowcanvas.cpp


