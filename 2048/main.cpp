#include <iostream>


/*
// Static size array saved on the stack #include <array>
std::array<int, 3> arr;
arr[i]; // O(1)
// Dynamic size array saved on the heap #include <vector>
std::vector<int> vec();
vec[i]; // O(1)
vec[i] = ...; // O(1) vec.push_back(int); // O(1) amortized vec.pop_back(); // O(1)

class MyClass {       // The class
  public:             // Access specifier
    int myNum;        // Attribute (int variable)
    string myString;  // Attribute (string variable)
};
 */

void res(int **board, int size) {
    char allMoves[] = {'A', 'W', 'S', 'D'}, move = allMoves[rand() % 4];
    for (int i = 0; i < size; i++) {
        if (move == 'A'|| move == 'W') {
            for (int j = size - 1; j <= 0; j++) {
                int current = board[i][j], bef = board[i][j - 1];
                if (bef && current && (bef == current)) {
                    board[i][size - 2] = board[i][size - 1] + board[i][size - 2];
                    board[i][size - 1] = 0;
                }
            }
        } else {
            for (int j = 0; j < size; j++) {

            }
        }

    }
}

int main() {
    /*
  MyClass myObj;  // Create an object of MyClass

  // Access attributes and set values
  myObj.myNum = 15;
  myObj.myString = "Some text";
*/
    // Print attribute values
    // We probably do not need this but it is faster
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::cout << n << "\n";
    return 0;
}
