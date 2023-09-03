include($$PWD/../KSerialize.pri)

QT = core core-private gui widgets
TEMPLATE	 = lib
DESTDIR = $$IDE_LIBRARY_PATH
TARGET	 = KSerialize$$FILE_POSTFIX
DEFINES += KSERIALIZE_LIBRARY

HEADERS += \
    KSerializationHelper.h \
    KSerialize.h \
    KSerialize_global.h \
    Kserialize_p.h

SOURCES += \
    KSerialize.cpp
