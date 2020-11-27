#ifndef ALGORITHMWIDGET_H
#define ALGORITHMWIDGET_H

#include <QWidget>
#include <QCommonStyle>

namespace Ui {
class AlgorithmWidget;
}

class AlgorithmWidget : public QWidget
{
    Q_OBJECT
signals:
    void feedbackChanged();
    void algorithmChanged();

public:
    explicit AlgorithmWidget(QWidget *parent = nullptr);
    ~AlgorithmWidget();

    char algorithm() const;
    char feedback() const;

    void setAlgorithm(char alg);
    void setFeedback(char fb);

public slots:
    void prevAlgorithm();
    void nextAlgorithm();
    void setDisplayFeedback(const int feedback);

private:
    Ui::AlgorithmWidget *ui;

    char _algorithm;
};

#endif // ALGORITHMWIDGET_H
