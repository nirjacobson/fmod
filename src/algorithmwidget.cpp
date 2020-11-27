#include "algorithmwidget.h"
#include "ui_algorithmwidget.h"

AlgorithmWidget::AlgorithmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgorithmWidget),
    _algorithm(0)
{

    ui->setupUi(this);

    QCommonStyle style;
    ui->prevButton->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
    ui->nextButton->setIcon(style.standardIcon(QStyle::SP_ArrowRight));

    connect(ui->prevButton, &QPushButton::clicked, this, &AlgorithmWidget::prevAlgorithm);
    connect(ui->nextButton, &QPushButton::clicked, this, &AlgorithmWidget::nextAlgorithm);
    connect(ui->feedbackDial, &QDial::valueChanged, this, &AlgorithmWidget::setDisplayFeedback);
    connect(ui->feedbackDial, &QDial::valueChanged, this, &AlgorithmWidget::feedbackChanged);
}

AlgorithmWidget::~AlgorithmWidget()
{
    delete ui;
}

char AlgorithmWidget::algorithm() const
{
    return _algorithm;
}

char AlgorithmWidget::feedback() const
{
    return ui->feedbackDial->value();
}

void AlgorithmWidget::setAlgorithm(char alg)
{
    _algorithm = alg;

    ui->prevButton->setEnabled(_algorithm > 0);
    ui->nextButton->setEnabled(_algorithm < 7);

    ui->algorithmDisplayWidget->setAlgorithm(_algorithm);
    ui->label->setText(QString::number(_algorithm));

    emit algorithmChanged();
}

void AlgorithmWidget::setFeedback(char fb)
{
    ui->feedbackDial->setValue(fb);
}

void AlgorithmWidget::prevAlgorithm()
{
    ui->nextButton->setEnabled(true);
    if (--_algorithm == 0) {
        ui->prevButton->setEnabled(false);
    }

    ui->algorithmDisplayWidget->setAlgorithm(_algorithm);
    ui->label->setText(QString::number(_algorithm));

    emit algorithmChanged();
}

void AlgorithmWidget::nextAlgorithm()
{
    ui->prevButton->setEnabled(true);
    if (++_algorithm == 7) {
        ui->nextButton->setEnabled(false);
    }

    ui->algorithmDisplayWidget->setAlgorithm(_algorithm);
    ui->label->setText(QString::number(_algorithm));

    emit algorithmChanged();
}

void AlgorithmWidget::setDisplayFeedback(const int feedback)
{
    ui->algorithmDisplayWidget->setFeedback(feedback);
}
