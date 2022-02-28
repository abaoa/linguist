#ifndef CENTERFORM_H
#define CENTERFORM_H

#include <QWidget>

namespace Ui {
class CenterForm;
}

class CenterForm : public QWidget
{
    Q_OBJECT

public:
    explicit CenterForm(QWidget *parent = nullptr);
    ~CenterForm();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CenterForm *ui;
};

#endif // CENTERFORM_H
