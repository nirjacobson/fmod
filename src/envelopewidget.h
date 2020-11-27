#ifndef ENVELOPEWIDGET_H
#define ENVELOPEWIDGET_H

#include <QWidget>

#include "envelope.h"

namespace Ui {
class EnvelopeWidget;
}

class EnvelopeWidget : public QWidget
{
    Q_OBJECT
signals:
    void envelopeChanged();

public:
    explicit EnvelopeWidget(QWidget *parent = nullptr);
    ~EnvelopeWidget();

    const Envelope& envelope() const;

    void setEnvelope(const Envelope& e);

public slots:
    void arDialChanged(const int value);
    void t1lDialChanged(const int value);
    void d1rDialChanged(const int value);
    void t2lDialChanged(const int value);
    void d2rDialChanged(const int value);
    void rrDialChanged(const int value);
    void reset();

private:
    Ui::EnvelopeWidget *ui;
    Envelope _envelope;
};

#endif // ENVELOPEWIDGET_H
