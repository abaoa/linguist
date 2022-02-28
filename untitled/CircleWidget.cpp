#include "CircleWidget.h"
#include "ui_CircleWidget.h"
#include <QStyleOption>
#include <QApplication>
#include <QPainter>
#include <QPainterPath>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizeGrip>
#include "framelesshelper.h"

CircleWidget::CircleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CircleWidget)
{
    ui->setupUi(this);
    auto windowFlags = this->windowFlags();
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(windowFlags | Qt::FramelessWindowHint);
    this->setFramelessHelper(this);

    auto layout = new QHBoxLayout(ui->frame_titleBar);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(0);
    layout->setContentsMargins(10,0,0,0);
    layout->addWidget(ui->label_icon,1);
    layout->addWidget(ui->label_title,7);
    layout->addWidget(ui->pushButton_min,1);
    layout->addWidget(ui->pushButton_max,1);
    layout->addWidget(ui->pushButton_close,1,Qt::AlignTop);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(ui->frame_titleBar,1,Qt::AlignTop);
    mainLayout->addWidget(ui->frame_center,8);
    mainLayout->addWidget(ui->frame_bottom,1,Qt::AlignBottom);

    auto icon = qApp->windowIcon();
    this->setIcon(icon.pixmap(ui->label_icon->size()));
}

CircleWidget::~CircleWidget()
{
    delete ui;
}

void CircleWidget::setIcon(const QString &path)
{
    QPixmap pixmap(path);
    setIcon(pixmap);
}

void CircleWidget::setIcon(const QPixmap &pixmap)
{
    if(pixmap.isNull()) return;

    auto temp = pixmap.scaled(ui->label_icon->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label_icon->setPixmap(temp);
}

void CircleWidget::setTitle(const QString &text)
{
    ui->label_title->setText(text);
    this->setWindowTitle(text);
}

void CircleWidget::setWidget(QWidget *widget)
{
    if(widget)
    {
        auto layout = new QHBoxLayout(ui->frame_center);
        layout->setAlignment(Qt::AlignTop);
        layout->setSpacing(0);
        layout->setMargin(0);
        layout->addWidget(widget);
    }
}

void CircleWidget::setFramelessHelper(QWidget *parent)
{
    auto p = new FramelessHelper(parent);
    p->activateOn(parent);  //激活当前窗体
    p->setTitleHeight(32);  //设置窗体的标题栏高度
    p->setBorderWidth(6);
    p->setWidgetMovable(true);  //设置窗体可移动
    p->setWidgetResizable(true);  //设置窗体可缩放
    p->setRubberBandOnMove(false);  //设置橡皮筋效果-可移动
    p->setRubberBandOnResize(false);  //设置橡皮筋效果-可缩放
}

void CircleWidget::setNoMinButton()
{
    ui->pushButton_min->setHidden(true);
}

void CircleWidget::setNoMaxButton()
{
    ui->pushButton_max->setHidden(true);
}

void CircleWidget::setOnlyCloseButton()
{
    setNoMinButton();
    setNoMaxButton();
}

void CircleWidget::setNoCloseButton()
{
    ui->pushButton_close->setHidden(true);
}

void CircleWidget::setNoBottomFrame()
{
    ui->frame_bottom->setHidden(true);
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
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::gray);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);

    QPainterPath path;
    path.addRoundedRect(rect, 15, 15);
    painter.drawPath(path);

    QWidget::paintEvent(event);
}
