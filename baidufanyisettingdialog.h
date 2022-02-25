#ifndef BAIDUFANYISETTINGDIALOG_H
#define BAIDUFANYISETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class BaiduFanyiSettingDialog;
}

class BaiduFanyiSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaiduFanyiSettingDialog(QWidget *parent = nullptr);
    ~BaiduFanyiSettingDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::BaiduFanyiSettingDialog *ui;
};

#endif // BAIDUFANYISETTINGDIALOG_H
