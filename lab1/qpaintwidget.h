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
    int i;  // Индекс первой точки
    int j;  // Индекс второй точки
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
private:
    qreal minX;
    qreal minY;
    qreal maxX;
    qreal maxY;
    QPointF scalePoint(QPointF point);
    QTriangle scaleTrianglePoints(QTriangle triangle);
    void calcMinMaxPoint();
    void drawAxis(QPainter *);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPAINTWIDGET_H
