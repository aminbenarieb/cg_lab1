#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QVarLengthArray>


class QPaintEvent;
class QLabel;

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
    int i;  // Индекс первой точки прямой прходящей через центр окружности
    int j;  // Индекс второй точки -/-
    int k;  // Индекс первой точки стороны, образующей наименьший угол с осью абцисс
    int q;  // Индекс второй точки -/-
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
    int cursorX;
    int cursorY;
    QPointF scalePoint(QPointF);
    double scalePointX(double x);
    double scalePointY(double y);

private:
    qreal minX;
    qreal minY;
    qreal maxX;
    qreal maxY;
    QLabel *initAxisLabel(int, int, int, int, QFont);
    QTriangle scaleTrianglePoints(QTriangle);
    void calcScale();
    void drawMouseLabels(QPainter *);
    void drawAxis(QPainter *);
    void drawCircle(QPainter *);
    void drawPoints(QPainter *);
    void drawTriangle(QPainter *);
    double canvasWidth();
    double canvasHeight();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPAINTWIDGET_H
