/*
=====================================================================
QUESTION SUMMARY: "LLM Accounts"
=====================================================================
A company has N accounts for chatbot services.
Account i has:
 - Xi = tokens left (its quota)
 - Qi = quality. It costs Qi baht per token.
        (No two accounts have the same quality.)

M requests arrive, one at a time. Each request has:
 - T = how many tokens it needs
 - R = the minimum quality it needs

For each request, pick the BEST account, which must satisfy:
 1) Qj >= R         (good enough quality)
 2) Xj >= T         (enough tokens left)
 3) Among those, the one with the SMALLEST Qj (cheapest).

If such an account exists:
 - its tokens go DOWN by T,
 - the company pays T * Qj baht.
If no account works, the request is DISCARDED.

TASK: After all requests, print:
      (total baht paid) and (number of discarded requests).

INPUT:
 - Line 1: N and M (each up to 1000)
 - Next N lines: Xi and Qi
 - Next M lines: T and R

OUTPUT:
 - One line with two integers: total cost, discarded count.

SAMPLE OUTPUT:
31600 1

WHY? (walking through the first requests of the sample)
 Accounts (tokens, quality): 1:(100,20) 2:(200,30) 3:(200,15)
                             4:(300,100) 5:(100,10)
 Request (T=50, R=20): quality >= 20 -> accounts 1, 2, 4.
     Cheapest is account 1 (20), it has 100 >= 50 tokens.
     Pay 50 * 20 = 1000. Account 1 now has 50 tokens.
 Request (T=100, R=17): quality >= 17 -> accounts 1, 2, 4.
     Account 1 only has 50 < 100, so skip it. Next cheapest is
     account 2 (30). Pay 100 * 30 = 3000.
 ...and so on. Request 5 finds nobody, so it is discarded.
 Total = 1000 + 3000 + 500 + 25000 + 2100 = 31600, discarded = 1.

KEY IDEA:
 N and M are at most 1000, so for each request we can simply check
 EVERY account (1000 x 1000 = 1 million checks, very fast).
 For each request we remember the best account found so far.
 The total money can reach about 1000 x 1000 x 2000 = 2 billion,
 which is too close to the int limit, so we use "long long".
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n, m;         // n = number of accounts, m = number of requests
    cin >> n >> m;

    // tokens[i] = tokens left in account i
    // quality[i] = quality of account i (cost per token)
    // (C++ lists start counting at 0, so account 1 is spot 0.)
    vector<long long> tokens(n);
    vector<int> quality(n);

    for (int i = 0; i < n; i++) {
        cin >> tokens[i] >> quality[i];   // read Xi then Qi
    }

    long long totalCost = 0;   // total baht paid so far. Starts at 0.
    int discarded = 0;         // number of discarded requests. Starts at 0.

    // Handle each request one by one.
    for (int r = 0; r < m; r++) {

        long long t;           // tokens needed by this request
        int minQuality;        // minimum quality needed
        cin >> t >> minQuality;

        // "best" is the spot of the best account found so far.
        // -1 means "none found yet".
        int best = -1;

        // Check every account.
        for (int i = 0; i < n; i++) {

            // The account must have good enough quality AND enough tokens.
            // "&&" means AND: both must be true.
            if (quality[i] >= minQuality && tokens[i] >= t) {

                // It qualifies. Is it better than the best so far?
                // Better = nothing found yet, OR a smaller quality
                // (a smaller quality means a cheaper cost).
                if (best == -1 || quality[i] < quality[best]) {
                    best = i;
                }
            }
        }

        if (best == -1) {
            // Nobody qualifies: discard this request.
            discarded = discarded + 1;
        } else {
            // Use the best account: take away the tokens and pay.
            tokens[best] = tokens[best] - t;
            totalCost = totalCost + t * quality[best];
        }
    }

    // Print both answers on one line, separated by a space.
    cout << totalCost << " " << discarded << endl;

    return 0;         // tells the computer the program finished successfully
}