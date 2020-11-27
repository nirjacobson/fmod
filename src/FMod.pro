QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /home/nir/GitHub/libfmod/src

SOURCES += \
    algorithmdisplaywidget.cpp \
    algorithmgraph.cpp \
    algorithmwidget.cpp \
    envelopedisplaywidget.cpp \
    envelopewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    midi_input.cpp \
    midipoller.cpp \
    pianowidget.cpp \
    settingswidget.cpp

HEADERS += \
    algorithmdisplaywidget.h \
    algorithmgraph.h \
    algorithmwidget.h \
    audio_output.h \
    consumer.h \
    envelopedisplaywidget.h \
    envelopewidget.h \
    mainwindow.h \
    midi_input.h \
    midipoller.h \
    pianowidget.h \
    settingswidget.h

FORMS += \
    algorithmdisplaywidget.ui \
    algorithmwidget.ui \
    envelopedisplaywidget.ui \
    envelopewidget.ui \
    mainwindow.ui \
    pianowidget.ui \
    settingswidget.ui

QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"
QMAKE_CXXFLAGS += -pthread
LIBS += -lportaudio -lasound -lm -lpthread -lportmidi -L/home/nir/GitHub/libfmod -lfmod

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
