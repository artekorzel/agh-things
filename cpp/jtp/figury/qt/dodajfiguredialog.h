#ifndef DODAJFIGUREDIALOG_H
#define DODAJFIGUREDIALOG_H

#include <QDialog>
#include"figura.h"
#include"punkt.h"
#include"kolo.h"
#include"pierscien.h"
#include"trojkat.h"
#include<string>

using namespace figury;

namespace Ui {
    class DodajFigureDialog;
}

class DodajFigureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DodajFigureDialog(QWidget *parent, figura *&, int *);
    ~DodajFigureDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DodajFigureDialog *ui;
    figura ** f;
    int * type;
};

#endif // DODAJFIGUREDIALOG_H
