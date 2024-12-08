#include <iostream>
#include "FourInARowGame.h"
using namespace std;

int main() {
    FourInARowGame game;
    game.startBoard();
    char playerMarkers[2] = {'X', 'O'};
    int mode;

    cout << "Welcome to Four-in-a-Row!" << endl;
    cout << "Choose a mode:" << endl;
    cout << "1. PlayerX vs PlayerO" << endl;
    cout << "2. Player vs AI" << endl;
    cin >> mode;

    while (mode != 1 && mode != 2) {
        cout << "Invalid choice! Please enter 1 or 2: ";
        cin >> mode;
    }


    bool isAI = (mode == 2);
    char aiMarker = 'O';
    char humanMarker = 'X';

    game.printBoard();

    int currentPlayer = 0;

    while (!game.GameOver()) {
        if (isAI && currentPlayer == 1) {
            // AI Move
            int col = game.AIMove(aiMarker, humanMarker);
            cout << "AI chooses column " << (col + 1) << endl;
            game.makeMove(col, aiMarker);
        } else {
            // Human Move
            int col;
            cout << "Player " << (currentPlayer + 1) << " (" << playerMarkers[currentPlayer] << "), choose a column (1-7): ";
            cin >> col;
            col -= 1; // Adjust for 0-based indexing

            if (!game.isValidMove(col)) {
                cout << "Invalid move. Try again!" << endl;
                continue;
            }

            game.makeMove(col, playerMarkers[currentPlayer]);
        }

        game.printBoard();

        if (game.GameOver()) break;

        currentPlayer = 1 - currentPlayer; // Switch players
    }

    if (game.getWinner() != 0) {
        if (isAI && game.getWinner() == 2) {
            cout << "AI wins!" << endl;
        } else {
            cout << "Player " << game.getWinner() << " wins!" << endl;
        }
    } else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}

