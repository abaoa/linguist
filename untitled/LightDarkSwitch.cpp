#include "LightDarkSwitch.h"

#include <QtCore>
#include <QtGui>
#pragma execution_character_set("utf-8")

LightDarkSwitch::LightDarkSwitch(QWidget *parent)
    :QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
}
LightDarkSwitch::~LightDarkSwitch()
{

}

void LightDarkSwitch::mousePressEvent(QMouseEvent *event)
{

    this->update();
}

void LightDarkSwitch::mouseReleaseEvent(QMouseEvent *event)
{
}


void LightDarkSwitch::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform |
                           QPainter::Qt4CompatiblePainting);

    painter.setPen(Qt::SolidLine);

    auto rect = this->rect();
    auto center = rect.center();
    
}
