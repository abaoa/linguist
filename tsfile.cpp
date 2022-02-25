#include "tsfile.h"
#include <QtCore>
#include <QtXml>

TsFile::TsFile()
{

}

bool TsFile::readTsFile(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly))
    {
        file.close();
        return false;
    }

    QDomDocument doc;
    if(!doc.setContent(file.readAll()))
    {
        file.close();
        return false;
    }

    mTsFileData.clear();

    QDomElement rootEle = doc.firstChildElement();

    auto name = rootEle.nodeName();
    mTsFileData.version = rootEle.attribute(QStringLiteral("version"));
    mTsFileData.language = rootEle.attribute(QStringLiteral("language"));
    mTsFileData.sourcelanguage = rootEle.attribute(QStringLiteral("sourcelanguage"));

    return true;
}
