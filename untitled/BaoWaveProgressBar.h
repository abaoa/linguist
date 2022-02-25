#ifndef BAOWAVEPROGRESSBAR_H
#define BAOWAVEPROGRESSBAR_H

#include <QWidget>

class BaoWaveProgressBar : public QWidget
{
    Q_OBJECT

public:
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    struct WaveData{
        int waterDensity = 5;         // 水波的密度
        double waterHeight = 0.03;    //水波高度
        double waterOffset = 80;           //水波相位差
        double waterSpeed = 0.4;           //一次刷新的位移，可代表波浪移动速度
        WaveData() {}
    };
    struct StyleData{
        QColor bgColor = QColor("#C7D7F4");                            //背景颜色
        QColor waterColor = Qt::white;              //水体颜色
        QColor textColor = QColor("#07CD31");                         //字体颜色
        QFont font;       //字体，默认大小为控件大小的1/4
        StyleData() {}
    };

    explicit BaoWaveProgressBar(QWidget *parent = 0);
    ~BaoWaveProgressBar();

    int maxRange() const;
    void setMaxRange(int maxRange);

    int minRange() const;
    void setMinRange(int minRange);

    int value() const;
    void setValue(int value);

    int updateTime() const;
    void setUpdateTime(int updateTime);

    const QString &text() const;
    void setText(const QString &newText);

signals:
    void valueChanged(int value);
protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
private:
    int mMaxRange;
    int mMinRange;
    int mValue;

    int mTimerID = -1;
    int mUpdateTime = 100;         //水波波动速度，越大越慢
    QString mText;

    BaoWaveProgressBar::WaveData *mWaveData;
    BaoWaveProgressBar::StyleData *mStyleData;
};

#endif // BAOWAVEPROGRESSBAR_H
