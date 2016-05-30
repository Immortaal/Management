TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Measure.cpp \
    Element.cpp \
    BackpackProblem.cpp \
    Backpack.cpp \
    Aprox.cpp

HEADERS += \
    Element.h \
    BackpackProblem.h \
    Backpack.h \
    Aprox.h
