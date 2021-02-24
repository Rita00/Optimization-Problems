/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef struct Board {
    int size{};
    int max_moves{};
    vector<int> matrix;
} Board;

int minMoves;

/**
 * Permite obter o vetor que representa o tabuleiro do stdin
 * @param size numero de linhas/colunas do tabuleiro
 * @return vetor com o tabuleiro
 */
vector<int> getMatrix(int size) {
    vector<int> vect;
    int total_size = size * size;
    vect.reserve(total_size);
    int aux;
    for (int i = 0; i < total_size; i++) {
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
    vector<Board> boards;
    boards.reserve(n);
    Board aux;
    int size, moves;
    for (int i = 0; i < n; i++) {
        cin >> size >> moves;
        aux.size = size;
        aux.max_moves = moves;
        aux.matrix = getMatrix(size);
        boards.push_back(aux);
    }
    return boards;
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
bool isSolved(vector<int> board, char move, int size) {
    int cnt = 0, num_it;
    switch (move) {
        case 'L':
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < size; j++) {
                    if (board[j * size + i] != 0) cnt++;
                    if (cnt > 1)
                        return false;
                }
            }
            break;
        case 'U':
            for (int i = 0; i <= size * 2; i++) {
                if (board[i] != 0) cnt++;
                if (cnt > 1)
                    return false;
            }
            break;
        case 'D':
            num_it = (size * size - 1) - (size * 2);
            for (int i = size * size - 1; i >= num_it; i--) {
                if (board[i] != 0) cnt++;
                if (cnt > 1)
                    return false;
            }
            break;
        case 'R':
            for (int i = size - 1; i >= size - 2; i--) {
                for (int j = 0; j < size; j++) {
                    if (board[j * size + i] != 0) cnt++;
                    if (cnt > 1)
                        return false;
                }
            }
            break;
        default:
            for (int i : board) {
                if (i != 0) cnt++;
                if (cnt > 1) return false;
            }
            break;
    }
    return true;
}

/**
 * Modifica o vetor do jogo em questão passando a representar o movimento para cima
 * @param board vetor de um determinado jogo/tabuleiro
 * @param size numero de linhas/colunas do tabuleiro
 */
inline vector<int> caseUp(vector<int> board, int size) {
    for (int i = 0; i < size; i++) {
        int current = 0, next = 1, write = 0;
        while (next < size) {
            if (!board[current * size + i]) {
                current++;
                next++;
            } else if (!board[next * size + i]) {
                next++;
            } else if (board[current * size + i] == board[next * size + i]) {
                board[write * size + i] = board[current * size + i] << 1;
                write++;
                current = next + 1;
                next += 2;
            } else {
                board[write * size + i] = board[current * size + i];
                current = next;
                next++;
                write++;
            }
        }
        if (current < size) {
            board[write * size + i] = board[current * size + i];
            write++;
        }
        while (write < size) {
            board[write * size + i] = 0;
            write++;
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
    for (int i = 0; i < size; i++) {
        int current = size - 1, next = size - 2, write = size - 1;
        while (next >= 0) {
            if (!board[current * size + i]) {
                current--;
                next--;
            } else if (!board[next * size + i]) {
                next--;
            } else if (board[current * size + i] == board[next * size + i]) {
                board[write * size + i] = board[current * size + i] << 1;
                write--;
                current = next - 1;
                next -= 2;
            } else {
                board[write * size + i] = board[current * size + i];
                current = next;
                next--;
                write--;
            }
        }
        if (current >= 0) {
            board[write * size + i] = board[current * size + i];
            write--;
        }
        while (write >= 0) {
            board[write * size + i] = 0;
            write--;
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
    for (int i = 0; i < size; i++) {
        int current = 0, next = 1, write = 0;
        int line = i * size;
        while (next < size) {
            if (!board[line + current]) {
                current++;
                next++;
            } else if (!board[line + next]) {
                next++;
            } else if (board[line + current] == board[line + next]) {
                board[line + write] = board[line + current] << 1;
                write++;
                current = next + 1;
                next += 2;
            } else {
                board[line + write] = board[line + current];
                current = next;
                next++;
                write++;
            }
        }
        if (current < size) {
            board[line + write] = board[line + current];
            write++;
        }
        while (write < size) {
            board[line + write] = 0;
            write++;
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
    for (int i = 0; i < size; i++) {
        int current = size - 1, next = size - 2, write = size - 1;
        int line = i * size;
        while (next >= 0) {
            if (!board[line + current]) {
                current--;
                next--;
            } else if (!board[line + next]) {
                next--;
            } else if (board[line + current] == board[line + next]) {
                board[line + write] = board[line + current] << 1;
                write--;
                current = next - 1;
                next -= 2;
            } else {
                board[line + write] = board[line + current];
                current = next;
                next--;
                write--;
            }
        }
        if (current >= 0) {
            board[line + write] = board[line + current];
            write--;
        }
        while (write >= 0) {
            board[line + write] = 0;
            write--;
        }
    }
    return board;
}


void depthFirstSearch(vector<int> board, int size, int used_moves, int maxMoves, char move) {
    if (!isSolved(board, move, size)) {
        if (used_moves >= minMoves - 1) {
            return;
        }
        // Check if transformation was effective, if not ignore recursive step
        vector<int> aux = caseLeft(board, size);
        if (aux != board) {
            depthFirstSearch(aux, size, used_moves + 1, maxMoves, 'L');
            if (used_moves >= minMoves - 1) {
                return;
            }
        }
        aux = caseUp(board, size);
        if (aux != board) {
            depthFirstSearch(aux, size, used_moves + 1, maxMoves, 'U');
            if (used_moves >= minMoves - 1) {
                return;
            }
        }
        aux = caseRight(board, size);
        if (aux != board) {
            depthFirstSearch(aux, size, used_moves + 1, maxMoves, 'R');
            if (used_moves >= minMoves - 1) {
                return;
            }
        }
        aux = caseDown(board, size);
        if (aux != board) {
            depthFirstSearch(aux, size, used_moves + 1, maxMoves, 'D');
        }
    } else {
        if (minMoves > used_moves) {
            minMoves = used_moves;
        }
        return;
    }
}

/*void breadthFirstSearch(vector<int> board, int size) {
    vector<vector<int>> boards;
    minMoves=0;
    if(!isSolved(board)){
        boards.push_back(caseLeft(board, size));
        boards.push_back(caseUp(board, size));
        boards.push_back(caseRight(board, size));
        boards.push_back(caseDown(board, size));
        minMoves++;
        while(!boards.empty()){
            boards.erase(boards.begin());
            vector<vector<int>> aux = boards;
            for(auto b : aux){
                if(!isSolved(b)){
                    boards.push_back(caseLeft(b, size));
                    boards.push_back(caseUp(b, size));
                    boards.push_back(caseRight(b, size));
                    boards.push_back(caseDown(b, size));
                }else{
                    return;
                }
                minMoves++;
            }
        }
        return;
    }else{
        return;
    }
}*/


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
        depthFirstSearch(board.matrix, board.size, 0, board.max_moves, '\0');
        if (minMoves <= board.max_moves) {
            cout << minMoves << endl;
        } else {
            cout << "no solution" << endl;
        }
        /*
        breadthFirstSearch(board.matrix, board.size);
        int m = (int)(log2(minMoves)/log2(4));
        if (m <= board.max_moves) {
            cout << m << endl;
        } else {
            cout << "no solution" << endl;
        }
        */
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
