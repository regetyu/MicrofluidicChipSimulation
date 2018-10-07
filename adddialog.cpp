#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setFixedSize(700,500);
    connect(ui->ChipSize, SIGNAL(valueChanged(int)), this, SLOT(SetRange()));
    connect(ui->ChipSize, SIGNAL(valueChanged(int)), this, SLOT(CheckLegal()));
    connect(ui->i1, SIGNAL(valueChanged(int)), this, SLOT(CheckLegal()));
    connect(ui->i2, SIGNAL(valueChanged(int)), this, SLOT(CheckLegal()));
    connect(ui->o1, SIGNAL(valueChanged(int)), this, SLOT(CheckLegal()));
    connect(ui->o2, SIGNAL(valueChanged(int)), this, SLOT(CheckLegal()));
    connect(ui->o3, SIGNAL(valueChanged(int)), this, SLOT(CheckLegal()));
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::SetRange()
{
    ui->i1->setMaximum(ui->ChipSize->value());
    ui->i2->setMaximum(ui->ChipSize->value());
    ui->o1->setMaximum(ui->ChipSize->value());
    ui->o2->setMaximum(ui->ChipSize->value());
    ui->o3->setMaximum(ui->ChipSize->value());
}

int AddDialog::GetNum()
{
    return (ui->ChipSize->value());
}

int AddDialog::Geti1()
{
    if(ui->i1->value()<ui->i2->value())
        return (ui->i1->value());
    else
        return (ui->i2->value());
}

int AddDialog::Geti2()
{
    if(ui->i1->value()<ui->i2->value())
        return (ui->i2->value());
    else
        return (ui->i1->value());
}

int AddDialog::Geto1()
{
    if(ui->o1->value()<ui->o2->value()&&ui->o1->value()<ui->o3->value())
        return (ui->o1->value());
    else if(ui->o2->value()<ui->o3->value())
        return (ui->o2->value());
    else
        return (ui->o3->value());
}

int AddDialog::Geto2()
{
    if((ui->o2->value()>ui->o1->value()&&ui->o2->value()<ui->o3->value())||(ui->o2->value()<ui->o1->value()&&ui->o2->value()>ui->o3->value()))
        return (ui->o2->value());
    else if((ui->o1->value()>ui->o2->value()&&ui->o1->value()<ui->o3->value())||(ui->o1->value()<ui->o2->value()&&ui->o1->value()>ui->o3->value()))
        return (ui->o1->value());
    else
        return ui->o3->value();
}

int AddDialog::Geto3()
{
    if(ui->o3->value()>ui->o1->value()&&ui->o3->value()>ui->o2->value())
        return (ui->o3->value());
    else if (ui->o2->value()>ui->o1->value())
        return (ui->o2->value());
    else
        return ui->o1->value();
}

void AddDialog::CheckLegal()
{
    if(ui->i1->value() == ui->i2->value() || ui->o1->value() == ui->o2->value() || ui->o1->value() == ui->o3->value() || ui->o2->value() == ui->o3->value()||ui->ChipSize->value()<5)
        ui->Ok->setEnabled(false);
    else
        ui->Ok->setEnabled(true);
}
