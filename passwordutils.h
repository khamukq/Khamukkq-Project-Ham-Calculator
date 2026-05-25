#ifndef PASSWORDUTILS_H
#define PASSWORDUTILS_H

double entropy(int len, bool up, bool dig, bool sym);
int strength(double e);

#endif