#include "qpaintwidget.h"
#include "congif.h"

#include <QDebug>
#include <QPainter>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
    circle.pos = QPointF(0,0);
    circle.radius = 0;

}

void QPaintWidget::paintEvent(QPaintEvent *) {

    QPainter ppainter(this);

    calcMinMaxPoint();
    drawAxis(&ppainter);
    ppainter.save();
    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::transparent));
//    if (circle.radius !=0)
//    {
//           ppainter.drawEllipse(circle.pos.x()-circle.radius, circle.pos.y()-circle.radius, 2*circle.radius, 2*circle.radius);
//    }
//    foreach (QTriangle triangle, triangles) {
//        ppainter.drawPolygon(triangle.points, 3);
//    }
//    if (triangle.min)
//    {
//           ppainter.setPen(QPen(Qt::blue, kDrawPenWidth));
//           ppainter.drawPolygon(triangle.points, 3);
//    }
    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::green));
//    if (circle.radius !=0)
//    {
//           ppainter.drawEllipse(circle.pos.x()-kDrawPointRadius, circle.pos.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
//    }
    foreach (QPointF point, points) {

        QPointF scalePos = QPointF();
        scalePos.setX( ((point.x()-minX)/ (maxX - minX)) * this->width());
        scalePos.setY( ((point.y()-minY)/ (maxY - minY)) * this->height());

        ppainter.drawEllipse(scalePos.x()-kDrawPointRadius, scalePos.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
    }
    ppainter.restore();
}


void QPaintWidget::calcMinMaxPoint()
{
    bool flagFirst = true;

    foreach (QPointF point, points)
    {
       if (flagFirst || point.x() < minX)
            minX = point.x();
       if (flagFirst || point.x() > minX)
            maxX = point.x();
       if (flagFirst || point.y() < minY)
            minY = point.y();
       if (flagFirst || point.y() > maxY)
            maxY = point.y();

       if (flagFirst)
           flagFirst = false;
    }
    qDebug()<<"maxX: "<<maxX<<", maxY: "<<maxY;
    qDebug()<<"minX: "<<minX<<", minY: "<<minY;


}
void QPaintWidget::drawAxis(QPainter *ppainter)
{
    double w = this->width();
    double h = this->height();
    //double size = kmax(w,h);
    double step = 100;

    ppainter->save();
    ppainter->setPen(QPen(Qt::lightGray,2,Qt::DashLine));
    for (double i = step; i <= w; i += step)
    {
        ppainter->drawLine(QPointF(i,h), QPointF(i,0));
     }
    for (double i = step; i <= h; i += step)
    {
        ppainter->drawLine(QPointF(0,i), QPointF(w,i));
    }
    ppainter->restore();

}
