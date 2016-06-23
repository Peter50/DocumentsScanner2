#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:35:42
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DocumentsScanner2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    documentanalyser.cpp \
    documenthandler.cpp \
    odtreader.cpp \
    pdfreader.cpp \
    textreader.cpp \
    webreader.cpp

HEADERS  += mainwindow.h \
    documentanalyser.h \
    documenthandler.h \
    documentreader.h \
    odtreader.h \
    pdfreader.h \
    textreader.h \
    webreader.h

FORMS    += mainwindow.ui

INCLUDEPATH  += /usr/include/poppler/qt5
LIBS         += -L/usr/lib -lpoppler-qt5

INCLUDEPATH  += /usr/include/quazip
LIBS         += -L/usr/lib -lquazip

LIBS         += -L/usr/local/zlib/lib
INCLUDEPATH  += /usr/local/zlib/include
