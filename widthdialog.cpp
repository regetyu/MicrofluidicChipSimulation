#include "widthdialog.h"
#include "ui_widthdialog.h"

WidthDialog::WidthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WidthDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setFixedSize(550,225);
}

WidthDialog::~WidthDialog()
{
    delete ui;
}

void WidthDialog::initialize(double width)
{
    ui->spinBox->setValue(width);
}

double WidthDialog::GetWidth()
{
    return (ui->spinBox->value());
}

void WidthDialog::on_horizontalSlider_valueChanged(int value)
{
    if(value==ui->spinBox->value())
        return;
    else
        ui->spinBox->setValue(value);
}

void WidthDialog::on_spinBox_valueChanged(int arg1)
{
    if(arg1==ui->horizontalSlider->value())
        return;
    else
        ui->horizontalSlider->setValue(arg1);
}
