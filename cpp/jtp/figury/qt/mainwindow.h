#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
#include"figura.h"
#include"punkt.h"
#include"kolo.h"
#include"pierscien.h"
#include"trojkat.h"
#include"dodajfiguredialog.h"
#include"dodajkolodialog.h"
#include"dodajpiersciendialog.h"
#include"dodajtrojkatdialog.h"
#include"zmianaetykietydialog.h"
#include<fstream>
#include<QMessageBox>
#include<QFileDialog>

using namespace figury;
using namespace std;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_actionZamknij_triggered();

private:
    Ui::MainWindow *ui;
    vector<figura*> wekt;
};

#endif // MAINWINDOW_H
