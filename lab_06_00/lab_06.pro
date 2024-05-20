QT += core gui testlib widgets
CONFIG += c++20 testcase

CONFIG -= app_bundle #creates test.exe instead of test.exe.app
TARGET = release.exe

INCLUDEPATH += inc/
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
DESTDIR = out/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/buttons.cpp \
    src/color.cpp \
    src/drawing.cpp \
    src/fill.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/menu.cpp \
    src/requests.cpp \
    src/table.cpp \
    src/table_widget.cpp \
    # unit_fill.cpp \
    # unit_main.cpp

HEADERS += \
    inc/drawing.h \
    inc/fill.h \
    inc/mainwindow.h \
    inc/requests.h \
    inc/structures.h \
    inc/table.h \
    # unit_fill.h

FORMS += \
    forms/mainwindow.ui

RESOURCES += \
    image.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
