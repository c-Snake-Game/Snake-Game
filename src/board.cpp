#include <iostream>
using namespace std;

int main() {
    int board[32][64];
    for (int i=0; i<32; i++) {
        for (int j=0; j<64; j++) {
            board[i][j] = 0;
        }
    }
    for (int i=0; i<32; i++) {
        for (int j=0; j<64; j++) {
            if (i == 0) board[i][j] = 9;
            else if (i == 31) board[i][j] = 9;
            else if (j == 0 || j == 1 || j == 62 || j==63) board[i][j] = 9;
            else if (j == 2 || j == 60) {
                if (i == 1 || i == 30) board[i][j] = 2;
                else board[i][j] = 1;
            }
            else if (i == 1 || i == 30) {
                if ( j>= 2 && j<= 61) {
                    if(j % 2 == 0) board[i][j] = 1;
                }
            }
        }
    }
    for (int i=0; i<32; i++) {
        for (int j=0; j<64; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}