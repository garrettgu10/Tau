#ifndef HELPER_H
#define HELPER_H
#include <QPointF>
int difference (int a, int b); // returns difference between two angles
void normalize (int &a);
int randomInBound(int min, int max);
void seedRandomFunction();
double distance(QPointF* a, QPointF* b);
double distance(QPointF a, QPointF b);
#endif // HELPER_H
