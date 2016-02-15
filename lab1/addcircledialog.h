#ifndef ADDCIRCLEDIALOG_H
#define ADDCIRCLEDIALOG_H

#include <QDialog>

class QLineEdit;

class AddCircleDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* textFieldX;
    QLineEdit* textFieldY;
    QLineEdit* textFieldR;

public:
    AddCircleDialog (QWidget* pwgt = 0);
    QString X() const;
    QString Y() const;
    QString R() const;

signals:
public slots:

};

#endif // ADDCIRCLEDIALOG_H
