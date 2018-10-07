#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    cal = new Cal(this);
    ui->setupUi(this);
    setFixedSize(1000,1000);
    flag=false;
    caled=false;
    changed=false;
    CalMode=velocity;
    ui->label->hide();
    ui->label_1->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->action_cal->setEnabled(false);
    ui->action_reset->setEnabled(false);
    ui->action_save->setEnabled(false);
    ui->action_saveas->setEnabled(false);
    connect(this, SIGNAL(initialize(int, vector <double>, int, int, int, int, int)), cal, SLOT(initialize(int, vector <double>, int, int, int, int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_add_triggered()
{
    if(changed)
    {
        QMessageBox box(QMessageBox::Warning, "警告", "是否保存更改?",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,this);
        box.setFixedSize(578,193);
        switch(box.exec())
        {
        case(QMessageBox::Save):
            emit ui->action_save->triggered();
            break;
        case(QMessageBox::Discard):
            break;
        default:
            return;
        }
    }
    AddDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted)
    {
        int num = dialog.GetNum();
        int size = 2 * num * num - 2 * num + 5;
        vector <double> length;
        for(int i=0; i<size; i++)
            length.push_back(1);
        int i1 = dialog.Geti1()-1;
        int i2 = dialog.Geti2()-1;
        int o1 = dialog.Geto1()-1;
        int o2 = dialog.Geto2()-1;
        int o3 = dialog.Geto3()-1;
        emit initialize(num, length, i1, i2, o1, o2, o3);
        filename="";
        changed=true;
        int x=x_blank*2+(cal->n-1)*(len+wid)+wid;
        int y=y_blank*2+(cal->n-1)*(len+wid)+wid;
        setFixedSize(x,y);
        flag = true;
        caled = false;
        ui->label_6->setGeometry(x-125,y_blank-150,100,100);
        ui->label_5->setGeometry(x-100,y_blank+350,100,100);
        ui->label_7->setGeometry(x-100,y_blank-200,300,100);
        ui->label_8->setGeometry(10,height()-225,300,100);
        ui->label->hide();
        ui->label_1->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->label_8->hide();
        ui->action_cal->setEnabled(true);
        ui->action_reset->setEnabled(false);
        ui->action_save->setEnabled(true);
        ui->action_saveas->setEnabled(true);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(flag)
    {
        QPainter painter(this);
        for(int i=0; i< (cal->n * cal->n - cal->n); i++)
        {
            if(cal->length[i]>=NAX)
            {
                if(caled)
                    painter.setBrush(cal->color(i,CalMode));
                painter.drawRect(x_blank + i/(cal->n-1)*(len+wid)+wid/2-cal->width[i]/40, y_blank + i%(cal->n-1)*(len+wid)+wid, cal->width[i]/20, len);
            }
        }
        for(int i=0; i< (cal->n * cal->n - cal->n); i++)
        {
            if(cal->length[i+cal->n * cal->n - cal->n]>=NAX)
                {
                if(caled)
                      painter.setBrush(cal->color(i+cal->n * cal->n - cal->n,CalMode));
                      painter.drawRect(x_blank + i/(cal->n)*(len+wid)+wid, y_blank + i%(cal->n)*(len+wid)+wid/2-cal->width[i+cal->n * cal->n - cal->n]/40,len, cal->width[i+cal->n * cal->n - cal->n]/20);
            }

        }
        if(caled)
            painter.setBrush(cal->color(cal->EDGESUM-5,CalMode));
        painter.drawRect(x_blank +cal->i1*(len+wid)+wid/2-cal->width[cal->EDGESUM-5]/40, y_blank-len, cal->width[cal->EDGESUM-5]/20, len);
        if(caled)
            painter.setBrush(cal->color(cal->EDGESUM-4,CalMode));
        painter.drawRect(x_blank +cal->i2*(len+wid)+wid/2-cal->width[cal->EDGESUM-4]/40, y_blank-len, cal->width[cal->EDGESUM-4]/20, len);
        if(caled)
            painter.setBrush(cal->color(cal->EDGESUM-3,CalMode));
        painter.drawRect(x_blank +cal->o1*(len+wid)+wid/2-cal->width[cal->EDGESUM-3]/40, y_blank+(cal->n-1)*(len+wid)+wid, cal->width[cal->EDGESUM-3]/20, len);
        if(caled)
            painter.setBrush(cal->color(cal->EDGESUM-2,CalMode));
        painter.drawRect(x_blank +cal->o2*(len+wid)+wid/2-cal->width[cal->EDGESUM-2]/40, y_blank+(cal->n-1)*(len+wid)+wid, cal->width[cal->EDGESUM-2]/20, len);
        if(caled)
            painter.setBrush(cal->color(cal->EDGESUM-1,CalMode));
        painter.drawRect(x_blank +cal->o3*(len+wid)+wid/2-cal->width[cal->EDGESUM-1]/40, y_blank+(cal->n-1)*(len+wid)+wid, cal->width[cal->EDGESUM-1]/20, len);

        painter.setBrush(QColor(0,0,0));
        for(int i=0;i<cal->n*cal->n; i++)
            painter.drawRect(x_blank + i/cal->n*(len+wid), y_blank+ i%cal->n*(len+wid), wid, wid);
        if(caled)
        {
            for(int i=0; i<255; i++)
            {
                painter.setPen(QColor(255-i,0,i));
                painter.setBrush(QColor(255-i,0,i));
                painter.drawRect(x_blank*2+(cal->n-1)*(len+wid)+wid-75,y_blank+i,50,1);
            }
            for(int i=0; i<=255; i++)
            {
                painter.setPen(QColor(0,i,255-i));
                painter.setBrush(QColor(0,i,255-i));
                painter.drawRect(x_blank*2+(cal->n-1)*(len+wid)+wid-75,y_blank+i+255,50,1);
            }
        }
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(flag&&!caled)
        //if(event->button()==Qt::LeftButton)
        {
            for(int i=0; i<cal->n; i++)
                for(int k=0; k<cal->n-1; k++)
                    if((event->x()>=x_blank+i*(len+wid)+wid/2-cal->width[i*(cal->n-1)+k]/40||event->x()>=x_blank+i*(len+wid))&&(event->x()<x_blank+i*(len+wid)+wid/2+cal->width[i*(cal->n-1)+k]/40||event->x()<x_blank+i*(len+wid)+wid)&&event->y()>=y_blank+wid+k*(len+wid)&&event->y()<y_blank+k*(len+wid)+len)
                    {
                        if(event->button()==Qt::LeftButton)
                        {
                            if(cal->length[i*(cal->n-1)+k]>=NAX)
                            {
                                cal->length[i*(cal->n-1)+k]=0;
                                cal->width[i*(cal->n-1)+k]=200;
                                changed=true;
                                repaint();
                            }
                            else
                            {
                                cal->length[i*(cal->n-1)+k]=1;
                                changed=true;
                                repaint();
                            }
                        }
                        if(event->button()==Qt::RightButton)
                        {
                            if(cal->length[i*(cal->n-1)+k]>=NAX)
                            {
                                WidthDialog dialog(this);
                                dialog.initialize(cal->width[i*(cal->n-1)+k]);
                                if(dialog.exec()==QDialog::Accepted)
                                {
                                    if(cal->WidthLegal(i*(cal->n-1)+k, dialog.GetWidth()))
                                    {
                                        cal->width[i*(cal->n-1)+k]=dialog.GetWidth();
                                        changed=true;
                                    }
                                    else
                                    {
                                        QMessageBox box(QMessageBox::Critical,"错误", "宽度输入不合法",QMessageBox::Ok,this);
                                        box.exec();
                                    }

                                    repaint();
                                }
                            }
                        }
                    }
            for(int i=0; i<cal->n; i++)
                for(int k=0; k<cal->n-1; k++)
                    if((event->y()>=y_blank+i*(len+wid)+wid/2-cal->width[cal->n*(cal->n-1)+k*(cal->n)+i]/40||event->y()>=y_blank+i*(len+wid))&&(event->y()<y_blank+i*(len+wid)+wid/2+cal->width[cal->n*(cal->n-1)+k*(cal->n)+i]/40||event->y()<y_blank+i*(len+wid)+wid)&&event->x()>=x_blank+wid+k*(len+wid)&&event->x()<x_blank+k*(len+wid)+len)
                    {
                        if(event->button()==Qt::LeftButton)
                        {
                            if(cal->length[cal->n*(cal->n-1)+k*(cal->n)+i]>=NAX)
                            {
                                cal->length[cal->n*(cal->n-1)+k*(cal->n)+i]=0;
                                cal->width[cal->n*(cal->n-1)+k*(cal->n)+i]=200;
                                changed=true;
                                repaint();
                            }
                            else
                            {
                                cal->length[cal->n*(cal->n-1)+k*(cal->n)+i]=1;
                                changed=true;
                                repaint();
                            }
                        }
                        if(event->button()==Qt::RightButton)
                        {
                            if(cal->length[cal->n*(cal->n-1)+k*(cal->n)+i]>=NAX)
                            {
                                WidthDialog dialog(this);
                                dialog.initialize(cal->width[cal->n*(cal->n-1)+k*(cal->n)+i]);
                                if(dialog.exec()==QDialog::Accepted)
                                {
                                    if(cal->WidthLegal(cal->n*(cal->n-1)+k*(cal->n)+i,dialog.GetWidth()))
                                    {
                                        cal->width[cal->n*(cal->n-1)+k*(cal->n)+i]=dialog.GetWidth();
                                        changed=true;
                                    }
                                    else
                                    {
                                        QMessageBox box(QMessageBox::Critical,"错误", "宽度输入不合法",QMessageBox::Ok,this);
                                        box.exec();
                                    }
                                    repaint();
                                }
                            }
                        }
                    }
            if(event->button()==Qt::RightButton)
            {
                if((event->x()>=x_blank +cal->i1*(len+wid)+wid/2-cal->width[cal->EDGESUM-5]/40||event->x()>=x_blank +cal->i1*(len+wid))&&(event->x()<x_blank +cal->i1*(len+wid)+wid/2+cal->width[cal->EDGESUM-5]/40||event->x()<x_blank +cal->i1*(len+wid)+wid)&&event->y()>=y_blank-len&&event->y()<y_blank)
                {
                    WidthDialog dialog(this);
                    dialog.initialize(cal->width[cal->EDGESUM-5]);
                    if(dialog.exec()==QDialog::Accepted)
                    {
                        if(cal->WidthLegal(cal->EDGESUM-5,dialog.GetWidth()))
                        {
                            cal->width[cal->EDGESUM-5]=dialog.GetWidth();
                            changed=true;
                        }
                        else
                        {
                            QMessageBox box(QMessageBox::Critical,"错误", "宽度输入不合法",QMessageBox::Ok,this);
                            box.exec();
                        }
                        repaint();
                    }
                }
                if((event->x()>=x_blank +cal->i2*(len+wid)+wid/2-cal->width[cal->EDGESUM-4]/40||event->x()>=x_blank +cal->i2*(len+wid))&&(event->x()<x_blank +cal->i2*(len+wid)+wid/2+cal->width[cal->EDGESUM-4]/40||event->x()<x_blank +cal->i2*(len+wid)+wid)&&event->y()>=y_blank-len&&event->y()<y_blank)
                {
                    WidthDialog dialog(this);
                    dialog.initialize(cal->width[cal->EDGESUM-4]);
                    if(dialog.exec()==QDialog::Accepted)
                    {
                        if(cal->WidthLegal(cal->EDGESUM-4,dialog.GetWidth()))
                        {
                            cal->width[cal->EDGESUM-4]=dialog.GetWidth();
                            changed=true;
                        }
                        else
                        {
                            QMessageBox box(QMessageBox::Critical,"错误", "宽度输入不合法",QMessageBox::Ok,this);
                            box.exec();
                        }
                        repaint();
                    }
                }
                if((event->x()>=x_blank +cal->o1*(len+wid)+wid/2-cal->width[cal->EDGESUM-3]/40||event->x()>=x_blank +cal->o1*(len+wid))&&(event->x()<x_blank +cal->o1*(len+wid)+wid/2+cal->width[cal->EDGESUM-3]/40||event->x()<x_blank +cal->o1*(len+wid)+wid)&&event->y()>=y_blank+(cal->n-1)*(len+wid)+wid&&event->y()<y_blank+(cal->n-1)*(len+wid)+wid+len)
                {
                    WidthDialog dialog(this);
                    dialog.initialize(cal->width[cal->EDGESUM-3]);
                    if(dialog.exec()==QDialog::Accepted)
                    {
                        if(cal->WidthLegal(cal->EDGESUM-3,dialog.GetWidth()))
                        {
                            cal->width[cal->EDGESUM-3]=dialog.GetWidth();
                            changed=true;
                        }
                        else
                        {
                            QMessageBox box(QMessageBox::Critical,"错误", "宽度输入不合法",QMessageBox::Ok,this);
                            box.exec();
                        }
                        repaint();
                    }
                }
                if((event->x()>=x_blank +cal->o2*(len+wid)+wid/2-cal->width[cal->EDGESUM-2]/40||event->x()>=x_blank +cal->o2*(len+wid))&&(event->x()<x_blank +cal->o2*(len+wid)+wid/2+cal->width[cal->EDGESUM-2]/40||event->x()<x_blank +cal->o2*(len+wid)+wid)&&event->y()>=y_blank+(cal->n-1)*(len+wid)+wid&&event->y()<y_blank+(cal->n-1)*(len+wid)+wid+len)
                {
                    WidthDialog dialog(this);
                    dialog.initialize(cal->width[cal->EDGESUM-2]);
                    if(dialog.exec()==QDialog::Accepted)
                    {
                        if(cal->WidthLegal(cal->EDGESUM-2,dialog.GetWidth()))
                        {
                            cal->width[cal->EDGESUM-2]=dialog.GetWidth();
                            changed=true;
                        }
                        else
                        {
                            QMessageBox box(QMessageBox::Critical,"错误", "宽度输入不合法",QMessageBox::Ok,this);
                            box.exec();
                        }
                        repaint();
                    }
                }
                if((event->x()>=x_blank +cal->o3*(len+wid)+wid/2-cal->width[cal->EDGESUM-1]/40||event->x()>=x_blank +cal->o3*(len+wid))&&(event->x()<x_blank +cal->o3*(len+wid)+wid/2+cal->width[cal->EDGESUM-1]/40||event->x()<x_blank +cal->o3*(len+wid)+wid)&&event->y()>=y_blank+(cal->n-1)*(len+wid)+wid&&event->y()<y_blank+(cal->n-1)*(len+wid)+wid+len)
                {
                    WidthDialog dialog(this);
                    dialog.initialize(cal->width[cal->EDGESUM-1]);
                    if(dialog.exec()==QDialog::Accepted)
                    {
                        if(cal->WidthLegal(cal->EDGESUM-1,dialog.GetWidth()))
                        {
                            cal->width[cal->EDGESUM-1]=dialog.GetWidth();
                            changed=true;
                        }
                        else
                        {
                            QMessageBox box(QMessageBox::Critical,"错误", "宽度输入不合法",QMessageBox::Ok,this);
                            box.exec();
                        }
                        repaint();
                    }
                }
            }

        }
}


void MainWindow::on_action_cal_triggered()
{
    vector<double> _length;
    for(int i=0; i<cal->length.size(); i++)
    {
        _length.push_back(cal->length[i]/cal->width[i]);
    }
    cal->caluconspeed(cal->n, _length,cal->i1,cal->i2,cal->o1,cal->o2,cal->o3);
    caled=true;
    if(CalMode==velocity)
    {
        ui->label->setText("出口流速:");
        ui->label_7->setText("流速");
        ui->label_6->setText("400");
        ui->label_6->setGeometry(x_blank*2+(cal->n-1)*(len+wid)+wid-125,y_blank-150,100,100);
        ui->label_1->setText(QString::number(cal->edges[cal->EDGESUM-3].v,'g',3));
        ui->label_2->setText(QString::number(cal->edges[cal->EDGESUM-2].v,'g',3));
        ui->label_3->setText(QString::number(cal->edges[cal->EDGESUM-1].v,'g',3));
        repaint();
    }
    else
    {
        CalMode=concentration;
        ui->label->setText("出口浓度:");
        ui->label_7->setText("浓度");
        ui->label_6->setText("1");
        ui->label_6->setGeometry(x_blank*2+(cal->n-1)*(len+wid)+wid-100,y_blank-150,100,100);
        ui->label_1->setText(QString::number(cal->c[cal->EDGESUM-3],'g',3));
        ui->label_2->setText(QString::number(cal->c[cal->EDGESUM-2],'g',3));
        ui->label_3->setText(QString::number(cal->c[cal->EDGESUM-1],'g',3));
        repaint();
    }
    ui->label->show();
    ui->label_1->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->show();
    ui->label_6->show();
    ui->label_7->show();
    ui->label_8->show();
    ui->action_cal->setEnabled(false);
    ui->action_reset->setEnabled(true);
    repaint();
}

void MainWindow::on_action_reset_triggered()
{
    caled = false;
    ui->label->hide();
    ui->label_1->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->action_cal->setEnabled(true);
    ui->action_reset->setEnabled(false);
    repaint();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(changed)
    {
        QMessageBox box(QMessageBox::Warning, "警告", "是否保存更改?",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,this);
        box.setFixedSize(578,193);
        switch(box.exec())
        {
        case(QMessageBox::Save):
            emit ui->action_save->triggered();
            break;
        case(QMessageBox::Discard):
            break;
        default:
            event->ignore();
        }
    }
}

void MainWindow::on_action_read_triggered()
{
    if(changed)
    {
        QMessageBox box(QMessageBox::Warning, "警告", "是否保存更改?",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,this);
        box.setFixedSize(578,193);
        switch(box.exec())
        {
        case(QMessageBox::Save):
            emit ui->action_save->triggered();
            break;
        case(QMessageBox::Discard):
            break;
        default:
            return;
        }
    }
    QString FileName = QFileDialog::getOpenFileName(this,
          tr("读取已有芯片"), "", tr("Chip Information Files (*.chip)"));
    if(FileName!="")
    {
        filename=FileName;
        changed=false;
        QFile file(FileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream str(&file);
        int n,i1,i2,o1,o2,o3;
        str>>n>>i1>>i2>>o1>>o2>>o3;
        int size = 2 * n * n - 2 * n + 5;
        vector <double> length;
        for(int i=0; i<size; i++)
            length.push_back(1);
        emit initialize(n, length, i1, i2, o1, o2, o3);
        cal->length.clear();
        cal->width.clear();
        for(int i=0;i<size;i++)
        {
            double a;
            str>>a;
            cal->length.push_back(a);
        }
        for(int i=0;i<size;i++)
        {
            double a;
            str>>a;
            cal->width.push_back(a);
        }
        int x=x_blank*2+(cal->n-1)*(len+wid)+wid;
        int y=y_blank*2+(cal->n-1)*(len+wid)+wid;
        setFixedSize(x,y);
        flag = true;
        caled = false;
        ui->label_6->setGeometry(x-125,y_blank-150,100,100);
        ui->label_5->setGeometry(x-100,y_blank+350,100,100);
        ui->label_7->setGeometry(x-100,y_blank-200,300,100);
        ui->label_8->setGeometry(10,height()-225,300,100);
        ui->label->hide();
        ui->label_1->hide();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->action_cal->setEnabled(true);
        ui->action_reset->setEnabled(false);
        ui->action_save->setEnabled(true);
        ui->action_saveas->setEnabled(true);
        repaint();
    }
}

void MainWindow::on_action_save_triggered()
{
    if(changed)
    {
        if(filename=="")
            emit ui->action_saveas->triggered();
        else
        {
            QFile file(filename);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream str(&file);
            str<<cal->n<<" "<<cal->i1<<" "<<cal->i2<<" "<<cal->o1<<" "<<cal->o2<<" "<<cal->o3<<endl;
            for(int i=0;i<cal->EDGESUM;i++)
            {
                str<<cal->length[i]<<" ";
            }
            str<<endl;
            for(int i=0; i<cal->EDGESUM;i++)
            {
                str<<cal->width[i]<<" ";
            }
            file.close();
            changed=false;
        }
    }
}

void MainWindow::on_action_saveas_triggered()
{
    QString FileName = QFileDialog::getSaveFileName(this,tr("另存为"),"",tr("Chip Information Files(*.chip)"));
    if(FileName!="")
    {
        filename=FileName;
        changed=false;
        QFile file(FileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream str(&file);
        str<<cal->n<<" "<<cal->i1<<" "<<cal->i2<<" "<<cal->o1<<" "<<cal->o2<<" "<<cal->o3<<endl;
        for(int i=0;i<cal->EDGESUM;i++)
        {
            str<<cal->length[i]<<" ";
        }
        str<<endl;
        for(int i=0; i<cal->EDGESUM;i++)
        {
            str<<cal->width[i]<<" ";
        }
        file.close();
    }
}

void MainWindow::on_action_help_triggered()
{
    QMessageBox box(QMessageBox::Question,"帮助","左键点击管道: 修改管道有无\n右键点击管道: 修改管道宽度\n回车: 计算流速和浓度\n左右方向键: 流速和浓度切换\n退格: 重新修改",QMessageBox::Ok,this);
    box.exec();
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::about(this,"关于","Microfluidic Chip Simulation\n编译环境:Qt 5.11.1 MinGW 32bit\n");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(caled)
    {
        if((event->key()==Qt::Key_Left||event->key()==Qt::Key_Right)&&CalMode==velocity)
        {
            CalMode=concentration;
            ui->label->setText("出口浓度:");
            ui->label_7->setText("浓度");
            ui->label_6->setText("1");
            ui->label_6->setGeometry(x_blank*2+(cal->n-1)*(len+wid)+wid-100,y_blank-150,100,100);
            ui->label_1->setText(QString::number(cal->c[cal->EDGESUM-3],'g',3));
            ui->label_2->setText(QString::number(cal->c[cal->EDGESUM-2],'g',3));
            ui->label_3->setText(QString::number(cal->c[cal->EDGESUM-1],'g',3));
            repaint();
        }
        else if((event->key()==Qt::Key_Left||event->key()==Qt::Key_Right)&&CalMode==concentration)
        {
            CalMode=velocity;
            ui->label->setText("出口流速:");
            ui->label_7->setText("流速");
            ui->label_6->setText("400");
            ui->label_6->setGeometry(x_blank*2+(cal->n-1)*(len+wid)+wid-125,y_blank-150,100,100);
            ui->label_1->setText(QString::number(cal->edges[cal->EDGESUM-3].v,'g',3));
            ui->label_2->setText(QString::number(cal->edges[cal->EDGESUM-2].v,'g',3));
            ui->label_3->setText(QString::number(cal->edges[cal->EDGESUM-1].v,'g',3));
            repaint();
        }
    }
}
