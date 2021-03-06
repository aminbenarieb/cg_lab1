#include "mainwindow.h"
#include "congif.h"

#include <QGridLayout>
#include <QEvent>
#include <QResizeEvent>
#include <QPushButton>
#include <QHeaderView>
#include <QStatusBar>


MainWindow::~MainWindow()
{
    wgt->deleteLater();
}


void MainWindow::addRow(QPointF point)
{
    // Сбрасываем решение
    wgt->triangle.min = false;

    // Добавление в массив
    wgt->points.append(point);

    // Обновление рисунка
    wgt->update();

    // Обновление таблицы
    updateTable();

}
void MainWindow::updateTable()
{

    while (tableView->rowCount() != 0)
    {
        delete  tableView->item(tableView->rowCount()-1, 0);
        delete  tableView->item(tableView->rowCount()-1, 1);
        delete  tableView->item(tableView->rowCount()-1, 2);
        tableView->removeRow(0);
    }

    foreach (QPointF point, wgt->points) {

        tableView->insertRow(tableView->rowCount());
        tableView->setItem(tableView->rowCount()-1, 0,  new QTableWidgetItem(QString::number(tableView->rowCount())));
        tableView->setItem(tableView->rowCount()-1, 1,  new QTableWidgetItem(QString::number(point.x())));
        tableView->setItem(tableView->rowCount()-1, 2,  new QTableWidgetItem(QString::number(point.y())));
    }

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::Resize )
    {
//       QResizeEvent *res = reinterpret_cast<QResizeEvent*>(event); размер измененного окна
        return true;
    }
    else if (event->type() ==QMouseEvent::MouseButtonDblClick)
    {
//        addRow(  wgt->scalePoint( ((QMouseEvent*)event)->pos()) );
        return true;
    }
    else if (event->type() ==QMouseEvent::MouseMove)
    {
//        QPointF pos = ((QMouseEvent*)event)->pos();
//        wgt->cursorX = pos.x();
//        wgt->cursorY = pos.y();

//        pos = wgt->scalePoint(pos);
//        this->setWindowTitle(  QString("%1 (%2,%3)").arg(kTextTitle, QString::number(pos.x()), QString::number(pos.y())) );

//        wgt->update();

        return true;
    }
    else if (event->type() ==QEvent::Leave)
    {
        this->setWindowTitle(kTextTitle);

        return true;
    }

    return false;
}
