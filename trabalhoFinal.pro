TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QT   += core gui opengl
LIBS += -lopengl32 -lfreeglut -lglu32
SOURCES += \
        main.cpp

HEADERS += \
    pecas.h
