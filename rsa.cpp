#include "rsa.h"
#include "powmod.h"
#include "euclid.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

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

void consoleMode(int e, int n, int d) {
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

void encryptFile(const std::string& src, const std::string& dst, int e, int n) {
    std::ifstream in(src, std::ios::binary);
    std::ofstream out(dst, std::ios::binary);
    if (!in || !out) {
        std::cout << "Ошибка открытия файлов" << std::endl;
        return;
    }
    std::string text((std::istreambuf_iterator<char>(in)),
                      std::istreambuf_iterator<char>());
    in.close();

    std::vector<int> cipher;
    for (char ch : text) {
        int m = (unsigned char)ch;
        cipher.push_back(modulo(m, e, n));
    }
    for (size_t i = 0; i < cipher.size(); ++i) {
        out << cipher[i];
        if (i + 1 < cipher.size()) out << " ";
    }
    out.close();
}

void decryptFile(const std::string& src, const std::string& dst, int d, int n) {
    std::ifstream in(src, std::ios::binary);
    std::ofstream out(dst, std::ios::binary);
    if (!in || !out) {
        std::cout << "Ошибка открытия файлов" << std::endl;
        return;
    }
    std::vector<int> cipher;
    int num;
    while (in >> num) {
        cipher.push_back(num);
    }
    in.close();

    for (int c : cipher) {
        int m = modulo(c, d, n);
        out.put((char)m);
    }
    out.close();
}

void fileMode(int e, int n, int d) {
    std::string inFile = "input.txt";
    std::string encFile = "encrypted.txt";
    std::string decFile = "decrypted.txt";

    std::cout << "Шифрование файла " << inFile << " -> " << encFile << std::endl;
    encryptFile(inFile, encFile, e, n);
    std::cout << "Расшифровка файла " << encFile << " -> " << decFile << std::endl;
    decryptFile(encFile, decFile, d, n);
    std::cout << "Готово." << std::endl;
}

void runRSA() {
    int n, e, d;
    generateKeys(n, e, d);
    std::cout << "Открытый ключ (e, n): (" << e << ", " << n << ")" << std::endl;
    std::cout << "Закрытый ключ (d, n): (" << d << ", " << n << ")" << std::endl;

    int mode;
    std::cout << "Выберите режим: 1 - консоль, 2 - файлы (input.txt)" << std::endl;
    std::cin >> mode;

    if (mode == 1) {
        consoleMode(e, n, d);
    } else if (mode == 2) {
        fileMode(e, n, d);
    } else {
        std::cout << "Неверный режим" << std::endl;
    }
}
