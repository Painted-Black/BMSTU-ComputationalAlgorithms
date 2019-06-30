TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    filehelper.cpp \
    functiontable.cpp \
    menu.cpp \
    action.cpp

HEADERS += \
    filehelper.h \
    functiontable.h \
    menu.h \
    action.h
