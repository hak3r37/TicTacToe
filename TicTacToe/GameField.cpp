#include "GameField.h"
#include <iostream>
#include <vector>
#include <string>
using std::endl;
using std::cout;
using std::vector;
using std::to_string;
using std::string;

GameField::GameField() : GameField(3,3) {}

GameField::GameField(int sideSize, int fieldsToPoint) {
    this->sideSize = sideSize;
    this->emptyFieldsLeft = sideSize * sideSize;
    this->createFields();
    this->createVRows();
}

void GameField::createFields() {
    for (int i = 0; i < this->sideSize * this->sideSize; i++) {
        this->fields.push_back(SingleField());
    }
}

void GameField::createVRows() {
    //Poziome
    for (int x = 0; x < this->sideSize; x++) {
        vector<reference_wrapper<SingleField>> fields;
        for (int y = 0; y < this->sideSize; y++) {
            fields.push_back(this->fields.at(x + this->sideSize * y));
        }
        VirtualRow vRow = VirtualRow(fields);
        this->vRows.push_back(vRow);
    }
    //Pionowe
    for (int x = 0; x < this->sideSize; x++) {
        vector<reference_wrapper<SingleField>> fields;
        for (int y = 0; y < this->sideSize; y++) {
            fields.push_back(this->fields.at(y + this->sideSize * x));
        }
        VirtualRow vRow = VirtualRow(fields);
        this->vRows.push_back(vRow);
    }

    //todo: dodaæ ograniczenie - minimalna d³ugoœæ = minFieldsToPoint, aby unikn¹æ VRow d³ugoœci < minimalna liczba pól do zdobycia punktu
    //Skos [1/2] - Lewo góra -> Prawo dó³
    for (int i = 1; i <= this->sideSize - 3; i++) {
        vector<reference_wrapper<SingleField>> fields;
        for (int y = 0; y <= this->sideSize - (i + 1); y++) {
            fields.push_back(this->fields.at((y + i) + this->sideSize * (y)));
        }
        VirtualRow vRow = VirtualRow(fields);
        this->vRows.push_back(vRow);
    }
    for (int i = 0; i <= this->sideSize - 3; i++) {
        vector<reference_wrapper<SingleField>> fields;
        for (int y = 0; y <= this->sideSize - (i + 1); y++) {
            fields.push_back(this->fields.at(y + this->sideSize * (y + i)));
        }
        VirtualRow vRow = VirtualRow(fields);
        this->vRows.push_back(vRow);
    }
    //Skos [2/2] - Lewo dó³ -> Prawo góra
    for (int i = 2; i <= this->sideSize - 1; i++) {
        vector<reference_wrapper<SingleField>> fields;
        for (int y = 0; y <= i; y++) {
            fields.push_back(this->fields.at(y + this->sideSize * (i - y)));
        }
        VirtualRow vRow = VirtualRow(fields);
        this->vRows.push_back(vRow);
    }
    for (int i = 1; i <= this->sideSize - 3; i++) {
        vector<reference_wrapper<SingleField>> fields;
        for (int y = i; y <= this->sideSize - 1; y++) {
            fields.push_back(this->fields.at((this->sideSize - (y - i) - 1) + this->sideSize * y));
        }
        VirtualRow vRow = VirtualRow(fields);
        this->vRows.push_back(vRow);
    }
    system("pause");
}

void GameField::printBoard() {
    this->printBoard(false);
}

void GameField::printBoard(bool useCoords) {
    int charsToInt = (useCoords ? to_string(this->sideSize - 1).length()*2+1 : to_string(this->sideSize * this->sideSize - 1).length());
    string roofString = "";
    string fillSignSpaces = "";
    while (roofString.length() < charsToInt) roofString = "-" + roofString;
    while (fillSignSpaces.length() < charsToInt-1) fillSignSpaces = " " + fillSignSpaces;
    vector<string> lines;
    for (int i = 0; i < this->sideSize * 2 + 1; i++) lines.push_back("");
    system("cls");
    for (int row = 0; row < this->sideSize; row++) {
        for (int col = 0; col < this->sideSize; col++) {
            int fieldNo = col + row * this->sideSize;
            string fieldNoString = (useCoords ? to_string(col)+","+to_string(row) : to_string(fieldNo));
            if (this->fields.at(fieldNo).getChar() == SingleField::NULL_CHAR)
                while (fieldNoString.length() < charsToInt) fieldNoString = " " + fieldNoString;
            else fieldNoString = fillSignSpaces + this->fields.at(fieldNo).getChar();
            int topLine = row * 2;
            if (col == 0 && row == 0) {
                lines.at(topLine) = lines.at(topLine) + "+--"+roofString+"--+";
                lines.at(topLine + 1) = lines.at(topLine + 1) + "|  " + fieldNoString + "  |";
                lines.at(topLine + 2) = lines.at(topLine + 2) + "+--" + roofString + "--+";
            }
            else if (row == 0) {
                lines.at(topLine) = lines.at(topLine) + "--" + roofString + "--+";
                lines.at(topLine + 1) = lines.at(topLine + 1) + "  " + fieldNoString + "  |";
                lines.at(topLine + 2) = lines.at(topLine + 2) + "--" + roofString + "--+";
            }
            else if (col == 0) {
                lines.at(topLine + 1) = lines.at(topLine + 1) + "|  " + fieldNoString + "  |";
                lines.at(topLine + 2) = lines.at(topLine + 2) + "+--" + roofString + "--+";
            }
            else {
                lines.at(topLine + 1) = lines.at(topLine + 1) + "  " + fieldNoString + "  |";
                lines.at(topLine + 2) = lines.at(topLine + 2) + "--" + roofString + "--+";
            }
        }
    }
    for (int line = 0; line < lines.size(); line++) {
        cout << lines.at(line) << endl;
    }
}

bool GameField::emptyFieldsExists() {
    if (this->emptyFieldsLeft == 0) return false;
    return true;
}

void GameField::resetBoard() {
    for (int i = 0; i < this->sideSize * this->sideSize; i++) {
        this->fields.at(i).resetChar();
    }
    this->emptyFieldsLeft = this->sideSize * this->sideSize;
}

bool GameField::makeMove(char player, int fieldNo) {
    if (fieldNo < 0 || fieldNo >= this->fields.size()) {
        cout << "Podano zle pole. Wybierz pole z zakresu [0," << this->fields.size() - 1 << "]" << endl;
        system("pause");
        return false;
    }
    if (this->fields.at(fieldNo).getChar() != SingleField::NULL_CHAR) {
        cout << "Podane pole jest juz zajete. Wybierz pole z zakresu [0," << this->fields.size() - 1 << "] bez pol juz wybranych" << endl;
        system("pause");
        return false;
    }
    if (this->emptyFieldsLeft == 0) {
        cout << "Nie ma wiecej pol do wybrania" << endl;
        system("pause");
        return false;
    }
    this->fields.at(fieldNo).setChar(player);
    this->emptyFieldsLeft--;
    return true;
}

vector<Points> GameField::getPoints() {
    vector<Points> points;
    vector<vector<reference_wrapper<SingleField>>> allFieldsToClear;
    for (int i = 0; i < this->vRows.size(); i++) {
        Dominant rowDominant = this->vRows.at(i).checkRow();
        if (rowDominant.sign == SingleField::NULL_CHAR) continue;
        
        Points rowPoint = Points{};
        rowPoint.sign = rowDominant.sign;
        rowPoint.points = rowDominant.strike - 2;
        points.push_back(rowPoint);
        allFieldsToClear.push_back(rowDominant.fields);
    }

    for (int i = 0; i < allFieldsToClear.size(); i++) {
        for (int y = 0; y < allFieldsToClear.at(i).size(); y++) {
            if (allFieldsToClear.at(i).at(y).get().getChar() != SingleField::NULL_CHAR) {
                this->emptyFieldsLeft--;
                allFieldsToClear.at(i).at(y).get().resetChar();
            }
        }
    }
    return points;
}

void GameField::checkVRows()
{
    if (this->fields.size() != this->emptyFieldsLeft) return;
    for (int i = 0; i < this->vRows.size(); i++) {
        this->vRows.at(i).setSigns('_');
        this->printBoard();
        system("pause");
        this->vRows.at(i).resetSigns();
    }
}
