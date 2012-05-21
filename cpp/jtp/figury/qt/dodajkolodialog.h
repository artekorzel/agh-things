#ifndef DODAJKOLODIALOG_H
#define DODAJKOLODIALOG_H

#include <QDialog>
#include"kolo.h"

using namespace figury;

namespace Ui {
    class DodajKoloDialog;
}

class DodajKoloDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DodajKoloDialog(QWidget *parent, kolo *);
    ~DodajKoloDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DodajKoloDialog *ui;
    kolo * k;
};

#endif // DODAJKOLODIALOG_H
