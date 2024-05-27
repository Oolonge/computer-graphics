QT += core gui testlib widgets
CONFIG += c++20 testcase

CONFIG -= app_bundle #creates test.exe instead of test.exe.app
TARGET = func_tests.exe

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
    src/menu.cpp \
    src/algorithms.cpp \
    src/buttons.cpp \
    src/drawing.cpp \
    src/mainwindow.cpp \
    src/request_handler.cpp \
    src/structures.cpp \
    func_data/func_main.cpp \
    func_data/test.cpp \
    func_data/testparser.cpp \
    # src/main.cpp \
    # unit_tests.cpp \

HEADERS += \
    func_data/test.h \
    func_data/testparser.h \
    inc/algorithms.h \
    inc/drawing.h \
    inc/mainwindow.h \
    inc/request_handler.h \
    inc/structures.h

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
