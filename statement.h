#ifndef STATEMENT_H
#define STATEMENT_H
#include <vector>
#pragma execution_character_set("utf-8")
using namespace std;
#define NAX 0.000000001
#define velocity true
#define concentration false

const static int x_blank = 200;
const static int y_blank = 200;
const static int len = 80;
const static int wid = 10;

struct edge
{
    double v; //流速
    double leng; //管道长度
    int n1,n2;
};

struct node
{
    vector<int> elist;  //点所连接的边，按照顺时针的顺序存储下来
};



#endif // STATEMENT_H
