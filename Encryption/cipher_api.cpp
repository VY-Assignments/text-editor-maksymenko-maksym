#define _CRT_SECURE_NO_WARNINGS
#include "cipher_api.h"
#include "cipher.h"
#include <cstring>

extern "C" {
    EXPORT cipher_t cipher_create_caesar(int key) {
        return new CaesarCipher(key);
    }

    EXPORT cipher_t cipher_create_vigenere(const char* key) {
        return new VigenereCipher(key);
    }

    EXPORT char* cipher_encrypt(cipher_t cipher, const char* text) {
        Cipher* c = static_cast<Cipher*>(cipher);
        std::string result = c->encrypt(text);
        char* out = new char[result.size() + 1];
        std::strcpy(out, result.c_str());
        return out;
    }

    EXPORT char* cipher_decrypt(cipher_t cipher, const char* text) {
        Cipher* c = static_cast<Cipher*>(cipher);
        std::string result = c->decrypt(text);
        char* out = new char[result.size() + 1];
        std::strcpy(out, result.c_str());
        return out;
    }

    EXPORT void cipher_destroy(cipher_t cipher) {
        delete static_cast<Cipher*>(cipher);
    }

    EXPORT void cipher_free(char* str) {
        delete[] str;  
    }
}