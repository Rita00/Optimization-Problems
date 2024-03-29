/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>

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

int multiply(int a, int b, int mod) {
    int res = 0;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1)
            res = (res + a) % mod;

        a = (a * 2) % mod;

        b /= 2;
    }
    return res % mod;
}

int f(int n, int h, int block_h, vector<vector<int>> &matrix) {
    int soma = 0;
    if (n == 1 && h == block_h) {
        soma = 1;
    } else {
        //printf("............................ F %d - %d\n", n, h);
        for (int i = 1; i < block_h; i++) {
            soma = mod_add(soma, mod_sub(matrix[n - 1][h - i], matrix[n - 2][h - i], 1000000007), 1000000007);
            //printf("%d\n", soma);
        }
    }
    //printf("............................ F solo %d - %d\n", n, h);
    soma = mod_add(soma, matrix[n - 1][h], 1000000007);
    //printf("solo soma F %d\n", soma);
    matrix[n][h] = soma;
    return matrix[n][h];
}

int architecture2(int num_blocks, int block_h, int max_H) {
    vector<vector<int>> matrix;

    matrix.resize(num_blocks, vector<int>(max_H + 1, 0));
    int total = 0;
    int max_col = min(max_H, block_h + ((num_blocks / 2 + num_blocks % 2) * (block_h - 1)));
    for (int coluna = block_h; coluna <= max_col; coluna++) {
        int blocks_min = ceil((float) (coluna - block_h) / (float) (block_h - 1) + 1);
        for (int linha = blocks_min; linha < num_blocks; linha++) {
            int lc = f(linha, coluna, block_h, matrix);
            if (lc == 0)
                continue;
            int soma = 0;

            int remaining_blocks = num_blocks - linha;
            //printf("............................ Arch soma %d - %d\n", coluna, linha);
            for (int i = 1; coluna - i >= block_h && i < block_h; i++) {
                int current_ind = matrix[remaining_blocks][coluna - i];
                //printf("%d - %d\n", remaining_blocks, coluna - i);
                //printf("%d\n", current_ind);
                //if (current_ind == 0) continue;
                soma = mod_add(soma, current_ind, 1000000007);
                /*if (soma != 0)
                    printf("Soma Arch ? %d\n", soma);
                else printf("Soma Arch %d\n", soma);*/
            }
            int res = multiply(soma, mod_sub(lc, matrix[linha - 1][coluna], 1000000007), 1000000007);
            total = mod_add(total, res, 1000000007);
        }
    }
    /*for (int i = 0; i < num_blocks; i++) {
        for (int j = 0; j < max_H + 1; j++) {
            printf("%u\t", matrix[i][j]);
        }
        printf("\n");
    }*/
    return total;
}

int main() {
    /*
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    */
    
    
    int test_cases, num_blocks, block_h, max_H;
    cin >> test_cases;
    for (int i = 0; i < test_cases; i++) {
        cin >> num_blocks;
        cin >> block_h;
        cin >> max_H;
        cout << architecture2(num_blocks, block_h, max_H) << endl;
    }
    
    
    /*
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";
    */
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
/*
 #### Input (Example 1)
 7
 3 3 3
 3 3 4
 3 3 5
 3 3 6
 4 3 7
 5 5 10
 8 4 30
 
 
 ### Output (Example 1)
 0
 1
 2
 2
 4
 54
 819
 
 
 ### Input (Example 2)
 1
 32 3 100
 
 
 ### Output (Example 2)
 431655757
 
 
 ### Input (Example 3)
 2
 17 29 5899
 70 16 276
 
 
 ### Output (Example 3)
 162344589
 70718620
 
 
 */
