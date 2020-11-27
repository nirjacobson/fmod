#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <iomanip>

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <QtDBus/QDBusInterface>

#include "generator.h"
#include "audio_output.h"
#include "midi_input.h"
#include "midipoller.h"
#include "patchfile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setEnvelope1();
    void setEnvelope2();
    void setEnvelope3();
    void setEnvelope4();
    void setAlgorithm();
    void setFeedback();

    void handleMIDIMessage(const long msg);

    void poweroff();

    void setMIDIDevice(int device);
    void keyOn(const char key);
    void keyOff(const char key);

    void savePatchFile();

private:
    Ui::MainWindow *ui;

    Generator _generator;

    AudioOutput<float>* _audioOutput;
    MIDIInput* _midiInput;
    MIDIPoller _midiPoller;

    QDBusInterface _systemdIface;

    PatchFile _patchFile;

    void readPatchFile();
};
#endif // MAINWINDOW_H
