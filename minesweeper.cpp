#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 9; // Board size
const int MINES = 10; // Number of mines
vector<vector<char>> board(SIZE, vector<char>(SIZE, '-') );
vector<vector<int>> mineBoard(SIZE, vector<int>(SIZE, 0)); // Stores mine info
vector<vector<bool>> flagged(SIZE, vector<bool>(SIZE, false)); // Flagged cells
bool gameOver = false; // Game over flag
int flaggedMines = 0;

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
        gameOver = true;
        return;
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
            if ((board[i][j] == '-' && mineBoard[i][j] != -1) || (flagged[i][j] && mineBoard[i][j] != -1))
                return false;
        }
    }
    return true;
}

// Function to toggle flag on a cell
void toggleFlag(int x, int y) {
    if (board[x][y] == '-') {
        board[x][y] = 'F';
        flagged[x][y] = true;
        if (mineBoard[x][y] == -1) flaggedMines++;
    } else if (board[x][y] == 'F') {
        board[x][y] = '-';
        flagged[x][y] = false;
        if (mineBoard[x][y] == -1) flaggedMines--;
    }
}

// Main game loop
void playGame() {
    initializeBoard();
    while (!gameOver) {
        printBoard();
        int x, y;
        char action;
        cout << "Enter row, column, and action (r c [r/f]): ";
        cin >> x >> y >> action;
        
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Invalid input! Please enter values between 0 and " << SIZE-1 << "\n";
            continue;
        }
        
        if (action == 'r') {
            revealCells(x, y);
        } else if (action == 'f') {
            toggleFlag(x, y);
        } else {
            cout << "Invalid action! Use 'r' to reveal or 'f' to flag.\n";
            continue;
        }
        
        if (gameOver) {
            printBoard();
            cout << "Game Over! Better luck next time.\n";
            break;
        }
        
        if (checkWin()) {
            printBoard();
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
