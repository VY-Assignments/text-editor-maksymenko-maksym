#pragma once
#include <string>
#include <iostream>
#include <sstream>

class Line {
public:
    virtual void print() const = 0;
    virtual std::string serialize() const = 0;
    virtual ~Line() = default;
};

class TextLine : public Line {
private:
    std::string text;
public:
    TextLine(const std::string& t) : text(t) {}

    void print() const override {
        std::cout << "Text: " << text << std::endl;
    }

    std::string serialize() const override {
        return "TEXT|" + text;
    }
};

class ChecklistLine : public Line {
private:
    std::string item;
    bool checked;
public:
    ChecklistLine(const std::string& i, bool c) : item(i), checked(c) {}

    void print() const override {
        std::cout << "[ " << (checked ? "x" : " ") << " ] " << item << std::endl;
    }
        
    std::string serialize() const override {
        return "CHECKLIST|" + std::to_string(checked) + "|" + item;
    }
};

class ContactLine : public Line {
private:
    std::string name;
    std::string surname;
    std::string email;
public:
    ContactLine(const std::string& n, const std::string& s, const std::string& e)
        : name(n), surname(s), email(e) {
    }

    void print() const override {
        std::cout << "Contact - " << name << " " << surname
            << ", email: " << email << std::endl;
    }

    std::string serialize() const override {
        return "CONTACT|" + name + "|" + surname + "|" + email;
    }
};