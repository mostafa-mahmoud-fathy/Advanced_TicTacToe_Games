#include "4x4_Tic_Tac_Toe.h"
#include "5x5_Tic_Tac_Toe.h"
#include "Misere_TicTacToe.h"
#include "Ultimate_Tic_Tac_Toe.h"
#include "Pyramid Tic-Tac-Toe.h"
#include "Word Tic-Tac-Toe.h"
#include "FourInARowGame.h"
#include "NumericTicTacToe.h"
using namespace std;

void showMenu() {
    cout << "Welcome to Tic Tac Toe!\n";
    cout << "Please select an option:\n";
    cout << "1. Play 4x4 Tic Tac Toe\n";
    cout << "2. Play 5x5 Tic Tac Toe\n";
    cout << "3. Play Misere Tic Tac Toe\n";
    cout << "4. Play Ultimate Tic Tac Toe\n";
    cout << "5. Play Pyramid Tic Tac Toe\n";
    cout << "6. Play Word Tic Tac Toe\n";
    cout << "7. play Four In A Row\n";
    cout << "8. Play Numeric Tic Tac Toe\n";
    cout << "9. Exit\n";
    cout << "Your choice: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 7) {
            cout << "Thank you for playing!\n";
            break;
        }

        // Declare pointers for the board and player array
        Board<char>* board;
        Player<char>* players[2];

        cout << "Select game mode:\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "Your choice: ";
        int mode;
        cin >> mode;

        if (mode != 1 && mode != 2) {
            cout << "Invalid game mode, returning to main menu.\n";
            continue;
        }

        switch (choice) {
            case 1: { // 4x4 Game
                cout << "4x4 Tic Tac Toe selected.\n";
                board = new TicTacToe_4X4<char>();

                // Player setup
                for (int i = 0; i < 2; ++i) {
                    cout << "Player " << (i + 1) << (i == 0 ? " (X): " : " (O): ");
                    if (mode == 2 && i == 1) {
                        cout << "Computer player will be used.\n";
                        players[i] = new Random_Player4X4<char>('O');
                    } else {
                        cout << "Enter name or type 'Random' for a computer player: ";
                        string name;
                        cin >> name;
                            players[i] = new Player4X4<char>(name, i == 0 ? 'X' : 'O');
                    }
                }
                break;
            }
            case 2: { // 5x5 Game
                cout << "5x5 Tic Tac Toe selected.\n";
                board = new TicTacToe_5X5<char>();

                // Player setup
                for (int i = 0; i < 2; ++i) {
                    cout << "Player " << (i + 1) << (i == 0 ? " (X): " : " (O): ");
                    if (mode == 2 && i == 1) {
                        cout << "Computer player will be used.\n";
                        players[i] = new Random_Player5x5<char>('O');
                    } else {
                        cout << "Enter name or type 'Random' for a computer player: ";
                        string name;
                        cin >> name;
                            players[i] = new Player5x5<char>(name, i == 0 ? 'X' : 'O');
                    }
                }
                break;
            }
            case 3: { // Misere Game
                cout << "Misere Tic Tac Toe selected.\n";
                board = new Misere_Board<char>();

                // Player setup
                for (int i = 0; i < 2; ++i) {
                    cout << "Player " << (i + 1) << (i == 0 ? " (X): " : " (O): ");
                    if (mode == 2 && i == 1) {
                        cout << "Computer player will be used.\n";
                        players[i] = new Misere_Random_Player<char>( 'O');
                    } else {
                        cout << "Enter name or type 'Random' for a computer player: ";
                        string name;
                        cin >> name;
                            players[i] = new Misere_Player<char>(name, i == 0 ? 'X' : 'O');
                    }
                }
                break;
            }
            case 4: { // Ultimate Game
                cout << "Ultimate Tic Tac Toe selected.\n";
                board = new UltimateBoard<char>();

                // Player setup
                for (int i = 0; i < 2; ++i) {
                    cout << "Player " << (i + 1) << (i == 0 ? " (X): " : " (O): ");
                    if (mode == 2 && i == 1) {
                        cout << "Computer player will be used.\n";
                        players[i] = new Ultimate_Random_Player<char>('O');
                    } else {
                        cout << "Enter name or type 'Random' for a computer player: ";
                        string name;
                        cin >> name;
                            players[i] = new Ultimate_Player<char>(name, i == 0 ? 'X' : 'O');

                    }
                }
                break;
            }
            case 5: { // Pyramid Game
                cout << "Pyramid Tic Tac Toe selected.\n";
                board = new PyramidBoard<char>();

                // Player setup
                for (int i = 0; i < 2; ++i) {
                    cout << "Player " << (i + 1) << (i == 0 ? " (X): " : " (O): ");
                    if (mode == 2 && i == 1) {
                        cout << "Computer player will be used.\n";
                        players[i] = new RandomPyramidPlayer<char>('O');
                    } else {
                        cout << "Enter name or type 'Random' for a computer player: ";
                        string name;
                        cin >> name;
                            players[i] = new PyramidPlayer<char>(name, i == 0 ? 'X' : 'O');
                    }
                }
                break;
            }
            case 6:{
                cout << "Word Tic Tac Toe selected.\n";
                board = new WordBoard();

                // Player setup
                for (int i = 0; i < 2; ++i) {
                    cout << "Player " << (i + 1) << (i == 0 ? " (X): " : " (O): ");
                    if (mode == 2 && i == 1) {
                        cout << "Computer player will be used.\n";
                        players[i] = new WordRandomPlayer('O');
                    } else {
                        cout << "Enter name or type 'Random' for a computer player: ";
                        string name;
                        cin >> name;
                        players[i] = new WordPlayer(name, i == 0 ? 'X' : 'O');
                    }
                }
                break;
            }
            case 7:{
                cout << "Four In A Row selected.\n";
                FourInARowGame();
            }
            case 8:{
                cout << "Numeric Tic Tac Toe selected.\n";
                Numerical_Tic_Tac_Toe();
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
