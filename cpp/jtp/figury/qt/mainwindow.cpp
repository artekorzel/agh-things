#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int pom = -1;
    figura* f;
    DodajFigureDialog dial(this, f, &pom);
    dial.exec();
    switch(pom)
    {
    case 0:
    {
	DodajTrojkatDialog dial2(this, dynamic_cast<trojkat *>(f));
	dial2.exec();
	break;
    }
    case 1:
    {
	DodajKoloDialog dial2(this, dynamic_cast<kolo *>(f));
	dial2.exec();
	break;
    }
    case 2:
    {
	DodajPierscienDialog dial2(this, dynamic_cast<pierscien *>(f));
	dial2.exec();
	break;
    }
    }    
    wekt.push_back(f);
    ui->listWidget->addItem(QString::fromStdString(f->opis()));
}

void MainWindow::on_pushButton_4_clicked()
{
    int tmp = ui->listWidget->currentRow();
    if(tmp != -1)
	QMessageBox::information(this, "Pole", QString::number(wekt[tmp]->pole()));
}

void MainWindow::on_pushButton_3_clicked()
{
    int tmp = ui->listWidget->currentRow();
    if(tmp != -1)
    {
	ZmianaEtykietyDialog dial(this, wekt[tmp]);
	dial.exec();
	ui->listWidget->item(tmp)->setText(QString::fromStdString(wekt[tmp]->opis()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int tmp = ui->listWidget->currentRow();
    if(tmp != -1)
    {
	delete ui->listWidget->takeItem(tmp);
	delete wekt[tmp];
	for(int i = tmp + 1; i < wekt.size(); ++i)
	    wekt[i - 1] = wekt[i];
	wekt.pop_back();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int tmp = ui->listWidget->currentRow();
    if(tmp != -1)
    {
	QString plik = QFileDialog::getOpenFileName(this);
	ifstream Martyna(plik.toStdString().c_str());
	wekt[tmp]->wczytaj(Martyna);
	ui->listWidget->item(tmp)->setText(QString::fromStdString(wekt[tmp]->opis()));
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    int tmp = ui->listWidget->currentRow();
    if(tmp != -1)
    {
	QString plik = QFileDialog::getSaveFileName(this);
	ofstream Martyna(plik.toStdString().c_str());
	wekt[tmp]->zapisz(Martyna);
    }
}

void MainWindow::on_actionZamknij_triggered()
{
    QApplication::exit();
}
