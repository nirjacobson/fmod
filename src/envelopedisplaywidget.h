#ifndef ENVELOPEDISPLAYWIDGET_H
#define ENVELOPEDISPLAYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QPointF>
#include <QList>
#include <QtMath>

#include "envelope.h"

namespace Ui {
class EnvelopeDisplayWidget;
}

class EnvelopeDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnvelopeDisplayWidget(QWidget *parent = nullptr);
    ~EnvelopeDisplayWidget();

    void setEnvelope(const Envelope& e);

protected:
    virtual void paintEvent(QPaintEvent* event);

private:
    static QPointF NULL_POINTF;

    Ui::EnvelopeDisplayWidget *ui;
    Envelope _envelope;

    QList<QPointF> getPoints() const;
};

#endif // ENVELOPEDISPLAYWIDGET_H
