#include "powmod.h"
#include <iostream>

bool inputPow(int& a, int& x, int& p) {
    bool isDone = 0;
    if (std::cin >> a && a >= 1 &&
        std::cin >> x && x >= 0 &&
        std::cin >> p && p > 1) {
        isDone = 1;
    }
    return isDone;
}

bool simple(int p) {
    bool isDone = 1;
    for (int i = 2; i * i <= p; ++i) {
        if (p % i == 0) {
            isDone = 0;
            break;
        }
    }
    return isDone;
}

bool ferm(int a, int p) {
    bool isDone = 0;
    if (simple(p) && a % p != 0) {
        isDone = 1;
    }
    return isDone;
}

int modulo(int a, int x, int p) {
    a %= p;
    int res = 1;
    if (ferm(a, p)) {
        x %= (p - 1);
    }
    while (x > 0) {
        if (x % 2 != 0) {
            res = (res * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return res;
}
