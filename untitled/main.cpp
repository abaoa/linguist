#include "MainWindow.h"
#include <QDebug>
#include <QApplication>
#include <LanguageManager.h>
#include "CircleWidget.h"
#include <iostream>
#include <ctype.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LanguageManagerPtr->setDefaultList();
    LanguageManagerPtr->changeCurLanguage();

    CircleWidget/*MainWindow*/ w;
    w.show();

    return a.exec();
}
