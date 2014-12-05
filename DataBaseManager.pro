#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T09:04:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataBaseManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    visualizacionmodo.cpp \
    edicionmodo.cpp \
    menu.cpp \
    creartabla.cpp \
    abrirbd.cpp \
    DataBaseManager.cpp \
    DataField.cpp \
    Field.cpp \
    ManejadorArchivos.cpp \
    MetaDataField.cpp \
    MetaDataReg.cpp \
    Register.cpp \
    Table.cpp

HEADERS  += mainwindow.h \
    visualizacionmodo.h \
    edicionmodo.h \
    menu.h \
    creartabla.h \
    abrirbd.h \
    DataBaseManager.h \
    DataField.h \
    Field.h \
    Lista.h \
    ManejadorArchivos.h \
    MetaDataField.h \
    MetaDataReg.h \
    Nodo.h \
    Register.h \
    Table.h

FORMS    += mainwindow.ui \
    visualizacionmodo.ui \
    edicionmodo.ui \
    menu.ui \
    creartabla.ui \
    abrirbd.ui \
    modoedicion.ui

RESOURCES += \
    res.qrc
