TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QT   += core gui opengl
LIBS += -lopengl32 -lfreeglut -lglu32
SOURCES += \
        entradas.cpp \
        iniciar_jogo.cpp \
        leitura.cpp \
        main.cpp \
        textura.cpp

HEADERS += \
    ../trabalhoFinal/pecas.h \
    objeto.h \
    pecas.h \
    tabuleiro.h
