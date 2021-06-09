# NOTE: this is only for viewing the source code, use the Makefile for building and running.

INCLUDEPATH += .

HEADERS += \
    helpers.h

SOURCES += \
    type_conversion.cpp \
    loop_unrolling.cpp \
    global_storage.cpp \
    abstract_machine.cpp \
    cache_locality.cpp \
    branch_prediction.cpp \
    false_sharing.cpp

OTHER_FILES += \
    README.md \
    Makefile

CONFIG += c++2a
LIBS += -lbenchmark
