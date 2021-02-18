#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

typedef struct Game{
    int dim;
    int moves;
    int** board;
}Game;

/*
int* split(string line, int size){
    int array[size];
    int i = 0;
    size_t pos = 0;
    string token;
    while ((pos = line.find(" ")) != string::npos) {
        //substring até pos
        token = line.substr(0, pos);
        array[i] = stoi(token,nullptr,10);
        //apaga string até pos+1
        line.erase(0, pos+1);
        i++;
    }
    return array;
}
*/

Game* getInput(){
    string input;
	//get boards
    int boards;
	cin >> boards;
    Game* game = (Game*) malloc(boards*sizeof(Game));
    //get dim and moves
	for(int i=0; i<boards; i++){
        cin >> game[i].dim >> game[i].moves;
        //get board
        game[i].board = (int**) malloc(game[i].dim*sizeof(int*));
        for(int r=0; r<game[i].dim; r++){
            for(int c=0; c<game[i].dim; c++){
                *((game[i].board)+r) = (int*) malloc(game[i].dim*sizeof(int));
                cin >> *(*(game[i].board+r)+c);
            }
        }
	}
    return game;
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
	getInput();
    cout << input << "\n";
    return 0;
}
 
