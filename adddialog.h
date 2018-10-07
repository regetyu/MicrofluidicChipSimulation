#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
    int GetNum();
    int Geti1();
    int Geti2();
    int Geto1();
    int Geto2();
    int Geto3();

private:
    Ui::AddDialog *ui;

public slots:
    void SetRange();
    void CheckLegal();
};

#endif // ADDDIALOG_H
