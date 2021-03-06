#include "qpaintwidget.h"
#include "congif.h"

#include <QDebug>
#include <QPainter>
#include <QLabel>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
    // Inirialization
    circle.pos = QPointF(0,0);
    circle.radius = 0;

}

// QLabel initialization

QLabel* QPaintWidget::initAxisLabel(int x, int y, int labelWidth, int labelHeight, QFont font)
{
    QLabel *item = new QLabel(this);

    item->setAlignment(Qt::AlignCenter);
    item->setFont(font);
    item->setFixedSize(labelWidth,labelHeight);
    item->setGeometry(x,y,x+labelWidth,y+labelHeight);

    return item;
}

// Padding Width

double QPaintWidget::canvasWidth()
{
    return this->width()-2*kPadding;
}

double QPaintWidget::canvasHeight()
{
    return this->height()-2*kPadding;
}

// Calculation

void QPaintWidget::calcScale()
{

    double deltaX, deltaY;

    // Calculation min, max of points
    bool flagFirst = true;
    foreach (QPointF point, points)
    {
       if (flagFirst || point.x() < minX)
            minX = point.x();
       if (flagFirst || point.x() > maxX)
            maxX = point.x();
       if (flagFirst || point.y() < minY)
            minY = point.y();
       if (flagFirst || point.y() > maxY)
            maxY = point.y();

       if (flagFirst)
           flagFirst = false;
    }

     // Calculation min, max of circle
    if (circle.radius != 0)
    {
        if (minX > circle.pos.x()-circle.radius)
            minX = circle.pos.x()-circle.radius;

        if (maxX < circle.pos.x()+circle.radius)
            maxX = circle.pos.x()+circle.radius;

        if (minY > circle.pos.y()-circle.radius)
            minY = circle.pos.y()-circle.radius;

        if (maxY < circle.pos.y()+circle.radius)
            maxY = circle.pos.y()+circle.radius;
    }


    // Setting scale coef
    deltaX = maxX - minX;
    deltaY = maxY - minY;


    // Increasing Y axis
    if (deltaX > deltaY)
    {
        double delta = deltaX - deltaY;
        maxY += delta / 2.0;
        minY -= delta / 2.0;
        deltaY = deltaX;
    }

    // Increasing X axis
    if (deltaY > deltaX)
    {
        double delta = deltaY - deltaX;
        maxY += delta / 2.0;
        minY -= delta / 2.0;
        deltaX = deltaY;
    }

    // Settings for one point
    if (deltaX == 0 && deltaY == 0)
    {
        deltaX = 40;
        deltaY = 40;

        maxX += deltaX / 20.0;
        minX -= deltaX / 20.0;
        maxY += deltaY / 20.0;
        minY -= deltaY / 20.0;
    }

}

// Scaling

QPointF QPaintWidget::scalePoint(QPointF point)
{

    return QPointF(scalePointX(point.x()) , scalePointY(point.y()));

}

double QPaintWidget::scalePointX(double x){
    return  ((x - minX)/ (maxX - minX)) * canvasWidth() + kPadding;
}
double QPaintWidget::scalePointY(double y){

    return  ((y - minY)/ (maxY - minY)) * canvasHeight() *(-1) + canvasHeight() + kPadding;
}

QTriangle QPaintWidget::scaleTrianglePoints(QTriangle triangle)
{
    for (int i = 0; i < 3; i++)
        triangle.points[i] = scalePoint(triangle.points[i]);
    return triangle;

}

// Drawing

void QPaintWidget::drawCircleLine(QPainter *ppainter)
{

//    double x1 = kPadding;
//    double x2 = canvasWidth();

//    double a = ( triangle.points[triangle.i].y() -  triangle.points[triangle.j].y() ) /   ( triangle.points[triangle.i].x() -  triangle.points[triangle.j].x() );
//    double b =  triangle.points[triangle.i].y()  - a * triangle.points[triangle.i].x();

//    double y1 = scalePointX( a*x1  +b );
//    double y2 = scalePointY( a*x2 + b );

    if (triangle.min)
    {
        double x1 = circle.pos.x();
        double y1 = circle.pos.y();
        double x2 = triangle.points[triangle.j].x();
        double y2 = triangle.points[triangle.j].y();

        ppainter->save();

        ppainter->setPen(QPen(Qt::red,2,Qt::SolidLine));
        ppainter->drawLine(  scalePoint ( QPointF(x1,y1) ),  scalePoint ( QPointF(x2, y2) ) );

        ppainter->restore();
    }
}

void QPaintWidget::drawFrame(QPainter *ppainter){

    QVector<QPointF> linePoints;
    linePoints <<  QPointF(kPadding,kPadding)
                <<  QPointF(kPadding,canvasHeight()+kPadding)
                 <<  QPointF(kPadding,canvasHeight()+kPadding)
                  <<  QPointF(canvasWidth()+kPadding,canvasHeight()+kPadding)
                   <<  QPointF(canvasWidth()+kPadding,canvasHeight()+kPadding)
                    <<  QPointF(canvasWidth()+kPadding,kPadding)
                     <<  QPointF(canvasWidth()+kPadding,kPadding)
                      <<  QPointF(kPadding,kPadding);

    ppainter->save();

    ppainter->setPen(QPen(Qt::lightGray,1,Qt::DashLine));
    ppainter->drawLines( linePoints );

    ppainter->restore();


}

void QPaintWidget::drawAxis(QPainter *ppainter)
{
    double w = canvasWidth()+kPadding;
    double h = canvasHeight()+kPadding;
    double step = 92;

    ppainter->save();
    ppainter->setPen(QPen(Qt::lightGray,1,Qt::DashLine));
    for (double x = kPadding; x <= w; x += step)
    {
        ppainter->drawLine(QPointF(x,h), QPointF(x,kPadding));
     }
    for (double y = kPadding; y <= h; y += step)
    {
        ppainter->drawLine(QPointF(kPadding,y), QPointF(w,y));
    }
    ppainter->restore();

}

void QPaintWidget::drawCircle(QPainter *ppainter)
{
    if (circle.radius !=0)
    {

           ppainter->save();

           double posXCenter = scalePointX(circle.pos.x());
           double posYCenter = scalePointY(circle.pos.y());
           int sizeX = static_cast<int>(circle.radius/((maxX - minX) / canvasWidth()));
           int sizeY = static_cast<int>(circle.radius/((maxY - minY) / canvasHeight()));
           int size = kmin(sizeX, sizeY);

           ppainter->setPen(QPen(Qt::darkGreen, kDrawPenWidth));
           ppainter->setBrush(QBrush(Qt::transparent));
           ppainter->drawEllipse(
                                 posXCenter-size,
                                 posYCenter-size,
                                 2*size+1,
                                 2*size+1
                                 );

           ppainter->restore();
    }
}

void QPaintWidget::drawPoints(QPainter *ppainter)
{

    ppainter->save();

    // Drawing general points
    ppainter->setBrush(QBrush(triangle.min ? Qt::gray : Qt::red));
    ppainter->setPen(QPen(triangle.min ? Qt::gray : Qt::red, kDrawPenWidth));
    foreach (QPointF point, points)
    {
        QPointF scalePos = scalePoint(point);
        ppainter->drawEllipse(scalePos.x()-kDrawPointRadius, scalePos.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
    }
    ppainter->restore();

     // Drawing trinagle points
     if (triangle.min)
     {
         ppainter->setBrush(QBrush(Qt::red));
         ppainter->setPen(QPen(Qt::red, kDrawPenWidth));

         for (int i = 0; i < 3; i++)
         {
             QPointF scalePos = scalePoint(triangle.points[i]);
             ppainter->drawEllipse(scalePos.x()-kDrawPointRadius, scalePos.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
         }
     }

     // Drawing circle points
     if (circle.radius != 0)
     {
         QPointF scalePos = scalePoint(circle.pos);
         ppainter->setBrush(QBrush(Qt::red));
         ppainter->setPen(QPen(Qt::red, kDrawPenWidth));
         ppainter->drawEllipse(scalePos.x()-kDrawPointRadius, scalePos.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
     }

}

void QPaintWidget::drawTriangle(QPainter *ppainter)
{
    if (triangle.min)
    {
        ppainter->save();
        ppainter->setPen(QPen(Qt::blue, kDrawPenWidth));
        ppainter->drawPolygon(scaleTrianglePoints(triangle).points, 3);
        ppainter->restore();
    }
}

void QPaintWidget::paintEvent(QPaintEvent *) {

    calcScale();

    QPainter ppainter(this);
    ppainter.save();

    ppainter.setRenderHint(QPainter::Antialiasing, true);
    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::transparent));

    drawFrame(&ppainter);
    drawAxis(&ppainter);
    drawCircle(&ppainter);
    drawTriangle(&ppainter);
    drawPoints(&ppainter);
//    drawCircleLine(&ppainter);

    ppainter.restore();
}
