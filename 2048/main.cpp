/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Board {
    int size{};
    int max_moves{};
    vector<int> matrix;
} Board;

/**
 * Permite obter o vetor que representa o tabuleiro do stdin
 * @param size numero de linhas/colunas do tabuleiro
 * @return vetor com o tabuleiro
 */
vector<int> getMatrix(int size) {
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
        aux.matrix = getMatrix(size);
        board.push_back(aux);
    }
    return board;
}

/*void printMatrix(vector<int> board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i * size + j] << " ";
        }
        cout << endl;
    }
}*/

/**
 * Verfifica se o jogo está resolvido contando o numero de 0's é igual ao tamanho da linha/coluna ao quadrado menos 1
 * @param board linha/coluna do vetor que representa a matriz
 * @param size tamanho do array
 * @return booleano que responde se o jogo está resolvido
 */
bool isSolved(vector<int> board, int size) {
    long n = count(board.begin(), board.end(), 0);
    if (n == size * size - 1) {
        return true;
    } else {
        return false;
    }
}

/**
 * Faz as devidas somas dos indices do array , caso seja possível
 * Recebe o array na devida ordem
 * @param array linha/coluna do vetor que representa a matriz
 * @param size tamanho do array
 */
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

/**
 * Modifica o vetor do jogo em questão passando a representar o movimento para cima
 * @param board vetor de um determinado jogo/tabuleiro
 * @param size numero de linhas/colunas do tabuleiro
 */
inline vector<int> caseUp(vector<int> board, int size) {
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
    return board;
}

/**
 * Modifica o vetor do jogo em questão passando a representar o movimento para baixo
 * @param board vetor de um determinado jogo/tabuleiro
 * @param size numero de linhas/colunas do tabuleiro
 */
inline vector<int> caseDown(vector<int> board, int size) {
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
        for (int j = 0; j < size; j++) {
            board[j * size + i] = arrayAux[size - j - 1];
        }
    }
    return board;
}

/**
 * Modifica o vetor do jogo em questão passando a representar o movimento para a esquerda
 * @param board vetor de um determinado jogo/tabuleiro
 * @param size numero de linhas/colunas do tabuleiro
 */
inline vector<int> caseLeft(vector<int> board, int size) {
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
            board[i * size + j] = arrayAux[j];
        }
    }
    return board;
}

/**
 * Modifica o vetor do jogo em questão passando a representar o movimento para a direita
 * @param board vetor de um determinado jogo/tabuleiro
 * @param size numero de linhas/colunas do tabuleiro
 */
inline vector<int> caseRight(vector<int> board, int size) {
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
    return board;
}

int minMoves;

void depthFirstSearch(vector<int> board, int size, int used_moves, int maxMoves) {
    if (!isSolved(board, size)) {
        if (used_moves >= minMoves || used_moves >= maxMoves) {
            return;
        }
        // Check if transformation was effective, if not ignore recursive step
        vector<int> aux = caseLeft(board, size);
        if (aux != board) {
            depthFirstSearch(aux , size, used_moves + 1, maxMoves);
        }
        aux = caseUp(board, size);
        if (aux != board) {
            depthFirstSearch(aux , size, used_moves + 1, maxMoves);
        }
        aux = caseRight(board, size);
        if (aux != board) {
            depthFirstSearch(aux , size, used_moves + 1, maxMoves);
        }
        aux = caseDown(board, size);
        if (aux != board) {
            depthFirstSearch(aux , size, used_moves + 1, maxMoves);
        }
    } else {
        if (minMoves > used_moves || minMoves < 0) {
            minMoves = used_moves;
        }
        return;
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
        minMoves = board.max_moves + 1;
        depthFirstSearch(board.matrix, board.size, 0, board.max_moves);
        if (minMoves <= board.max_moves) {
            cout << minMoves << endl;
        } else {
            cout << "no solution" << endl;
        }
        //breadthFirstSearch(board.vector, board.size, board.max_moves, moves);

        //cout << "=========Board===============" << endl;
        //printMatrix(board.vector, board.size);

        //breadthFirstSearch(board.vector, board.size, board.max_moves, moves);
        //cout << "---------------------------" << endl;
        //printMatrix(board.vector, board.size);
        //res(board.vector, board.size, board.max_moves);
    }
    return 0;
}

/*
INPUT EXAMPLE

4
3 5
2 0 2
4 0 8
0 0 0
3 10
4 2 4
4 2 4
4 4 4
3 4
4 2 4
4 2 4
4 4 4
4 10
8 4 0 0
4 0 0 0
8 4 0 0
0 0 4 0
 
EXAMPLE OUTPUT
 
3
5
no solution
4
 
*/
