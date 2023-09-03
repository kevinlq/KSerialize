TEMPLATE = subdirs

SUBDIRS += \
    src \
    example \

equals(TEST,1){
SUBDIRS += $$PWD/test
}

CONFIG += ordered
