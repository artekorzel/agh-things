#include "dodajtrojkatdialog.h"
#include "ui_dodajtrojkatdialog.h"

DodajTrojkatDialog::DodajTrojkatDialog(QWidget *parent, trojkat * tr) :
    QDialog(parent),
    ui(new Ui::DodajTrojkatDialog)
{
    ui->setupUi(this);
    t = tr;
}

DodajTrojkatDialog::~DodajTrojkatDialog()
{
    delete ui;
}

void DodajTrojkatDialog::on_buttonBox_accepted()
{
    t->punkty(ui->textEdit->toPlainText().toFloat(),
	      ui->textEdit_2->toPlainText().toFloat(),
	      ui->textEdit_4->toPlainText().toFloat(),
	      ui->textEdit_3->toPlainText().toFloat(),
	      ui->textEdit_5->toPlainText().toFloat(),
	      ui->textEdit_6->toPlainText().toFloat());
}
