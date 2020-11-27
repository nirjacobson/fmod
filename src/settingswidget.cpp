#include "settingswidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget),
    _midiInput(MIDIInput::instance())
{
    ui->setupUi(this);

    for (const std::string& deviceName : _midiInput->devices()) {
        ui->midiDeviceComboBox->addItem(QString::fromStdString(deviceName));
    }

    connect(ui->midiDeviceComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(midiDeviceSet(int)));
    connect(ui->powerOffButton, &QPushButton::clicked, this, &SettingsWidget::poweroff);
    connect(ui->saveButton, &QPushButton::clicked, this, &SettingsWidget::save);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}


