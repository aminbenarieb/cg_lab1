#include "adddialog.h"
#include "congif.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

AddDialog::AddDialog(QWidget* pwgt/*= 0*/)
    : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{

    textFieldX = new QLineEdit;
    textFieldY = new QLineEdit;
    QLabel* labelX = new QLabel(kDialogLabelTextX);
    QLabel* labelY = new QLabel(kDialogLabelTextY);
    labelX->setBuddy(textFieldX);
    labelY->setBuddy(textFieldY);
    QPushButton* pcmdOk = new QPushButton(kDialogBtnTextOK);
    QPushButton* pcmdCancel = new QPushButton(kDialogBtnTextCancel);
    connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(labelX, 0, 0);
    ptopLayout->addWidget(labelY, 1, 0);
    ptopLayout->addWidget(textFieldX, 0, 1);
    ptopLayout->addWidget(textFieldY, 1, 1);
    ptopLayout->addWidget(pcmdOk, 2,0);
    ptopLayout->addWidget(pcmdCancel, 2, 1);
    setLayout(ptopLayout);

}

QString AddDialog::X() const {
    return textFieldX->text();
}

QString AddDialog::Y() const {
    return textFieldY->text();
}
