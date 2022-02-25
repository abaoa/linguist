#ifndef BAOHOOK_H
#define BAOHOOK_H
#include <QApplication>
#include <QObject>
#include <qt_windows.h>

#define BaoHookPtr BaoHook::instance()
class QMutex;
class BaoHook : public QObject
{
    Q_OBJECT

public:
    struct STMouse{
        QPoint point;
        HWND hwnd;
        uint wHitTestCode;
        qulonglong dwExtraInfo;
        STMouse() {}
    };

    ~BaoHook();
    static BaoHook *instance();

    bool switchMouseHook(bool isInstall);
    bool switchKeyBoardHook(bool isInstall);
signals:
    void mouseSig(int code,uint wParam,STMouse lParam);
public slots:

private:
    explicit BaoHook(QObject *parent = nullptr);
    BaoHook(const BaoHook &p) = delete;
public:
    HHOOK mMouseHook,mKeyBoardHook;
private:
    static BaoHook *mPtr;
    static QMutex *mMutex;

};

#endif // BAOHOOK_H
