QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets testlib gui

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutpopup.cpp \
    algorithm.cpp \
    graphicscene.cpp \
    main.cpp \
    mainwindow.cpp \
    solutionpopup.cpp \
    taskpopup.cpp \
    test_graphicscene.cpp

HEADERS += \
    aboutpopup.h \
    algorithm.h \
    graphicscene.h \
    mainwindow.h \
    solutionpopup.h \
    taskpopup.h \
    test_graphicscene.h

FORMS += \
    aboutpopup.ui \
    mainwindow.ui \
    solutionpopup.ui \
    taskpopup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
