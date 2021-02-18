#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void getInput(string input) {

}


int boardAux[7][7] = {
        {2, 4, 4,  8, 8, 4, 4},
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
        if (!current) {
            array[i] = after;
            array[i + 1] = 0;
        } else if (after) {
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
}

inline void caseUp(int **board, int size) {
    int current, after, aux;
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
    int current, bef, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = size - 1;
        fill(arrayAux, arrayAux + size, 0);

        for (int j = size - 1; j >= 0; j--) {
            current = boardAux[j][i];
            if (j - 1 < 0) {
                bef = 0;
            } else {
                bef = boardAux[j - 1][i];
            }
            if (current) {
                if (bef == current) {
                    //Operações bitwise são mais rápidas
                    arrayAux[aux--] = bef << 1;
                    j--;
                } else {
                    arrayAux[aux--] = current;
                }
            }
        }
        for (int j = size - 1; j >= 0; j--) {
            boardAux[j][i] = arrayAux[j];
        }
    }
}


inline void caseLeft(int **board, int size) {
    int current, after, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = 0; j < size; j++) {
            current = boardAux[i][j];
            if (j + 1 == size) {
                after = 0;
            } else {
                after = boardAux[i][j + 1];
            }
            if (current) {
                if (after == current) {
                    //Operações bitwise são mais rápidas
                    arrayAux[aux++] = after << 1;
                    j++;
                } else {
                    arrayAux[aux++] = current;
                }
            }
        }
        memcpy(boardAux[i], arrayAux, sizeof(int) * size);
    }
}

inline void caseRight(int **board, int size) {
    int current, before, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = size - 1;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = size - 1; j >= 0; j--) {
            current = boardAux[i][j];
            if (j - 1 < 0) {
                before = 0;
            } else {
                before = boardAux[i][j - 1];
            }
            if (current) {
                if (before == current) {
                    //Operações bitwise são mais rápidas
                    arrayAux[aux--] = before << 1;
                    j--;
                } else {
                    arrayAux[aux--] = current;
                }
            }
        }
        memcpy(boardAux[i], arrayAux, sizeof(int) * size);
    }
}

void res(int **board, int size, int maxMoves) {
    char allMoves[] = {'A', 'W', 'S', 'D'}, move;

    for (int k = 0; k < maxMoves; k++) {
        move = 'W';
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
 
 