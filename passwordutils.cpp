#include "passwordutils.h"
#include <cmath>

double entropy(int len, bool up, bool dig, bool sym)
{
    int set = 26;
    if (up) set += 26;
    if (dig) set += 10;
    if (sym) set += 8;
    return len * log2(set);
}

int strength(double e)
{
    if (e < 40) return 25;
    if (e < 60) return 50;
    if (e < 80) return 75;
    return 100;
}