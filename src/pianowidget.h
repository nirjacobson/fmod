#ifndef PIANOWIDGET_H
#define PIANOWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QtMath>
#include <QList>

namespace Ui {
class PianoWidget;
}

class PianoWidget : public QWidget
{
    Q_OBJECT
signals:
    void keyPressed(const char key);
    void keyReleased(const char key);

public:
    explicit PianoWidget(QWidget *parent = nullptr);
    ~PianoWidget();

    static constexpr float WHITE_WIDTH_RATIO = 21.0f / 140.0f;
    static constexpr float BLACK_WIDTH_RATIO = 15.0f / 140.0f;
    static constexpr float BLACK_HEIGHT_RATIO = 90.0f / 140.0f;
    static constexpr int DEFAULT_BASE_OCTAVE = 4;
    static constexpr int KEYS_PER_OCTAVE = 12;
    static constexpr int WHITE_KEYS_PER_OCTAVE = 7;
    static constexpr int BLACK_KEYS_PER_OCTAVE = 5;
    static constexpr int HEADER_HEIGHT = 24;

    static int WHITE_KEY_INTERVALS[7];
    static int BLACK_KEY_INTERVALS[5];

    void pressKey(const int key);
    void releaseKey(const int key);

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::PianoWidget *ui;

    int _baseOctave;
    QList<int> _pressedKeys;

    void drawBlackKey(const int octave, const int key, QPaintEvent* event, QPainter& painter);
    void drawBlackKeys(const int octave, QPaintEvent* event, QPainter& painter);
    void drawWhiteKeys(const int octave, QPaintEvent* event, QPainter& painter);
    void drawOctaveHeader(const int octave, QPaintEvent* event, QPainter& painter);
    void drawOctave(const int octave, QPaintEvent* event, QPainter& painter);
    void drawOctaves(QPaintEvent* event, QPainter& painter);

    int keyAt(const QPoint& pos) const;

    // QWidget interface

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // PIANOWIDGET_H
