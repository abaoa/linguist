#include "baidufanyisettingdialog.h"
#include "ui_baidufanyisettingdialog.h"
#include "baidufanyi.h"
#include <QFile>
#pragma execution_character_set("utf-8")
BaiduFanyiSettingDialog::BaiduFanyiSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaiduFanyiSettingDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("设置百度翻译"));
    ui->lineEdit_appid->setText(BaiduFanyiPtr->appId());
    ui->lineEdit_keyText->setText(BaiduFanyiPtr->keyText());
    ui->checkBox_isUseTsLang->setChecked(BaiduFanyiPtr->isUsedTsLangage());

    auto fromLangage = BaiduFanyiPtr->fromLangage();
    auto toLangage = BaiduFanyiPtr->toLangage();
    QFile file(QStringLiteral("://images/baidulange.txt"));
    if(file.open(QFile::ReadOnly))
    {
        while(!file.atEnd())
        {
            auto data = tr(file.readLine());
            data = data.trimmed();
            auto list = data.split(tr(" "));
            if(list.size() == 2)
            {
                ui->comboBox_from->addItem(data,list[1]);
                if(list[1] != tr("auto"))
                    ui->comboBox_to->addItem(data,list[1]);
            }
        }
        file.close();
    }

    for(int i = 0; i < ui->comboBox_from->count();i++)
    {
        auto lang = ui->comboBox_from->itemData(i,Qt::UserRole).toString();
        if(lang == fromLangage) {
            ui->comboBox_from->setCurrentIndex(i);
            break;
        }
    }

    for(int i = 0; i < ui->comboBox_to->count();i++)
    {
        auto lang = ui->comboBox_to->itemData(i,Qt::UserRole).toString();
        if(lang == toLangage) {
            ui->comboBox_to->setCurrentIndex(i);
            break;
        }
    }
}

BaiduFanyiSettingDialog::~BaiduFanyiSettingDialog()
{
    delete ui;
}

void BaiduFanyiSettingDialog::on_buttonBox_accepted()
{
    BaiduFanyiPtr->setAppId(ui->lineEdit_appid->text());
    BaiduFanyiPtr->setKeyText(ui->lineEdit_keyText->text());
    BaiduFanyiPtr->setFromLangage(ui->comboBox_from->currentData().toString());
    BaiduFanyiPtr->setToLangage(ui->comboBox_to->currentData().toString());
    BaiduFanyiPtr->setIsUsedTsLangage(ui->checkBox_isUseTsLang->isChecked());
    BaiduFanyiPtr->save();
}

