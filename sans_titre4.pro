#-------------------------------------------------
#
# Project created by QtCreator 2017-07-18T18:09:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sans_titre4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QT       += core

QT       -= gui

TARGET = HttpGetExample
CONFIG   += console
CONFIG   -= app_bundle
QT += network

