/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <vector>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

using namespace std;

typedef struct Board {
    int size;
    int max_moves;
    int used_moves;
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

void printMatrix(vector<int> board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i * size + j] << " ";
        }
        cout << endl;
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

inline void caseUp(vector<int> &board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = 0; j < size; j++) {
            current = board[j * size + i];
            if (current)
                arrayAux[aux++] = current;
        }
        solveArray(arrayAux, size);
        for (int j = size - 1; j >= 0; j--) {
            board[j * size + i] = arrayAux[j];
        }
    }
}

inline void caseDown(vector<int> board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);

        for (int j = size - 1; j >= 0; j--) {
            current = board[j * size + i];
            if (current)
                arrayAux[aux++] = current;
        }
        solveArray(arrayAux, size);
        for (int j = size - 1; j >= 0; j--) {
            board[j * size + i] = arrayAux[size - j - 1];
        }
    }
}

inline void caseLeft(vector<int> &board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = 0; j < size; j++) {
            current = board[i * size + j];
            if (current) {
                arrayAux[aux++] = current;
            }
        }
        solveArray(arrayAux, size);
        for (int j = 0; j < size; j++) {
            board[j * size + i] = arrayAux[j];
        }
    }
}

inline void caseRight(vector<int> &board, int size) {
    int current, aux;
    int arrayAux[size];
    for (int i = 0; i < size; i++) {
        aux = 0;
        fill(arrayAux, arrayAux + size, 0);
        for (int j = size - 1; j >= 0; j--) {
            current = board[i * size + j];
            if (current) {
                arrayAux[aux++] = current;
            }
        }
        solveArray(arrayAux, size);
        for (int j = size - 1; j >= 0; j--) {
            board[i * size + j] = arrayAux[size - j - 1];
        }
    }
}

void breadthFirstSearch(vector<int> &board, int size, int maxMoves){
    vector<int> queue = {LEFT,UP,RIGHT,DOWN};
    cout<<"INICIAL\n";
    printMatrix(board, size);
    for(int q : queue){
        switch (q) {
            case LEFT:
                caseLeft(board,size);
                cout<<"LEFT MOVE\n";
                printMatrix(board, size);
                break;
            case UP:
                caseUp(board,size);
                cout<<"UP MOVE\n";
                printMatrix(board, size);
                break;
            case RIGHT:
                caseRight(board,size);
                cout<<"RIGHT MOVE\n";
                printMatrix(board, size);
                break;
            case DOWN:
                caseDown(board,size);
                cout<<"DOWN MOVE\n";
                printMatrix(board, size);
                break;
        }
    }
}

void res(vector<int> &board, int size, int maxMoves) {
    char allMoves[] = {'A', 'W', 'S', 'D'}, move;

    for (int k = 0; k < maxMoves; k++) {
        move = 'D';
        move = allMoves[rand() % 4];
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

int main() {
    //faster with this lines
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //get number of boards
    int n;
    cin >> n;
    //get all boards
    vector<Board> boards = getInput(n);
    for (auto board : boards) {
        cout << "=========Board===============" << endl;
        printMatrix(board.vector, board.size);
        breadthFirstSearch(board.vector, board.size, board.max_moves);
        cout << "---------------------------" << endl;
        printMatrix(board.vector, board.size);
    }
    return 0;
}
 

