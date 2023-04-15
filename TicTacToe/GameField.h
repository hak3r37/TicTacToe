#pragma once
#include<vector>
#include "SingleField.h"
#include "VirtualRow.h"
using std::vector;

struct Points {
    int points;
    char sign;
};

class GameField {
    vector<SingleField> fields;
    vector<VirtualRow> vRows;
    int sideSize;
    int emptyFieldsLeft;
    void createFields();
    void createVRows();
    void checkVRows();
public:
    GameField();
    GameField(int sideSize, int fieldsToPoint);
    bool emptyFieldsExists();
    bool makeMove(char player, int fieldNo);
    void printBoard();
    void printBoard(bool useCoords);
    void resetBoard();
    vector<Points> getPoints();
};