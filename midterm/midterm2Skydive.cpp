/*
ssss
/*
=====================================================================
QUESTION SUMMARY:
=====================================================================
N poles stand in a row (pole 1 = leftmost). Pole i has height Hi.
You start on pole s and jump to ANOTHER pole:
 - to the LEFT (a pole j with j < s), or
 - to the RIGHT (a pole k with k > s).
You may only jump to a pole that is STRICTLY LOWER than pole s.
The distance of a jump = (height of pole s) - (height of the
destination pole).

For each question s, find:
 - the MAXIMUM distance you can jump to the left,
 - the MAXIMUM distance you can jump to the right.
If you cannot jump in a direction (no pole there, or no pole there is
strictly lower), print -1 for that direction.

INPUT:
 - Line 1: N and Q (each up to 200,000)
 - Next N lines: the heights Hi (0 to 1,000,000,000)
 - Next Q lines: one pole number s per line

OUTPUT:
 - For each question, one line with two numbers: left right.

SAMPLE INPUT 2:          SAMPLE OUTPUT 2:
5 3                      35 5
10                       42 -1
45                       -1 -1
60
40
52
2
5
1

WHY? (heights: 10 45 60 40 52)
 s = 2 (height 45):
   left poles:  {10}        lowest is 10 -> 45 - 10 = 35
   right poles: {60,40,52}  lowest is 40 -> 45 - 40 = 5
   -> "35 5"
 s = 5 (height 52):
   left poles:  {10,45,60,40} lowest is 10 -> 52 - 10 = 42
   right poles: none -> -1
   -> "42 -1"
 s = 1 (height 10):
   left poles: none -> -1
   right poles: {45,60,40,52} lowest is 40, which is NOT lower than 10
   -> -1
   -> "-1 -1"
 (Sample 1, s = 3 (height 60): left 60-10 = 50, right 60-40 = 20
  -> "50 20". I traced all of these by hand and they match.)

=====================================================================
SIMILAR / DIFFERENT
=====================================================================
SIMILAR TO: "Big Bags" (prefix sums), "Sport Tournament", and "Planting
            trees".
   - Many questions (Q up to 200,000) about the SAME list. The trick is
     to PRECOMPUTE once, then answer every question by one lookup.
   - Big Bags used a prefix SUM array. Here the idea is the same, but
     we store the running MINIMUM instead of the running sum.
 DIFFERENT:
   - Prefix min: leftMin[s] = the lowest height among poles 1..s-1.
     Suffix min: rightMin[s] = the lowest height among poles s+1..N.
     (We need a list for each direction.)
   - The biggest distance always comes from the LOWEST pole, because
     distance = Hs - (destination height). Smallest destination height
     gives the biggest distance.
   - STRICT rule: if even the lowest pole is NOT lower than Hs
     (lowest >= Hs), no jump is possible -> -1. Poles of equal height do
     NOT count.
   - "No pole in that direction" is handled with a huge fake value
     (INFINITY). Then the same check "lowest < Hs" fails automatically
     and we print -1. No special case is needed.

=====================================================================
PLAN
=====================================================================
 1. Read the heights into h[1..n].
 2. leftMin[1] = INFINITY (no poles on the left of pole 1).
    leftMin[i] = min(leftMin[i-1], h[i-1])   for i = 2..n
 3. rightMin[n] = INFINITY (no poles on the right of pole n).
    rightMin[i] = min(rightMin[i+1], h[i+1]) for i = n-1 down to 1
 4. For each question s:
      left  = (leftMin[s]  < h[s]) ? h[s] - leftMin[s]  : -1
      right = (rightMin[s] < h[s]) ? h[s] - rightMin[s] : -1
 5. Print left and right.
 Total work: about N + Q steps. Fast.
=====================================================================
*/
/*
#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <algorithm>  // lets us use min (pick the smaller of two numbers)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines (the question asks for them): there can be
    // 400,000 numbers to read and 200,000 lines to print.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;         // n = number of poles, q = number of questions
    cin >> n >> q;

    // h[i] = height of pole i. Poles are numbered from 1, so we make
    // n + 2 spots (spot 0 and spot n+1 are unused).
    // "long long" is a big number box, to be safe.
    vector<long long> h(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    // A fake HUGE height. It is bigger than any real height (max 1e9),
    // so "no poles in this direction" means: the lowest pole there is
    // INFINITY, which is never lower than pole s.
    const long long INFINITY_H = 4000000000LL;

    // leftMin[i]  = the LOWEST height among poles 1 .. i-1.
    // rightMin[i] = the LOWEST height among poles i+1 .. n.
    vector<long long> leftMin(n + 2, INFINITY_H);
    vector<long long> rightMin(n + 2, INFINITY_H);

    // leftMin[1] stays INFINITY_H: pole 1 has nobody on its left.
    // For the other poles, the lowest on the left is either the lowest
    // before the previous pole, or the previous pole itself.
    for (int i = 2; i <= n; i++) {
        leftMin[i] = min(leftMin[i - 1], h[i - 1]);
    }

    // rightMin[n] stays INFINITY_H: pole n has nobody on its right.
    // We go from the right end towards the left.
    for (int i = n - 1; i >= 1; i--) {
        rightMin[i] = min(rightMin[i + 1], h[i + 1]);
    }

    // Answer each question with just two lookups.
    for (int k = 0; k < q; k++) {

        int s;                    // the starting pole
        cin >> s;

        long long left;           // the answer for the LEFT direction
        long long right;          // the answer for the RIGHT direction

        // We can jump left only if the LOWEST pole on the left is
        // STRICTLY lower than pole s. (If it is equal or taller, every
        // pole on the left is too, so no jump is possible.)
        if (leftMin[s] < h[s]) {
            left = h[s] - leftMin[s];     // biggest drop = to the lowest pole
        } else {
            left = -1;
        }

        // Same idea for the right direction.
        if (rightMin[s] < h[s]) {
            right = h[s] - rightMin[s];
        } else {
            right = -1;
        }

        cout << left << " " << right << '\n';   // '\n' is faster than endl
    }

    return 0;         // tells the computer the program finished successfully
}
*/