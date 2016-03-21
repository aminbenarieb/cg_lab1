#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QTableWidget>
#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>

#include "ui_mainwindow.h"
#include "qpaintwidget.h"
#include "addpointdialog.h"
#include "addcircledialog.h"
#include "congif.h"

class MainWindow : public  QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

    MainWindow(QMainWindow* pwgt = 0) : QMainWindow(pwgt) {

        setupUi(this);

        this->setWindowTitle(kTextTitle);
        //this->set;

        //***** QPaintWidget Settings ******
        //wgt->setMinimumWidth(500);
        wgt->setMouseTracking(true);
        wgt->installEventFilter(this);
        wgt->setAutoFillBackground(true);
        QPalette Pal = palette();
        Pal.setColor(QPalette::Background, Qt::white);
        wgt->setPalette(Pal);
        //*******************************

        //***** TableView Settings ******

        tableView->setColumnCount(3);
        tableView->setFixedWidth(140);
        tableView->setColumnWidth(0,26);
        tableView->setColumnWidth(1,46);
        tableView->setColumnWidth(2,46);

        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView:: SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        tableView->horizontalHeader()->setSectionsClickable(false);

        tableView->setHorizontalHeaderItem(0, new QTableWidgetItem("№"));
        tableView->setHorizontalHeaderItem(1, new QTableWidgetItem("X"));
        tableView->setHorizontalHeaderItem(2, new QTableWidgetItem("Y"));

        tableView->verticalHeader()->setVisible(false);

        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        QItemSelectionModel *sm = tableView->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(pointSelected(QModelIndex)));
        //*******************************


        //***** Label Settings ******
        labelCircle->setText(kLabelCircleUndefined);
        //*******************************

        //***** Buttons Settings ******
        btnQuit->setText(kBtnTextQuit);
        btnClean->setText(kBtnTextClean);
        btnCalc->setText(kBtnTextCalc);
        btnAddPoint ->setText(kBtnTextAddPoint);
        btnDelPoint->setText(kBtnTextDelPoint);
        btnEditPoint->setText(kBtnTextEditPoint);
        btnAddCircle ->setText(kBtnTextAddCircle);
        btnDelCircle->setText(kBtnTextDelCircle);
        btnGenerate->setText(kBtnTextGenerate);

        QObject::connect(btnQuit, SIGNAL(clicked()), this, SLOT(actionQuit()) );
        QObject::connect(btnClean, SIGNAL(clicked()), this, SLOT(actionClean()));
        QObject::connect(btnCalc, SIGNAL(clicked()), this, SLOT(actionCalc()));
        QObject::connect(btnGenerate, SIGNAL(clicked()), this, SLOT(actionGenerate()));
        QObject::connect(btnAddPoint, SIGNAL(clicked()), this, SLOT(actionAddPoint()));
        QObject::connect(btnEditPoint, SIGNAL(clicked()), this, SLOT(actionEditPoint()));
        QObject::connect(btnDelPoint, SIGNAL(clicked()), this, SLOT(actionDelPoint()));
        QObject::connect(btnAddCircle, SIGNAL(clicked()), this, SLOT(actionAddCircle()));
        QObject::connect(btnDelCircle, SIGNAL(clicked()), this, SLOT(actionDelCircle()));
        //*******************************
    }

public slots:
    void actionQuit(){
        QApplication::quit();
    }

    void actionGenerate()
    {

        actionClean();

        wgt->circle.pos = QPointF(0,0);
        wgt->circle.radius = 100;

        labelCircle->setText(QString(kLabelCircleInfo).arg(
                                 QString::number(wgt->circle.pos.x()),
                                 QString::number(wgt->circle.pos.y()),
                                 QString::number(wgt->circle.radius)
                                 ));
        btnDelCircle->setEnabled(true);
        btnAddCircle ->setText(kBtnTextEditCircle);


        addRow(QPointF(-10,10));
        addRow(QPointF(10,10));
        addRow(QPointF(-10,-10));

        actionCalc();
    }
    void actionClean(){

        while (wgt->points.count() != 0)
            wgt->points.removeLast();

        while (wgt->triangles.count() != 0)
            wgt->triangles.removeLast();

        // Сбрасываем решение
        wgt->triangle.min = false;

        wgt->circle.radius = 0;
        labelCircle->setText(kLabelCircleUndefined);
        btnDelCircle->setEnabled(false);
        btnAddCircle ->setText(kBtnTextAddCircle);

        wgt->update();
        updateTable();

    }
    void actionCalc(){

        while (wgt->triangles.count() != 0)
            wgt->triangles.removeLast();

        const int count = wgt->points.count();
        if  (count > 2)
            for (int i = 0; i < count; i++ )
                for (int j = i+1; j < count; j++ )
                    for (int k = j+1; k < count; k++ )
                      if ( ( i != j) && (j != k) && (k != i) )
                        {
                            QTriangle triangle;
                            triangle.points[0] = wgt->points[i];
                            triangle.points[1] = wgt->points[j];
                            triangle.points[2] = wgt->points[k];

                            //Проверка вырожденного треуольника
                            qreal a = kcalcSide(triangle.points[0], triangle.points[1]);
                            qreal b = kcalcSide(triangle.points[0], triangle.points[2]);
                            qreal c = kcalcSide(triangle.points[1], triangle.points[2]);

                            //Формула Герона
                            qreal p = (a+b+c)/2;                    //полупериметр
                            qreal area = sqrt(p*(p-a)*(p-b)*(p-c)); //площадь

                            bool center_circle_on_side_1 = kIfPointOnLine(
                                       wgt->circle.pos,
                                       triangle.points[0],
                                       triangle.points[1]);
                            bool center_circle_on_side_2 = kIfPointOnLine(
                                       wgt->circle.pos,
                                       triangle.points[0],
                                       triangle.points[2]);
                            bool center_circle_on_side_3 = kIfPointOnLine(
                                       wgt->circle.pos,
                                       triangle.points[1],
                                       triangle.points[2]);

                            if (area != 0 &&
                                (center_circle_on_side_1 ||
                                center_circle_on_side_2 ||
                                center_circle_on_side_3))
                            {
                                // Сохраняем индексы точек для показа их в текстовом решении
                                if (center_circle_on_side_1)
                                {
                                    triangle.i = 0;
                                    triangle.j = 1;
                                }
                                else if (center_circle_on_side_2)
                                {
                                    triangle.i = 0;
                                    triangle.j = 2;
                                }
                                else if (center_circle_on_side_3)
                                {
                                    triangle.i = 1;
                                    triangle.j = 2;
                                }

                                 wgt->triangles.append(triangle);
                            }

                        }


        int i = 0;
        foreach(QTriangle triangle, wgt->triangles)
        {
            QPointF point1 = triangle.points[0];
            QPointF point2 = triangle.points[1];
            QPointF point3 = triangle.points[2];

            double angle1 = kAngleVector_XAxis(point1.x(), point1.y(), point2.x(), point2.y());
            double angle2 = kAngleVector_XAxis(point1.x(), point1.y(), point3.x(), point3.y());
            double angle3 = kAngleVector_XAxis(point2.x(), point2.y(), point3.x(), point3.y());

            qDebug()<<QString().sprintf("%i) angles: %.2lf %.2lf %.2lf", ++i, angle1, angle2, angle3);


            double angle;
            int k = 0, q = 0;

            if (angle1 < angle2)
            {
                if (angle1 < angle3)
                {
                    angle = angle1;
                    k = 0;
                    q = 1;
                }
                else
                {
                    angle = angle3;
                    k = 1;
                    q = 2;
                }
            }
            else
            {
                if (angle2 < angle3)
                {
                    angle = angle2;
                    k = 0;
                    q = 2;
                }
                else
                {
                    angle = angle3;
                    k = 1;
                    q = 2;
                }
            }


            if (!wgt->triangle.min || wgt->triangle.angle > angle)
            {
                // Сохраняем индексы точек для показа их в текстовом решении

                wgt->triangle = triangle;
                wgt->triangle.angle = angle;
                wgt->triangle.min = true;
                wgt->triangle.k = k;
                wgt->triangle.q = q;

                qDebug()<<QString().sprintf("%i) min angle: %.2lf", i, angle);

            }
        }

        wgt->update();


        if (wgt->triangle.min)
        {
            QMessageBox *msgBox = new QMessageBox(0);
            msgBox->setText("Решение");
            msgBox->setWindowModality(Qt::NonModal);
            msgBox->setInformativeText(
                        QString(kInfoResult).arg
                        (
                            QString("(%1, %2), (%3, %4), (%5, %6)").arg(
                                QString::number(wgt->triangle.points[0].x()),
                                QString::number(wgt->triangle.points[0].y()),
                                QString::number(wgt->triangle.points[1].x()),
                                QString::number(wgt->triangle.points[1].y()),
                                QString::number(wgt->triangle.points[2].x()),
                                QString::number(wgt->triangle.points[2].y())
                            ),
                            QString("(%1, %2), (%3, %4)").arg(
                                QString::number(wgt->triangle.points[wgt->triangle.i].x()),
                                QString::number(wgt->triangle.points[wgt->triangle.i].y()),
                                QString::number(wgt->triangle.points[wgt->triangle.j].x()),
                                QString::number(wgt->triangle.points[wgt->triangle.j].y())
                            ),
                            QString("(%1, %2)").arg(
                                QString::number(wgt->circle.pos.x()),
                                QString::number(wgt->circle.pos.y())
                            ),
                            QString("%1").arg(QString::number(wgt->circle.radius)),

                            QString("(%1, %2), (%3, %4)").arg(
                                QString::number(wgt->triangle.points[wgt->triangle.k].x()),
                                QString::number(wgt->triangle.points[wgt->triangle.k].y()),
                                QString::number(wgt->triangle.points[wgt->triangle.q].x()),
                                QString::number(wgt->triangle.points[wgt->triangle.q].y())
                            ),
                            QString("").sprintf("%.2lf", wgt->triangle.angle)
                        )
                    );

           QSpacerItem* horizontalSpacer = new QSpacerItem(400, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
           QGridLayout* layout = (QGridLayout*)msgBox->layout();
           layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

           msgBox->exec();
      }


    }

    void actionAddPoint(){

        AddPointDialog* addDialog = new AddPointDialog;
        if (addDialog->exec() == QDialog::Accepted) {
            addRow(QPointF(addDialog->X().toFloat(), addDialog->Y().toFloat()));
        }
        delete addDialog;

    }
    void actionEditPoint(){

        if (tableView->currentRow() >= 0)
        {
            AddPointDialog* addDialog = new AddPointDialog;
            if (addDialog->exec() == QDialog::Accepted) {

                double newX = addDialog->X().toFloat();
                double newY = addDialog->Y().toFloat();

                wgt->points[tableView->currentRow()] = QPointF(newX, newY);

                wgt->triangle.min = false;
                wgt->update();
                updateTable();


            }
            delete addDialog;

        }

    }
    void actionDelPoint(){

        if (tableView->currentRow() >= 0)
        {
            wgt->points.removeAt(tableView->currentRow());

            if (wgt->points.size() == 0)
            {
                btnEditPoint->setEnabled(false);
                btnDelPoint->setEnabled(false);
            }

            wgt->triangle.min = false;
            wgt->update();
            updateTable();
        }


    }

    void actionAddCircle(){

        AddCircleDialog* addDialog = new AddCircleDialog;
        if (addDialog->exec() == QDialog::Accepted)
        {
            wgt->circle.pos = QPointF(addDialog->X().toFloat(), addDialog->Y().toFloat());;
            wgt->circle.radius = addDialog->R().toFloat();

            labelCircle->setText(QString(kLabelCircleInfo).arg(
                                     QString::number(wgt->circle.pos.x()),
                                     QString::number(wgt->circle.pos.y()),
                                     QString::number(wgt->circle.radius)
                                     ));
            btnDelCircle->setEnabled(true);
            btnAddCircle ->setText(kBtnTextEditCircle);

            wgt->update();
        }
        delete addDialog;

    }
    void actionDelCircle(){

        wgt->circle.pos = QPointF(0,0);
        wgt->circle.radius = 0;
        labelCircle->setText(kLabelCircleUndefined);

        // Сбрасываем решение
        wgt->triangle.min = false;

        btnDelCircle->setEnabled(false);
        btnAddCircle ->setText(kBtnTextAddCircle);

        wgt->update();
    }

    void pointSelected(QModelIndex ind1)
    {
        btnEditPoint->setEnabled(ind1.row() >= 0);
        btnDelPoint->setEnabled(ind1.row() >= 0);

    }

private:
    bool eventFilter(QObject *, QEvent *);
    void addRow(QPointF pt);
    void updateTable();

};

#endif // MAINWINDOW_H

