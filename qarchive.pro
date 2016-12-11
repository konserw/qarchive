TEMPLATE = subdirs
SUBDIRS +=	\
    libqarchive \
    test

include(qarchive.pri)

test.depends = libqarchive
