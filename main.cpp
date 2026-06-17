#include "enums.h"
#include "powmod.h"
#include "euclid.h"
#include "rsa.h"
#include <iostream>

int main() {
    int choice;
    std::cout << "1. a^x mod p (теорема Ферма, бинарное возведение)" << std::endl;
    std::cout << "2. Расширенный алгоритм Евклида (вывод u и v)" << std::endl;
    std::cout << "3. Обратное число c^(-1) mod m = d (вывод d)" << std::endl;
    std::cout << "4. RSA шифрование/дешифрование" << std::endl;
    std::cin >> choice;

    switch (choice) {
        case task::POWMOD: {
            int a, x, p;
            if (inputPow(a, x, p)) {
                std::cout << modulo(a, x, p) << std::endl;
            } else {
                std::cout << "Некорректные значения" << std::endl;
            }
            break;
        }
        case task::EUCLID: {
            int c, m;
            if (inputEuclid(c, m)) {
                int u, v;
                int g = egcd(c, m, u, v);
                std::cout << "НОД = " << g << std::endl;
                std::cout << "u = " << u << ", v = " << v << std::endl;
            } else {
                std::cout << "Некорректные значения" << std::endl;
            }
            break;
        }
        case task::INVERS: {
            int c, m;
            if (inputEuclid(c, m)) {
                int d;
                if (inverse(c, m, d)) {
                    std::cout << "d = " << d << std::endl;
                } else {
                    std::cout << "Числа не взаимно просты" << std::endl;
                }
            } else {
                std::cout << "Некорректные значения" << std::endl;
            }
            break;
        }
        case task::RSA: {
            runRSA();
            break;
        }
        default:
            std::cout << "Неверный выбор" << std::endl;
    }
    return 0;
}
