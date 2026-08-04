#include <bits/stdc++.h>
#include <limits.h>
using namespace std;
char board[3][3] = {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};
char player = 'X';
char ai = 'O';
void printBoard() {
    cout << "\n";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}
bool isMovesLeft() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == '_')
                return true;
    return false;
}
int evaluate() {
    for(int row = 0; row < 3; row++) {
        if(board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if(board[row][0] == ai) return +10;
            else if(board[row][0] == player) return -10;
        }
    }

    for(int col = 0; col < 3; col++) {
        if(board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if(board[0][col] == ai) return +10;
            else if(board[0][col] == player) return -10;
        }
    }

    if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if(board[0][0] == ai) return +10;
        else if(board[0][0] == player) return -10;
    }

    if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if(board[0][2] == ai) return +10;
        else if(board[0][2] == player) return -10;
    }

    return 0;
}

int minimax(int depth, bool isMax, int alpha, int beta) {
    int score = evaluate();

    if(score == 10 || score == -10)
        return score;

    if(!isMovesLeft())
        return 0;

    if(isMax) {
        int best = INT_MIN;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == '_') {
                    board[i][j] = ai;

                    int val = minimax(depth + 1, false, alpha, beta);
                    best = max(best, val);

                    board[i][j] = '_';
                    alpha = max(alpha, best);

                    if(beta <= alpha)
                        break;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == '_') {
                    board[i][j] = player;

                    int val = minimax(depth + 1, true, alpha, beta);
                    best = min(best, val);

                    board[i][j] = '_';
                    beta = min(beta, best);

                    if(beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove() {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == '_') {
                board[i][j] = ai;

                int moveVal = minimax(0, false, INT_MIN, INT_MAX);

                board[i][j] = '_';

                if(moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    int x, y;

    while(true) {
        printBoard();

        cout << "Enter your move (row and column): ";
        cin >> x >> y;

        if(board[x][y] != '_') {
            cout << "Invalid move!\n";
            continue;
        }

        board[x][y] = player;

        if(evaluate() == -10) {
            printBoard();
            cout << "You win!\n";
            break;
        }

        if(!isMovesLeft()) {
            printBoard();
            cout << "Draw!\n";
            break;
        }

        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = ai;

        if(evaluate() == 10) {
            printBoard();
            cout << "AI wins!\n";
            break;
        }

        if(!isMovesLeft()) {
            printBoard();
            cout << "Draw!\n";
            break;
        }
    }

    return 0;
}
