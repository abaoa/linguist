#include "MainWindow.h"
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <LanguageManager.h>
#include "CircleWidget.h"
#include "CenterForm.h"
#include <iostream>
#include <ctype.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/close.png"));

    QFile file("://qss.txt");
    file.open(QFile::ReadOnly);
    auto data = file.readAll();
    a.setStyleSheet(data);

    LanguageManagerPtr->setDefaultList();
    LanguageManagerPtr->changeCurLanguage();

    CircleWidget/*MainWindow*/ w;
//    w.setIcon(":/close.png");
    w.setTitle("main.cpp");
    w.setWidget(new CenterForm());
//    w.setOnlyCloseButton();
    w.setNoBottomFrame();
    w.show();

    return a.exec();
}
