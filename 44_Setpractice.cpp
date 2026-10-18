/*
=====================================================================
QUESTION SUMMARY: "Practice: set"
=====================================================================
You are given N integers X1..XN and M queries Y1..YM.
For each query Y, find the X that is CLOSEST to Y, meaning the one
with the smallest |X - Y|. If two X values are equally close, print
the SMALLER one.

You must use the STL "set" (a collection that keeps its numbers
sorted and has no duplicates).

INPUT:
 - Line 1: N and M (each up to 100,000)
 - Next N lines: the numbers X (0 to 1,000,000,000)
 - Next M lines: the queries Y (0 to 1,000,000,000)

OUTPUT:
 - M lines: the closest X for each query.

SAMPLE INPUT:
5 4
10 20 35 12 25        (X values, one per line in the real input)
100 11 17 25          (queries, one per line in the real input)

SAMPLE OUTPUT:
35
10
20
25

WHY? (walking through the sample, set = {10, 12, 20, 25, 35})
 Query 100: closest is 35.
 Query 11 : 10 is 1 away, 12 is 1 away. Tie -> the smaller one: 10.
 Query 17 : 12 is 5 away, 20 is 3 away -> 20.
 Query 25 : 25 itself is in the set (distance 0) -> 25.

KEY IDEA:
 In a sorted set, the closest number to Y is either:
   - the first number that is >= Y   (found with lower_bound), or
   - the number just BEFORE that one (the biggest number < Y).
 We find both (if they exist), compare their distances to Y, and pick
 the closer one. On a tie we pick the smaller one (the one before).
 Each search is fast (about log N steps).
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <set>        // lets us use "set" (a sorted collection)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading lots of numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;         // n = how many X numbers, m = how many queries
    cin >> n >> m;

    set<long long> numbers;   // the sorted collection of X values

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        numbers.insert(x);    // insert puts x in the right sorted place
    }

    // Answer each query.
    for (int j = 0; j < m; j++) {

        long long y;
        cin >> y;

        // lower_bound gives an "iterator" (a pointer-like finger) to the
        // first number that is >= y. If there is none, it equals end().
        set<long long>::iterator right = numbers.lower_bound(y);

        long long answer;

        if (right == numbers.end()) {
            // Every number is smaller than y, so the closest is the
            // last (biggest) number in the set.
            // rbegin() points at the last element.
            answer = *numbers.rbegin();

        } else if (right == numbers.begin()) {
            // There is no number before "right", so "right" is the answer.
            // The "*" means "the value that the finger points at".
            answer = *right;

        } else {
            // Both neighbors exist.
            set<long long>::iterator left = right;
            --left;               // move the finger one step back

            long long distLeft = y - *left;     // distance to the smaller one
            long long distRight = *right - y;   // distance to the bigger one

            // On a tie (equal distance) we want the SMALLER number,
            // which is "left". So we use <= for the left side.
            if (distLeft <= distRight) {
                answer = *left;
            } else {
                answer = *right;
            }
        }

        cout << answer << '\n';   // '\n' is faster than endl
    }

    return 0;         // tells the computer the program finished successfully
}