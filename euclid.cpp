#include "euclid.h"
#include <iostream>

bool inputEuclid(int& c, int& m) {
    bool isDone = 0;
    if (std::cin >> c && c > 0 && std::cin >> m && m > 1) {
        isDone = 1;
    }
    return isDone;
}

int egcd(int a, int b, int& u, int& v) {
    int u0 = 1, v0 = 0;
    int u1 = 0, v1 = 1;
    while (b != 0) {
        int q = a / b;
        int r = a % b;
        int u2 = u0 - q * u1;
        int v2 = v0 - q * v1;
        a = b;
        b = r;
        u0 = u1;
        v0 = v1;
        u1 = u2;
        v1 = v2;
    }
    u = u0;
    v = v0;
    return a;
}

bool inverse(int a, int mod, int& d) {
    int u0 = 1, u1 = 0;
    int A = a, M = mod;
    while (M != 0) {
        int q = A / M;
        int r = A % M;
        int u2 = u0 - q * u1;
        A = M;
        M = r;
        u0 = u1;
        u1 = u2;
    }
    if (A != 1) {
        return false;
    }
    d = u0 % mod;
    if (d < 0) d += mod;
    return true;
}
