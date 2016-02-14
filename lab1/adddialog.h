#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

class QLineEdit;

class AddDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* textFieldX;
    QLineEdit* textFieldY;

public:
    AddDialog(QWidget* pwgt = 0);
    QString X() const;
    QString Y() const;

signals:
public slots:

};

#endif // ADDDIALOG_H
