#include "CircleWidget.h"
#include "ui_CircleWidget.h"
#include <QStyleOption>
#include <QPainter>
CircleWidget::CircleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CircleWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    auto layout = new QHBoxLayout(ui->frame);
//    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addStretch(8);
    layout->addWidget(ui->pushButton_3);
    layout->addWidget(ui->pushButton,1,Qt::AlignTop);


}

CircleWidget::~CircleWidget()
{
    delete ui;
}

void CircleWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CircleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(Qt::green));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    // rect: 绘制区域  15：圆角弧度
    painter.drawRoundedRect(rect, 15, 15);

    QWidget::paintEvent(event);
}
