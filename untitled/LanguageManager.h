#ifndef LanguageManager_H
#define LanguageManager_H
#include <QApplication>
#include <QObject>
#include <QTranslator>
#include <QLocale>
#include <QList>
#define LanguageManagerPtr LanguageManager::instance()
class QMutex;
class LanguageManager : public QObject
{
    Q_OBJECT

public:
    enum Language{
        Language_zh, //简体中文
        Language_chf, //繁体中文
        Language_yue, //粤语
        Language_en, //英语
        Language_jp, //日语
        Language_kor, //韩语
        Language_fra, //法语
    };
    Q_ENUM(Language)
    typedef QList<LanguageManager::Language> LanguageList;

    struct STData{
      Language language;
      QString name; //语言名字
      QString qmFilePath; //qm翻译文件
    };
    typedef QList<STData> STDataList;

    ~LanguageManager();
    static LanguageManager *instance();
    void setDefaultList();
    void setLanguageList(LanguageList list);

    void addLangage(Language language, const QString &name,const QString &qmFilePath);
    void addAutoLangage();

    bool changeCurLanguage();
    bool changLanguage(Language language);
    Language getCurLanguage();
    STDataList getDataList();

    void saveConfig();
    void loadConfig();

private:
    explicit LanguageManager(QObject *parent = nullptr);
    LanguageManager(const LanguageManager &p) = delete;
private:
    static LanguageManager *mPtr;
    static QMutex *mMutex;
    STDataList mDataList;
    QTranslator *mCurTranslator;
    Language mCurLanguage;
};

#endif // LanguageManager_H

/*
   调用例子1
   LanguageManagerPtr->setDefaultList();
   LanguageManagerPtr->changeCurLanguage();

   调用例子2
   LanguageManagerPtr->setLanguageList(...);
   LanguageManagerPtr->changeCurLanguage();

   //问题切换后需要重启软件，不然需要重写changeEvent
 */
