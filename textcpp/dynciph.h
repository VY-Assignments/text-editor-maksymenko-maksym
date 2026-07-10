#pragma once
#include <string>
#include <stdexcept>
#include <windows.h> 
class DynamicCipher {
private:
    HMODULE hDll;          
    void* cipherInstance;   
    typedef void* (*CreateVigenereFunc)(const char*);
    typedef char* (*EncryptFunc)(void*, const char*);
    typedef char* (*DecryptFunc)(void*, const char*);
    typedef void (*DestroyFunc)(void*);
    typedef void (*FreeFunc)(char*);

    EncryptFunc pEncrypt;
    DecryptFunc pDecrypt;
    DestroyFunc pDestroy;
    FreeFunc pFree;

public:
    DynamicCipher(const std::string& dllPath, const std::string& key);
    ~DynamicCipher();
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
};