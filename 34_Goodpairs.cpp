/*
=====================================================================
QUESTION SUMMARY: "Good pairs"
=====================================================================
A shop has N products. Their prices are given in SORTED order
(smallest first): p1 <= p2 <= ... <= pN.

A pair of two different products is a GOOD PAIR if BOTH are true:
 1) PROMOTION rule: the two prices added together are >= S.
    (Then you only pay for the more expensive one.)
 2) DIFFERENCE rule: the two prices differ by at most T.

TASK: Count how many good pairs exist.
      (Two products with the same price are still different
       products, so they can form a pair.)

INPUT:
 - Line 1: N, S and T
       (2 <= N <= 100,000, 1 <= S <= 1e9, 1 <= T <= 1e9)
 - Next N prices, in sorted order (each 1 to 1e9).

OUTPUT:
 - One integer: the number of good pairs.

SAMPLE INPUT 1:
5 100 20
40 45 60 61 70
SAMPLE OUTPUT 1:
6

WHY 6? (walking through sample 1, S = 100, T = 20)
 (40,60): sum 100 >= 100 OK, difference 20 <= 20 OK   -> good
 (45,60): sum 105, difference 15                      -> good
 (45,61): sum 106, difference 16                      -> good
 (60,61): sum 121, difference 1                       -> good
 (60,70): sum 130, difference 10                      -> good
 (61,70): sum 131, difference 9                       -> good
 (40,45): sum 85 < 100                                -> bad
 (40,61): difference 21 > 20                          -> bad
 (45,70): difference 25 > 20                          -> bad
 (40,70): difference 30 > 20                          -> bad
 Total good pairs = 6.

SAMPLE INPUT 2:
10 10 3
1 2 3 4 5 6 7 8 9 10
SAMPLE OUTPUT 2:
14

KEY IDEA:
 Checking every pair is about 5 BILLION pairs when N = 100,000.
 That is too slow. Instead, for each product j, we count how many
 EARLIER products i (before j in the list) pair well with it.
 Because the list is sorted, price[j] is the bigger one of the pair.
 The earlier price p must satisfy:
     p >= S - price[j]      (the sum is big enough)
     p >= price[j] - T      (the difference is small enough)
 So p must be at least the BIGGER of those two numbers. Call it "need".
 The list is sorted, so all prices >= need sit together at the END
 of the earlier products. We use lower_bound (a fast binary search)
 to find where they start. Everything from that spot up to j-1 counts.
 Each product costs about log(N) work, so the total is fast.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <algorithm>  // lets us use lower_bound (fast search) and max
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;            // number of products
    long long s, t;   // s = promotion limit, t = biggest allowed difference
    cin >> n >> s >> t;

    // The prices, already sorted by the question.
    // "long long" is a big number box. S - price can go below zero and
    // the numbers can be large, so we use it to be safe.
    vector<long long> price(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }

    // The number of good pairs. It can reach billions, so we use
    // long long (a normal int would overflow).
    long long pairs = 0;

    // Treat each product j as the MORE expensive product of the pair
    // (j is later in the list, so its price is >= all earlier ones).
    for (int j = 1; j < n; j++) {

        // The earlier price must be at least this big:
        //   - S - price[j]  to make the sum reach S
        //   - price[j] - T  to keep the difference within T
        // "max" picks the bigger of the two numbers.
        long long need = max(s - price[j], price[j] - t);

        // Search ONLY among the earlier products (spots 0 to j-1).
        // lower_bound gives the first spot whose price is >= need.
        // "- price.begin()" turns that spot into a plain number.
        int firstGood = lower_bound(price.begin(), price.begin() + j, need)
                        - price.begin();

        // Every earlier product from firstGood up to j-1 works.
        // If none works, firstGood equals j and we add 0.
        pairs = pairs + (j - firstGood);
    }

    cout << pairs << endl;   // print the number of good pairs

    return 0;                // tells the computer the program finished successfully
}