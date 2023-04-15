#include "VirtualRow.h"
#include<iostream>
using std::reference_wrapper;

VirtualRow::VirtualRow(vector<reference_wrapper<SingleField>> rowFields) : VirtualRow(rowFields, 3) {}

VirtualRow::VirtualRow(vector<reference_wrapper<SingleField>> rowFields, int fieldsToPoint) {
    this->rowFields = rowFields;
    this->fieldsToPoint = fieldsToPoint;
}

Dominant VirtualRow::checkRow() {
    vector<reference_wrapper<SingleField>> rowFieldsToClear;
    vector<reference_wrapper<SingleField>> maxRowFieldsToClear;
    Dominant dominant{};
    dominant.sign = SingleField::NULL_CHAR;
    dominant.strike = 0;
    dominant.fields = rowFieldsToClear;

    int currentStrike = 1, maxStrike = 0;
    char currentStrikeChar = this->rowFields.at(0).get().getChar();
    char maxStrikeChar = SingleField::NULL_CHAR;
    rowFieldsToClear.push_back(this->rowFields.at(0));

    for (int fieldNo = 1; fieldNo < this->rowFields.size(); fieldNo++) {
        if (this->rowFields.at(fieldNo).get().getChar() == currentStrikeChar) {
            currentStrike++;
            rowFieldsToClear.push_back(this->rowFields.at(fieldNo));
        }
        else {
            if (currentStrike > maxStrike && currentStrikeChar != SingleField::NULL_CHAR) {
                maxStrike = currentStrike;
                maxStrikeChar = currentStrikeChar;
                maxRowFieldsToClear = rowFieldsToClear;
            }
            currentStrike = 1;
            currentStrikeChar = this->rowFields.at(fieldNo).get().getChar();
            rowFieldsToClear.clear();
            rowFieldsToClear.push_back(this->rowFields.at(fieldNo));
        }
    }
    //Sprawdzenie po ostatnim polu tj. "___xoxx_xxxx" - przy ostatnich polach nie wejdzie w else'a bo s¹ te same znaki
    if (currentStrike > maxStrike && currentStrikeChar != SingleField::NULL_CHAR) {
        maxStrike = currentStrike;
        maxStrikeChar = currentStrikeChar;
        maxRowFieldsToClear = rowFieldsToClear;
    }

    if (maxStrike >= this->fieldsToPoint) {
        dominant.sign = maxStrikeChar;
        dominant.strike = maxStrike;
        dominant.fields = maxRowFieldsToClear;
    }

    return dominant;
}

void VirtualRow::setSigns(char sign) {
    for (int i = 0; i < this->rowFields.size(); i++) {
        this->rowFields.at(i).get().setChar(sign);
    }
}

void VirtualRow::resetSigns()
{
    for (int i = 0; i < this->rowFields.size(); i++) {
        this->rowFields.at(i).get().resetChar();
    }
}
