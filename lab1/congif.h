#ifndef CONGIF_H
#define CONGIF_H

#include "math.h"

#define kBtnTextQuit "Выйти"
#define kBtnTextClean "Очистить"
#define kBtnTextCalc "Вычислить"
#define kBtnTextGenerate "Сгенерировать решение"
#define kBtnTextAddPoint "Добавить точку"
#define kBtnTextDelPoint "Удалить точку"
#define kBtnTextEditPoint "Редактировать точку"
#define kBtnTextAddCircle "Добавить окружность"
#define kBtnTextDelCircle "Удалить окружность"
#define kBtnTextEditCircle "Редактировать окружность"

#define kTextTitle "Аминоточки"

#define kDialogLabelTextX "Координата-X"
#define kDialogLabelTextY "Координата-Y"
#define kDialogLabelTextR "Радиус"
#define kDialogBtnTextOK "ОК"
#define kDialogBtnTextCancel "Отмена"

#define kDrawPointRadius 3
#define kDrawPenWidth 2
#define kPadding 20
#define kAxisStep 100
#define kAXIS_LABEL_WIDTH 50
#define kAXIS_LABEL_HEIGHT 10

#define kmin(a, b) ( ( a < b) ? a : b )
#define kmax(a, b) ( ( a > b) ? a : b )
#define kcalcSide(a, b) sqrt( pow( (a.x()-b.x()), 2) + pow( (a.y() - b.y()), 2) )
#define kRadianToDegree(radian) ( radian*180/M_PI )

class QPointF;


inline bool kIfPointOnLine(QPointF currPoint, QPointF point1, QPointF point2)
{
    return ((currPoint.x() - point1.x())/(point2.x() - point1.x())) == ((currPoint.y() - point1.y())/(point2.y() - point1.y()));

}

inline bool kIfPointOnSide(QPointF currPoint, QPointF point1, QPointF point2)
{
    int dxc = currPoint.x() - point1.x();
    int dyc = currPoint.y() - point1.y();

    int dxl = point2.x() - point1.x();
    int dyl = point2.y() - point1.y();

    if ( (dxc * dyl - dyc * dxl) != 0)
        return false;

    if (abs(dxl) >= abs(dyl))
      return dxl > 0 ?
        point1.x() <= currPoint.x() && currPoint.x() <= point2.x() :
        point2.x() <= currPoint.x() && currPoint.x() <= point1.x();
    else
      return dyl > 0 ?
        point1.y() <= currPoint.y() && currPoint.y() <= point2.y() :
        point2.y() <= currPoint.y() && currPoint.y() <= point1.y();


}
inline double kAngleVector_XAxis(double x1, double y1, double x2, double y2)
{
    return  kRadianToDegree( atan2( fabs(y1 - y2), fabs(x1 - x2) ) );

}

#endif // CONGIF_H
