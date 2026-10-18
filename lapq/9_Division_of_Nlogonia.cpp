/*
=====================================================================
QUESTION SUMMARY: "Nlogonia" (Division of Nlogonia)
=====================================================================
A land is split into four countries by two lines that cross at a
"division point" (N, M):
 - a North-South line (a vertical line at x = N)
 - an East-West line  (a horizontal line at y = M)

The four countries are:
   NO (Northwest) : left of the vertical line,  ABOVE the horizontal line
   NE (Northeast) : right of the vertical line, ABOVE the horizontal line
   SE (Southeast) : right of the vertical line, BELOW the horizontal line
   SO (Southwest) : left of the vertical line,  BELOW the horizontal line

If a house sits exactly ON either line, it is on the border: "divisa".

TASK: For each house (X, Y), print which country it is in.

INPUT (many test cases):
 - Line 1: K = number of houses to check (0 < K <= 1000).
           A line with just 0 means the whole input is finished.
 - Line 2: N and M = coordinates of the division point.
 - Next K lines: X and Y = coordinates of one house each.

OUTPUT:
 - For each house, one line: divisa, NO, NE, SE or SO.

SAMPLE INPUT:
3
2 1
10 10
-10 1
0 33
4
-1000 -1000
-1000 -1000
0 0
-2000 -10000
-999 -1001
0

SAMPLE OUTPUT:
NE
divisa
NO
divisa
NE
SO
SE

WHY? (walking through the first test case, division point = (2, 1))
 House (10, 10): x=10 is right of 2, y=10 is above 1   -> NE
 House (-10, 1): y=1 is exactly the horizontal line   -> divisa
 House (0, 33) : x=0 is left of 2, y=33 is above 1    -> NO

 Second test case, division point = (-1000, -1000):
 House (-1000, -1000): exactly on both lines          -> divisa
 House (0, 0)        : right of -1000, above -1000    -> NE
 House (-2000,-10000): left of -1000, below -1000     -> SO
 House (-999, -1001) : right of -1000, below -1000    -> SE

KEY IDEA:
 Compare the house's X with N, and its Y with M.
   X == N or Y == M  -> divisa
   otherwise X > N means East (right), X < N means West (left)
             Y > M means North (above), Y < M means South (below)
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int k;            // a box to hold K, the number of houses in a test case

    // Read K. Keep going as long as the reading worked AND k is not 0.
    // When k is 0, that is the final "0" line, so the loop stops.
    // Each time around this loop handles ONE test case.
    while (cin >> k && k != 0) {

        int n, m;         // the division point: n = x position, m = y position
        cin >> n >> m;    // read the division point

        // Repeat once for each house in this test case.
        // "i" counts the houses, starting at 0 and stopping before k.
        for (int i = 0; i < k; i++) {

            int x, y;         // the position of THIS house
            cin >> x >> y;    // read the house's coordinates

            if (x == n || y == m) {
                // "||" means OR. If the house is on the vertical line
                // (x equals n) OR on the horizontal line (y equals m),
                // it sits on the border.
                cout << "divisa" << '\n';

            } else if (x < n && y > m) {
                // "&&" means AND. Left of the vertical line AND above
                // the horizontal line: Northwest.
                cout << "NO" << '\n';

            } else if (x > n && y > m) {
                // Right AND above: Northeast.
                cout << "NE" << '\n';

            } else if (x > n && y < m) {
                // Right AND below: Southeast.
                cout << "SE" << '\n';

            } else {
                // The only choice left is left AND below: Southwest.
                cout << "SO" << '\n';
            }
        }
    }

    return 0;         // tells the computer the program finished successfully
}