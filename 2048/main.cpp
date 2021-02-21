/**
 * @author Dylan Gonçalves Perdigão - 2018233092
 * @author Ana Rita Rodrigues -  xxxxxxxxx
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

typedef struct Board{
    int size;
    int max_moves;
    vector<int> vector;
}Board;

/**
 * Permite obter o vetor que representa o tabuleiro do stdin
 * @param size numero de linhas/colunas do tabuleiro
 * @return vetor com o tabuleiro
 */
vector<int> getVector(int size) {
    vector<int> vect;
    int aux;
    for(int i=0; i<pow(size,2);i++){
        cin>>aux;
        vect.push_back(aux);
    }
    return vect;
}

/**
 * Permite obter os tabuleiros com os respetivos tamanhos e jogadas maximas do stdin
 * @param n numero de tabuleiros
 * @return vetor com os tabuleiros
 */
vector<Board> getInput(int n) {
    vector<Board> board;
    Board aux;
    int size,moves;
    for(int i=0; i<n; i++){
        cin>>size>>moves;
        aux.size=size;
        aux.max_moves=moves;
        aux.vector=getVector(size);
        board.push_back(aux);
    }
    return board;
}


int boardAux[7][7] = {
        {0, 4, 4,  8, 8, 4, 4},
        {0, 0, 0,  2, 2, 4, 2},
        {8, 0, 0,  2, 2, 4, 8},
        {0, 0, 0,  0, 0, 0, 0},
        {2, 2, 2,  2, 2, 2, 2},
        {4, 4, 0,  4, 0, 0, 8},
        {8, 8, 16, 0, 0, 4, 0}
};

inline void solveArray(int *array, int size) {
    int current, after;
    for (int i = 0; i < size - 1; i++) {
        current = array[i];
        after = array[i + 1];
        if (after) {
            if (after == current) {
                //Operações bitwise são mais rápidas
                array[i] = after << 1;
                array[i + 1] = 0;
            }
        } else {
            // Evita iterações desnecessárias assim que encontra o primeiro zero no array
            break;
        }
    }
    int aux = 0;
    for (int j = 0; j < size; j++) {
        if (array[j])
            array[aux++] = array[j];
    }
    for (int j = aux; j < size; j++) {
        array[j] = 0;
    }
}

void printMatrix(int** matrix,int dim){
    for(int r=0; r<dim; r++){
        for(int c=0; c<dim; c++){
            printf("%i\t",matrix[r][c]);
        }
        printf("\n");
    }
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
    //faster with this lines
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //get number of boards
    int n;
    cin>>n;
    //get all boards
    vector<Board> board = getInput(n);

    printMatrix(NULL, 7);
    res(NULL, 7, 1);
    printf("---------------------------\n");
    printMatrix(NULL, 7);
    //string input;

    //input
    //cin >> input;
    //cout << input << "\n";
    return 0;
}
 
 
