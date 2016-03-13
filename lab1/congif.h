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
#define kDrawPenWidth 1
#define kAxisStep 100

#define kmin(a, b) ( ( a < b) ? a : b )
#define kmax(a, b) ( ( a > b) ? a : b )
#define kcalcSide(a, b) sqrt( pow( (a.x()-b.x()), 2) + pow( (a.y() - b.y()), 2) )
#define kRadianToDegree(radian) ( radian*180/M_PI )

class QPointF;

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
inline double kAngleOfTwoVectors(double x1, double y1, double x2, double y2)
{
//    double dot = x1*x2 + y1*y2;
//    double det = x1*y2 - y1*x2;
//    return fabs(atan2(det, dot));

//    double ab = x1*x2 + y1*y2;
//    double ab_l = sqrt(x1*x1+y1*y1)*sqrt(x2*x2+y2*y2);
//    return fabs(acos(ab/ab_l));

    double angle1 = atan2(y1 - y2, x1 - x2 );
    double angle2 = atan2( 0, 10 );
    double angle = kRadianToDegree(angle1-angle2);
    if (fabs(angle) > 180)
        angle = fabs(angle-180);
    else if (angle < 0)
        angle = fabs(angle+180);



    return angle;

}

#endif // CONGIF_H
