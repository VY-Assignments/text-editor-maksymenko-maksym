#include "commandLine.h"
#include "deserialize.h"
#include "dynciph.h"
#include "line.h"
#include <iostream>
#include <fstream>
#include <string>

void CommandLine::run() {
    int command;
    while (true) {
        std::cout << "1. Add new line\n"
            << "2. Print all text\n"
            << "3. Save to file\n"
            << "4. Load file\n"
            << "5. En/Decrypt menu\n"
            << "6. Exit\n"
            << "\n> Choose the command:\n";

        if (!(std::cin >> command)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        switch (command) {
        case 1:
            addTextMenu();
            break;
        case 2:
            storage.printAll();
            break;
        case 3:
            saveToFile();
            break;
        case 4:
            loadFromFile();
            break;
        case 5:
            encryptDecrypt(); 
            break;
        case 14:
            std::cout << "> Exiting\n";
            return;
        default:
            std::cout << "> The command does not exist \n";
        }
    }
}

void CommandLine::addTextMenu() {
    int type;
    std::cout << "\n> Select line type:\n"
        << "1.Pure Text\n"
        << "2.Checklist\n"
        << "3.Contact\n";
    if (!(std::cin >> type)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "> Invalid input\n";
        return;
    }
    std::cin.ignore(10000, '\n');

    if (type == 1) {
        std::string text;
        std::cout << "> Etner text: ";
        std::getline(std::cin, text);
        storage.addLine(new TextLine(text));
        std::cout << ">line added.\n";
    }
    else if (type == 2) {
        std::string item;
        int status;
        std::cout << "> Enter task name: ";
        std::getline(std::cin, item);
        std::cout << "> Is it done? (1 - yes, 0 - no): ";
        std::cin >> status;
        storage.addLine(new ChecklistLine(item, status != 0));
        std::cout << "> Checklist line added.\n";
    }
    else if (type == 3) {
        std::string name, surname, email;
        std::cout << "> Enter name: ";
        std::getline(std::cin, name);
        std::cout << "> Enter surname: ";
        std::getline(std::cin, surname);
        std::cout << "> Enter email: ";
        std::getline(std::cin, email);
        storage.addLine(new ContactLine(name, surname, email));
        std::cout << "> Contact line added.\n";
    }
    else {
        std::cout << "> Unknown type.\n";
    }
}

void CommandLine::saveToFile() {
    std::string filename;
    std::cout << "> Enter the file name for saving: ";
    std::getline(std::cin, filename);
    std::ofstream file(filename);
    if (file.is_open()) {
        file << storage.getSerializedText();
        file.close();
        std::cout << "> Text has been saved successfully\n";
    }
    else {
        std::cout << "> Error opening file for saving\n";
    }
}

void CommandLine::loadFromFile() {
    std::string filename;
    std::cout << "> Enter the file name for loading: ";
    std::getline(std::cin, filename);

    std::ifstream file(filename);
    if (file.is_open()) {
        storage.clear();
        std::string line;
        while (std::getline(file, line)) {
            storage.addLine(deserializeLine(line));
        }
        file.close();
        std::cout << "> Text has been loaded successfully\n";
    }
    else {
        std::cout << "> Error opening file\n";
    }
}

void CommandLine::encryptDecrypt() {
    int choice;
    std::cout << "\n> 1. Encrypt file\n> 2. Decrypt file\n> Choose: ";
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }
    std::cin.ignore(10000, '\n');

    std::string inputPath, outputPath, key, dllPath;
    std::cout << "> Enter input file: ";
    std::getline(std::cin, inputPath);
    std::cout << "> Enter output file: ";
    std::getline(std::cin, outputPath);
    std::cout << "> Enter the key: ";
    std::getline(std::cin, key);
    std::cout << "> Enter DLL path: ";
    std::getline(std::cin, dllPath);

    try {
        DynamicCipher cipher(dllPath, key);

        std::ifstream inFile(inputPath);
        if (!inFile.is_open()) {
            std::cout << "> Cant open file.\n";
            return;
        }
        std::stringstream buffer;
        buffer << inFile.rdbuf();
        std::string content = buffer.str();
        inFile.close();

        std::string resultText;
        if (choice == 1) {
            resultText = cipher.encrypt(content);
            std::cout << "> Text encrypted successfully.\n";
        }
        else if (choice == 2) {
            resultText = cipher.decrypt(content);
            std::cout << "> Text decrypted successfully.\n";
        }
        else {
            std::cout << "> Invalid choice.\n";
            return;
        }

        std::ofstream outFile(outputPath);
        if (outFile.is_open()) {
            outFile << resultText;
            outFile.close();
            std::cout << "> Saved to " << outputPath << "\n";
        }
        else {
            std::cout << "> Error: Cannot open output file.\n";
        }

    }
    catch (const std::exception& e) {
        std::cout << "> Cipher Error: " << e.what() << "\n";
    }
}