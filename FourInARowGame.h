#ifndef FOUR_IN_A_ROW_BOARD_H
#define FOUR_IN_A_ROW_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard() {
        rows = 6;
        columns = 7;
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            fill(board[i], board[i] + columns, '.');
        }
    }

    ~FourInARowBoard() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    bool update_board(int x, int y, char symbol) override {
        if (y < 0 || y >= columns || board[0][y] != '.') {
            return false;
        }
        for (int i = rows - 1; i >= 0; --i) {
            if (board[i][y] == '.') {
                board[i][y] = symbol;
                last_move = {i, y};
                ++n_moves;
                return true;
            }
        }
        return false;
    }

    void display_board() override {
        string display;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                display += board[i][j];
                display += " ";
            }
            display += "\n";
        }
        display += "1 2 3 4 5 6 7\n";
        cout << display;
    }

    bool is_win() override {
        return check_win(last_move.first, last_move.second);
    }

    bool is_draw() override {
        return n_moves == rows * columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

    bool isValidMove(int col) {
        return col >= 0 && col < columns && board[0][col] == '.';
    }

    bool simulateMove(int row, int col, char marker) {
        board[row][col] = marker;
        bool win = check_win(row, col);
        board[row][col] = '.'; // Undo move
        return win;
    }

private:
    pair<int, int> last_move = {-1, -1};
    friend class StrongAIPlayer;
    bool check_win(int row, int col) {
        if (row == -1 || col == -1) return false;
        const int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        char symbol = board[row][col];

        for (auto [dr, dc] : directions) {
            int count = 1;
            count += count_in_direction(row, col, dr, dc, symbol);
            count += count_in_direction(row, col, -dr, -dc, symbol);
            if (count >= 4) {
                return true;
            }
        }
        return false;
    }

    int count_in_direction(int row, int col, int dr, int dc, char symbol) {
        int count = 0;
        for (int step = 1; step < 4; ++step) {
            int nr = row + dr * step, nc = col + dc * step;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < columns && board[nr][nc] == symbol) {
                ++count;
            } else {
                break;
            }
        }
        return count;
    }
};

class HumanPlayer : public Player<char> {
public:
    HumanPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << name << ", enter column (1-7): ";
        cin >> y;
        --y;
        x = 0; 
    }
};

class RandomAIPlayer : public Player<char> {
public:
    RandomAIPlayer(string name, char symbol) : Player<char>(name, symbol) {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    void getmove(int& x, int& y) override {
        y = rand() % 7;
        x = 0; 
    }
};

class StrongAIPlayer : public Player<char> {
public:
    StrongAIPlayer(string name, char symbol) : Player<char>(name, symbol) {}

    void getmove(int& x, int& y) override {
        char opponentMarker = (symbol == 'X') ? 'O' : 'X';

        // 1. Check for winning move
        for (y = 0; y < 7; ++y) {
            if (board->isValidMove(y)) {
                for (int row = 5; row >= 0; --row) {
                    if (board->board[row][y] == '.') {
                        if (board->simulateMove(row, y, symbol)) {
                            x = row;
                            return;
                        }
                        break;
                    }
                }
            }
        }

        // 2. Check to block opponent's winning move
        for (y = 0; y < 7; ++y) {
            if (board->isValidMove(y)) {
                for (int row = 5; row >= 0; --row) {
                    if (board->board[row][y] == '.') {
                        if (board->simulateMove(row, y, opponentMarker)) {
                            x = row;
                            return;
                        }
                        break;
                    }
                }
            }
        }

        // 3. Random valid move
        vector<int> validMoves;
        for (y = 0; y < 7; ++y) {
            if (board->isValidMove(y)) {
                validMoves.push_back(y);
            }
        }
        if (!validMoves.empty()) {
            y = validMoves[rand() % validMoves.size()];
            for (int row = 5; row >= 0; --row) {
                if (board->board[row][y] == '.') {
                    x = row;
                    return;
                }
            }
        }

        x = -1; // No valid move
        y = -1;
    }

    void setBoard(FourInARowBoard* gameBoard) {
        board = gameBoard;
    }

private:
    FourInARowBoard* board = nullptr;
};

#endif 
// ///////////////////////////////////// impl


void FourInARowGame() {
    FourInARowBoard game;  
    HumanPlayer player1("Player 1", 'X');
    HumanPlayer player2("Player 2", 'O');
    RandomAIPlayer randomAI("Random AI", 'O');
    StrongAIPlayer strongAI("Strong AI", 'O');
    strongAI.setBoard(&game); 

    cout << "Welcome to Four In A Row!\n";
    cout << "Select game mode:\n";
    cout << "1. Player 1 vs Player 2\n";
    cout << "2. Player 1 vs Random AI\n";
    cout << "3. Player 1 vs Strong AI\n";
    int choice;
    cin >> choice;

    Player<char>* currentPlayer = &player1; 
    Player<char>* opponent = nullptr;

    switch (choice) {
        case 1:
            opponent = &player2;
            break;
        case 2:
            opponent = &randomAI;
            break;
        case 3:
            opponent = &strongAI;
            break;
        default:
            cout << "Invalid choice. Exiting.\n";
            return;
    }
    game.display_board();

    bool isGameOver = false;
    while (!isGameOver) {
        int x = 0, y;
        currentPlayer->getmove(x, y); 

        if (!game.update_board(x, y, currentPlayer->getsymbol())) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        game.display_board(); 

        if (game.is_win()) {
            cout << currentPlayer->getname() << " wins!\n";
            isGameOver = true;
        } else if (game.is_draw()) {
            cout << "The game is a draw!\n";
            isGameOver = true;
        } else {
            currentPlayer = (currentPlayer == &player1) ? opponent : &player1;
        }
    }

    cout << "Game over. Thanks for playing!\n";
}
