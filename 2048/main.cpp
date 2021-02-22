/**
 * @author Dylan Gonçalves Perdigão - 2018233092
 * @author Ana Rita Rodrigues -  xxxxxxxxx
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef struct Board {
    int size;
    int max_moves;
    vector<int> vector;
} Board;

/**
 * Permite obter o vetor que representa o tabuleiro do stdin
 * @param size numero de linhas/colunas do tabuleiro
 * @return vetor com o tabuleiro
 */
vector<int> getVector(int size) {
    vector<int> vect;
    int aux;
    for (int i = 0; i < size * size; i++) {
        cin >> aux;
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
    int size, moves;
    for (int i = 0; i < n; i++) {
        cin >> size >> moves;
        aux.size = size;
        aux.max_moves = moves;
        aux.vector = getVector(size);
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

void printMatrix(int **matrix, int dim) {
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            printf("%i\t", matrix[r][c]);
        }
        printf("\n");
    }
}

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

inline void caseUp(int **board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = 0; j < size; j++) {
            current = boardAux[j][i];
            if (current)
                arrayAux[aux++] = current;
        }
        solveArray(arrayAux, size);
        for (int j = size - 1; j >= 0; j--) {
            boardAux[j][i] = arrayAux[j];
        }
    }
}

inline void caseDown(int **board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);

        for (int j = size - 1; j >= 0; j--) {
            current = boardAux[j][i];
            if (current)
                arrayAux[aux++] = current;
        }
        solveArray(arrayAux, size);
        for (int j = size - 1; j >= 0; j--) {
            boardAux[j][i] = arrayAux[size - j - 1];
        }
    }
}

inline void caseLeft(int **board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = 0; j < size; j++) {
            current = boardAux[i][j];
            if (current) {
                arrayAux[aux++] = current;
            }
        }
        solveArray(arrayAux, size);
        memcpy(boardAux[i], arrayAux, sizeof(int) * size);
    }
}

inline void caseRight(int **board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = size - 1; j >= 0; j--) {
            current = boardAux[i][j];
            if (current) {
                arrayAux[aux++] = current;
            }
        }
        solveArray(arrayAux, size);
        for (int j = size - 1; j >= 0; j--) {
            boardAux[i][j] = arrayAux[size - j - 1];
        }
    }
}

void res(int **board, int size, int maxMoves) {
    char allMoves[] = {'A', 'W', 'S', 'D'}, move;

    for (int k = 0; k < maxMoves; k++) {
        move = 'D';
        //move = allMoves[rand() % 4];
        if (move == 'A') {
            caseLeft(board, 7);
        } else if (move == 'W') {
            caseUp(board, size);
        } else if (move == 'S') {
            caseDown(board, size);
        } else {
            caseRight(board, size);
        }
    }
}

void printMatrix2(int **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", boardAux[i][j]);
        }
        printf("\n");
    }

}

int main() {
    //faster with this lines
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //get number of boards
    int n;
    cin >> n;
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
 

