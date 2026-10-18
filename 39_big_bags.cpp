/*
=====================================================================
QUESTION SUMMARY: "Big Bags"
=====================================================================
You have N bags, numbered 1 to N. Bag i has size Si.
The sizes are all different and given in increasing order.
A bag of size Si can hold a total weight of at most 10 * Si.
You are also given a number K.

A bag is called BIG if it can hold K OTHER bags inside it, where each
of those K bags is FULL (a bag j full of weight weighs 10 * Sj).

TASK: Count how many bags are big.

INPUT:
 - Line 1: N and K
 - Next N lines: Si (the sizes, in increasing order)

OUTPUT:
 - One integer: the number of big bags.

SAMPLE INPUT 1:
5 2
2 3 4 6 10          (one per line in the real input)
SAMPLE OUTPUT 1:
2

WHY 2? (walking through sample 1, K = 2)
 Capacities: bag1=20, bag2=30, bag3=40, bag4=60, bag5=100
 Full weights of the bags: 20, 30, 40, 60, 100
 Bag 3 (capacity 40): the two lightest OTHER bags weigh 20 + 30 = 50.
                      50 > 40, so NOT big.
 Bag 4 (capacity 60): 20 + 30 = 50 <= 60, so BIG.
 Bag 5 (capacity 100): 20 + 30 = 50 <= 100, so BIG.
 Bags 1 and 2 are too small. Answer = 2.

SAMPLE INPUT 2:
5 3
2 3 4 6 10
SAMPLE OUTPUT 2:
1
 (Only bag 5 works: 20 + 30 + 40 = 90 <= 100.)

KEY IDEA:
 To fit K bags into bag i most easily, choose the K LIGHTEST bags
 other than bag i. Everything is multiplied by 10 on both sides, so
 we can simply compare sizes:
        (sum of sizes of the K smallest OTHER bags) <= Si
 Because the sizes are sorted, the K smallest bags are the first K.
   - If i is AFTER the first K bags (i > K):
         the K smallest others are bags 1..K, so the sum = P[K].
   - If i is among the first K bags (i <= K):
         bag i is one of the smallest, so we take bags 1..K+1
         but skip bag i, so the sum = P[K+1] - Si.
         (This needs K+1 <= N, otherwise there are not enough
          other bags.)
 where P[x] = size1 + size2 + ... + sizex (a "prefix sum").
 The sums can be very large, so we use long long.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;         // n = number of bags, k = how many bags must fit inside
    cin >> n >> k;

    // size[i] = the size of bag i (bags are numbered from 1).
    // prefix[x] = size[1] + size[2] + ... + size[x].
    // Spot 0 is unused / zero. "long long" is a big number box.
    vector<long long> size(n + 1, 0);
    vector<long long> prefix(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> size[i];                         // read the size of bag i
        prefix[i] = prefix[i - 1] + size[i];    // running total so far
    }

    int answer = 0;   // how many big bags we have found. Starts at 0.

    // Check every bag one by one.
    for (int i = 1; i <= n; i++) {

        long long sumNeeded;     // total size of the K lightest OTHER bags
        bool possible = true;    // do enough other bags exist?

        if (i > k) {
            // Bag i is not among the K lightest, so those are bags 1..K.
            sumNeeded = prefix[k];
        } else {
            // Bag i is among the first K bags. Take bags 1..K+1 and
            // skip bag i. This only works if bag K+1 exists.
            if (k + 1 > n) {
                possible = false;    // not enough other bags
                sumNeeded = 0;
            } else {
                sumNeeded = prefix[k + 1] - size[i];
            }
        }

        // The bag is big if enough bags exist AND they fit inside.
        if (possible && sumNeeded <= size[i]) {
            answer = answer + 1;
        }
    }

    cout << answer << endl;   // print the number of big bags

    return 0;                 // tells the computer the program finished successfully
}