TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QT   += core gui opengl
LIBS += -lopengl32 -lfreeglut -lglu32
SOURCES += \
        leitura.cpp \
        main.cpp \
        textura.cpp

HEADERS += \
    objeto.h \
    tabuleiro.h
