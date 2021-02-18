#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void getInput(string input){

}

void res(int **board, int size) {
    char allMoves[] = {'A', 'W', 'S', 'D'}, move = allMoves[rand() % 4];
    for (int i = 0; i < size; i++) {
        if (move == 'A' || move == 'W') {
            for (int j = size - 1; j <= 0; j++) {
                int current = board[i][j], bef = board[i][j - 1];
                if (bef && current && (bef == current)) {
                    board[i][size - 2] = board[i][size - 1] + board[i][size - 2];
                    board[i][size - 1] = 0;
                }
            }
        } else {
            for (int j = 0; j < size; j++) {

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
 
 