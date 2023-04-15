#include "TicTacToe.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

TicTacToe::TicTacToe() : TicTacToe(3, 3, 1) {}

TicTacToe::TicTacToe(int sideSize, int fieldsToPoint, int maxPoints) {
    if (fieldsToPoint > sideSize)
        fieldsToPoint = sideSize;
    this->gameField = GameField(sideSize, fieldsToPoint);
    this->maxPoints = maxPoints;
}

bool TicTacToe::addPlayer(Player& player) {
    for (int i = 0; i < this->players.size(); i++) {
        if (this->players.at(i).getSign() == player.getSign())
            return false;
    }
    this->players.push_back(player);
    return true;
}

//todo: OOP
void TicTacToe::Start() {
    if (this->players.size() < 2) {
        return;
    }
    bool nobodyHasMinWins = true;
    int currentPlayerId = 0;
    int chosenField = 0; //todo - GameField.getMove(player);
    while (nobodyHasMinWins) {
        char player = this->players.at(currentPlayerId).getSign(); //Kolejny gracz
        this->gameField.printBoard(false);
        for (int i = 0; i < this->players.size(); i++) {
            cout << "Player " << this->players.at(i).getSign() << " -> " << this->players.at(i).getPoints() << endl;
        }
        if (!this->gameField.emptyFieldsExists()) {
            cout << "Nie ma wiecej wolnych pol. Reset tablicy.";
            this->gameField.resetBoard();
            system("pause");
            continue;
        }
        cout << "Tura gracza " << player << endl;
        cout << "Podaj numer pola: ";
        cin >> chosenField;
        if (this->gameField.makeMove(player, chosenField)) {
            currentPlayerId++;
            if (currentPlayerId == this->players.size()) 
                currentPlayerId = 0;
        }
        vector<Points> pointsToAssign = gameField.getPoints();
        for (int i = 0; i < pointsToAssign.size(); i++) {
            for (int y = 0; y < this->players.size(); y++) {
                if (pointsToAssign.at(i).sign == this->players.at(y).getSign()) {
                    this->players.at(y).addPoints(pointsToAssign.at(i).points);
                    break;
                }
            }
        }
        for (int i = 0; i < this->players.size(); i++) {
            if (this->players.at(i).getPoints() >= this->maxPoints) {
                nobodyHasMinWins = false;
                cout << "WYGRANY: " << this->players.at(i).getSign() << " Punkty: " << this->players.at(i).getPoints() << endl;
            }
        }
    }
}

GameField TicTacToe::getGameField() {
    return this->gameField;
}