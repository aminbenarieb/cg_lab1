#include "mainwindow.h"
#include "congif.h"

#include <QGridLayout>
#include <QEvent>
#include <QResizeEvent>
#include <QDebug>
#include <QPushButton>
#include <QHeaderView>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle(kTextTitle);
    this->setFixedSize(600, 400);

     //***** QPaintWidget Settings ******
    wgt = new QPaintWidget(this);
    wgt->setMinimumWidth(300);
    wgt->setMouseTracking(true);
    wgt->installEventFilter(this);
    //*******************************

    //***** TableView Settings ******
    tableView  = new QTableWidget();

    tableView->setColumnCount(3);
    tableView->setFixedWidth(119);
    tableView->setColumnWidth(0,35);
    tableView->setColumnWidth(1,35);
    tableView->setColumnWidth(2,35);

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
               this, SLOT(tableViewRowSelected(QModelIndex,QModelIndex)));
    //*******************************



    //***** Buttons Settings ******
    QPushButton *btnQuit = new QPushButton(kBtnTextQuit);
    QPushButton *btnClean = new QPushButton(kBtnTextClean);
    QPushButton *btnCalc = new QPushButton(kBtnTextCalc);
    QPushButton *btnAddPoint  = new QPushButton(kBtnTextAddPoint);
    QPushButton *btnDelPoint = new QPushButton(kBtnTextDelPoint);
    QPushButton *btnEditPoint = new QPushButton(kBtnTextEditPoint);

    QObject::connect(btnQuit, SIGNAL(clicked()), this, SLOT(actionQuit()) );
    QObject::connect(btnClean, SIGNAL(clicked()), this, SLOT(actionClean()));
    QObject::connect(btnCalc, SIGNAL(clicked()), this, SLOT(actionCalc()));
    QObject::connect(btnAddPoint, SIGNAL(clicked()), this, SLOT(actionAddPoint()));
    QObject::connect(btnEditPoint, SIGNAL(clicked()), this, SLOT(actionEditPoint()));
    QObject::connect(btnDelPoint, SIGNAL(clicked()), this, SLOT(actionDelPoint()));
    //*******************************

    //***** Layout Settings ******
    QGridLayout* pvbxLayout = new QGridLayout;
    pvbxLayout->setContentsMargins(0, 0, 0, 0);
    pvbxLayout->addWidget(wgt,0,0);
    pvbxLayout->addWidget(tableView, 0, 1);
    pvbxLayout->addWidget(btnQuit, 0, 2);
    pvbxLayout->addWidget(btnClean, 1, 2);
    pvbxLayout->addWidget(btnCalc, 2, 2);
    pvbxLayout->addWidget(btnAddPoint, 3, 2);
    pvbxLayout->addWidget(btnEditPoint, 4, 2);
    pvbxLayout->addWidget(btnDelPoint, 5, 2);
    setLayout(pvbxLayout);
    //*******************************

}

MainWindow::~MainWindow()
{
    wgt->deleteLater();
}


void MainWindow::addRow(QPointF point)
{
    // Добавление
    wgt->points.append(point);
    wgt->update();

    // Добавление в таблицу точки
    const int rowCount = tableView->rowCount();
    tableView->insertRow(rowCount);
    tableView->setItem(rowCount, 0,  new QTableWidgetItem(QString::number(rowCount)));
    tableView->setItem(rowCount, 1,  new QTableWidgetItem(QString::number(point.y())));
    tableView->setItem(rowCount, 2,  new QTableWidgetItem(QString::number(point.y())));

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
        addRow( ((QMouseEvent*)event)->pos() );
        return true;
    }
    else if (event->type() ==QMouseEvent::MouseMove)
    {
        QPointF pos = ((QMouseEvent*)event)->pos();
        this->setWindowTitle(  QString("%1 (%2,%3)").arg(kTextTitle, QString::number(pos.x()), QString::number(pos.y())) );
        return true;
    }
    else if (event->type() ==QEvent::Leave)
    {
        this->setWindowTitle(kTextTitle);

        return true;
    }

    return false;
}
