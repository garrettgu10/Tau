#include <helper.h>
#include <math.h>
#include <QGlobal.h>
#include <QTime>
#include <stdlib.h>

int difference(int a, int b)
{
    int result = a-b;
    if(result <= -2880){
        result += 5760;
    }else if(result > 2880){
        result -= 5760;
    }
    return result;
}

void normalize(int &a)
{
    while(a > 5760){
        a-=5760;
    }
    while(a<0)
    {
        a+=5760;
    }
}



int randomInBound(int min, int max)
{
    return qrand() % ((max + 1) - min) + min;
}

double randomInBound(double min, double max){
    return (double)qrand()/RAND_MAX*(max-min)+min;
}

void seedRandomFunction()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}
