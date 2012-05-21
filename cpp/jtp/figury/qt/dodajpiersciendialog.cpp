#include "dodajpiersciendialog.h"
#include "ui_dodajpiersciendialog.h"

DodajPierscienDialog::DodajPierscienDialog(QWidget *parent, pierscien * pier) :
    QDialog(parent),
    ui(new Ui::DodajPierscienDialog)
{
    ui->setupUi(this);
    p = pier;
}

DodajPierscienDialog::~DodajPierscienDialog()
{
    delete ui;
}

void DodajPierscienDialog::on_buttonBox_accepted()
{
    p->promienie(ui->textEdit->toPlainText().toFloat(),
		 ui->textEdit_2->toPlainText().toFloat());
}
