#include "cipher.h"
#include <string>
#include <cctype>

CaesarCipher::CaesarCipher(int key) : key_(key) {}

std::string CaesarCipher::encrypt(const std::string& text) {
	std::string result = text;
	for(char& c : result)
		if (std::isupper(c)) {
			c = 'A' + (c - 'A' + key_ +26) % 26;
		}
		else if (std::islower(c)) {
			c = 'a' + (c - 'a' + key_+26) % 26;
		}
	return result;
}

std::string CaesarCipher::decrypt(const std::string& text) {
	CaesarCipher reverse(-key_);
	return reverse.encrypt(text);
}

VigenereCipher::VigenereCipher(const std::string& key) : key_(key) {}

std::string VigenereCipher::encrypt(const std::string& text) {
    std::string result = text;
    int keyIndex = 0;

    for (char& c : result) {
        if (std::isalpha(c)) {
            int shift = std::toupper(key_[keyIndex % key_.size()]) - 'A';
			if (std::isupper(c)) {
				c = 'A' + (c - 'A' + shift + 26) % 26;
			}
			else if (std::islower(c)) {
				c = 'a' + (c - 'a' + shift + 26) % 26;
			}
            keyIndex++;
        }
    }
    return result;
}

std::string VigenereCipher::decrypt(const std::string& text) {
    std::string result = text;
    int keyIndex = 0;

    for (char& c : result) {
        if (std::isalpha(c)) {
            int shift = std::toupper(key_[keyIndex % key_.size()]) - 'A';
            if (std::isupper(c)) {
                c = 'A' + (c - 'A' - shift + 26) % 26;
            }
            else if (std::islower(c)) {
                c = 'a' + (c - 'a' - shift + 26) % 26;
            }
            keyIndex++;
        }
    }
    return result;
}