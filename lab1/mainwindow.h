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

       //    QItemSelectionModel *sm = tableView->selectionModel();
       //    connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
       //               this, SLOT(pointSelected(QModelIndex,QModelIndex)));
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
           btnEditCircle->setText(kBtnTextEditCircle);


           QObject::connect(btnQuit, SIGNAL(clicked()), this, SLOT(actionQuit()) );
           QObject::connect(btnClean, SIGNAL(clicked()), this, SLOT(actionClean()));
           QObject::connect(btnCalc, SIGNAL(clicked()), this, SLOT(actionCalc()));
           QObject::connect(btnAddPoint, SIGNAL(clicked()), this, SLOT(actionAddPoint()));
           QObject::connect(btnEditPoint, SIGNAL(clicked()), this, SLOT(actionEditPoint()));
           QObject::connect(btnDelPoint, SIGNAL(clicked()), this, SLOT(actionDelPoint()));
           QObject::connect(btnAddCircle, SIGNAL(clicked()), this, SLOT(actionAddCircle()));
           QObject::connect(btnEditCircle, SIGNAL(clicked()), this, SLOT(actionEditCircle()));
           QObject::connect(btnDelCircle, SIGNAL(clicked()), this, SLOT(actionDelCircle()));
           //*******************************
    }

public slots:
    void actionQuit(){
        QApplication::quit();
    }
    void actionClean(){

        while (wgt->points.count() != 0)
            wgt->points.removeLast();

        while (wgt->triangles.count() != 0)
            wgt->triangles.removeLast();

        wgt->circle.radius = 0;
        wgt->triangle.min = false;

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
                            qreal s = (a+b+c)/2;
                            qreal area = sqrt(s*(s-a)*(s-b)*(s-c));

                            bool center_circle_on_side_1 = kIfPointOnSide(
                                       wgt->circle.pos,
                                       triangle.points[0],
                                       triangle.points[1]);
                            bool center_circle_on_side_2 = kIfPointOnSide(
                                       wgt->circle.pos,
                                       triangle.points[0],
                                       triangle.points[2]);
                            bool center_circle_on_side_3 = kIfPointOnSide(
                                       wgt->circle.pos,
                                       triangle.points[1],
                                       triangle.points[2]);

                            if (area != 0 &&
                                (center_circle_on_side_1 ||
                                center_circle_on_side_2 ||
                                center_circle_on_side_3))
                                    wgt->triangles.append(triangle);

                        }


        int i = 0;
        foreach(QTriangle triangle, wgt->triangles)
        {
            QPointF point1 = triangle.points[0];
            QPointF point2 = triangle.points[1];
            QPointF point3 = triangle.points[2];


            double angle1 = kAngleOfTwoVectors(point1.x(), point1.y(), point2.x(), point2.y());
            double angle2 = kAngleOfTwoVectors(point1.x(), point1.y(), point3.x(), point3.y());
            double angle3 = kAngleOfTwoVectors(point2.x(), point2.y(), point3.x(), point3.y());


            double angle = kmin( kmin(angle1, angle2),  angle3);

            qDebug()<<++i<<angle1<<angle2<<angle3<<";min: "<<angle;


            if (!wgt->triangle.min || wgt->triangle.angle < angle)
            {
                qDebug()<<i<<angle;
                wgt->triangle = triangle;
                wgt->triangle.angle = angle;
                wgt->triangle.min = true;
            }
        }

        wgt->update();

    }
    void actionAddPoint(){

        AddPointDialog* addDialog = new AddPointDialog;
        if (addDialog->exec() == QDialog::Accepted) {
            addRow(QPointF(addDialog->X().toFloat(), addDialog->Y().toFloat()));

        }
        delete addDialog;

    }
    void actionEditPoint(){}
    void actionDelPoint(){}
    void actionAddCircle(){


        AddCircleDialog* addDialog = new AddCircleDialog;
        if (addDialog->exec() == QDialog::Accepted)
        {
            wgt->circle.pos = QPointF(addDialog->X().toFloat(), addDialog->Y().toFloat());;
            wgt->circle.radius = addDialog->R().toFloat();
            wgt->update();
        }
        delete addDialog;

    }
    void actionEditCircle(){}
    void actionDelCircle(){}

//    void pointSelected(QModelIndex indeMod,QModelIndex indeMod2)
//    {
//        AddDialog* addDialog = new AddDialog;
//        if (addDialog->exec() == QDialog::Accepted)
//        {
//            tableView->setItem(indeMod.row(), 1,  new QTableWidgetItem(addDialog->X()));
//            tableView->setItem(indeMod.row(), 2,  new QTableWidgetItem(addDialog->Y()));
//        }
//        delete addDialog;
//    }


private:
    bool eventFilter(QObject *, QEvent *);
    void addRow(QPointF pt);
    void updateTable();

};

#endif // MAINWINDOW_H

