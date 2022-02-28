QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    3rd/cursorposcalculator.cpp \
    3rd/widgetdata.cpp \
    BaoHook.cpp \
    BaoWaveProgressBar.cpp \
    CenterForm.cpp \
    CircleWidget.cpp \
    LanguageManager.cpp \
    LightDarkSwitch.cpp \
    framelesshelper.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    3rd/cursorposcalculator.h \
    3rd/frameless_helper.h \
    3rd/widgetdata.h \
    BaoHook.h \
    BaoWaveProgressBar.h \
    CenterForm.h \
    CircleWidget.h \
    LanguageManager.h \
    LightDarkSwitch.h \
    MainWindow.h \
    framelesshelper.h

FORMS += \
    CenterForm.ui \
    CircleWidget.ui \
    MainWindow.ui

TRANSLATIONS +=  language.zh.ts language.en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
