QT       += core gui

QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addedmaterial.cpp \
    calculatedtablemodel.cpp \
    dbconnection.cpp \
    main.cpp \
    mainwindow.cpp \
    materialtablemodel.cpp \
    workers.cpp \
    workerscalculated.cpp \
    workerstablemodel.cpp

HEADERS += \
    addedmaterial.h \
    calculatedtablemodel.h \
    dbconnection.h \
    mainwindow.h \
    materialtablemodel.h \
    workers.h \
    workerscalculated.h \
    workerstablemodel.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
