#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>
#include "adddialog.h"
#include "widthdialog.h"
#include "statement.h"
#include "cal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_add_triggered();

    void on_action_cal_triggered();

    void on_action_reset_triggered();

    void on_action_read_triggered();

    void on_action_save_triggered();

    void on_action_saveas_triggered();

    void on_action_help_triggered();

    void on_action_about_triggered();

signals:
    void initialize(int, vector <double>, int, int, int, int, int);

private:
    Ui::MainWindow *ui;
    Cal *cal;
    bool flag;
    bool caled;
    bool changed;
    bool CalMode;
    QString filename;

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
