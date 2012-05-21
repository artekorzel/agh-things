#include "dodajkolodialog.h"
#include "ui_dodajkolodialog.h"

DodajKoloDialog::DodajKoloDialog(QWidget *parent, kolo * pom) :
    QDialog(parent),
    ui(new Ui::DodajKoloDialog)
{
    ui->setupUi(this);
    k = pom;
}

DodajKoloDialog::~DodajKoloDialog()
{
    delete ui;
}

void DodajKoloDialog::on_buttonBox_accepted()
{
    k->setPromien(ui->textEdit->toPlainText().toFloat());
}
