#include "cal.h"

Cal::Cal(QObject *parent)
{

}

void Cal::setedgelength(int x, double leng)
{
    edges[x].leng = leng;
}

void Cal::addrect(vector<double> &tmp){
    rect.push_back(tmp);
}

int Cal::getdirline(int x, int y, int dir){
    int e;
    int sum = x*n+y;
    if (dir == 0){
        if (y==0){
            if (edges[EDGESUM-5].n2 == sum)
                e = EDGESUM-5;
            else if (edges[EDGESUM-4].n2 == sum)
                e = EDGESUM-4;
            else
                e = EDGESUM;
        }
        else
            e=(x*(n-1)+y-1);
    }else if (dir == 1){
        if (x==n-1)
            e=EDGESUM;
        else
            e=n*n-n+x*n+y;
    }else if (dir == 2){
        if (y==n-1){
            if (edges[EDGESUM-3].n1 == sum)
                e = EDGESUM-3;
            else if (edges[EDGESUM-2].n1 == sum)
                e = EDGESUM-2;
            else if (edges[EDGESUM-1].n1 == sum)
                e = EDGESUM-1;
            else
                e = EDGESUM;
        }
        else
            e=(x*(n-1)+y);
    }else if (dir == 3){
        if (x==0)
            e=EDGESUM;
        else
            e=n*n-n+(x-1)*n+y;
    }
    return e;
}

bool Cal::existdir(int x, int y, int dir)
{
    int e = getdirline(x,y,dir);
    if (e>=EDGESUM)
        return false;
    return (edges[e].leng!=0);
}

bool Cal::_existdir(int x,int y,int dir)
{
    int e = getdirline(x,y,dir);
    if (e>=EDGESUM)
        return false;
    return (edges[e].v!=0);
}

void Cal::recursionline(int x, int y, int dir, vector<double> &tmp,int end){
    int e = getdirline(x,y,dir);
    if (e>EDGESUM-6)
        return;
    int nodeno = x*n+y;
    int x1;
    if (edges[e].n1 == nodeno){
        tmp[e] = edges[e].leng;
        x1 = edges[e].n2;
    }
    else{
        tmp[e] = -edges[e].leng;
        x1 = edges[e].n1;
    }

    if (e == end){
        addrect(tmp);
        return;
    }
    if (dir == 0){
        y--;
    }else if (dir == 1){
        x++;
    }else if (dir == 2){
        y++;
    }else if (dir == 3){
        x--;
    }
    for(int i=0; i<4; i++)
    {
        int newdir = dir+1-i;
        newdir = (newdir+4)%4;
        if (existdir(x,y,newdir))
        {
            recursionline(x,y,newdir,tmp,end);
            break;
        }
    }
}

bool Cal::recursionrect(int x, int y, vector<double> &tmp,int end){
    int xx,yy;
    for(int i=1; i<5; i++)
    {
        int e =  getdirline(x,y,i%4);
        int dir = i%4;
        if (e>=EDGESUM)
            continue;
        if (fr[e])
            continue;
        if (edges[e].leng==0)
            continue;
        fr[e] = true;
        int nodeno = x*n+y;
        int x1;
        if (edges[e].n1 == nodeno){
            tmp[e] = edges[e].leng;
            x1 = edges[e].n2;
        }
        else{
            tmp[e] = -edges[e].leng;
            x1 = edges[e].n1;
        }
        if (e == end){
            return true;
        }
        if (e>EDGESUM-5){
            tmp[e] = 0;
            continue;
        }

        if (dir == 0){
            xx=x;yy=y-1;
        }else if (dir == 1){
            xx=x+1;yy=y;
        }else if (dir == 2){
            xx=x;yy=y+1;
        }else if (dir == 3){
            xx=x-1;yy=y;
        }
        if (recursionrect(xx,yy,tmp,end))
            return true;
        tmp[e] = 0;
    }
    return false;
}

void Cal::findline(int x, int y,int t){
    vector<double> tmp(EDGESUM+1,0);
    recursionline(x,y,1,tmp,t);
}

void Cal::findrect(int x1){
    vector<double> tmp(EDGESUM+1,0);
    for (int i=0; i<EDGESUM; i++)
        fr[i] = false;
    recursionrect(edges[x1].n2/n,0,tmp,EDGESUM-1);
    vector<double> temp(EDGESUM+1,0);
    for (int i=0; i<EDGESUM; i++)
        fr[i] = false;
    recursionrect(edges[x1].n2/n,0,temp,EDGESUM-2);
    vector<double> tep(EDGESUM+1,0);
    for (int i=0; i<EDGESUM; i++)
        fr[i] = false;
    recursionrect(edges[x1].n2/n,0,tep,EDGESUM-3);
    vector<double> emp(EDGESUM+1,0);
    for (int i=0; i<EDGESUM+1; i++)
        emp[i] = tmp[i]-temp[i];
    rect.push_back(emp);
    vector<double> tem(EDGESUM+1,0);
    for (int i=0; i<EDGESUM+1; i++)
        tem[i] = tep[i]-temp[i];
    rect.push_back(tem);
}


void Cal::initrect(){
    for (int i=0;i<EDGESUM-5; i++)
        if (edges[i].leng == 0)
        {
            vector<double> tmp(EDGESUM+1,0);
            tmp[i]=1;
            addrect(tmp);
        }
    for (int i=0; i<NODESUM-2; i++)
    {
        int number = 0;
        vector<double> tmp(EDGESUM+1,0);
        for (int j=0; j<nodes[i].elist.size(); j++)
        if (edges[nodes[i].elist[j]].leng!=0)
        {
            number++;
            if (edges[nodes[i].elist[j]].n1 == i)
                tmp[nodes[i].elist[j]] = 1;
            else
                tmp[nodes[i].elist[j]] = -1;
        }
        tmp[EDGESUM] = 0;
        if (number>0)
            addrect(tmp);
    }
    for (int i=0; i<n-1; i++)
        for (int j=0; j<n-1; j++)
        {
            int t = i*(n-1)+j;
            int m = n*n-n+i*n+j;
            if (edges[t].leng !=0 && edges[m].leng !=0)
                    findline(i,j,t);
        }
    findrect(EDGESUM-4);
    vector<double> tmp(EDGESUM+1,0);
    tmp[EDGESUM-5] = 1;
    tmp[EDGESUM] = width[EDGESUM-5];
    addrect(tmp);
    vector<double> temp(EDGESUM+1,0);
    temp[EDGESUM-4] = 1;
    temp[EDGESUM] =width[EDGESUM-4];
    addrect(temp);

}
int Cal::min (int a, int b)  {
    if (a>b)
        return b;
    else
        return a;
}


double Cal::GreatestCommonDivisor(double a, double b)
{
    double t;
    if (a < b)
    {
        t = a;
        a = b;
        b = t;
    }
    if (b==1)
        return 1;
    while (abs(b) >= NAX)
    {
        t = fmod(a , b);
        a = b;
        b = t;
    }
    return a;
}

double Cal::LeastCommonMultiple (double a, double b)

{
    double c = GreatestCommonDivisor(a,b);
    double t = a  /c * b;
    return t;

}

void Cal::getans()
{
    int n = rect.size();

    for (int i=0; i<n; i++)
        for (int j=0; j<EDGESUM+1; j++)
            if (abs(rect[i][j])<NAX)
                rect[i][j] = 0;

    int num = 0;
    for (int i=0; i<n; i++){
        if (abs(rect[i][num]) <NAX){
            int mjj = 0;
            for (int j=i+1; j<n; j++)
                if ( !(abs(rect[j][num])<NAX))
                {
                    mjj++;
                    for (int k=0; k<EDGESUM+1; k++)
                    {
                        double t = rect[j][k];
                        rect[j][k] = rect[i][k];
                        rect[i][k] = t;
                    }
                    break;
                }
        }
        for (int j=0; j<n; j++)
            if (i!=j && (abs(rect[j][num])>NAX))
                {
                    double ml = LeastCommonMultiple(abs(rect[j][num]),abs(rect[i][num]));
                    double t = ml/rect[j][num];
                    double kt = ml/rect[i][num];
                    for (int k=EDGESUM; k>=0; k--){
                        rect[j][k] = rect[j][k]*t;
                        rect[j][k] = (abs(rect[j][k])<NAX)?0:rect[j][k];
                    }
                    for (int k=EDGESUM; k>=num; k--)
                    {
                        rect[j][k] -= kt*rect[i][k];
                        rect[j][k] = (abs(rect[j][k])<NAX)?0:rect[j][k];
                    }


                }


            num ++;
            for (int j=0; j<n; j++){
                double common = 0;
                for (int k=0; k<EDGESUM+1; k++)
                if ((abs(rect[j][k]) > NAX)){
                    if (abs(common) < NAX)
                        common = abs(rect[j][k]);
                    else
                        common = GreatestCommonDivisor(common,abs(rect[j][k]));
                }
                if (common!=0)
                    for (int k=0; k<EDGESUM+1; k++){
                        rect[j][k] = rect[j][k]/common;
                        rect[j][k] = (abs(rect[j][k])<NAX)?0:rect[j][k];
                    }
            }
        if (num==EDGESUM)
            break;
    }

    num = 0;
    for (int i=0; i<EDGESUM; i++)
    {
        edges[num].v = double(rect[i][EDGESUM])/double(rect[i][num]);
        if (edges[num].v<0)
        {
            edges[num].v = -edges[num].v;
            int tm = edges[num].n1;
            edges[num].n1 = edges[num].n2;
            edges[num].n2 = tm;
        }
        num++;
        if (num==EDGESUM)
            break;
    }

}

void Cal::_getans()
{
    int n = rect.size();

    for (int i=0; i<n; i++)
        for (int j=0; j<EDGESUM+1; j++)
            if (abs(rect[i][j])<NAX)
                rect[i][j] = 0;

    int num = 0;
    for (int i=0; i<n; i++){
        if (abs(rect[i][num]) <NAX){
            int mjj = 0;
            for (int j=i+1; j<n; j++)
                if ( !(abs(rect[j][num])<NAX))
                {
                    mjj++;
                    for (int k=0; k<EDGESUM+1; k++)
                    {
                        double t = rect[j][k];
                        rect[j][k] = rect[i][k];
                        rect[i][k] = t;
                    }
                    break;
                }
        }
        for (int j=0; j<n; j++)
            if (i!=j && (abs(rect[j][num])>NAX))
                {
                    double t = 1/rect[j][num];
                    double kt = 1/rect[i][num];
                    for (int k=EDGESUM; k>=0; k--){
                        rect[j][k] = rect[j][k]*t;
                        rect[j][k] = (abs(rect[j][k])<NAX)?0:rect[j][k];
                    }
                    for (int k=EDGESUM; k>=num; k--)
                    {
                        rect[j][k] -= kt*rect[i][k];
                        rect[j][k] = (abs(rect[j][k])<NAX)?0:rect[j][k];
                    }


                }


            num ++;
            for (int j=0; j<n; j++){
                double common = 0;
                for (int k=0; k<EDGESUM+1; k++)
                if ((abs(rect[j][k]) > NAX)){
                    if (abs(common) < NAX)
                        common = abs(rect[j][k]);
                    else
                        common = GreatestCommonDivisor(common,abs(rect[j][k]));
                }
                if (common!=0)
                    for (int k=0; k<EDGESUM+1; k++){
                        rect[j][k] = rect[j][k]/common;
                        rect[j][k] = (abs(rect[j][k])<NAX)?0:rect[j][k];
                    }
            }
        if (num==EDGESUM)
            break;
    }

    num = 0;
    for (int i=0; i<EDGESUM; i++)
    {
        c[num] = double(rect[i][EDGESUM])/double(rect[i][num]);
        num++;
        if (num==EDGESUM)
            break;
    }

}

void Cal::caluconspeed(int num, vector<double>&length, int i1, int i2, int o1, int o2, int o3)
{
    rect.clear();
    n = num;
    for(int i=0; i<200; i++)
        nodes[i].elist.clear();
    EDGESUM = 2*n*n-2*n+5;
    NODESUM = n*n+2;
    int n1 = 0;
    int n2 = 1;
    fr = new bool[EDGESUM];
    for (int i=0; i<n*n-n; i++)
    {
        edges[i].n1 = n1;
        edges[i].n2 = n2;
        nodes[n1].elist.push_back(i);
        nodes[n2].elist.push_back(i);
        n1++;n2++;
        if (n2%n==0)
        {
            n1++;n2++;
        }
    }
    n1 = 0;
    n2 = n1+n;
    for (int i=n*n-n; i<2*n*n-2*n; i++)
    {
        edges[i].n1 = n1;
        edges[i].n2 = n2;
        nodes[n1].elist.push_back(i);
        nodes[n2].elist.push_back(i);
        n1++;n2++;
    }

    edges[2*n*n-2*n+0].n1 = n*n;
    edges[2*n*n-2*n+0].n2 = (i1)*n;
    nodes[n*n].elist.push_back(2*n*n-2*n+0);
    nodes[(i1)*n].elist.push_back(2*n*n-2*n+0);

    edges[2*n*n-2*n+1].n1 = n*n;
    edges[2*n*n-2*n+1].n2 = (i2)*n;
    nodes[n*n].elist.push_back(2*n*n-2*n+1);
    nodes[(i2)*n].elist.push_back(2*n*n-2*n+1);

    edges[2*n*n-2*n+2].n1 = (o1+1)*n-1;
    edges[2*n*n-2*n+2].n2 = n*n+1;
    nodes[(o1+1)*n-1].elist.push_back(2*n*n-2*n+2);
    nodes[n*n+1].elist.push_back(2*n*n-2*n+2);

    edges[2*n*n-2*n+3].n1 = (o2+1)*n-1;
    edges[2*n*n-2*n+3].n2 = n*n+1;
    nodes[(o2+1)*n-1].elist.push_back(2*n*n-2*n+3);
    nodes[n*n+1].elist.push_back(2*n*n-2*n+3);

    edges[2*n*n-2*n+4].n1 = (o3+1)*n-1;
    edges[2*n*n-2*n+4].n2 = n*n+1;
    nodes[(o3+1)*n-1].elist.push_back(2*n*n-2*n+4);
    nodes[n*n+1].elist.push_back(2*n*n-2*n+4);

    for (int i=0; i<2*n*n-2*n+5; i++)
    {
        setedgelength(i,length[i]);
    }
    edges[EDGESUM-4].v = 200*200/width[EDGESUM-4];
    edges[EDGESUM-5].v = 200*200/width[EDGESUM-5];

    initrect();
    getans();
    calc();
    for(int i=0;i<EDGESUM;i++)
    {
        edges[i].v=edges[i].v/width[i]*200;
    }
    vector <double> nilanle;
}
void Cal::initialize(int _num, vector <double> _length, int _i1, int _i2, int _o1, int _o2, int _o3)
{
    n=_num;
    EDGESUM = 2*n*n-2*n+5;
    NODESUM = n*n+2;
    length.assign(_length.begin(), _length.end());
    width.clear();
    for(int i=0; i<length.size(); i++)
        width.push_back(200);
    for(int i=0; i<length.size(); i++)
        c.push_back(0);
    c[EDGESUM-5]=1;
    i1=_i1;
    i2=_i2;
    o1=_o1;
    o2=_o2;
    o3=_o3;
}

bool Cal::WidthLegal(int i, int _width)
{
    if(0<=i && i< n-1)
    {
        if(_width+width[i+n-1]<=3200)
            return true;
        else
            return false;
    }
    else if(i>=n-1&& i<n*n-2*n+1)
    {
        if(_width+width[i-n+1]<=3200 && _width+width[i+n-1]<=3200)
            return true;
        else
            return false;
    }
    else if(i>=n*n-2*n+1 && i <n*n-n)
    {
        if(_width+width[i-n+1]<=3200)
            return true;
        else
            return false;
    }
    else if(i>=n*n-n && i%n==0)
    {
        if(_width+width[i+1]<=3200)
            return true;
        else
            return false;
    }
    else if(i>=n*n-n && i%n==n-1)
    {
        if(_width+width[i-1]<=3200)
            return true;
        else
            return false;
    }
    else if(i==EDGESUM-5)
    {
        if(_width+width[EDGESUM-4]<=3200)
            return true;
        else
            return false;
    }
    else if(i==EDGESUM-4)
    {
        if(_width+width[EDGESUM-5]<=3200)
            return true;
        else
            return false;
    }
    else if(i==EDGESUM-3)
    {
        if(_width+width[EDGESUM-2]<=3200)
            return true;
        else
            return false;
    }
    else if(i==EDGESUM-2)
    {
        if(_width+width[EDGESUM-1]<=3200&&_width+width[EDGESUM-3]<=3200)
            return true;
        else
            return false;
    }
    else if(i==EDGESUM-1)
    {
        if(_width+width[EDGESUM-2]<=3200)
            return true;
        else
            return false;
    }
    else
    {
        if(_width+width[i-1]<=3200 && _width+width[i+1]<=3200)
            return true;
        else
            return false;
    }
}

QColor Cal::color(int i, bool CalMode)
{
    if(CalMode==velocity)
    {
        if(edges[i].v>=400)
            return QColor(255,0,0);
        else if(edges[i].v>=200&&edges[i].v<400)
        {
            return QColor((edges[i].v-200)/200*255,0,(400-edges[i].v)/200*255);
        }
        else if(edges[i].v<=NAX)
            return QColor(0,255,0);
        else
            return QColor(0,(200-edges[i].v)/200*255,edges[i].v/200*255);
    }
    else
    {
        if(c[i]>=1)
            return QColor(255,0,0);
        else if(c[i]>=0.5)
            return QColor((c[i]-0.5)/0.5*255,0,(1-c[i])/0.5*255);
        else if(c[i]<=NAX)
            return QColor(0,255,0);
        else
            return QColor(0,(0.5-c[i])/0.5*255,c[i]/0.5*255);
    }
}

void Cal::calc()
{
    rect.clear();
    for(int x=0;x<n;x++)
        for(int y=0;y<n;y++)
        {
                    if(_existdir(x,y,0)+_existdir(x,y,1)+_existdir(x,y,2)+_existdir(x,y,3)==2)
                    {
                        vector <int> a;
                        for(int i=0;i<=3;i++)
                            if(_existdir(x,y,i))
                                a.push_back(getdirline(x,y,i));
                        vector <double> temp(EDGESUM+1,0);
                        temp[a[0]]=1;
                        temp[a[1]]=-1;
                        addrect(temp);
                    }
                    else if(_existdir(x,y,0)+_existdir(x,y,1)+_existdir(x,y,2)+_existdir(x,y,3)==3)
                    {
                        vector <int> a;
                        vector <double> temp(EDGESUM+1,0);
                        for(int i=0;i<=3;i++)
                            if(_existdir(x,y,i))
                                a.push_back(getdirline(x,y,i));
                        if(edges[a[0]].n1==edges[a[1]].n1)
                        {
                            temp[a[2]]=1;
                            temp[a[0]]=-1;
                            addrect(temp);
                            temp[a[0]]=0;
                            temp[a[1]]=-1;
                            addrect(temp);
                        }
                        else if (edges[a[0]].n1==edges[a[2]].n1)
                        {
                            temp[a[1]]=1;
                            temp[a[0]]=-1;
                            addrect(temp);
                            temp[a[0]]=0;
                            temp[a[2]]=-1;
                            addrect(temp);
                        }
                        else if (edges[a[1]].n1==edges[a[2]].n1)
                        {
                            temp[a[0]]=1;
                            temp[a[1]]=-1;
                            addrect(temp);
                            temp[a[1]]=0;
                            temp[a[2]]=-1;
                            addrect(temp);
                        }
                        else if(edges[a[0]].n2==edges[a[1]].n2)
                        {
                            temp[a[0]]=edges[a[0]].v;
                            temp[a[1]]=edges[a[1]].v;
                            temp[a[2]]=-edges[a[2]].v;
                            addrect(temp);
                        }
                        else if(edges[a[0]].n2==edges[a[2]].n2)
                        {
                            temp[a[0]]=edges[a[0]].v;
                            temp[a[2]]=edges[a[2]].v;
                            temp[a[1]]=-edges[a[1]].v;
                            addrect(temp);
                        }
                        else if(edges[a[1]].n2==edges[a[2]].n2)
                        {
                            temp[a[1]]=edges[a[1]].v;
                            temp[a[2]]=edges[a[2]].v;
                            temp[a[0]]=-edges[a[0]].v;
                            addrect(temp);
                        }
                    }
                    else if (_existdir(x,y,0)+_existdir(x,y,1)+_existdir(x,y,2)+_existdir(x,y,3)==4)
                    {
                        vector <int> a;
                        vector <double> temp(EDGESUM+1,0);
                        for(int i=0;i<=3;i++)
                            if(_existdir(x,y,i))
                                a.push_back(getdirline(x,y,i));
                        if(edges[a[0]].n1==edges[a[1]].n1&&edges[a[1]].n1==edges[a[2]].n1)
                                {
                                    temp[a[3]]=1;
                                    temp[a[0]]=-1;
                                    addrect(temp);
                                    temp[a[0]]=0;
                                    temp[a[1]]=-1;
                                    addrect(temp);
                                    temp[a[1]]=0;
                                    temp[a[2]]=-1;
                                    addrect(temp);
                                }
                        else if(edges[a[0]].n1==edges[a[1]].n1&&edges[a[1]].n1==edges[a[3]].n1)
                                {
                                    temp[a[2]]=1;
                                    temp[a[0]]=-1;
                                    addrect(temp);
                                    temp[a[0]]=0;
                                    temp[a[1]]=-1;
                                    addrect(temp);
                                    temp[a[1]]=0;
                                    temp[a[3]]=-1;
                                    addrect(temp);
                                }
                        else if(edges[a[0]].n1==edges[a[2]].n1&&edges[a[2]].n1==edges[a[3]].n1)
                                {
                                    temp[a[1]]=1;
                                    temp[a[0]]=-1;
                                    addrect(temp);
                                    temp[a[0]]=0;
                                    temp[a[2]]=-1;
                                    addrect(temp);
                                    temp[a[2]]=0;
                                    temp[a[3]]=-1;
                                    addrect(temp);
                                }
                        else if(edges[a[1]].n1==edges[a[2]].n1&&edges[a[2]].n1==edges[a[3]].n1)
                                {
                                    temp[a[0]]=1;
                                    temp[a[1]]=-1;
                                    addrect(temp);
                                    temp[a[1]]=0;
                                    temp[a[2]]=-1;
                                    addrect(temp);
                                    temp[a[2]]=0;
                                    temp[a[3]]=-1;
                                    addrect(temp);
                                }
                        else if(edges[a[0]].n2==edges[a[1]].n2&&edges[a[1]].n2==edges[a[2]].n2)
                                {
                                     temp[a[0]]=edges[a[0]].v;
                                     temp[a[1]]=edges[a[1]].v;
                                     temp[a[2]]=edges[a[2]].v;
                                     temp[a[3]]=-edges[a[3]].v;
                                     addrect(temp);
                                }
                        else if(edges[a[0]].n2==edges[a[1]].n2&&edges[a[1]].n2==edges[a[3]].n2)
                                {
                                     temp[a[0]]=edges[a[0]].v;
                                     temp[a[1]]=edges[a[1]].v;
                                     temp[a[3]]=edges[a[3]].v;
                                     temp[a[2]]=-edges[a[2]].v;
                                     addrect(temp);
                                }
                        else if(edges[a[0]].n2==edges[a[2]].n2&&edges[a[2]].n2==edges[a[3]].n2)
                                {
                                     temp[a[0]]=edges[a[0]].v;
                                     temp[a[2]]=edges[a[2]].v;
                                     temp[a[3]]=edges[a[3]].v;
                                     temp[a[1]]=-edges[a[1]].v;
                                     addrect(temp);
                                }
                        else if(edges[a[1]].n2==edges[a[2]].n2&&edges[a[2]].n2==edges[a[3]].n2)
                                {
                                     temp[a[1]]=edges[a[1]].v;
                                     temp[a[2]]=edges[a[2]].v;
                                     temp[a[3]]=edges[a[3]].v;
                                     temp[a[0]]=-edges[a[0]].v;
                                     addrect(temp);
                                }
                        else if(edges[getdirline(x,y,0)].n2==n*x+y&&edges[getdirline(x,y,1)].n1==n*x+y)
                        {
                            if(edges[getdirline(x,y,0)].v>edges[getdirline(x,y,1)].v)
                            {
                                temp[getdirline(x,y,0)]=1;
                                temp[getdirline(x,y,1)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,3)]=edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,1)]=-edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;

                                addrect(temp);
                            }
                            else
                            {
                                temp[getdirline(x,y,3)]=1;
                                temp[getdirline(x,y,2)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,3)]=edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,1)]=-edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;
                                addrect(temp);
                            }
                        }
                        else if(edges[getdirline(x,y,0)].n2==n*x+y&&edges[getdirline(x,y,1)].n2==n*x+y)
                        {
                            if(edges[getdirline(x,y,0)].v>edges[getdirline(x,y,3)].v)
                            {
                                temp[getdirline(x,y,0)]=1;
                                temp[getdirline(x,y,3)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,1)]=edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,3)]=-edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;
                                addrect(temp);
                            }
                            else
                            {
                                temp[getdirline(x,y,1)]=1;
                                temp[getdirline(x,y,2)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,1)]=edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,3)]=-edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;
                                addrect(temp);
                            }
                        }
                        else if(edges[getdirline(x,y,0)].n1==n*x+y&&edges[getdirline(x,y,1)].n1==n*x+y)
                        {
                            if(edges[getdirline(x,y,3)].v>edges[getdirline(x,y,0)].v)
                            {
                                temp[getdirline(x,y,0)]=1;
                                temp[getdirline(x,y,3)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,1)]=edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,3)]=-edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;
                                addrect(temp);
                            }
                            else
                            {
                                temp[getdirline(x,y,1)]=1;
                                temp[getdirline(x,y,2)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,1)]=edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,3)]=-edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;
                                addrect(temp);
                            }
                        }
                        else if(edges[getdirline(x,y,0)].n1==n*x+y&&edges[getdirline(x,y,1)].n2==n*x+y)
                        {
                            if(edges[getdirline(x,y,1)].v>edges[getdirline(x,y,0)].v)
                            {
                                temp[getdirline(x,y,0)]=1;
                                temp[getdirline(x,y,1)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,3)]=edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,1)]=-edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;
                                addrect(temp);
                            }
                            else
                            {
                                temp[getdirline(x,y,3)]=1;
                                temp[getdirline(x,y,2)]=-1;
                                addrect(temp);
                                temp[getdirline(x,y,0)]=edges[getdirline(x,y,0)].v;
                                temp[getdirline(x,y,3)]=edges[getdirline(x,y,3)].v;
                                temp[getdirline(x,y,1)]=-edges[getdirline(x,y,1)].v;
                                temp[getdirline(x,y,2)]=-edges[getdirline(x,y,2)].v;
                                addrect(temp);
                            }
                        }
                    }

        }
    for(int i=0;i<EDGESUM;i++)
    {
        if(edges[i].v<=NAX)
        {
            vector<double> temp(EDGESUM+1,0);
            temp[i]=1;
            addrect(temp);
        }
    }
    vector <double> temp(EDGESUM+1,0);
    temp[EDGESUM-5]=1;
    temp[EDGESUM]=1;
    addrect(temp);
    temp[EDGESUM-5]=0;
    temp[EDGESUM-4]=1;
    temp[EDGESUM]=0;
    addrect(temp);
    _getans();
}
