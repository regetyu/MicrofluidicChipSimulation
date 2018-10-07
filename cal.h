#ifndef CAL_H
#define CAL_H

#include <QObject>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <math.h>
#include <QtDebug>
#include <QColor>
#include "statement.h"
using namespace std;
#define NAX 0.000000001

class Cal : public QObject
{
    Q_OBJECT
public:
    explicit Cal(QObject *parent = nullptr);
    edge edges[200];
    node nodes[200];
    vector< vector<double>> rect;
    bool *fr;
    int n,EDGESUM,NODESUM;
    vector <double> length;
    vector <double> width;
    vector <double> c;
    int i1, i2, o1, o2, o3;
    void setedgelength(int x, double leng);
    void addrect(vector<double> &tmp);
    int getdirline(int x, int y, int dir);
    bool existdir(int x, int y, int dir);
    bool _existdir(int x,int y, int dir);
    void recursionline(int x, int y, int dir, vector<double> &tmp,int end);
    bool recursionrect(int x, int y, vector<double> &tmp,int end);
    void findline(int x, int y,int t);
    void findrect(int x1);
    void initrect();
    int min (int a, int b) ;
    double GreatestCommonDivisor(double a, double b);
    double LeastCommonMultiple (double a, double b);
    void getans();
    void _getans();
    void caluconspeed(int num, vector<double>&length, int i1, int i2, int o1, int o2, int o3);
    void calc();
    bool WidthLegal(int i, int width);
signals:

public slots:
    void initialize(int, vector <double>, int, int, int, int, int);
    QColor color(int i, bool CalMode);
};

#endif // CAL_H
