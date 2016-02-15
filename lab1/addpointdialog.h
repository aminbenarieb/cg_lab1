#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>

class QLineEdit;

class AddPointDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* textFieldX;
    QLineEdit* textFieldY;

public:
    AddPointDialog(QWidget* pwgt = 0);
    QString X() const;
    QString Y() const;

signals:
public slots:

};

#endif // ADDPOINTDIALOG_H
