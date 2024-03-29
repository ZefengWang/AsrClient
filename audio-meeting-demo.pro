QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = AsrClient
#LIBS += lib/libeay32.dll \
#        lib/ssleay.dll

LIBS += lib/libeay32.dll \
        lib/ssleay.dll \
        lib/libcrypto-1_1-x64.dll \
        libssl-1_1-x64.dll

SOURCES += \
    src/audioio.cpp \
    src/audiothread.cpp \
    src/audioutils.cpp \
    src/configutils.cpp \
    src/fileutils.cpp \
    src/main.cpp \
    src/asrclient.cpp \
    src/netutils.cpp

HEADERS += \
    include/asrclient.h \
    include/audioio.h \
    include/audiothread.h \
    include/audioutils.h \
    include/configutils.h \
    include/fileutils.h \
    include/netutils.h

FORMS += \
    ui/asrclient.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
