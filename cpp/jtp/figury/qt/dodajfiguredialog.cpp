#include "dodajfiguredialog.h"
#include "ui_dodajfiguredialog.h"

using namespace figury;
using namespace std;

DodajFigureDialog::DodajFigureDialog(QWidget *parent, figura *& fig, int * t) :
    QDialog(parent),
    ui(new Ui::DodajFigureDialog)
{
    ui->setupUi(this);
    f = &fig;
    type = t;
}

DodajFigureDialog::~DodajFigureDialog()
{
    delete ui;
}

void DodajFigureDialog::on_buttonBox_accepted()
{
    float nx = ui->textEdit_2->toPlainText().toFloat();
    float ny = ui->textEdit->toPlainText().toFloat();
    string str = ui->textEdit_3->toPlainText().toStdString();
    *type =ui->comboBox->currentIndex();
    switch(*type)
    {
    case 0:
        {
            *f = new trojkat(0, 0, 0, 0, 0, 0, str, nx, ny);
            break;
        }
    case 1:
        {
            *f = new kolo(0, str, nx, ny);
            break;
        }
    case 2:
        {
            *f = new pierscien(0, 0, str, nx, ny);
            break;
        }
    }
}
