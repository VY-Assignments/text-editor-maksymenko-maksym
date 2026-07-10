#pragma once
#include "TextStorage.h"

class CommandLine {
private:
    TextStorage storage;
    void addTextMenu();
    void saveToFile();
    void loadFromFile();
    void encryptDecrypt();

public:
    void run();
};