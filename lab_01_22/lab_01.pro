QT += core gui testlib widgets
CONFIG += c++20 testcase

CONFIG -= app_bundle #creates test.exe instead of test.exe.app
TARGET = release.exe

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    # unit_tests/unit_main.cpp \
    # unit_tests/test_graphicscene.cpp \
    src/aboutpopup.cpp \
    src/algorithm.cpp \
    src/graphicscene.cpp \
    src/mainwindow.cpp \
    src/solutionpopup.cpp \
    src/taskpopup.cpp

HEADERS += \
    inc/aboutpopup.h \
    inc/algorithm.h \
    inc/graphicscene.h \
    inc/mainwindow.h \
    inc/solutionpopup.h \
    inc/taskpopup.h \
    # unit_tests/test_graphicscene.h

FORMS += \
    forms/aboutpopup.ui \
    forms/mainwindow.ui \
    forms/solutionpopup.ui \
    forms/taskpopup.ui

INCLUDEPATH += inc/
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
DESTDIR = out/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
