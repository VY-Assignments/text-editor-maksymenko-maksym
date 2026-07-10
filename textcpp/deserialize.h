#pragma once
#include "line.h"
#include <string>

Line* deserializeLine(const std::string& data) {
    if (data.empty()) {
        return new TextLine("");
    }

    size_t firstBar = data.find('|');
    std::string type = data.substr(0, firstBar);

    if (type == "TEXT") {
        std::string text = data.substr(firstBar + 1);
        return new TextLine(text);
    }
    else if (type == "CHECKLIST") {
        std::string rest = data.substr(firstBar + 1);
        size_t secondBar = rest.find('|');

        std::string checkedStr = rest.substr(0, secondBar);
        std::string item = rest.substr(secondBar + 1);

        bool checked = (checkedStr == "1");
        return new ChecklistLine(item, checked);
    }
    else if (type == "CONTACT") {
        std::string rest = data.substr(firstBar + 1);

        size_t secondBar = rest.find('|');
        std::string name = rest.substr(0, secondBar);

        std::string afterName = rest.substr(secondBar + 1);
        size_t thirdBar = afterName.find('|');
        std::string surname = afterName.substr(0, thirdBar);
        std::string email = afterName.substr(thirdBar + 1);

        return new ContactLine(name, surname, email);
    }
    return new TextLine(data);
}