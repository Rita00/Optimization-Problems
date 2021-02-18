#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void getInput(string input){

}

void res(int **board, int size, int maxMoves) {
    char allMoves[] = {'A', 'W', 'S', 'D'}, move;
    int current, bef;
    for (int k = 0; k < maxMoves; k++) {
        move = allMoves[rand() % 4];
        for (int i = 0; i < size; i++) {
            if (move == 'A' || move == 'W') {
                for (int j = size - 1; j <= 0; j--) {
                    if (move == 'A')
                        current = board[i][j], bef = board[i][j - 1];
                    else
                        current = board[i][j], bef = board[i - 1][j];

                    if (bef && current && (bef == current)) {
                        board[i][j - 1] = bef + current;
                        board[i][j] = 0;
                        if (j > 0)
                            j--;
                    }
                }
            } else {
                for (int j = 0; j < size; j++) {
                    if (move == 'S')
                        current = board[i][j], bef = board[i][j + 1];
                    else
                        current = board[i][j], bef = board[i + 1][j];
                    if (bef && current && (bef == current)) {
                        board[i][j - 1] = bef + current;
                        board[i][j] = 0;
                        if (j < size)
                            j++;
                    }
                }
            }
        }
    }

}

int main() {
	string input;
	//faster with this lines
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	//input
	cin >> input;
    cout << input << "\n";
    return 0;
}
 
 