#include "singleField.h"

int SingleField::AUTO_ID = 0;
const char SingleField::NULL_CHAR = ' ';

SingleField::SingleField() {
    this->sign = SingleField::NULL_CHAR;
    this->id = SingleField::AUTO_ID++;
}

bool SingleField::setChar(Player& player) {
    return this->setChar(player.getSign());
}

bool SingleField::setChar(char player) {
    if (this->getChar() == SingleField::NULL_CHAR) {
        this->sign = player;
        return true;
    }
    return false;
}

char SingleField::getChar() {
    return this->sign;
}

void SingleField::resetChar() {
    this->sign = SingleField::NULL_CHAR;
}