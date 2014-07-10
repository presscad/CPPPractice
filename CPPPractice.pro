TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    alg.cpp \
    simplestring.cpp \
    util.cpp

HEADERS += \
    alg.h \
    simplestring.h \
    util.h

win32:CONFIG(release, debug|release): {
    LIBS += -lVersion -lAdvapi32 -lWs2_32
}
win32:CONFIG(debug, debug|release): {
    LIBS += -lVersion -lAdvapi32 -lWs2_32
}


