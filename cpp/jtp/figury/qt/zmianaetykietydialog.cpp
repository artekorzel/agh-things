#include "zmianaetykietydialog.h"
#include "ui_zmianaetykietydialog.h"

ZmianaEtykietyDialog::ZmianaEtykietyDialog(QWidget *parent, figura * fig) :
    QDialog(parent),
    ui(new Ui::ZmianaEtykietyDialog)
{
    ui->setupUi(this);
    f = fig;
}

ZmianaEtykietyDialog::~ZmianaEtykietyDialog()
{
    delete ui;
}

void ZmianaEtykietyDialog::on_buttonBox_accepted()
{
    f->setEtykieta(ui->textEdit->toPlainText().toStdString());
}
