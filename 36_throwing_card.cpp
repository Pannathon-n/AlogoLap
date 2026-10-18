/*
=====================================================================
QUESTION SUMMARY: "Throwing cards away"
=====================================================================
You have a deck of n cards numbered 1 to n. Card 1 is on TOP and
card n is on the BOTTOM.

While the deck has at least TWO cards, repeat these two steps:
 1) THROW AWAY the top card.
 2) Take the card that is now on top and move it to the BOTTOM.

TASK: For each n, print the cards in the order they were thrown away,
      then print the one card that is left at the end.

INPUT:
 - Each line has a number n (n <= 50).
 - The last line is 0. Do NOT process it.

OUTPUT (for each n, two lines):
 - Discarded cards: a, b, c      (separated by ", ")
 - Remaining card: x
 - No leading or trailing spaces on any line.

SAMPLE INPUT:
7
19
10
6
0

SAMPLE OUTPUT (first two cases):
Discarded cards: 1, 3, 5, 7, 4, 2
Remaining card: 6
Discarded cards: 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 4, 8, 12, 16, 2, 10, 18, 14
Remaining card: 6

WHY? (walking through n = 7, deck shown top -> bottom)
 Deck: 1 2 3 4 5 6 7
 Throw 1, move 2 to bottom: 3 4 5 6 7 2
 Throw 3, move 4 to bottom: 5 6 7 2 4
 Throw 5, move 6 to bottom: 7 2 4 6
 Throw 7, move 2 to bottom: 4 6 2
 Throw 4, move 6 to bottom: 2 6
 Throw 2, move 6 to bottom: 6
 Discarded: 1, 3, 5, 7, 4, 2     Remaining: 6

SPECIAL CASE: n = 1
 The deck already has only one card, so nothing is thrown away.
 The first line is just "Discarded cards:" (nothing after it, and no
 trailing space). The second line is "Remaining card: 1".

KEY IDEA:
 A "queue" is a line where you add at the BACK and remove from the
 FRONT, like people waiting in a line. The deck is exactly that:
   top of deck    = front of the queue
   bottom of deck = back of the queue
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <queue>      // lets us use "queue" (a line: add at back, remove from front)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold n, the number of cards

    // Read n. Keep going while reading works AND n is not 0.
    // Each time around this loop handles ONE test case.
    while (cin >> n && n != 0) {

        // Build the deck: put cards 1, 2, ..., n into the queue.
        // Card 1 goes in first, so it is at the FRONT (the top).
        queue<int> deck;
        for (int i = 1; i <= n; i++) {
            deck.push(i);     // push adds a card at the BACK
        }

        // Print the label first. We print the cards after it as we go.
        // There is NO space after the colon yet, so n = 1 prints just
        // "Discarded cards:" with no trailing space.
        cout << "Discarded cards:";

        bool first = true;    // true until we print the first discarded card

        // Repeat while there are at least two cards in the deck.
        while (deck.size() >= 2) {

            int top = deck.front();   // front() looks at the top card
            deck.pop();               // pop() throws it away

            // Print the discarded card.
            // The first one gets a space before it (after the colon).
            // Every later one gets ", " before it.
            if (first) {
                cout << " " << top;
                first = false;
            } else {
                cout << ", " << top;
            }

            // Move the new top card to the bottom:
            // look at the front card, remove it, add it at the back.
            int moved = deck.front();
            deck.pop();
            deck.push(moved);
        }

        cout << '\n';   // end the "Discarded cards" line

        // Only one card is left. It is at the front of the queue.
        cout << "Remaining card: " << deck.front() << '\n';
    }

    return 0;           // tells the computer the program finished successfully
}