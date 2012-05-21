#ifndef DODAJTROJKATDIALOG_H
#define DODAJTROJKATDIALOG_H

#include <QDialog>
#include"trojkat.h"

using namespace figury;

namespace Ui {
    class DodajTrojkatDialog;
}

class DodajTrojkatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DodajTrojkatDialog(QWidget *parent, trojkat *);
    ~DodajTrojkatDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DodajTrojkatDialog *ui;
    trojkat * t;
};

#endif // DODAJTROJKATDIALOG_H
