#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>

typedef void* cipher_t;
typedef cipher_t(*CreateCaesar)(int);
typedef cipher_t(*CreateVigenere)(const char*);
typedef char* (*CipherEncrypt)(cipher_t, const char*);
typedef char* (*CipherDecrypt)(cipher_t, const char*);
typedef void (*CipherDestroy)(cipher_t);
typedef void (*CipherFree)(char*);

int main() {
    HMODULE lib = LoadLibraryA("Encryption.dll");
    if (!lib) {
        std::cout << "unable to load dll\n";
        return 1;
    }

    auto createCaesar = (CreateCaesar)GetProcAddress(lib, "cipher_create_caesar");
    auto createVigenere = (CreateVigenere)GetProcAddress(lib, "cipher_create_vigenere");
    auto encrypt = (CipherEncrypt)GetProcAddress(lib, "cipher_encrypt");
    auto decrypt = (CipherDecrypt)GetProcAddress(lib, "cipher_decrypt");
    auto destroy = (CipherDestroy)GetProcAddress(lib, "cipher_destroy");
    auto freeStr = (CipherFree)GetProcAddress(lib, "cipher_free");
    if (!createCaesar || !createVigenere || !encrypt || !decrypt || !destroy || !freeStr) {
        std::cout << "Failed to load functions from DLL\n";
        FreeLibrary(lib);
        return 1;
    }
    std::cout << "All functions loaded successfully\n";

    while (true) {
        std::cout << "1. Caesar\n2. Vigenere\n0. Exit\n> ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;
        if (choice != 1 && choice != 2) {
            std::cout << "wrong choice\n";
            continue;
        }

        cipher_t cipher = nullptr;

        if (choice == 1) {
            int key;
            std::cout << "Enter key: ";
            std::cin >> key;
            cipher = createCaesar(key);
        }
        else {
            std::string key;
            std::cout << "Enter key: ";
            std::cin >> key;
            cipher = createVigenere(key.c_str());
        }

        int op;
        std::cout << "1. Encrypt\n2. Decrypt\n> ";
        std::cin >> op;
        std::cin.ignore();

        std::string text;
        std::cout << "Enter text: ";
        std::getline(std::cin, text);

        char* result = nullptr;
        if (op == 1)
            result = encrypt(cipher, text.c_str());
        else
            result = decrypt(cipher, text.c_str());

        std::cout << "Result: " << result << "\n";

        freeStr(result);
        destroy(cipher);
    }

    FreeLibrary(lib);
    return 0;
}