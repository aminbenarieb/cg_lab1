#include "qpaintwidget.h"
#include "congif.h"

#include <QPainter>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
    circle.pos = QPointF(0,0);
    circle.radius = 0;
}

void QPaintWidget::paintEvent(QPaintEvent *) {

    QPainter ppainter(this);

    ppainter.save();
    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::transparent));
    if (circle.radius !=0)
    {
           ppainter.drawEllipse(circle.pos.x()-circle.radius, circle.pos.y()-circle.radius, 2*circle.radius, 2*circle.radius);
    }
    foreach (QTriangle triangle, triangles) {
        ppainter.drawPolygon(triangle.points, 3);
    }
    if (triangle.min)
    {
           ppainter.setPen(QPen(Qt::blue, kDrawPenWidth));
           ppainter.drawPolygon(triangle.points, 3);
    }
    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::green));
    if (circle.radius !=0)
    {
           ppainter.drawEllipse(circle.pos.x()-kDrawPointRadius, circle.pos.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
    }
    foreach (QPointF point, points) {
        ppainter.drawEllipse(point.x()-kDrawPointRadius, point.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
    }

    ppainter.restore();
}
