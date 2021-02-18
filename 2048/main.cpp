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

void printMatrix(int** matrix,int dim){
    for(int r=0; r<dim; r++){
        for(int c=0; c<dim; c++){
            printf("%i\t",matrix[r][c]);
        }
        printf("\n");
    }
}

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
                game[i].board[r] = (int*) malloc(game[i].dim*sizeof(int));
                cin >> game[i].board[r][c];
            }
        }
	}
    return game;
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
	Game* game = getInput();
    printMatrix(game[0].board,game[0].dim);
    cout << input << "\n";
    return 0;
}
 
