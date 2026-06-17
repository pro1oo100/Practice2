#ifndef RSA_H
#define RSA_H

void generateKeys(int& n, int& e, int& d);
void consoleMode(int e, int n, int d);
void fileMode(int e, int n, int d);
void runRSA();

#endif
