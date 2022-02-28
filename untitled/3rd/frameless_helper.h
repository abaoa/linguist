#ifndef FRAMELESS_HELPER_H
#define FRAMELESS_HELPER_H

/*****
 * FramelessHelperPrivate
 * 存储界面对应的数据集合，以及是否可移动、可缩放属性
*****/
#include <QWidget>
#include "widgetdata.h"
#include <QHash>
class WidgetData;
class FramelessHelperPrivate
{
public:
    QHash<QWidget*,WidgetData*> m_widgetDataHash;
    bool m_bWidgetMovable        : true;
    bool m_bWidgetResizable      : true;
    bool m_bRubberBandOnResize   : true;
    bool m_bRubberBandOnMove     : true;
};

#endif //FRAMELESS_HELPER_H

