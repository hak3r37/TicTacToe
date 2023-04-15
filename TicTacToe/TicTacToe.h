#pragma once
#include "GameField.h"

class TicTacToe {
    int maxPoints;
    GameField gameField;
    GameField getGameField();
    vector<Player> players;
public:
    TicTacToe();
    TicTacToe(int sideSize, int fieldsToPoint, int maxPoints);
    bool addPlayer(Player& player);
    void Start();
};
