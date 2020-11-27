#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _generator(AudioOutput<float>::SAMPLE_RATE)
    , _audioOutput(AudioOutput<float>::instance())
    , _midiInput(MIDIInput::instance())
    , _systemdIface("org.freedesktop.login1",
                    "/org/freedesktop/login1",
                    "org.freedesktop.login1.Manager",
                    QDBusConnection::systemBus())
    , _patchFile("/home/pi/fmod.pch")
{
    ui->setupUi(this);

    connect(ui->settingsWidget, &SettingsWidget::midiDeviceSet, this, &MainWindow::setMIDIDevice);

    _midiInput->init();
    connect(&_midiPoller, &MIDIPoller::receivedMessage, this, &MainWindow::handleMIDIMessage);
    _midiPoller.start();

    _audioOutput->producer(&_generator);
    _audioOutput->init();
    _audioOutput->start();

    connect(ui->pianoWidget, &PianoWidget::keyPressed, this, &MainWindow::keyOn);
    connect(ui->pianoWidget, &PianoWidget::keyReleased, this, &MainWindow::keyOff);

    connect(ui->settingsWidget, &SettingsWidget::poweroff, this, &MainWindow::poweroff);
    connect(ui->settingsWidget, &SettingsWidget::save, this, &MainWindow::savePatchFile);

    connect(ui->envelopeWidget1, &EnvelopeWidget::envelopeChanged, this, &MainWindow::setEnvelope1);
    connect(ui->envelopeWidget2, &EnvelopeWidget::envelopeChanged, this, &MainWindow::setEnvelope2);
    connect(ui->envelopeWidget3, &EnvelopeWidget::envelopeChanged, this, &MainWindow::setEnvelope3);
    connect(ui->envelopeWidget4, &EnvelopeWidget::envelopeChanged, this, &MainWindow::setEnvelope4);
    connect(ui->algorithmWidget, &AlgorithmWidget::algorithmChanged, this, &MainWindow::setAlgorithm);
    connect(ui->algorithmWidget, &AlgorithmWidget::feedbackChanged, this, &MainWindow::setFeedback);

    if (_patchFile.exists()) {
        readPatchFile();
    } else {
        setEnvelope1();
        setEnvelope2();
        setEnvelope3();
        setEnvelope4();
        setAlgorithm();
        setFeedback();
    }
}

MainWindow::~MainWindow()
{
    _audioOutput->stop();
    _audioOutput->destroy();

    _midiPoller.stop();
    _midiPoller.quit();
    _midiPoller.wait();

    _midiInput->destroy();

    delete ui;
}

void MainWindow::setEnvelope1()
{
    _generator.setEnvelope(0, ui->envelopeWidget1->envelope());
}

void MainWindow::setEnvelope2()
{
    _generator.setEnvelope(1, ui->envelopeWidget2->envelope());
}

void MainWindow::setEnvelope3()
{
    _generator.setEnvelope(2, ui->envelopeWidget3->envelope());
}

void MainWindow::setEnvelope4()
{
    _generator.setEnvelope(3, ui->envelopeWidget4->envelope());
}

void MainWindow::setAlgorithm()
{
    _generator.setAlgorithm(ui->algorithmWidget->algorithm());
}

void MainWindow::setFeedback()
{
    _generator.setFeedback(ui->algorithmWidget->feedback());
}

void MainWindow::handleMIDIMessage(const long msg)
{
    const char status = ((msg >> 0) & 0xFF);
    const char data1 = ((msg >> 8) & 0xFF);
//    const char data2 = ((msg >> 16) & 0xFF);

    if (status == 0x90) {
        keyOn(data1);
        ui->pianoWidget->pressKey(data1);
    } else if (status == 0x80) {
        keyOff(data1);
        ui->pianoWidget->releaseKey(data1);
    }
}

void MainWindow::poweroff()
{
    savePatchFile();
    _systemdIface.call("PowerOff", false);
}

void MainWindow::setMIDIDevice(int device)
{
    _midiPoller.stop();
    _midiPoller.quit();
    _midiPoller.wait();

    _midiInput->setDevice(device);

    _midiPoller.start();
}

void MainWindow::keyOn(const char key)
{
    _generator.keyOn(key);
}

void MainWindow::keyOff(const char key)
{
    _generator.keyOff(key);
}

void MainWindow::savePatchFile()
{
    _patchFile.setEnvelope(0, ui->envelopeWidget1->envelope());
    _patchFile.setEnvelope(1, ui->envelopeWidget2->envelope());
    _patchFile.setEnvelope(2, ui->envelopeWidget3->envelope());
    _patchFile.setEnvelope(3, ui->envelopeWidget4->envelope());
    _patchFile.setAlgorithm(ui->algorithmWidget->algorithm());
    _patchFile.setFeedback(ui->algorithmWidget->feedback());

    _patchFile.write();
}

void MainWindow::readPatchFile()
{
    _patchFile.read();

    ui->envelopeWidget1->setEnvelope(_patchFile.envelope(0));
    ui->envelopeWidget2->setEnvelope(_patchFile.envelope(1));
    ui->envelopeWidget3->setEnvelope(_patchFile.envelope(2));
    ui->envelopeWidget4->setEnvelope(_patchFile.envelope(3));
    ui->algorithmWidget->setAlgorithm(_patchFile.algorithm());
    ui->algorithmWidget->setFeedback(_patchFile.feedback());
}

