include($$PWD/../KSerialize.pri)

QT = core gui widgets
TEMPLATE = app
DESTDIR = $$IDE_BIN_PATH

SOURCES += \
    DStudent.cpp \
    main.cpp

LIBS += -L$$IDE_LIBRARY_PATH -lKSerialize$$FILE_POSTFIX

HEADERS += \
    DStudent.h
