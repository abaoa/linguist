QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaoHook.cpp \
    BaoWaveProgressBar.cpp \
    CircleWidget.cpp \
    LanguageManager.cpp \
    LightDarkSwitch.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    BaoHook.h \
    BaoWaveProgressBar.h \
    CircleWidget.h \
    LanguageManager.h \
    LightDarkSwitch.h \
    MainWindow.h

FORMS += \
    CircleWidget.ui \
    MainWindow.ui

TRANSLATIONS +=  language.zh.ts language.en.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
