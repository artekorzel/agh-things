#ifndef ZMIANAETYKIETYDIALOG_H
#define ZMIANAETYKIETYDIALOG_H

#include <QDialog>
#include"figura.h"

using namespace figury;

namespace Ui {
    class ZmianaEtykietyDialog;
}

class ZmianaEtykietyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZmianaEtykietyDialog(QWidget *parent, figura *);
    ~ZmianaEtykietyDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ZmianaEtykietyDialog *ui;
    figura * f;
};

#endif // ZMIANAETYKIETYDIALOG_H
