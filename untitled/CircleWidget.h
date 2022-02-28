#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
class FramelessHelper;

namespace Ui {
class CircleWidget;
}

class CircleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CircleWidget(QWidget *parent = nullptr);
    ~CircleWidget();

    void setIcon(const QString &path);
    void setIcon(const QPixmap &pixmap);
    void setTitle(const QString &text);
    void setWidget(QWidget *widget);

    void setFramelessHelper(QWidget *parent);

    void setNoMinButton();
    void setNoMaxButton();
    void setOnlyCloseButton();
    void setNoCloseButton();
    void setNoBottomFrame();
protected:
    void changeEvent(QEvent *e);
private:
    Ui::CircleWidget *ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CIRCLEWIDGET_H
