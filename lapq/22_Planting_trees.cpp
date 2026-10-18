/*
=====================================================================
QUESTION SUMMARY: "Planting trees"
=====================================================================
A field has R rows and C columns. N trees are planted, tree k at
row Ak and column Bk. No two trees share a cell.

For a tree k, count the trees that are in the SAME ROW or the SAME
COLUMN as tree k, INCLUDING tree k itself. Each tree is counted once.

TASK: Find the tree with the biggest count. If several trees tie,
      choose the SMALLEST index k. Print k and its count.

INPUT:
 - Line 1: R, C and N (each up to 100,000)
 - Next N lines: Ak and Bk (row and column of tree k)

OUTPUT:
 - Two integers: the index k, and the count for that tree.

SAMPLE INPUT:
5 7 6
1 3
3 3
3 1
5 6
5 4
3 4

SAMPLE OUTPUT:
2 4

WHY "2 4"? (walking through the sample)
 Trees per row:    row 1 has 1, row 3 has 3, row 5 has 2
 Trees per column: col 1 has 1, col 3 has 2, col 4 has 2, col 6 has 1
 Tree 1 (row 1, col 3): 1 + 2 - 1 = 2
 Tree 2 (row 3, col 3): 3 + 2 - 1 = 4
 Tree 3 (row 3, col 1): 3 + 1 - 1 = 3
 Tree 4 (row 5, col 6): 2 + 1 - 1 = 2
 Tree 5 (row 5, col 4): 2 + 2 - 1 = 3
 Tree 6 (row 3, col 4): 3 + 2 - 1 = 4
 Best is 4. Trees 2 and 6 tie, so we pick the smaller index: 2.

KEY IDEA:
 Checking every pair of trees would be too slow for 100,000 trees.
 Instead, count how many trees are in each row (rowCount) and in each
 column (colCount). For tree k:
      answer = rowCount[row] + colCount[column] - 1
 We subtract 1 because tree k itself is counted in BOTH its row and
 its column, but it should only be counted once.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of numbers)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 lines is fast.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, n;      // r = rows, c = columns, n = number of trees
    cin >> r >> c >> n;

    // rowCount[i] = how many trees are in row i.
    // colCount[j] = how many trees are in column j.
    // Rows/columns are numbered from 1, so we make one extra spot
    // (spot 0 is unused). Every spot starts at 0.
    vector<int> rowCount(r + 1, 0);
    vector<int> colCount(c + 1, 0);

    // Lists to remember each tree's row and column,
    // because we need to look at every tree a second time later.
    vector<int> a(n + 1), b(n + 1);

    // FIRST PASS: read every tree and count trees per row and column.
    for (int k = 1; k <= n; k++) {
        cin >> a[k] >> b[k];     // read tree k's row and column
        rowCount[a[k]]++;        // one more tree in that row
        colCount[b[k]]++;        // one more tree in that column
    }

    int bestTree = 0;    // the index of the best tree found so far
    int bestCount = 0;   // the best count found so far

    // SECOND PASS: compute each tree's count and keep the best one.
    for (int k = 1; k <= n; k++) {

        // Trees in its row + trees in its column - 1 (itself counted twice).
        int total = rowCount[a[k]] + colCount[b[k]] - 1;

        // We use ">" (strictly bigger), NOT ">=".
        // Trees are checked from index 1 upwards, so if there is a tie
        // we keep the EARLIER (smaller) index, as the question wants.
        if (total > bestCount) {
            bestCount = total;
            bestTree = k;
        }
    }

    cout << bestTree << " " << bestCount << endl;   // print index and count

    return 0;         // tells the computer the program finished successfully
}