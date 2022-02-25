#ifndef BAIDUFANYI_H
#define BAIDUFANYI_H
#include <QApplication>
#include <QtCore>
#include <QCryptographicHash>//md5加密的库
#include <QDebug>
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDesktopServices>
#include <QString>
#define BaiduFanyiPtr BaiduFanyi::instance()
class QMutex;
class BaiduFanyi : public QObject
{
    Q_OBJECT
public:
    ~BaiduFanyi();
    static BaiduFanyi *instance();
    QPair<bool,QString> trans(const QString &text,const QString &from,const QString &to);

    const QString &appId() const;
    void setAppId(const QString &newAppId);

    void save();
    void load();
    const QString &keyText() const;
    void setKeyText(const QString &newKeyText);

    bool isSetting();
    const QString &fromLangage() const;
    void setFromLangage(const QString &newFromLangage);

    const QString &toLangage() const;
    void setToLangage(const QString &newToLangage);

    bool isUsedTsLangage() const;
    void setIsUsedTsLangage(bool newIsUsedTsLangage);

private:
    BaiduFanyi();
    BaiduFanyi(const BaiduFanyi &p) = delete;
private slots:
    void replyFinishedSlot(QNetworkReply *reply);
private:
    static BaiduFanyi *mPtr;
    static QMutex *mMutex;
    QNetworkAccessManager *mManager;
    QPair<bool, QString> mTranResult;

    QString mAppId;
    QString mKeyText;
    QString mFromLangage;
    QString mToLangage;
    bool mIsUsedTsLangage;
};

#endif // BAIDUFANYI_H
