/*
=====================================================================
QUESTION SUMMARY: "Sport Tournament"
=====================================================================
There are N players (2 <= N <= 200,000). Player i has a potential Pi.
EVERY player plays against EVERY other player exactly once.
In a match between two players:
 - the player with HIGHER potential wins    -> gets 2 points
 - the player with LOWER potential loses    -> gets 0 points
 - if the potentials are EQUAL, it is a draw -> both get 1 point

TASK: Print the total score of every player (one per line, in the
      order the players were given).

INPUT:
 - Line 1: N
 - Next N lines: Pi = the potential of player i (1 to 1,000,000,000)

OUTPUT:
 - N lines: line i is the total score of player i.

SAMPLE INPUT 1:
4
10
20
10
6

SAMPLE OUTPUT 1:
3
6
3
0

WHY? (walking through sample 1)
 Player 1 (10): beats player 4 (6) -> 2, draws with player 3 (10) -> 1,
                loses to player 2 (20) -> 0.   Total = 3
 Player 2 (20): beats all three others -> 2 + 2 + 2 = 6
 Player 3 (10): same as player 1 -> 3
 Player 4 (6) : loses to everyone -> 0

WHY NOT JUST COMPARE EVERY PAIR?
 With 200,000 players that is about 20 BILLION matches. Far too slow
 for 1 second.

KEY IDEA (sort + binary search):
 For one player with potential p:
   - Let "less"  = how many players have potential LESS than p.
   - Let "equal" = how many OTHER players have potential EQUAL to p.
   - Score = 2 * less + 1 * equal.
 If we SORT a copy of all the potentials, then:
   - lower_bound(p) gives the position of the first value that is
     NOT less than p. That position number IS "less"
     (it is how many values come before it).
   - upper_bound(p) gives the position just after the last value equal
     to p. So (upper - lower) is the number of players equal to p,
     INCLUDING the player himself, so we subtract 1.
 Sorting is fast, and each lookup is fast (it halves the search each
 time). Total time is about N * log(N), which is fine.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of values)
#include <algorithm>  // lets us use sort, lower_bound and upper_bound
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines (the question recommends them) because
    // there are up to 200,000 numbers to read and print.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;            // a box to hold N, the number of players
    cin >> n;         // read N from the input

    // The original potentials, in the original order (player 1 first).
    // We need to keep this order, because the output must follow it.
    vector<int> potential(n);
    for (int i = 0; i < n; i++) {
        cin >> potential[i];
    }

    // Make a SORTED copy (smallest to biggest).
    // Sorting this copy does not change the original list.
    vector<int> sorted = potential;
    sort(sorted.begin(), sorted.end());

    // Work out the score of each player, in the original order.
    for (int i = 0; i < n; i++) {

        int p = potential[i];   // this player's potential

        // lower_bound finds the first spot in the sorted list whose
        // value is NOT less than p. "- sorted.begin()" turns that spot
        // into a number = how many players have potential LESS than p.
        int less = lower_bound(sorted.begin(), sorted.end(), p) - sorted.begin();

        // upper_bound finds the first spot whose value is BIGGER than p.
        // So (upper - lower) = how many players have potential equal to p,
        // and that count includes this player himself.
        int upper = upper_bound(sorted.begin(), sorted.end(), p) - sorted.begin();
        int equalOthers = (upper - less) - 1;   // remove himself

        // Wins give 2 points each, draws give 1 point each.
        // A player can win about 200,000 games = 400,000 points at most,
        // which fits easily in an int.
        int score = 2 * less + equalOthers;

        cout << score << '\n';   // print with '\n' (faster than endl)
    }

    return 0;         // tells the computer the program finished successfully
}