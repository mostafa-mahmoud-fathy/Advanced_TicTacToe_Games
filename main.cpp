#include "4x4_Tic_Tac_Toe.h"
#include "5x5_Tic_Tac_Toe.h"
#include "Misere_TicTacToe.h"
#include "Ultimate_Tic_Tac_Toe.h"

using namespace std;

void showMenu() {
    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Please select an option:\n";
    cout << "1. Play 4x4 Tic Tac Toe\n";
    cout << "2. Play 5x5 Tic Tac Toe\n";
    cout << "3. Play Misere Tic Tac Toe\n";
    cout << "4. Play Ultimate Tic Tac Toe\n";  // Added Ultimate option
    cout << "5. Exit\n";
    cout << "Your choice: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 5) {  // Adjusted exit option to 5
            cout << "Thank you for playing!\n";
            break;
        }

        // Declare pointers for the board and player array
        Board<char>* board;
        Player<char>* players[2];

        switch (choice) {
            case 1: { // 4x4 Game
                cout << "4x4 Tic Tac Toe selected.\n";

                // Create the board
                board = new TicTacToe_4X4<char>();

                // Player 1 setup
                cout << "Player 1 (X): Enter name or type 'Random' for a computer player: ";
                string name1;
                cin >> name1;
                if (name1 == "Random") {
                    players[0] = new Random_Player4X4<char>('X');
                } else {
                    players[0] = new Player4X4<char>(name1, 'X');
                }

                // Player 2 setup
                cout << "Player 2 (O): Enter name or type 'Random' for a computer player: ";
                string name2;
                cin >> name2;
                if (name2 == "Random") {
                    players[1] = new Random_Player4X4<char>('O');
                } else {
                    players[1] = new Player4X4<char>(name2, 'O');
                }

                break;
            }
            case 2: { // 5x5 Game
                cout << "5x5 Tic Tac Toe selected.\n";

                // Create the board
                board = new TicTacToe_5X5<char>();

                // Player 1 setup
                cout << "Player 1 (X): Enter name or type 'Random' for a computer player: ";
                string name1;
                cin >> name1;
                if (name1 == "Random") {
                    players[0] = new Random_Player5x5<char>('X');
                } else {
                    players[0] = new Player5x5<char>(name1, 'X');
                }

                // Player 2 setup
                cout << "Player 2 (O): Enter name or type 'Random' for a computer player: ";
                string name2;
                cin >> name2;
                if (name2 == "Random") {
                    players[1] = new Random_Player5x5<char>('O');
                } else {
                    players[1] = new Player5x5<char>(name2, 'O');
                }

                break;
            }
            case 3: { // Misere Game
                cout << "Misere Tic Tac Toe selected.\n";

                // Create the board
                board = new Misere_Board<char>();

                // Player 1 setup
                cout << "Player 1 (X): Enter name or type 'Random' for a computer player: ";
                string name1;
                cin >> name1;
                if (name1 == "Random") {
                    players[0] = new Misere_Random_Player<char>('X');
                } else {
                    players[0] = new Misere_Player<char>(name1, 'X');
                }

                // Player 2 setup
                cout << "Player 2 (O): Enter name or type 'Random' for a computer player: ";
                string name2;
                cin >> name2;
                if (name2 == "Random") {
                    players[1] = new Misere_Random_Player<char>('O');
                } else {
                    players[1] = new Misere_Player<char>(name2, 'O');
                }

                break;
            }
            case 4: { // Ultimate Game
                cout << "Ultimate Tic Tac Toe selected.\n";

                // Create the board
                board = new UltimateBoard<char>();

                // Player 1 setup
                cout << "Player 1 (X): Enter name or type 'Random' for a computer player: ";
                string name1;
                cin >> name1;
                if (name1 == "Random") {
                    players[0] = new Ultimate_Random_Player<char>('X');
                } else {
                    players[0] = new Ultimate_Player<char>(name1, 'X');
                }

                // Player 2 setup
                cout << "Player 2 (O): Enter name or type 'Random' for a computer player: ";
                string name2;
                cin >> name2;
                if (name2 == "Random") {
                    players[1] = new Ultimate_Random_Player<char>('O');
                } else {
                    players[1] = new Ultimate_Player<char>(name2, 'O');
                }

                break;
            }
            default:
                cout << "Invalid choice, please try again.\n";
                continue;
        }

        // Use the GameManager to run the game
        GameManager<char> manager(board, players);
        manager.run();

        // Clean up memory
        delete board;
        delete players[0];
        delete players[1];
    }

    return 0;
}
