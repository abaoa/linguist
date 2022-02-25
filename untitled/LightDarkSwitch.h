#ifndef LIGHTDARKSWITCH_H
#define LIGHTDARKSWITCH_H

#include <QWidget>

class LightDarkSwitch : public QWidget
{
    Q_OBJECT

public:
    explicit LightDarkSwitch(QWidget *parent = 0);
    ~LightDarkSwitch();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:

};

#endif // LIGHTDARKSWITCH_H
