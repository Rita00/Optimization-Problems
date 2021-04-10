/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int increasingState;
int decreasingState;

int mod_abs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
    return mod_add(a, -b, mod);
}


int architecture(int num_blocks, int block_h, int max_H) {
    int cnt, block_cnt;
    int available_blocks;
    vector<int> solutions_per_numBlocks;
    solutions_per_numBlocks.resize(0);
    solutions_per_numBlocks.resize(num_blocks);

    if (block_h == max_H) return 0;
    // Falta verificar se pode continuar a crescer com base na quantidade de blocos que pode meter a descer
    for (int i = 3; i <= num_blocks; i++) {
        cnt = 0;
        for (int j = 0; j < i - 2; j++) {
            block_cnt = (i / 2) + (i % 2) - 1 + j;
            available_blocks = num_blocks - (block_cnt + 1);
            if (block_h + block_cnt == max_H) cnt++;
            //else if (available_blocks * block_h >= block_cnt + block_h) cnt += 0;
            else cnt += block_cnt * (block_h - 1);
        }
        solutions_per_numBlocks[i - 3] = cnt;
    }
    int soma = accumulate(solutions_per_numBlocks.begin(), solutions_per_numBlocks.end(), 0);
    return soma;
}


/*else {
            while ((actual_h + block_h <= max_H) && block_cnt >= 0) { // Crescer até atingir limite máximo ou não poder passar desse limite
                while (increment_h < block_h) {
                    actual_h += increment_h;
                    architecture(num_blocks, block_h, max_H, actual_h + increment_h);
                    increment_h++;
                }
                block_cnt--;
            }
        }*/


int main() {
    int test_cases, num_blocks, block_h, max_H;
    cin >> test_cases;
    for (int i = 0; i < test_cases; i++) {
        cin >> num_blocks;
        cin >> block_h;
        cin >> max_H;
        cout << architecture(num_blocks, block_h, max_H) % 1000000007 << endl;
    }

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
