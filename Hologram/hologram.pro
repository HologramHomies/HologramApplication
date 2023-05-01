QT       += core gui multimedia multimediawidgets
LIBS += -LC:\Users\felip\Downloads\libusb-1.0.26-binaries\libusb-1.0.26-binaries\libusb-MinGW-x64\lib -lusb-1.0
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += C:\Users\felip\Downloads\libusb-1.0.26-binaries\libusb-1.0.26-binaries\libusb-MinGW-x64\include

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttonhandler.cpp \
    main.cpp \
    mainwindow.cpp \
    video_config.cpp

HEADERS += \
    buttonhandler.h \
    libusb.h \
    mainwindow.h \
    video_config.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
