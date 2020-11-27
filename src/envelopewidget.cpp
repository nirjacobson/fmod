#include "envelopewidget.h"
#include "ui_envelopewidget.h"

EnvelopeWidget::EnvelopeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnvelopeWidget),
    _envelope(0, 0, 0, 0, 0, 1)
{
    ui->setupUi(this);

    connect(ui->arDial, &QDial::valueChanged, this, &EnvelopeWidget::arDialChanged);
    connect(ui->t1lDial, &QDial::valueChanged, this, &EnvelopeWidget::t1lDialChanged);
    connect(ui->d1rDial, &QDial::valueChanged, this, &EnvelopeWidget::d1rDialChanged);
    connect(ui->t2lDial, &QDial::valueChanged, this, &EnvelopeWidget::t2lDialChanged);
    connect(ui->d2rDial, &QDial::valueChanged, this, &EnvelopeWidget::d2rDialChanged);
    connect(ui->rrDial, &QDial::valueChanged, this, &EnvelopeWidget::rrDialChanged);
    connect(ui->resetButton, &QPushButton::clicked, this, &EnvelopeWidget::reset);
}

EnvelopeWidget::~EnvelopeWidget()
{
    delete ui;
}

const Envelope& EnvelopeWidget::envelope() const
{
    return _envelope;
}

void EnvelopeWidget::setEnvelope(const Envelope& e)
{
    _envelope = e;

    ui->arDial->setValue(_envelope.ar() * ui->arDial->maximum());
    ui->t1lDial->setValue(_envelope.t1l() * ui->t1lDial->maximum());
    ui->d1rDial->setValue(_envelope.d1r() * ui->d1rDial->maximum());
    ui->t2lDial->setValue(_envelope.t2l() * ui->t2lDial->maximum());
    ui->d2rDial->setValue(_envelope.d2r() * ui->d2rDial->maximum());
    ui->rrDial->setValue(_envelope.rr() * ui->rrDial->maximum());
}

void EnvelopeWidget::arDialChanged(const int value)
{
    _envelope.setAr((float)value / ui->arDial->maximum());
    ui->envelopeDisplayWidget->setEnvelope(_envelope);
    emit envelopeChanged();
}

void EnvelopeWidget::t1lDialChanged(const int value)
{
    _envelope.setT1l((float)value / ui->t1lDial->maximum());
    ui->envelopeDisplayWidget->setEnvelope(_envelope);
    emit envelopeChanged();
}

void EnvelopeWidget::d1rDialChanged(const int value)
{
    _envelope.setD1r((float)value / ui->d1rDial->maximum());
    ui->envelopeDisplayWidget->setEnvelope(_envelope);
    emit envelopeChanged();
}

void EnvelopeWidget::t2lDialChanged(const int value)
{
    _envelope.setT2l((float)value / ui->t2lDial->maximum());
    ui->envelopeDisplayWidget->setEnvelope(_envelope);
    emit envelopeChanged();
}

void EnvelopeWidget::d2rDialChanged(const int value)
{
    _envelope.setD2r((float)value / ui->d2rDial->maximum());
    ui->envelopeDisplayWidget->setEnvelope(_envelope);
    emit envelopeChanged();
}

void EnvelopeWidget::rrDialChanged(const int value)
{
    _envelope.setRr((float)value / ui->rrDial->maximum());
    ui->envelopeDisplayWidget->setEnvelope(_envelope);
    emit envelopeChanged();
}

void EnvelopeWidget::reset()
{
    Envelope e(0, 0, 0, 0, 0, 1);

    ui->arDial->setValue(e.ar() * ui->arDial->maximum());
    ui->t1lDial->setValue(e.t1l() * ui->t1lDial->maximum());
    ui->d1rDial->setValue(e.d1r() * ui->d1rDial->maximum());
    ui->t2lDial->setValue(e.t2l() * ui->t2lDial->maximum());
    ui->d2rDial->setValue(e.d2r() * ui->d2rDial->maximum());
    ui->rrDial->setValue(e.rr() * ui->rrDial->maximum());
}
