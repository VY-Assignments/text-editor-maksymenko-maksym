#include "textstorage.h"

TextStorage::~TextStorage() {
    clear();
}

void TextStorage::addLine(Line* line) {
    if (line) {
        lines.push_back(line);
    }
}

void TextStorage::printAll() const {
    for (const auto& line : lines) {
        line->print(); 
    }
}

void TextStorage::clear() {
    for (auto& line : lines) {
        delete line;
    }
    lines.clear();
}

std::string TextStorage::getSerializedText() const {
    std::string fullText;
    for (size_t i = 0; i < lines.size(); ++i) {
        fullText += lines[i]->serialize();
        if (i < lines.size() - 1) {
            fullText += "\n";
        }
    }
    return fullText;
}