#include <iostream>
#include <vector>

using namespace std;

// Function prototypes
void displayBoard(const vector<char>& board);
bool makeMove(vector<char>& board, int space, char player);
bool checkWin(const vector<char>& board, char player);
bool checkDraw(const vector<char>& board);
void resetBoard(vector<char>& board);

int main() {
    // Using a vector (dynamic array) to represent the 3x3 board
    vector<char> board(9);
    char currentPlayer = 'X';
    bool gameRunning = true;

    cout << "=================================\n";
    cout << "   Welcome to C++ Tic-Tac-Toe!   \n";
    cout << "=================================\n";

    // Main Replay Loop
    while (gameRunning) {
        resetBoard(board);
        currentPlayer = 'X'; // 'X' always goes first
        bool matchRunning = true;

        // Individual Match Loop
        while (matchRunning) {
            displayBoard(board);
            int choice;

            cout << "Player " << currentPlayer << ", enter a position (1-9): ";
            
            // Input validation loop
            while (!(cin >> choice) || choice < 1 || choice > 9 || !makeMove(board, choice, currentPlayer)) {
                cout << "Invalid move! Please enter an available number between 1 and 9: ";
                cin.clear(); // Clear error flag
                while (cin.get() != '\n'); // Discard bad input
            }

            // Check for Win or Draw (Conditional Logic)
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "\n🎉 Player " << currentPlayer << " wins the match! 🎉\n";
                matchRunning = false;
            } else if (checkDraw(board)) {
                displayBoard(board);
                cout << "\n🤝 It's a draw! Well played both. 🤝\n";
                matchRunning = false;
            } else {
                // Switch players using a ternary conditional operator
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        // Replay Option
        char replayChoice;
        cout << "\nDo you want to play again? (y/n): ";
        cin >> replayChoice;
        
        if (replayChoice != 'y' && replayChoice != 'Y') {
            gameRunning = false;
            cout << "\nThanks for playing! Goodbye.\n";
        }
    }

    return 0;
}

// Resets the array back to placeholder numbers 1-9
void resetBoard(vector<char>& board) {
    for (int i = 0; i < 9; ++i) {
        board[i] = '1' + i; // Converts integer to character '1'-'9'
    }
}

// Dynamically displays the current board state
void displayBoard(const vector<char>& board) {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n";
    cout << "\n";
}

// Validates and places the player's move on the board
bool makeMove(vector<char>& board, int space, char player) {
    int index = space - 1; // Convert 1-9 user input to 0-8 array index
    
    // Check if the spot is already taken by 'X' or 'O'
    if (board[index] == 'X' || board[index] == 'O') {
        return false; 
    }
    
    board[index] = player;
    return true;
}

// Conditional logic checking all 8 possible winning combinations
bool checkWin(const vector<char>& board, char player) {
    // Row wins
    if ((board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player)) {
        return true;
    }
    // Column wins
    if ((board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player)) {
        return true;
    }
    // Diagonal wins
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)) {
        return true;
    }
    
    return false;
}

// Loop to check if all spaces are filled (Draw condition)
bool checkDraw(const vector<char>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            return false; // Found a remaining spot, not a draw yet
        }
    }
    return true;
}
