#pragma once
#include "Player.h"

class SingleField {
    static int AUTO_ID;
    int id;
    char sign;
public:
    static const char NULL_CHAR;
    SingleField();
    bool setChar(Player& player);
    bool setChar(char player);
    void resetChar();
    char getChar();
};

