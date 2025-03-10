#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 9; // Board size
const int MINES = 10; // Number of mines
vector<vector<char>> board(SIZE, vector<char>(SIZE, '-'));
vector<vector<int>> mineBoard(SIZE, vector<int>(SIZE, 0)); // Stores mine info

// Function to print the board
void printBoard() {
    cout << "\n   ";
    for (int i = 0; i < SIZE; i++) cout << i << " ";
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " |";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << "|\n";
    }
}

// Function to place mines randomly
void placeMines() {
    srand(time(0));
    int count = 0;
    while (count < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (mineBoard[x][y] == 0) {
            mineBoard[x][y] = -1; // -1 represents a mine
            count++;
        }
    }
}

// Function to count mines around a cell
int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && mineBoard[nx][ny] == -1)
                count++;
        }
    }
    return count;
}

// Function to initialize the board
void initializeBoard() {
    placeMines();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (mineBoard[i][j] != -1) {
                mineBoard[i][j] = countMines(i, j);
            }
        }
    }
}

// Function to reveal cells recursively (DFS)
void revealCells(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] != '-') return;
    if (mineBoard[x][y] == -1) {
        cout << "Game Over! You hit a mine!\n";
        exit(0);
    }
    board[x][y] = mineBoard[x][y] + '0';
    if (mineBoard[x][y] == 0) {
        board[x][y] = ' ';
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                revealCells(x + i, y + j);
            }
        }
    }
}

// Function to check if the player has won
bool checkWin() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '-' && mineBoard[i][j] != -1) return false;
        }
    }
    return true;
}

// Main game loop
void playGame() {
    initializeBoard();
    while (true) {
        printBoard();
        int x, y;
        cout << "Enter row and column (x y): ";
        cin >> x >> y;
        revealCells(x, y);
        if (checkWin()) {
            cout << "Congratulations! You won the game!\n";
            break;
        }
    }
}

int main() {
    cout << "Welcome to Minesweeper!" << endl;
    playGame();
    return 0;
}
