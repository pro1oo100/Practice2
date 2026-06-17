#include "powmod.h"
#include "euclid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int randomPrime(int min, int max) {
    int p = min + rand() % (max - min + 1);
    while (!simple(p)) {
        p = min + rand() % (max - min + 1);
    }
    return p;
}

void generateKeys(int& n, int& e, int& d) {
    std::srand(std::time(nullptr));
    int p = randomPrime(20, 100);
    int q = randomPrime(20, 100);
    while (q == p) {
        q = randomPrime(20, 100);
    }
    n = p * q;
    int phi = (p - 1) * (q - 1);
    e = 17;
    int u, v;
    while (egcd(e, phi, u, v) != 1) {
        ++e;
    }
    inverse(e, phi, d);
}

void runRSA() {
    int n, e, d;
    generateKeys(n, e, d);
    std::cout << "Открытый ключ (e, n): (" << e << ", " << n << ")" << std::endl;
    std::cout << "Закрытый ключ (d, n): (" << d << ", " << n << ")" << std::endl;

    std::string text;
    std::cout << "Введите текст: ";
    std::cin.ignore();
    std::getline(std::cin, text);

    std::vector<int> cipher;
    for (char ch : text) {
        int m = (unsigned char)ch;
        cipher.push_back(modulo(m, e, n));
    }
    std::cout << "Шифротекст: ";
    for (int c : cipher) std::cout << c << " ";
    std::cout << std::endl;

    std::cout << "Расшифрованный текст: ";
    for (int c : cipher) {
        int m = modulo(c, d, n);
        std::cout << (char)m;
    }
    std::cout << std::endl;
}
