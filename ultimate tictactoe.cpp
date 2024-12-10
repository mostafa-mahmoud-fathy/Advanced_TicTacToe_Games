#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding rand()
using namespace std;

// SubBoard Class
class SubBoard {
public:
    char cells[3][3];
    bool isWon;
    bool isTied;
    char winner;

    SubBoard() : isWon(false), isTied(false), winner(' ') {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                cells[i][j] = ' ';
    }

    bool isFull() const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (cells[i][j] == ' ')
                    return false;
        return true;
    }
};

// MainBoard Class
class MainBoard {
public:
    SubBoard boards[3][3];
    char mainGrid[3][3];

    MainBoard() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                mainGrid[i][j] = ' ';
    }

    bool isFull() const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (mainGrid[i][j] == ' ')
                    return false;
        return true;
    }
};

// Function to display the Ultimate Tic-Tac-Toe board
void displayMainBoard(const MainBoard &game) {
    for (int mainRow = 0; mainRow < 3; ++mainRow) {
        for (int subRow = 0; subRow < 3; ++subRow) {
            for (int mainCol = 0; mainCol < 3; ++mainCol) {
                for (int subCol = 0; subCol < 3; ++subCol) {
                    cout << game.boards[mainRow][mainCol].cells[subRow][subCol];
                    if (subCol < 2) cout << "|";
                }
                if (mainCol < 2) cout << " || ";
            }
            cout << endl;
        }
        if (mainRow < 2) cout << "=========================" << endl;
    }
}

// Function to validate and make a move
bool makeMove(SubBoard &board, int row, int col, char player) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board.cells[row][col] != ' ')
        return false;
    board.cells[row][col] = player;
    return true;
}

// Function to check for a win in a sub-board
bool checkWin(const SubBoard &board, char player) {
    for (int i = 0; i < 3; ++i) {
        if ((board.cells[i][0] == player && board.cells[i][1] == player && board.cells[i][2] == player) ||
            (board.cells[0][i] == player && board.cells[1][i] == player && board.cells[2][i] == player))
            return true;
    }
    if ((board.cells[0][0] == player && board.cells[1][1] == player && board.cells[2][2] == player) ||
        (board.cells[0][2] == player && board.cells[1][1] == player && board.cells[2][0] == player))
        return true;
    return false;
}

// Function to check for a win on the main board
bool checkMainWin(const MainBoard &game, char player) {
    for (int i = 0; i < 3; ++i) {
        if ((game.mainGrid[i][0] == player && game.mainGrid[i][1] == player && game.mainGrid[i][2] == player) ||
            (game.mainGrid[0][i] == player && game.mainGrid[1][i] == player && game.mainGrid[2][i] == player))
            return true;
    }
    if ((game.mainGrid[0][0] == player && game.mainGrid[1][1] == player && game.mainGrid[2][2] == player) ||
        (game.mainGrid[0][2] == player && game.mainGrid[1][1] == player && game.mainGrid[2][0] == player))
        return true;
    return false;
}

// AI Move Selection
pair<int, int> getAIMove(const SubBoard &board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.cells[i][j] == ' ') {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should never reach here
}

// Main Game Logic
int main() {
    MainBoard game;
    char currentPlayer = 'X';
    int nextMainRow = -1, nextMainCol = -1;
    int gameMode;
    srand(static_cast<unsigned>(time(0)));

    cout << "Welcome to Ultimate Tic-Tac-Toe!\n";
    cout << "Choose Game Mode:\n";
    cout << "1. Two-player mode\n";
    cout << "2. Player vs AI\n";
    cin >> gameMode;

    while (true) {
        displayMainBoard(game);
        cout << "Player " << currentPlayer << "'s turn.\n";

        int mainRow, mainCol, subRow, subCol;
        if (nextMainRow == -1 || game.boards[nextMainRow][nextMainCol].isWon || game.boards[nextMainRow][nextMainCol].isFull()) {
            cout << "Choose any open main grid (row column): ";
            cin >> mainRow >> mainCol;
        } else {
            mainRow = nextMainRow;
            mainCol = nextMainCol;
            cout << "You must play in main grid (" << mainRow << ", " << mainCol << ").\n";
        }

        if (mainRow < 0 || mainRow >= 3 || mainCol < 0 || mainCol >= 3 || game.boards[mainRow][mainCol].isWon) {
            cout << "Invalid main grid. Try again.\n";
            continue;
        }

        if (currentPlayer == 'X' || gameMode == 1) {
            cout << "Choose sub-grid (row column): ";
            cin >> subRow >> subCol;
        } else {
            tie(subRow, subCol) = getAIMove(game.boards[mainRow][mainCol]);
            cout << "AI chooses sub-grid (" << subRow << ", " << subCol << ").\n";
        }

        if (!makeMove(game.boards[mainRow][mainCol], subRow, subCol, currentPlayer)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        if (checkWin(game.boards[mainRow][mainCol], currentPlayer)) {
            game.boards[mainRow][mainCol].isWon = true;
            game.boards[mainRow][mainCol].winner = currentPlayer;
            game.mainGrid[mainRow][mainCol] = currentPlayer;
            cout << "Player " << currentPlayer << " wins the sub-board!\n";
        } else if (game.boards[mainRow][mainCol].isFull()) {
            game.boards[mainRow][mainCol].isTied = true;
            cout << "The sub-board is a draw!\n";
        }

        if (checkMainWin(game, currentPlayer)) {
            displayMainBoard(game);
            cout << "Player " << currentPlayer << " wins the main board!\n";
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        nextMainRow = subRow;
        nextMainCol = subCol;
    }

    return 0;
}
