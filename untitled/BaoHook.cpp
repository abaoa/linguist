#include "BaoHook.h"
#include <QMutex>
#include <QMutexLocker>
#pragma comment ( lib,"user32.lib" )
BaoHook* BaoHook::mPtr = nullptr;
QMutex *BaoHook::mMutex = new QMutex();

BaoHook::BaoHook(QObject *parent)
    : QObject(parent)
{
    mMouseHook = NULL;
    mKeyBoardHook = NULL;
}

BaoHook::~BaoHook()
{
    if(mMutex)
        delete mMutex;
}


BaoHook *BaoHook::instance()
{
    QMutexLocker locker(mMutex);
    if(mPtr == nullptr)
    {
        mPtr = new BaoHook();
        connect(qApp,&QApplication::aboutToQuit,
                []{
                    delete mPtr;
                });
    }
    return mPtr;
}

//键盘钩子处理函数
LRESULT CALLBACK BaoHookKeyBoardProc(int nCode,WPARAM wParam,LPARAM lParam) //钩子消息函数，系统消息队列信息会返回到该函数中
{
    if(WM_KEYDOWN == wParam)    //wParam用于判断事件类型，当前为按键按下事件
    {
        KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;  //lParam用于判断按键类型
        if(pkbhs->vkCode == 0x31)   //检测按键1按下
        {
            //处理程序
        }
        if(pkbhs->vkCode == 0x31 && GetAsyncKeyState(VK_CONTROL))   //组合按键检测 按下Ctrl+1，哪个后按下的，使用GetAsyncKeyState函数判断
        {
            //处理程序
        }
    }

    KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;  //lParam用于判断按键类型
    //emit BaoHook::instance()->keyBoardSig(wParam,pkbhs->vkCode);
    return CallNextHookEx(BaoHook::instance()->mKeyBoardHook,nCode,wParam,lParam);     //继续原有的事件队列
}

//鼠标钩子处理函数
LRESULT CALLBACK BaoHookMouseProc(int nCode,WPARAM wParam,LPARAM lParam) //钩子消息函数，系统消息队列信息会返回到该函数中
{
    //鼠标点击右键WM_RBUTTONDOWN
    MOUSEHOOKSTRUCT *st = (MOUSEHOOKSTRUCT*)lParam; //鼠标HOOK结构体
    BaoHook::STMouse mouse;
    mouse.point = QPoint(st->pt.x,st->pt.y);
    mouse.hwnd = st->hwnd;
    mouse.wHitTestCode = st->wHitTestCode;
    mouse.dwExtraInfo = st->dwExtraInfo;
    emit BaoHook::instance()->mouseSig(nCode,wParam,mouse);
    return CallNextHookEx(BaoHook::instance()->mMouseHook,nCode,wParam,lParam); //继续原有的事件队列
}

bool BaoHook::switchMouseHook(bool isInstall)
{
    if(isInstall && (mMouseHook == NULL))
    {
        mMouseHook = SetWindowsHookEx(WH_MOUSE_LL,BaoHookMouseProc,nullptr,0);
        if(mMouseHook)
            return true;
    }else if(!isInstall && (mMouseHook != NULL))
    {
        return UnhookWindowsHookEx(mMouseHook);
    }

    return false;
}

bool BaoHook::switchKeyBoardHook(bool isInstall)
{
    if(isInstall && (mKeyBoardHook == NULL))
    {
        mKeyBoardHook = SetWindowsHookEx(WH_KEYBOARD_LL,BaoHookKeyBoardProc,nullptr,0);
        if(mKeyBoardHook)
            return true;
    }else if(!isInstall && (mKeyBoardHook != NULL))
    {
        return UnhookWindowsHookEx(mKeyBoardHook);
    }

    return false;
}

