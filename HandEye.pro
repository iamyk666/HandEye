#-------------------------------------------------
#
# Project created by QtCreator 2016-01-15T09:06:34
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HandEye
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageacqdialog.cpp \
    imagegrabber.cpp \
    handeyedialog.cpp \
    widget.cpp

HEADERS  += mainwindow.h \
    imageacqdialog.h \
    imagegrabber.h \
    handeyedialog.h \
    widget.h

FORMS    += mainwindow.ui \
    imageacqdialog.ui \
    handeyedialog.ui \
    widget.ui

#INCLUDEPATH += D:\ProgramFiles\Basler\pylon\include/
#INCLUDEPATH += D:\ProgramFiles\Basler\genicam\library\cpp\include

#LIBS+=D:\ProgramFiles\Basler\pylon\lib\Win32\PylonGigE_MD_VC100_TL.lib
