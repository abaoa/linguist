#include "LanguageManager.h"
#include <QMutex>
#include <QMutexLocker>
#include <QApplication>
#include <QMetaEnum>
#include <QSettings>
#include <QLocale>
#include <QDebug>
LanguageManager* LanguageManager::mPtr = nullptr;
QMutex *LanguageManager::mMutex = new QMutex();
#pragma execution_character_set("utf-8")
LanguageManager::LanguageManager(QObject *parent)
    : QObject(parent)
{
    mCurTranslator = nullptr;
    mCurLanguage = Language_zh;
    loadConfig();
}

LanguageManager::~LanguageManager()
{
    if(mMutex)
        delete mMutex;
}


LanguageManager *LanguageManager::instance()
{
    QMutexLocker locker(mMutex);
    if(mPtr == nullptr)
    {
        mPtr = new LanguageManager();
        connect(qApp,&QApplication::aboutToQuit,
                []{
            delete mPtr;
        });
    }
    return mPtr;
}

void LanguageManager::setDefaultList()
{
    LanguageList list;
    list << Language_zh;
    list << Language_en;

    setLanguageList(list);
}

void LanguageManager::setLanguageList(LanguageList list)
{
    QStringList defines;
    defines.append("TRANSLATIONS += ");

    for(int i = 0; i < list.size();i++)
    {
        LanguageManager::Language language = list[i];
        QMetaEnum emLanguage = QMetaEnum::fromType<LanguageManager::Language>();
        auto text = QString(emLanguage.valueToKey(language));
        auto name = text.section('_',1,1);
        defines.append(QString("language.%1.ts").arg(name));
        QString languageText = "";
        switch (language) {
        case LanguageManager::Language_zh:
            languageText = tr("简体中文");
            break;
        case LanguageManager::Language_chf:
            languageText = tr("繁体中文");
            break;
        case LanguageManager::Language_yue:
            languageText = tr("粤语");
            break;
        case LanguageManager::Language_en:
            languageText = tr("English");
            break;
        case LanguageManager::Language_jp:
            languageText = tr("日语");
            break;
        case LanguageManager::Language_kor:
            languageText = tr("韩语");
            break;
        case LanguageManager::Language_fra:
            languageText = tr("法语");
            break;

        }
        addLangage(language,languageText,QString(":/language/language.%1.qm").arg(name));
    }

    qDebug() << "defines" << defines.join(" ");
}

void LanguageManager::addLangage(Language language, const QString &name, const QString &qmFilePath)
{
    STData data;
    data.language = language;
    data.name = name;
    data.qmFilePath = qmFilePath;
    mDataList.append(data);
}

void LanguageManager::addAutoLangage()
{
    QLocale locale = QLocale::system();
    auto lang = locale.language();
    auto text = QLocale::languageToString(lang);
    qDebug() << "text" << text << locale.nativeLanguageName();
}

bool LanguageManager::changeCurLanguage()
{
    return changLanguage(mCurLanguage);
}

bool LanguageManager::changLanguage(Language language)
{
    if(mCurTranslator != nullptr)
    {
        qApp->removeTranslator(mCurTranslator);
    }else{
        mCurTranslator = new QTranslator(this);
    }

    for(int i = 0;i < mDataList.size();i++)
    {
       auto data = mDataList[i];
       if(language == data.language)
       {
           auto isok = mCurTranslator->load(data.qmFilePath);
           if(isok)
           {
               isok = qApp->installTranslator(mCurTranslator);
               if(isok)
               {
                   mCurLanguage = language;
                   saveConfig();
               }
               return isok;
           }else
           {
               mCurLanguage = language;
               saveConfig();
               return true;
           }
       }
    }

    return false;
}

LanguageManager::Language LanguageManager::getCurLanguage()
{
    return mCurLanguage;
}

LanguageManager::STDataList LanguageManager::getDataList()
{
    return mDataList;
}

void LanguageManager::saveConfig()
{
    auto appPath = qApp->applicationDirPath();
    auto filePath = appPath + QString("/LanguageConfig.ini");
    QSettings settings(filePath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("config");
    settings.setValue("mCurLanguage",mCurLanguage);
    settings.endGroup();
}

void LanguageManager::loadConfig()
{
    auto appPath = qApp->applicationDirPath();
    auto filePath = appPath + QString("/LanguageConfig.ini");
    QSettings settings(filePath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup("config");
    mCurLanguage = settings.value("mCurLanguage",mCurLanguage).value<Language>();
    settings.endGroup();
}
