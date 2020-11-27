#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

#include "midi_input.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();

public slots:

signals:
    void midiDeviceSet(int device);
    void poweroff();
    void save();

private:
    Ui::SettingsWidget *ui;

    MIDIInput* _midiInput;
};

#endif // SETTINGSWIDGET_H
