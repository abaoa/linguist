#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>

namespace Ui {
class CircleWidget;
}

class CircleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CircleWidget(QWidget *parent = nullptr);
    ~CircleWidget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CircleWidget *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CIRCLEWIDGET_H
