QT += core gui testlib widgets
CONFIG += c++20 testcase

CONFIG -= app_bundle #creates test.exe instead of test.exe.app
TARGET = unit_tests.exe

QMAKE_CXXFLAGS += -g -fprofile-instr-generate -fcoverage-mapping -O0
QMAKE_LFLAGS += -fprofile-instr-generate

INCLUDEPATH += inc/
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
DESTDIR = out/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    # src/main.cpp \
    src/algorithms.cpp \
    src/buttons.cpp \
    src/mainwindow.cpp \
    src/measurement_funcs.cpp \
    src/menu.cpp \
    unit_tests/test_algorithms.cpp \
    unit_tests/unit_main.cpp

HEADERS += \
    inc/algorithms.h \
    inc/consts.h \
    inc/mainwindow.h \
    unit_tests/test_algorithms.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
