/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int mod_abs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
    return mod_add(a, -b, mod);
}

int f(int n, int h, int block_h, vector<vector<int>> &matrix) {
    int soma = 0;
    if (h < block_h || n == 0)
        return 0;
    if (matrix[n][h] != -1)
        return matrix[n][h];
    if (n == 1 && h == block_h)
        return 1;
    for (int i = 1; i < block_h; i++) {
        soma += f(n - 1, h - i, block_h, matrix);
    }
    matrix[n][h] = soma;
    return soma;
}

int architecture2(int num_blocks, int block_h, int max_H) {
    vector<vector<int>> matrix;
    vector<int> solutions_per_numBlocks;
    solutions_per_numBlocks.resize(num_blocks);

    matrix.resize(num_blocks, vector<int>(max_H + 1, -1));
    for (int i = 1; i < num_blocks; i++) {
        int h_max = block_h + ((i - 1) * (block_h - 1));
        if (h_max > max_H) h_max = max_H;
        for (int j = block_h + i - 1; j <= h_max; j++) {
            matrix[i][j] = f(i, j, block_h, matrix);
            //printf("%d\t%d\n", i, j);
        }
    }
    for (int i = 0; i < num_blocks; i++) {
        for (int j = 0; j < max_H + 1; j++) {
            if (matrix[i][j] == -1)
                matrix[i][j] = 0;
            //printf("%d\t", matrix[i][j]);
        }
        //printf("\n");
    }
    vector<int> soma_colunas;
    soma_colunas.resize(max_H + 1);
    int total = 0;
    for (int coluna = block_h; coluna <= min(max_H, block_h + ((num_blocks / 2 + num_blocks % 2) * (block_h - 1))); coluna++) {
        for (int linha = 1; linha < num_blocks; linha++) {
            for (int i = 1; i < block_h; i++) {
                int min_blocks = (coluna - block_h) / (block_h - 1) ;
                for (int l = min_blocks; l <= num_blocks - linha; l++) {
                    //if (matrix[linha][coluna] < 0) break;
                    if (matrix[linha][coluna] != 0 && f(l, coluna - i, block_h, matrix) != 0) {
                        //printf("(%d, %d) * (%d, %d)\n", l, coluna - i, linha, coluna);
                        total += f(l, coluna - i, block_h, matrix) * matrix[linha][coluna];
                    }
                }
            }
        }
    }
    return total;
}

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    int test_cases, num_blocks, block_h, max_H;
    auto t1 = high_resolution_clock::now();
    cin >> test_cases;
    for (int i = 0; i < test_cases; i++) {
        cin >> num_blocks;
        cin >> block_h;
        cin >> max_H;
        cout << architecture2(num_blocks, block_h, max_H) % 1000000007 << endl;
    }
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";
    return 0;
}

/**
 * Regras!
 * 1- Arco com dimensão 3 <= K <= num_legos, i = i é o primeiro bloco, i = 2 o segundo até ao último bloco i = K
 * 2- O primeiro e último blocos devem ser colocados no chão, ou seja, h1 = 0 e hK = 0
 * 3- O iº bloco deve "tocar" nos seus vizinhos
 * 4- Os valores de hi devem ser monotonicamnete crescentes, até um certo bloco e decrescescer novamente
 * 5- Dois blocos consecutivos não podem ter o mesmo valor de hi (a mesma altura)
 */
