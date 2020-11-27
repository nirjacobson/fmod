#include "pianowidget.h"
#include "ui_pianowidget.h"

int PianoWidget::WHITE_KEY_INTERVALS[] = {
    0, 2, 4, 5, 7, 9, 11
};

int PianoWidget::BLACK_KEY_INTERVALS[] = {
    1, 3, 6, 8, 10
};

PianoWidget::PianoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PianoWidget),
    _baseOctave(DEFAULT_BASE_OCTAVE)
{
    ui->setupUi(this);
}

PianoWidget::~PianoWidget()
{
    delete ui;
}

void PianoWidget::pressKey(const int key)
{
    int octave = key / KEYS_PER_OCTAVE;

    if (!_pressedKeys.contains(key)) {
        _pressedKeys.append(key);

        int firstKey = _baseOctave * KEYS_PER_OCTAVE;
        int lastKey = keyAt(rect().topRight());
        if (key < firstKey || key > lastKey) {
            _baseOctave = octave;
        }
    }
    update();
}

void PianoWidget::releaseKey(const int key)
{
    _pressedKeys.removeAll(key);
    update();
}


void PianoWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    drawOctaves(event, painter);
}

void PianoWidget::drawBlackKey(const int octave, const int key, QPaintEvent* event, QPainter& painter)
{
    int whiteWidth = event->rect().height() * WHITE_WIDTH_RATIO;
    int blackWidth = event->rect().height() * BLACK_WIDTH_RATIO;
    int blackHeight = event->rect().height() * BLACK_HEIGHT_RATIO;

    int startX = (octave - _baseOctave) * (whiteWidth * WHITE_KEYS_PER_OCTAVE);

    QRect keyRect(QPoint(0, 0), QSize(blackWidth, blackHeight));

    int x = 0;
    switch (key) {
    case 0:
        x = whiteWidth * 1 - ((2.0f/3.0f) * blackWidth);
        break;
    case 1:
        x = whiteWidth * 2 - ((1.0f/3.0f) * blackWidth);
        break;
    case 2:
        x = whiteWidth * 4 - ((2.0f/3.0f) * blackWidth);
        break;
    case 3:
        x = whiteWidth * 5 - ((1.0f/2.0f) * blackWidth);
        break;
    case 4:
        x = whiteWidth * 6 - ((1.0f/3.0f) * blackWidth);
    default:
        break;
    }

    QRect keyRectTranslated = keyRect.translated(QPoint(startX + x, 0));
    bool selected = _pressedKeys.contains(octave * 12 + BLACK_KEY_INTERVALS[key]);
    painter.fillRect(keyRectTranslated,
                     QBrush(selected ? Qt::cyan : Qt::black, Qt::SolidPattern));
    painter.setPen(Qt::gray);
    painter.drawRect(keyRectTranslated);
}

void PianoWidget::drawBlackKeys(const int octave, QPaintEvent* event, QPainter& painter)
{
    for (int i = 0; i < BLACK_KEYS_PER_OCTAVE; i++) {
        drawBlackKey(octave, i, event, painter);
    }
}

void PianoWidget::drawWhiteKeys(const int octave, QPaintEvent* event, QPainter& painter)
{
    int whiteWidth = event->rect().height() * WHITE_WIDTH_RATIO;

    int startX = (octave - _baseOctave) * (whiteWidth * WHITE_KEYS_PER_OCTAVE);

    painter.setPen(Qt::gray);
    for (int i = 0; i < WHITE_KEYS_PER_OCTAVE; i++) {
        bool selected = _pressedKeys.contains(octave * KEYS_PER_OCTAVE + WHITE_KEY_INTERVALS[i]);
        QRect keyRect(QPoint(startX + i * whiteWidth, 0), QSize(whiteWidth, event->rect().height()));
        painter.fillRect(keyRect, QBrush(selected ? Qt::cyan : Qt::white, Qt::SolidPattern));
        painter.drawRect(keyRect);
    }
}

void PianoWidget::drawOctaveHeader(const int octave, QPaintEvent* event, QPainter& painter)
{
    int whiteWidth = event->rect().height() * WHITE_WIDTH_RATIO;
    int octaveWidth = whiteWidth * WHITE_KEYS_PER_OCTAVE;

    QRect rect = QRect(QPoint(), QSize(octaveWidth, HEADER_HEIGHT))
            .translated(QPoint((octave - _baseOctave) * octaveWidth, 0));

    painter.setPen(Qt::darkGray);
    painter.fillRect(rect, QBrush(Qt::gray, Qt::SolidPattern));
    painter.drawRect(rect);
    painter.setPen(Qt::black);
    painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, "C"+QString::number(octave));
}

void PianoWidget::drawOctave(const int octave, QPaintEvent* event, QPainter& painter)
{
    drawWhiteKeys(octave, event, painter);
    drawBlackKeys(octave, event, painter);
    drawOctaveHeader(octave, event, painter);
}

void PianoWidget::drawOctaves(QPaintEvent* event, QPainter& painter)
{
    int whiteWidth = event->rect().height() * WHITE_WIDTH_RATIO;
    int octaveWidth = whiteWidth * WHITE_KEYS_PER_OCTAVE;

    int octaves = qCeil((float)event->rect().width() / octaveWidth);

    for (int i = 0; i < octaves; i++) {
        drawOctave(_baseOctave + i, event, painter);
    }
}

int PianoWidget::keyAt(const QPoint& pos) const
{
    int whiteWidth = height() * WHITE_WIDTH_RATIO;
    int octaveWidth = whiteWidth * WHITE_KEYS_PER_OCTAVE;
    int blackWidth = height() * BLACK_WIDTH_RATIO;
    int blackHeight = height() * BLACK_HEIGHT_RATIO;

    int octaveFromBase = (pos.x() / octaveWidth);
    int relativeX = pos.x() - (octaveFromBase * octaveWidth);
    int octave = _baseOctave + octaveFromBase;
    int interval = 0;

    if (pos.y() < blackHeight) {
        int left[] = {
            0,
            (int)((1 * whiteWidth) - ((2.0f/3.0f) * blackWidth)),
            (int)((1 * whiteWidth) + ((1.0f/3.0f) * blackWidth)),
            (int)((2 * whiteWidth) - ((1.0f/3.0f) * blackWidth)),
            (int)((2 * whiteWidth) + ((2.0f/3.0f) * blackWidth)),
            3 * whiteWidth,
            (int)((4 * whiteWidth) - ((2.0f/3.0f) * blackWidth)),
            (int)((4 * whiteWidth) + ((1.0f/3.0f) * blackWidth)),
            (int)((5 * whiteWidth) - ((1.0f/2.0f) * blackWidth)),
            (int)((5 * whiteWidth) + ((1.0f/2.0f) * blackWidth)),
            (int)((6 * whiteWidth) - ((1.0f/3.0f) * blackWidth)),
            (int)((6 * whiteWidth) + ((2.0f/3.0f) * blackWidth)),
            octaveWidth
        };

        for (int i = 0; i < KEYS_PER_OCTAVE; i++) {
            if (relativeX >= left[i] && relativeX < left[i+1]) {
                interval = i;
                break;
            }
        }
    } else {
        for (int i = 0; i < WHITE_KEYS_PER_OCTAVE; i++) {
            if (relativeX >= (i * whiteWidth) && relativeX < ((i + 1) * whiteWidth)) {
                interval = WHITE_KEY_INTERVALS[i];
                break;
            }
        }
    }

    return octave * KEYS_PER_OCTAVE + interval;
}

void PianoWidget::mousePressEvent(QMouseEvent* event)
{
    int whiteWidth = height() * WHITE_WIDTH_RATIO;
    int octaveWidth = whiteWidth * WHITE_KEYS_PER_OCTAVE;

    if (event->y() < HEADER_HEIGHT) {
        if (event->x() < octaveWidth) {
            _baseOctave--;
        } else {
            int lastOctave = keyAt(rect().topRight()) / KEYS_PER_OCTAVE;
            if (event->x() > (lastOctave - _baseOctave) * octaveWidth) {
                _baseOctave++;
            }
        }
    } else {
        const char key = keyAt(event->pos());
        pressKey(key);
        emit keyPressed(key);
    }
}

void PianoWidget::mouseReleaseEvent(QMouseEvent* event)
{
    const char key = keyAt(event->pos());
    releaseKey(key);
    emit keyReleased(key);

}
