#include "baidufanyi.h"
#include <QMutex>
#include <QMutexLocker>
#include <QSettings>
BaiduFanyi* BaiduFanyi::mPtr = nullptr;
QMutex *BaiduFanyi::mMutex = new QMutex();
#pragma execution_character_set("utf-8")

BaiduFanyi::BaiduFanyi()
{
    mAppId = tr("");
    mManager = new QNetworkAccessManager();
}

const QString &BaiduFanyi::appId() const
{
    return mAppId;
}

void BaiduFanyi::setAppId(const QString &newAppId)
{
    mAppId = newAppId;
}

void BaiduFanyi::save()
{
    auto appPath = qApp->applicationDirPath();
    auto filePath = appPath + tr("/config.ini");
    QSettings settings(filePath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup(tr("config"));
    settings.setValue(tr("mAppId"),mAppId);
    settings.setValue(tr("mKeyText"),mKeyText);
    settings.setValue(tr("mFromLangage"),mFromLangage);
    settings.setValue(tr("mToLangage"),mToLangage);
    settings.setValue(tr("mIsUsedTsLangage"),mIsUsedTsLangage);
    settings.endGroup();

}

void BaiduFanyi::load()
{
    auto appPath = qApp->applicationDirPath();
    auto filePath = appPath + tr("/config.ini");
    QSettings settings(filePath,QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    settings.beginGroup(tr("config"));
    mAppId = settings.value(tr("mAppId"),mAppId).value<QString>();
    mKeyText = settings.value(tr("mKeyText"),mKeyText).value<QString>();
    mFromLangage = settings.value(tr("mFromLangage"),mFromLangage).value<QString>();
    mToLangage = settings.value(tr("mToLangage"),mToLangage).value<QString>();
    mIsUsedTsLangage = settings.value(tr("mIsUsedTsLangage"),mIsUsedTsLangage).value<bool>();
    settings.endGroup();

}

BaiduFanyi::~BaiduFanyi()
{
    if(mMutex)
        delete mMutex;
}


BaiduFanyi *BaiduFanyi::instance()
{
    QMutexLocker locker(mMutex);
    if(mPtr == nullptr)
    {
        mPtr = new BaiduFanyi();
        mPtr->load();
    }
    return mPtr;
}

QPair<bool, QString> BaiduFanyi::trans(const QString &text, const QString &from, const QString &to)
{
    mTranResult = qMakePair<bool,QString>(false,tr(""));

    QString salt;
    for (int i = 0; i < 60; i++)
    {
        auto random = QRandomGenerator::system();
        auto number = random->bounded(65,90);
        salt.append(QChar(number));
    }
    QString sign = tr("%1%2%3%4").arg(mAppId).arg(text).arg(salt).arg(mKeyText);
    QByteArray str = QCryptographicHash::hash(sign.toUtf8(),QCryptographicHash::Md5);
    auto md5 = tr(str.toHex());

    QString url = tr("http://api.fanyi.baidu.com/api/trans/vip/translate?"
                   "q=%1&from=%2&to=%3&appid=%4"
                   "&salt=%5&sign=%6").arg(text).arg(from).arg(to).arg(mAppId).arg(salt).arg(md5);

    QEventLoop loop;
    auto reply = mManager->get(QNetworkRequest(QUrl(url)));
    connect(reply,&QNetworkReply::finished,this,[this,reply,&loop]{
        replyFinishedSlot(reply);
        loop.quit();
    });
    loop.exec();

    return mTranResult;
}

void BaiduFanyi::replyFinishedSlot(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QByteArray data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);
    QJsonObject object = json.object();
    QString cResult;
    if(object.contains(QLatin1String("error_code")))
    {
        int nResult = object.value(QLatin1String("error_code")).toInt();
        switch (nResult) {
        case 52001:
            cResult = tr("52001 请求超时 重试");
            break;
        case 52002:
            cResult = tr("52002 系统错误 重试");
            break;
        case 54000:
            cResult = tr("54000 必填参数为空");
            break;
        case 54001:
            cResult = tr("54001 签名错误");
            break;
        case 54003:
            cResult = tr("54003 速度过快访问频率受限");
            break;
        case 54004:
            cResult = tr("54004 账户余额不足");
            break;
        case 54005:
            cResult = tr("54005 请求频繁");
            break;
        case 58002:
            cResult = tr("58002 服务关闭");
            break;
        default:
            cResult = tr("其他错误") + tr(data);
            break;
        }

        mTranResult = qMakePair<bool,QString>(false,cResult);
    }
    else {
        QJsonArray value = object.value(QLatin1String("trans_result")).toArray();
        QJsonObject object1 = value.at(0).toObject();
        cResult = object1.value(QLatin1String("dst")).toString();//得到翻译结果
        mTranResult = qMakePair<bool,QString>(true,cResult);
    }

    reply->deleteLater();
}

bool BaiduFanyi::isUsedTsLangage() const
{
    return mIsUsedTsLangage;
}

void BaiduFanyi::setIsUsedTsLangage(bool newIsUsedTsLangage)
{
    mIsUsedTsLangage = newIsUsedTsLangage;
}

const QString &BaiduFanyi::toLangage() const
{
    return mToLangage;
}

void BaiduFanyi::setToLangage(const QString &newToLangage)
{
    mToLangage = newToLangage;
}

const QString &BaiduFanyi::fromLangage() const
{
    return mFromLangage;
}

void BaiduFanyi::setFromLangage(const QString &newFromLangage)
{
    mFromLangage = newFromLangage;
}

const QString &BaiduFanyi::keyText() const
{
    return mKeyText;
}

void BaiduFanyi::setKeyText(const QString &newKeyText)
{
    mKeyText = newKeyText;
}

bool BaiduFanyi::isSetting()
{
    if(!mAppId.isEmpty() && !mKeyText.isEmpty()) return true;
    return false;
}
