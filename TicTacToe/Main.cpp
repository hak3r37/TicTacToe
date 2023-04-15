#include "TicTacToe.h"

int main()
{
    TicTacToe game = TicTacToe(11,3,3);
    Player player1 = Player('x');
    Player player2 = Player('o');
    Player player3 = Player('w');
    game.addPlayer(player1);
    game.addPlayer(player2);
    game.addPlayer(player3);
    game.Start();
}