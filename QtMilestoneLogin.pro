QT += core network xml
QT -= gui

CONFIG += c++11

TARGET = QtMilestoneLogin
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    milestonemanager.cpp \
    soapconnectionmanager.cpp

HEADERS += \
    milestonemanager.h \
    soapconnectionmanager.h
