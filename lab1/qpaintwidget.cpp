#include "qpaintwidget.h"
#include "congif.h"

#include <QPainter>

QPaintWidget::QPaintWidget(QWidget * parent) : QWidget(parent)
{
}

void QPaintWidget::paintEvent(QPaintEvent *) {

    QPainter ppainter(this);
    ppainter.save();

    ppainter.setPen(QPen(Qt::black, kDrawPenWidth));
    ppainter.setBrush(QBrush(Qt::blue));
    foreach (QPointF point, points) {
        ppainter.drawEllipse(point.x()-kDrawPointRadius, point.y()-kDrawPointRadius, 2*kDrawPointRadius, 2*kDrawPointRadius);
    }

    ppainter.restore();
}
