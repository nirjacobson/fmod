#include "envelopedisplaywidget.h"
#include "ui_envelopedisplaywidget.h"

QPointF EnvelopeDisplayWidget::NULL_POINTF = QPointF(-1, -1);

EnvelopeDisplayWidget::EnvelopeDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnvelopeDisplayWidget)
{
    ui->setupUi(this);
}

EnvelopeDisplayWidget::~EnvelopeDisplayWidget()
{
    delete ui;
}

void EnvelopeDisplayWidget::setEnvelope(const Envelope& e)
{
    _envelope = e;
    update();
}

void EnvelopeDisplayWidget::paintEvent(QPaintEvent* event)
{
    const QList<QPointF> points = getPoints();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.fillRect(event->rect(), QBrush(Qt::white, Qt::SolidPattern));


    painter.setPen(Qt::blue);

    if (points[0] == NULL_POINTF) {
        painter.drawLine(0, rect().height(), rect().width(), rect().height());
    } else {
        QPoint p1(points[0].x() * rect().height(), points[0].y() * rect().height());
        painter.drawLine(QPoint(0, rect().height()), p1);

        painter.setPen(Qt::gray);
        painter.drawLine(p1, QPoint(p1.x(), rect().height()));
        painter.setPen(Qt::blue);

        if (points[1] == NULL_POINTF) {
            painter.drawLine(p1, QPoint(rect().width(), p1.y()));
        } else {
            QPoint p2(points[1].x() * rect().height(), points[1].y() * rect().height());
            painter.drawLine(p1, p2);

            painter.setPen(Qt::gray);
            painter.drawLine(p2, QPoint(p2.x(), rect().height()));
            painter.setPen(Qt::blue);

            if (points[2] == NULL_POINTF) {
                painter.drawLine(p2, QPoint(rect().width(), p2.y()));
            } else {
                QPoint p3(points[2].x() * rect().height(), points[2].y() * rect().height());
                painter.drawLine(p2, p3);
            }

            painter.setPen(Qt::cyan);

            if (points[3] == NULL_POINTF) {
                painter.drawLine(p2, QPoint(rect().width(), p2.y()));
            } else {
                QPoint p4(points[3].x() * rect().height(), points[3].y() * rect().height());
                painter.drawLine(p2, p4);
            }
        }
    }

    painter.setPen(Qt::gray);
    painter.drawRect(event->rect());
}

QList<QPointF> EnvelopeDisplayWidget::getPoints() const
{
    QPointF p1(NULL_POINTF);
    QPointF p2(NULL_POINTF);
    QPointF p3(NULL_POINTF);
    QPointF p4(NULL_POINTF);


    if (_envelope.ar() > 0) {
        p1.setY(_envelope.t1l());
        if (_envelope.ar() == 1) {
            p1.setX(0);
        } else {
            const qreal theta = M_PI_2 * _envelope.ar();
            p1.setX((1 - p1.y()) / qTan(theta));
        }

        if (_envelope.d1r() > 0) {
            p2.setY(p1.y() + _envelope.t2l() * (1 - p1.y()));
            if (_envelope.d1r() == 1) {
                p2.setX(p1.x());
            } else {
                const qreal theta = M_PI_2 * _envelope.d1r();
                p2.setX(p1.x() + (p2.y() - p1.y()) / qTan(theta));
            }

            if (_envelope.d2r() > 0) {
                p3.setY(1);
                if (_envelope.d2r() == 1) {
                    p3.setX(p2.x());
                } else {
                    const qreal theta = M_PI_2 * _envelope.d2r();
                    p3.setX(p2.x() + (1 - p2.y()) / qTan(theta));
                }
            }

            if (_envelope.rr() > 0) {
                p4.setY(1);
                if (_envelope.rr() == 1) {
                    p4.setX(p2.x());
                } else {
                    const qreal theta = M_PI_2 * _envelope.rr();
                    p4.setX(p2.x() + (1 - p2.y()) / qTan(theta));
                }

            }
        }
    }

    return QList<QPointF>({p1, p2, p3, p4});
}
