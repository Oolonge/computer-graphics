QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawing.cpp \
    errors.cpp \
    graphics.cpp \
    io.cpp \
    main.cpp \
    mainwindow.cpp \
    operations.cpp \
    projection.cpp \
    task_performer.cpp \
    volumetric_point.cpp

HEADERS += \
    drawing.h \
    errors.h \
    graphics.h \
    io.h \
    mainwindow.h \
    operations.h \
    projection.h \
    task_performer.h \
    volumetric_point.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
