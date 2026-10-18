/*
=====================================================================
QUESTION SUMMARY: "The Galactic Fleet Selection"
=====================================================================
N starships applied for a fleet. You must choose exactly K of them.
The ships are already listed from BEST (rank 1) to WORST (rank N).
Each ship has a Registration ID and belongs to a Star System.

DIVERSITY RULE: in the first pass, no more than C ships from the same
Star System may be chosen.

PASS 1: Go down the list from best to worst. Choose a ship if its
        Star System currently has FEWER than C chosen ships.
        Stop immediately once K ships are chosen.
PASS 2: If you reach the bottom with fewer than K chosen, the
        diversity rule is lifted. Go back to the TOP and go down
        again, choosing the skipped ships (the highest ranked first)
        until you have exactly K.

OUTPUT: Print the IDs of the K chosen ships in their ORIGINAL list
        order (not in the order they were chosen), one per line.

INPUT:
 - Line 1: N, K and C (1 <= K <= N <= 100,000, 1 <= C <= N)
 - Next N lines: ID and S (the ship's ID and its Star System ID,
   each up to 1,000,000,000), from best to worst.

OUTPUT:
 - K lines: the chosen IDs in original order.

SAMPLE INPUT 1:
6 4 1
201 9
202 9
203 9
204 8
205 9
206 9

SAMPLE OUTPUT 1:
201
202
203
204

WHY? (walking through sample 1, K = 4, C = 1)
 Pass 1:
   201 (system 9): 0 chosen from system 9 -> CHOOSE
   202 (system 9): already 1 -> skip
   203 (system 9): already 1 -> skip
   204 (system 8): 0 chosen -> CHOOSE
   205, 206 (system 9): skip
   Only 2 chosen, but we need 4.
 Pass 2: skipped ships from the top: 202, 203, 205, 206.
   Choose 202 and 203 -> now 4 chosen. Stop.
 Chosen: 201, 202, 203, 204 (printed in original order).

SAMPLE INPUT 2 (K = 8, C = 2) gives 596 868 200 931 989 553 947 479:
 Pass 1 chooses 596, 868, 200, 989, 553, 947, 479 (7 ships).
 931, 368 and 50 are skipped because their systems already have 2.
 Pass 2 chooses 931 (the highest ranked skipped ship) -> 8 chosen.
 Printed in original order: 596 868 200 931 989 553 947 479.

KEY IDEA:
 - Keep a "map" that counts how many chosen ships each Star System
   has. (Star System IDs go up to 1 billion, so we cannot use a plain
   list with one spot per ID. A map stores only the IDs we meet.)
 - Keep a true/false mark for each ship: "chosen or not".
 - Pass 1 and Pass 2 each go through the list once.
 - At the end, print the marked ships by going through the list from
   the top, which automatically gives the original order.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <map>        // lets us use "map" (a lookup table: key -> value)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 lines is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, c;      // n = ships, k = ships needed, c = limit per system
    cin >> n >> k >> c;

    // id[i] = Registration ID of the i-th ship (i = 0 is the best ship).
    // system[i] = Star System ID of the i-th ship.
    vector<int> id(n);
    vector<int> system(n);
    for (int i = 0; i < n; i++) {
        cin >> id[i] >> system[i];
    }

    // chosen[i] is true if the i-th ship has been chosen.
    // Every ship starts as "false" (not chosen).
    vector<bool> chosen(n, false);

    // countInSystem[s] = how many chosen ships belong to Star System s.
    // A map returns 0 for an ID it has not seen yet (when we use [ ]).
    map<int, int> countInSystem;

    int total = 0;    // how many ships we have chosen so far

    // ---------- PASS 1: respect the diversity rule ----------
    for (int i = 0; i < n && total < k; i++) {
        // The loop stops when total reaches k ("total < k" becomes false).

        // Choose the ship only if its Star System has fewer than C chosen.
        if (countInSystem[system[i]] < c) {
            chosen[i] = true;               // mark it as chosen
            countInSystem[system[i]]++;     // one more from this system
            total++;                        // one more ship in the fleet
        }
    }

    // ---------- PASS 2: lift the rule if we still need ships ----------
    // Go from the top again and take the skipped ships, best first.
    for (int i = 0; i < n && total < k; i++) {
        if (!chosen[i]) {       // "!" means NOT: this ship was skipped
            chosen[i] = true;   // choose it now (no diversity check)
            total++;
        }
    }

    // ---------- OUTPUT ----------
    // Going through the list from the top prints the chosen ships in
    // their original order.
    for (int i = 0; i < n; i++) {
        if (chosen[i]) {
            cout << id[i] << '\n';   // '\n' is faster than endl
        }
    }

    return 0;         // tells the computer the program finished successfully
}

/*
What the Galactic Fleet Selection is similar to
1. Closest match: Sorting by frequency (counting per group)

The core of this question is “count how many items belong to each group, and act on that count.” In Sorting by frequency, you counted how many times each number appeared. Here you count how many chosen ships belong to each Star System. The difference is that the Star System IDs go up to 1 billion, so you use a map instead of a plain list.

2. Two-pass greedy: Smallest Number and Good pairs

Fleet Selection is a greedy problem: go down the list in order and take whatever is allowed. It is a simpler cousin of Smallest Number, which also scans left to right and makes a rule-based choice at each step.

3. “Process in order, use a flag per item”: Card game and Color rocks

You keep a true/false mark for each item (chosen[i]) and print the marked ones in their original order at the end. Card game used the same trick with its removed[i] flags.

4. Simple simulation: Buckets and LLM Accounts

Both of those follow a rule like “pick the best item that meets the conditions, update its count, repeat.” Fleet Selection follows the same rule-following style, with the twist of a second pass when the first one comes up short.

5. Why this matters for the midterm
Skills tested: reading a rule carefully, counting per group with a map, and using a flag array.
Common mistakes: stopping at K in pass 1 (it must stop immediately), forgetting that pass 2 skips the diversity check, and printing in the order chosen instead of the original list order.
Efficiency: N is 100,000, so one pass through the list per step is fine. A map lookup is about log N, which is fast enough.
*/