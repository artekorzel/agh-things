#ifndef DODAJPIERSCIENDIALOG_H
#define DODAJPIERSCIENDIALOG_H

#include <QDialog>
#include"pierscien.h"

using namespace figury;

namespace Ui {
    class DodajPierscienDialog;
}

class DodajPierscienDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DodajPierscienDialog(QWidget *parent, pierscien *);
    ~DodajPierscienDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DodajPierscienDialog *ui;
    pierscien * p;
};

#endif // DODAJPIERSCIENDIALOG_H
