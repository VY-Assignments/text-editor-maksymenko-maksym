#include "dynciph.h"

DynamicCipher::DynamicCipher(const std::string& dllPath, const std::string& key) {
    hDll = LoadLibraryA(dllPath.c_str());
    if (!hDll) {
        throw std::runtime_error("Failed to load DLL: " + dllPath);
    }
    auto pCreateVigenere = (CreateVigenereFunc)GetProcAddress(hDll, "cipher_create_vigenere");
    pEncrypt = (EncryptFunc)GetProcAddress(hDll, "cipher_encrypt");
    pDecrypt = (DecryptFunc)GetProcAddress(hDll, "cipher_decrypt");
    pDestroy = (DestroyFunc)GetProcAddress(hDll, "cipher_destroy");
    pFree = (FreeFunc)GetProcAddress(hDll, "cipher_free");

    if (!pCreateVigenere || !pEncrypt || !pDecrypt || !pDestroy || !pFree) {
        FreeLibrary(hDll);
        throw std::runtime_error("Failed to locate one or more functions in DLL.");
    }

    cipherInstance = pCreateVigenere(key.c_str());
}

DynamicCipher::~DynamicCipher() {
    if (hDll) {
        if (cipherInstance && pDestroy) {
            pDestroy(cipherInstance);
        }
        FreeLibrary(hDll);
    }
}

std::string DynamicCipher::encrypt(const std::string& text) {
    char* encryptedCStr = pEncrypt(cipherInstance, text.c_str());
    std::string result(encryptedCStr);
    pFree(encryptedCStr); 
    return result;
}

std::string DynamicCipher::decrypt(const std::string& text) {
    char* decryptedCStr = pDecrypt(cipherInstance, text.c_str());
    std::string result(decryptedCStr);
    pFree(decryptedCStr);
    return result;
}