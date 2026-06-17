#ifndef RSA_H
#define RSA_H

bool generateKeys(int& n, int& e, int& d);
int encryptRSA(int m, int e, int n);
int decryptRSA(int c, int d, int n);
void runRSA();

#endif
