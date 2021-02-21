#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void getInput(string input) {

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

void printMatrix(int **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", boardAux[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printMatrix(NULL, 7);
    res(NULL, 7, 1);
    printf("---------------------------\n");
    printMatrix(NULL, 7);
    //string input;
    //faster with this lines
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    //input
    //cin >> input;
    //cout << input << "\n";
    return 0;
}
 
 