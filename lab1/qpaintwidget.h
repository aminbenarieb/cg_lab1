#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QVarLengthArray>

class QPaintEvent;
class QpointF;
struct QCircle
{
    QPointF pos;
    qreal radius;
};
struct QTriangle
{
    QPointF points[3];
    double angle;
    bool min;
};

struct QGVector
{

    QPointF point1;
    QPointF point2;
};


class QPaintWidget : public QWidget
{
    Q_OBJECT
public:
    QPaintWidget(QWidget * parent = 0);
    QVector <QPointF> points;
    QVector <QTriangle> triangles;
    QCircle circle;
    QTriangle triangle;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPAINTWIDGET_H
