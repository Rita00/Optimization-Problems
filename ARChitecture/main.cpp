/**
 * @author Ana Rita Rodrigues -  2018284515
 * @author Dylan Gonçalves Perdigão - 2018233092
 */
#include <iostream>
#include <vector>

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

int architecture(int width, int height, int maxHeight){
    //contage,
    int count=0;
    //contagem de crescimentos e descrescimentos do arco (para ser valido tem de crescer e descrescer 1 vez)
    int increasingStatus=0;
    int decreasingStatus=0;
    //boleanos para saber se está a crescer
    bool isIncreasing=false;
    
    for(int x=0; x<width; x++){
        int previousHeight=0;
        for(int y=height;y<=maxHeight;y++){
            for(int h=0;h<height; h++){
                if(y+h>maxHeight){
                    break;
                }
                if(previousHeight<y+h and not isIncreasing){
                    increasingStatus++;
                    isIncreasing=true;
                }
                if(previousHeight>y+h and isIncreasing){
                    decreasingStatus++;
                    isIncreasing=false;
                }
                if(increasingStatus==1 and decreasingStatus==1){
                    count++;
                }
                previousHeight=y+h;
            }
        }
    }
    return count;
}

int main() {
    int test_cases, num_blocks, block_h, max_H;
    cin >> test_cases;
    for (int i = 0; i < test_cases; i++) {
        cin >> num_blocks;
        cin >> block_h;
        cin >> max_H;
        cout << architecture(num_blocks,block_h,max_H)%1000000007 << endl;
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

/*
INPUT
------
7
3 3 3
3 3 4
3 3 5
3 3 6
4 3 7
5 5 10
8 4 30

 
OUTPUT
------
0
1
2
2
4
54
819
 

 */
