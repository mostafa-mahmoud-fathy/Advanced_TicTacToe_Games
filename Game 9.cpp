#include "Game 9.h"

int main() {
    int mode;
    cout << "Select a mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Random Player\n";
    cout << "Enter your choice:\n";
    cin >> mode;

    // Create a new game board of type SUSBoard
    SUSBoard<char>* board = new SUSBoard<char>(3, 3);

    Player<char>* players[2];

    if (mode == 1) {
        string name1, name2;
        cout << "Enter Player 1 name:\n";
        cin >> name1;
        cout << "Enter Player 2 name:\n";
        cin >> name2;

        players[0] = new SUSPlayer<char>(name1, 'S');
        players[1] = new SUSPlayer<char>(name2, 'U');

    } else if (mode == 2) {
        string name1;
        cout << "Enter Player name:\n";
        cin >> name1;

        players[0] = new SUSPlayer<char>(name1, 'S');
        players[1] = new SUSRandomPlayer<char>('U', 3);
    }

    // Set the board for each player
    players[0]->setBoard(board);
    players[1]->setBoard(board);

    // Create a game manager and run the game
    GameManager<char> gameManager(board, players);
    gameManager.run();

    // Clean up memory
    delete players[0];
    delete players[1];
    delete board;

    return 0;
}
