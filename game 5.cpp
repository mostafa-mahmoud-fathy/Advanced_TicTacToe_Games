#include <iostream>
#include <vector>
#include <tuple>
#include "NumericTicTacToe.h" 

using namespace std;

int main() {
    cout << "Welcome to Numerical Tic-Tac-Toe!" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Play against another human" << endl;
    cout << "2. Play against the AI" << endl;

    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice! Please enter 1 or 2: ";
        cin >> choice;
    }

    NumericTicTacToe game; 
    game.initializeBoard();

    bool AI = (choice == 2);
    cout << "Player 1 will use odd numbers (1, 3, 5, ...)." << endl;
    if (AI) {
        cout << "You are Player 1. The AI will play as Player 2 with even numbers (2, 4, 6, ...)." << endl;
    } else {
        cout << "Player 2 will use even numbers (2, 4, 6, ...)." << endl;
    }

    int currentPlayer = 1; 
    while (!game.GameOver()) {
        game.printBoard();

        if (currentPlayer == 1 || !AI) {
            // Human's turn
            int row, col, num;
            cout << "Player " << currentPlayer << "'s turn. Enter row, column, and number to place: ";
            cin >> row >> col >> num;

            while (!game.ValidMove(row, col, num, currentPlayer)) {
                cout << "Invalid move. Try again: ";
                cin >> row >> col >> num;
            }

            game.makeMove(row, col, num, currentPlayer);
        } else {
            // AI's turn
            cout << "AI  making its move..." << endl;
            auto [row, col, num] = game.getAIMove(); 
            game.makeMove(row, col, num, currentPlayer);
            cout << "AI placed " << num << " at (" << row << ", " << col << ")." << endl;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    game.printBoard();
    if (game.getWinner() == 1) {
        cout << "Player 1 wins!" << endl;
    } else if (game.getWinner() == 2) {
        if (AI) {
            cout << "AI wins!" << endl;
        } else {
            cout << "Player 2 wins!" << endl;
        }
    } else {
        cout << "It's a draw!" << endl;
    }

    return 0;
}
