/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

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

inline unsigned int f(int n, int h, int block_h, vector<vector<unsigned int>> &matrix) {
    unsigned int soma = 0;
    if (h < block_h || n == 0) {
        soma = 0;
    } else if (n == 1 && h == block_h) {
        soma = 1;
    } else {
        for (int i = 1; i < block_h; i++) {
            soma += matrix[n - 1][h - i] - matrix[n - 2][h - i] % 1000000007;
        }
    }
    soma += matrix[n - 1][h];

    matrix[n][h] = soma % 1000000007;
    return soma;
}

unsigned int architecture2(int num_blocks, int block_h, int max_H) {
    vector<vector<unsigned int>> matrix;

    matrix.resize(num_blocks, vector<unsigned int>(max_H + 1, 0));
    unsigned int total = 0;
    int max_col = min(max_H, block_h + ((num_blocks / 2 + num_blocks % 2) * (block_h - 1)));
    for (int coluna = block_h; coluna <= max_col; coluna++) {
        int blocks_min = ceil((float) (coluna - block_h) / (float) (block_h - 1) + 1);
        //int blocks_max = min(num_blocks, coluna - block_h + 1 + 1);
        for (int linha = blocks_min; linha < num_blocks; linha++) {
            unsigned int lc = f(linha, coluna, block_h, matrix);
            if (lc == 0)
                continue;
            int soma = 0;
            //int min_blocks = (coluna - block_h) / (block_h - 1);
//            for (int i = 1; i < block_h; i++) {
//                for (int l = min_blocks; l <= num_blocks - linha; l++) {
//                    //printf("(%d, %d) * (%d, %d)\n", l, coluna - i, linha, coluna);
//                    soma += matrix[l][coluna - i];
//                }
//            }
            int remaining_blocks = num_blocks - linha;

            for (int i = 1; i < block_h; i++) {
                soma += matrix[remaining_blocks][coluna - i] % 1000000007;
            }
            total += soma * (lc - matrix[linha - 1][coluna]);
            total %= 1000000007;
        }
    }
//    for (int i = 0; i < num_blocks; i++) {
//        for (int j = 0; j < max_H + 1; j++) {
//            printf("%u\t", matrix[i][j]);
//        }
//        printf("\n");
//    }
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
        cout << architecture2(num_blocks, block_h, max_H) << endl;
    }
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
//    std::cout << ms_int.count() << "ms\n";
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
