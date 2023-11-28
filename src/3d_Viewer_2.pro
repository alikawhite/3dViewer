QT  += openglwidgets
QT  += core gui printsupport opengl
QT  += widgets

include(QtGifImage/gifimage/qtgifimage.pri)


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 c

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
#    tests/test.c

HEADERS += \
    athenian.h \
    controller.h \
    mainwindow.h \
    model.h \
    myopenglwidget.h
 #    tests/test.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
