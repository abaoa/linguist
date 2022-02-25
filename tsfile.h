#ifndef TSFILE_H
#define TSFILE_H
#include <QtCore>

class TsFile
{
public:
    struct STLocation
    {
        QString filename;
        QString line;
    };

    struct STSource
    {
        QString text;
    };

    struct STTranslation
    {
        QString type;
        QString text;
        STTranslation(){
            type = QStringLiteral("");
            text = QStringLiteral("");
        }
    };

    struct STMessage
    {
        STLocation location;
        STSource source;
        STTranslation translation;
    };
    typedef QList<STMessage> STMessageList;

    struct STContext
    {
        QString name;
        STMessageList messageList;
        STContext(){
            name = QStringLiteral("");
        }
    };
    typedef QList<STContext> STContextList;

    struct STTsFileData
    {
        QString version;
        QString language;
        QString sourcelanguage;
        STContextList contextList;
        STTsFileData(){
            version = QStringLiteral("");
            language = QStringLiteral("");
            sourcelanguage = QStringLiteral("");
        }
        void clear(){
            version.clear();
            language.clear();
            sourcelanguage.clear();
            contextList.clear();
        }
    };

    TsFile();
    bool readTsFile(const QString &filePath);
    STTsFileData mTsFileData;
};

#endif // TSFILE_H

/*

<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="zh_CN" sourcelanguage="en_SD">
<context>
    <name>LoadingDialog</name>
    <message>
        <location filename="loadingdialog.ui" line="14"/>
        <source>Dialog</source>
        <translation type="unfinished">？</translation>
    </message>
    <message>
        <location filename="loadingdialog.ui" line="235"/>
        <source>TextLabel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="loadingdialog.cpp" line="21"/>
        <source>3D智慧视觉，推动工业更高效</source>
        <translation>3D smart vision to promote more efficient industry</translation>
    </message>
    <message>
        <location filename="loadingdialog.cpp" line="26"/>
        <source>正在加载（%1%）</source>
        <translation>Loading(%1%)</translation>
    </message>
    <message>
        <location filename="loadingdialog.cpp" line="23"/>
        <source>软件版本信息 ：%1</source>
        <translation>Software version information:%1</translation>
    </message>
</context>
<context>
    <name>NoSoftdogDialog</name>
    <message>
        <location filename="nosoftdogdialog.ui" line="14"/>
        <source>Dialog</source>
        <translation>对话</translation>
    </message>
    <message>
        <location filename="nosoftdogdialog.ui" line="73"/>
        <source>关闭</source>
        <translation>close</translation>
    </message>
    <message>
        <location filename="nosoftdogdialog.ui" line="104"/>
        <source>TextLabel</source>
        <translation>文本标签</translation>
    </message>
    <message>
        <location filename="nosoftdogdialog.ui" line="146"/>
        <source>软件未发现加密狗硬件，请检查加密狗是否正确插入。
请联系软件厂商。</source>
        <translation>The software did not find the dongle hardware. Please check whether the dongle is inserted correctly.</translation>
    </message>
    <message>
        <location filename="nosoftdogdialog.ui" line="192"/>
        <source>确定</source>
        <translation>determine</translation>
    </message>
    <message>
        <location filename="nosoftdogdialog.cpp" line="15"/>
        <source>软件启动失败</source>
        <translation>Software startup failed</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="main.cpp" line="115"/>
        <source>插件一览表</source>
        <translation>Plug in list</translation>
    </message>
</context>
<context>
    <name>TestQss</name>
    <message>
        <location filename="testqss/testqss.ui" line="14"/>
        <source>Form</source>
        <translation>类型</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="29"/>
        <source>PushButton</source>
        <translation>按钮</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="42"/>
        <source>...</source>
        <translation>...</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="55"/>
        <source>RadioButton</source>
        <translation>单选按钮</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="68"/>
        <source>CheckBox</source>
        <translation>复选框</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="81"/>
        <source>GroupBox</source>
        <translation>分组框</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="124"/>
        <source>Tab 1</source>
        <translation>表1</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="129"/>
        <source>Tab 2</source>
        <translation type="unfinished">表23</translation>
    </message>
    <message>
        <location filename="testqss/testqss.ui" line="260"/>
        <source>TextLabel</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
*/
