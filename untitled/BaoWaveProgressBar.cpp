#include "BaoWaveProgressBar.h"

#include <QtCore>
#include <QtGui>
#pragma execution_character_set("utf-8")

BaoWaveProgressBar::BaoWaveProgressBar(QWidget *parent)
    :QWidget(parent),
    mWaveData(new BaoWaveProgressBar::WaveData),
    mStyleData(new BaoWaveProgressBar::StyleData)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    mMaxRange = 100;
    mMinRange = 0;
    mValue = 0;

    mText = "";
    mTimerID = -1;
    this->setUpdateTime(mUpdateTime);

}
BaoWaveProgressBar::~BaoWaveProgressBar()
{
    delete mWaveData;
    mWaveData = nullptr;

    delete mStyleData;
    mStyleData = nullptr;

    if(mTimerID != -1)
    {
        this->killTimer(mTimerID);
    }
}

void BaoWaveProgressBar::paintEvent(QPaintEvent *event)
{
    if(mWaveData == nullptr || mStyleData == nullptr)
        return;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform |
                           QPainter::Qt4CompatiblePainting);

    painter.setPen(Qt::SolidLine);

    auto rect = this->rect();
    auto center = rect.center();

    int height = this->height();
    int width = this->width();
    int side = qMin(width, height);

    //计算当前值所占百分比
    double percent = 1 - (double)(mValue - mMinRange) / (mMaxRange - mMinRange);

    //正弦曲线公式 y = A * sin(ωx + φ) + k
    double w = mWaveData->waterDensity * M_PI / width;   //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    double A = height * mWaveData->waterHeight;  //A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比
    double k = height * percent;    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比

    QPainterPath waterPath1;    //第一条波浪路径集合
    QPainterPath waterPath2;    //第二条波浪路径集合

    //移动到左上角起始点
    waterPath1.moveTo(0, height);
    waterPath2.moveTo(0, height);

    mWaveData->waterOffset += mWaveData->waterSpeed;
    if (mWaveData->waterOffset > (width / 2))
        mWaveData->waterOffset = 0;

    //计算路劲
    for(int x = 0; x <= width; x++)
    {
        double waterY1 = (double)(A * sin(w * x + mWaveData->waterOffset)) + k; //第一条波浪Y轴
        double waterY2 = (double)(A * sin(w * x + mWaveData->waterOffset + (width / 2 * w))) + k; //第二条波浪Y轴
        if (mValue == mMinRange)   //如果当前值为最小值则Y轴为高度
        {
            waterY1 = height;
            waterY2 = height;
        }
        if (mValue == mMaxRange)  //如果当前值为最大值则Y轴为0
        {
            waterY1 = 0;
            waterY2 = 0;
        }
        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }
    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(width, height);
    waterPath2.lineTo(width, height);

    //大路径
    QPainterPath bigPath;
    painter.setPen(Qt::NoPen);
    painter.setBrush(mStyleData->bgColor);

    {
        painter.drawEllipse((width - side) / 2, 0, side, side);
        bigPath.addEllipse((width - side) / 2, 0, side, side);
    }

    //新路径,用大路径减去波浪区域的路径,形成遮罩效果
    QPainterPath path;

    //第一条波浪挖去后的路径
    mStyleData->waterColor.setAlpha(100);
    path = bigPath.intersected(waterPath1);
    painter.setPen(Qt::NoPen);
    painter.setBrush(mStyleData->waterColor);
    painter.drawPath(path);

    //第二条波浪挖去后的路径
    mStyleData->waterColor.setAlpha(180);
    path = bigPath.intersected(waterPath2);
    painter.setBrush(mStyleData->waterColor);
    painter.drawPath(path);

    //绘制文字
    mStyleData->font.setPixelSize(side/6);
    painter.setPen(mStyleData->textColor);
    painter.setFont(mStyleData->font);
    auto tempRect = rect;
    auto fm = painter.fontMetrics();
    tempRect.setHeight(tempRect.height() - fm.height()/2);
    painter.drawText(tempRect, Qt::AlignCenter, tr("%1%2%").arg(mText).arg(mValue));

}

void BaoWaveProgressBar::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if(mTimerID == event->timerId())
        this->update();
}

const QString &BaoWaveProgressBar::text() const
{
    return mText;
}

void BaoWaveProgressBar::setText(const QString &newText)
{
    mText = newText;
}

int BaoWaveProgressBar::updateTime() const
{
    return mUpdateTime;
}

void BaoWaveProgressBar::setUpdateTime(int updateTime)
{
    if(mTimerID != -1)
    {
        this->killTimer(mTimerID);
    }
    mUpdateTime = updateTime;
    mTimerID = this->startTimer(updateTime);
}

int BaoWaveProgressBar::value() const
{
    return mValue;
}

void BaoWaveProgressBar::setValue(int value)
{
    if (mValue == value)
        return;
    mValue = value;
    this->update();
    emit valueChanged(value);
}

int BaoWaveProgressBar::minRange() const
{
    return mMinRange;
}

void BaoWaveProgressBar::setMinRange(int minRange)
{
    if (mMinRange == minRange)
        return;
    mMinRange = minRange;
}

int BaoWaveProgressBar::maxRange() const
{
    return mMaxRange;
}

void BaoWaveProgressBar::setMaxRange(int maxRange)
{
    if (mMaxRange == maxRange)
        return;
    mMaxRange = maxRange;
}
