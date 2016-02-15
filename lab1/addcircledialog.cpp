#include "addcircledialog.h"
#include "congif.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

AddCircleDialog::AddCircleDialog(QWidget* pwgt/*= 0*/)
    : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{

    textFieldX = new QLineEdit;
    textFieldY = new QLineEdit;
    textFieldR = new QLineEdit;

    QLabel* labelX = new QLabel(kDialogLabelTextX);
    QLabel* labelY = new QLabel(kDialogLabelTextY);
    QLabel* labelR = new QLabel(kDialogLabelTextR);

    labelX->setBuddy(textFieldX);
    labelY->setBuddy(textFieldY);
    labelR->setBuddy(textFieldR);

    QPushButton* pcmdOk = new QPushButton(kDialogBtnTextOK);
    QPushButton* pcmdCancel = new QPushButton(kDialogBtnTextCancel);
    connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(labelX, 0, 0);
    ptopLayout->addWidget(labelY, 1, 0);
    ptopLayout->addWidget(labelR, 2, 0);
    ptopLayout->addWidget(textFieldX, 0, 1);
    ptopLayout->addWidget(textFieldY, 1, 1);
    ptopLayout->addWidget(textFieldR, 2, 1);
    ptopLayout->addWidget(pcmdOk, 3,0);
    ptopLayout->addWidget(pcmdCancel, 3, 1);
    setLayout(ptopLayout);

}

QString AddCircleDialog::X() const {
    return textFieldX->text();
}

QString AddCircleDialog::Y() const {
    return textFieldY->text();
}

QString AddCircleDialog::R() const {
    return textFieldR->text();
}
