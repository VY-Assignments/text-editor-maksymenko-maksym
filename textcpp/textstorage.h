#pragma once
#include <vector>
#include "Line.h"

class TextStorage {
private:
    std::vector<Line*> lines; 
public:
    TextStorage() = default;
    ~TextStorage();
    void addLine(Line* line);
    void printAll() const;
    void clear();
    std::string getSerializedText() const;
    size_t getLinesCount() const { return lines.size(); }
};