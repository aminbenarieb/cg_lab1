#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QApplication>
#include <QDialog>
#include <QMessageBox>

#include "qpaintwidget.h"
#include "adddialog.h"
#include "congif.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void actionQuit(){
        QApplication::quit();
    }
    void actionClean(){}
    void actionCalc(){}
    void actionAddPoint(){

        AddDialog* addDialog = new AddDialog;
        if (addDialog->exec() == QDialog::Accepted) {

            addRow(QPointF(addDialog->X().toInt(), addDialog->Y().toInt()));

        }
        delete addDialog;

    }
    void actionEditPoint(){}
    void actionDelPoint(){}

private:
    bool eventFilter(QObject *, QEvent *);
    void addRow(QPointF pt);

    QTableWidget *tableView;
    QPaintWidget *wgt;

};

#endif // MAINWINDOW_H

