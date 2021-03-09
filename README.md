# EA2021

## Problem A - 2048 clean up!

### Description
2048 is a single-player game consisting of a 2-dimentional board with numbered tiles. The player can slide the tiles in one of the four possible directions (left, right, up or down). Each play corresponds of a slide in one of the four directions. When a play is performed, all the tiles slide in that direction as far as possible, stopping whenever they collide with the target wall (board limit on the direction of the slide) or with another tile. When a tile collides with another tile of the same value, the two tiles merge into one, of value equal to the sum of their previous values. So, if a tile of value 2 collides with another tile of value 2, the merged tile assumes the value 4. The resulting tile cannot merge again in the same move with any other tile. This means that a slide to the right in in a row with tiles [2,2,4] will result in the sequence [4,4], not [8].

This sliding operation is applied iteratively, tile by tile, starting from the tiles closer to the target wall and advancing to the tiles farther away. This means that if the player makes a slide to the right direction in a row with the tiles [2,2,2], the resulting tiles will be [2, 4]. On contrary, if the play is a slide to the left direction, then the result will be [4, 2]

In the original version of the game, a new tile of value 2 or 4 appears on an empty space of the board after every play (a slide movement). However, in this version, no new tile appears. Also, in the original version the square board is 4x4, and in our version the square board can be of different sizes.

Your objective is to identify the minimum number of plays that merge all tiles into one. A maximum number of plays allowed is provided. If it is not possible to clear the board with that number of plays, you must report no solution.

### Input
The input starts with one line containing the number of test cases.

Then, for each test case, the first line contains two numbers: 1 ≤ N ≤ 20 and 1 ≤ M ≤ 50. N represents the size of the board, i.e. the number of rows and columns, and M represents the maximum number of slides allowed.

After that, N lines follow, each with N values, corresponding to the values of the tiles in the board. Empty tiles are represented by a value of 0.

### Output
For each test case, you should print one integer with the minimum number of slides needed to clear the board, followed by a '\n'.

If it is not possible to clear the board with at most M slides, output the text no solution followed by a '\n'.

### Example
#### Example input:
```python
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
```
#### Example output:
```python
3
5
no solution
4
```
