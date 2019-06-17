#-------------------------------------------------
#
# Project created by QtCreator 2019-05-14T20:58:42
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwidget.cpp \
        loginwidget.cpp \
        customelineedit.cpp \
        contentwidget.cpp \
        previewwidget.cpp \
        startconnectwork.cpp \
        moniter.cpp \
        playworker.cpp \
        controlwidget.cpp \
        previewstack.cpp \
    playbackwidget.cpp

INCLUDEPATH += \
        . \
        ../../include

HEADERS += \
        mainwidget.h \
        loginwidget.h \
        customelineedit.h \
        contentwidget.h \
        previewwidget.h \
        common.h \
        startconnectwork.h \
        moniter.h \
        playworker.h \
        controlwidget.h \
        previewstack.h \
    playbackwidget.h

FORMS += \
        mainwidget.ui \
        loginwidget.ui \
        contentwidget.ui \
        previewwidget.ui \
    playbackwidget.ui

CONFIG(debug, debug|release){
    MOC_DIR = ../../obj_d/aspsysclient/.moc
    UI_DIR = ../../obj_d/aspsysclient/.ui
    OBJECTS_DIR	= ../../obj_d/aspsysclient/
    DESTDIR = ../../bin_d
#    DLLDESTDIR 	= ../../lib_d
    TARGET = aspsysclient_d
    LIBS += -L../../lib_d \
        -llibgroupsockd \
        -lJVSDKP \
        -llibjvlived \
        -lJmp4pkg \
        -llibBasicUsageEnvironment \
        -llibeay32 \
        -llibliveMedia \
        -llibUsageEnvironment \
        -lQtSingleApplicationd \
        -lsqlite3 \
        -lssleay32 \
        -lVideoPlayer \
        -luser32 \
        -lws2_32

}
else{
    MOC_DIR = ../../obj/aspsysclient/.moc
    UI_DIR = ../../obj/aspsysclient/.ui
    OBJECTS_DIR	= ../../obj/aspsysclient/
    DESTDIR = ../../bin
#    DLLDESTDIR 	= ../../lib
    TARGET = aspsysclient
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    style.qss
