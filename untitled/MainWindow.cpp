#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <QtCore>
#include "LanguageManager.h"
#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_2->setText(tr("升级中"));

    auto curLanguage = LanguageManagerPtr->getCurLanguage();
    auto dataList = LanguageManagerPtr->getDataList();
    for(int i = 0;i < dataList.size();i++)
    {
       auto data = dataList[i];
       ui->comboBox->addItem(data.name,data.language);
       if(curLanguage == data.language)
       {
           ui->comboBox->setCurrentIndex(i);
       }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->widget_2->setValue(value);
}


void MainWindow::on_pushButton_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,
            this,[this]{

                auto value = ui->horizontalSlider->value();
                if(value == 100)
                    value = 0;
                ui->horizontalSlider->setValue(value + 1);
            });
    timer->start(500);


}


void MainWindow::on_comboBox_activated(int index)
{
    auto language = ui->comboBox->itemData(index).value<LanguageManager::Language>();
    LanguageManagerPtr->changLanguage(language);
}

