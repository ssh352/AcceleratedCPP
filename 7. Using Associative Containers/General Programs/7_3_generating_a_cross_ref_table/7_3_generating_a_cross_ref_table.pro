TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    split.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    split.h

