QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    camera.cpp \
    castlebase.cpp \
    castleroof.cpp \
    ceil.cpp \
    glassball.cpp \
    glassballbase.cpp \
    ground.cpp \
    light.cpp \
    main.cpp \
    model.cpp \
    snow.cpp \
    towerbase.cpp \
    towerroof.cpp \
    widget.cpp

HEADERS += \
    background.h \
    camera.h \
    castlebase.h \
    castleroof.h \
    ceil.h \
    glassball.h \
    glassballbase.h \
    ground.h \
    light.h \
    model.h \
    snow.h \
    towerbase.h \
    towerroof.h \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

