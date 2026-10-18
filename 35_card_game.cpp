/*
=====================================================================
QUESTION SUMMARY: "Card game"
=====================================================================
There is a row of N cards, each with a positive value. We also get a
list of M numbers x1, x2, ..., xM (each at most 10).
A "current card" marker starts on the FIRST card.

The game has M rounds. In round i:
 1) Starting from the current card, count cards one by one, adding up
    their values, until the total is AT LEAST xi.
 2) The LAST card counted is DISCARDED (removed from the list).
 3) The card right AFTER the discarded card becomes the new current
    card.
 4) The list is a CIRCLE: after the last card, counting continues at
    the first card.

TASK: After M rounds, print the values of the remaining cards
      (N - M of them), one per line, in their original order.

INPUT:
 - Line 1: N and M (1 <= N <= 100,000, 1 <= M < N)
 - Line 2: N card values (1 to 1000)
 - Next M lines: x1 ... xM (each 1 to 10)

OUTPUT:
 - N - M lines: the remaining card values. 

SAMPLE INPUT:
10 5
1 2 5 3 4 9 10 5 1 7
10
4
10
9
2

SAMPLE OUTPUT:
1
5
9
5
1

WHY? (walking through the sample, [ ] = current card)
 Start:   [1] 2 5 3 4 9 10 5 1 7
 x = 10:  count 1+2+5+3 = 11 >= 10, discard 3.   1 2 5 [4] 9 10 5 1 7
 x = 4:   count 4 = 4, discard 4.                1 2 5 [9] 10 5 1 7
 x = 10:  count 9+10 = 19, discard 10.           1 2 5 9 [5] 1 7
 x = 9:   count 5+1+7 = 13, discard 7. The next card wraps around to
          the first card.                        [1] 2 5 9 5 1
 x = 2:   count 1+2 = 3 >= 2, discard 2.         1 [5] 9 5 1
 Remaining: 1 5 9 5 1

KEY IDEA (circular linked list):
 Removing a card from the middle of a normal list is slow, because
 everything after it must shift. So for each card we keep a note:
 "which card comes right after me?" (like a treasure hunt).
 The last card's note points back to the first card, so it is a circle.
 To remove a card, the card BEFORE it just skips over it. That is why
 we also keep a marker "before" = the card just before the current
 one (the hint in the question says the same thing).

 Each round counts at most about 10 cards, because every card has a
 value of at least 1 and xi is at most 10. So the whole game is fast.

 At the end we do not need to follow the notes. We mark removed cards
 with a true/false flag, and print the unmarked cards in their
 original order (index 0, 1, 2, ...).
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;         // n = number of cards, m = number of rounds
    cin >> n >> m;    // read both numbers

    // value[i] = the number written on card i.
    // Cards are numbered 0 to n-1 (C++ lists start counting at 0).
    vector<int> value(n);
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    // nextCard[i] = the card that comes right after card i.
    // The last card (n-1) points back to card 0, making a circle.
    vector<int> nextCard(n);
    for (int i = 0; i < n; i++) {
        nextCard[i] = (i + 1) % n;   // "% n" wraps n back to 0
    }

    // removed[i] is true if card i has been discarded.
    // Every card starts as "false" (not removed).
    vector<bool> removed(n, false);

    int current = 0;       // the current card: the first card
    int before = n - 1;    // the card just BEFORE the current one:
                           // the last card (because it is a circle)

    // Play the M rounds.
    for (int round = 0; round < m; round++) {

        int x;             // the target total for this round
        cin >> x;          // read it from the input

        int total = 0;     // the running total of the counted cards

        // Count cards until the total reaches x.
        while (true) {

            total = total + value[current];   // count the current card

            if (total >= x) {
                // This is the LAST card counted, so we discard it.
                removed[current] = true;

                // The card before it now skips over it
                // (points to the card after it).
                nextCard[before] = nextCard[current];

                // The card after the discarded one is the new current
                // card. "before" stays the same, because it is still
                // the card in front of the new current card.
                current = nextCard[current];

                break;     // this round is finished
            }

            // Not enough yet: move on to the next card.
            // The card we just counted becomes the "before" card.
            before = current;
            current = nextCard[current];
        }
    }

    // Print the cards that were not removed, in the original order.
    for (int i = 0; i < n; i++) {
        if (!removed[i]) {
            cout << value[i] << '\n';   // '\n' is faster than endl
        }
    }

    return 0;         // tells the computer the program finished successfully
}   