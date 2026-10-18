/*
=====================================================================
QUESTION SUMMARY: "Bonus points"
=====================================================================
N players stand in a line. Each starts with 0 bonus points.
A game angel walks along the line, always standing next to ONE
player (the "current player"). At the start, the angel is with the
FIRST player.

The angel does M actions. There are 4 kinds:
 - Action 0: fly back to the FIRST player in the line.
 - Action 1: fly to the NEXT player in the line.
 - Action 2: insert a NEW player (with 0 points) right AFTER the
             current player. The angel STAYS with the current player
             (it does not move to the new one).
 - Action 3: give X bonus points to the current player.
             (This line has a second number, X.)

TASK: After all actions, print every player's bonus points, from the
      first player in the line to the last, on ONE line.

INPUT:
 - Line 1: N and M (1 <= N <= 50,000, 1 <= M <= 200,000)
 - Next M lines: the action type T (0 to 3).
   If T = 3, the line also has X (1 <= X <= 1000).

OUTPUT:
 - One line: the bonus of each player in line order, separated by spaces.

SAMPLE INPUT:
5 13
1
3 10
0
2
1
1
3 20
1
3 50
0
1
3 20
2

SAMPLE OUTPUT:
0 20 0 30 50 0 0

WHY? (walking through the first few actions, * = where the angel is)
 Start:                0* 0 0 0 0
 Action 1 (next):      0 0* 0 0 0
 Action 3 10 (give):   0 10* 0 0 0
 Action 0 (back):      0* 10 0 0 0
 Action 2 (insert):    0* 0 10 0 0 0   <- new player after the angel
 ...and so on, until the final line is  0 20 0 30 50 0 0

KEY IDEA (a "linked list"):
 Inserting into the middle of a normal list is slow, because
 everything after it has to shift. Instead, for every player we
 remember "which player comes right after me" (a note, like a treasure
 hunt). Inserting a new player only changes two notes, which is very
 fast no matter how long the line is.
 We also keep a box called "angel" that holds the current player.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of numbers)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 200,000 lines is fast.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;         // n = starting players, m = number of actions
    cin >> n >> m;    // read both numbers

    // Players are numbered by when they JOINED:
    // the starting players are 1..n, and each new player gets the next
    // free number. At most m new players can be added, so we need
    // room for n + m players (plus spot 0, which we do not use).
    //
    // nextPlayer[x] = the player standing right after player x
    //                 (0 means "nobody", i.e. x is last in the line).
    // bonus[x]      = how many bonus points player x has. All start at 0.
    vector<int> nextPlayer(n + m + 2, 0);
    vector<long long> bonus(n + m + 2, 0);

    // Link the starting players: 1 -> 2 -> 3 -> ... -> n
    for (int i = 1; i < n; i++) {
        nextPlayer[i] = i + 1;   // the player after i is i+1
    }
    nextPlayer[n] = 0;           // the last player has nobody after them

    int angel = 1;       // the angel starts with the first player (player 1)
    int count = n;       // how many players exist so far (to number new ones)

    // Repeat once for each action.
    for (int i = 0; i < m; i++) {

        int t;           // the type of this action (0, 1, 2 or 3)
        cin >> t;

        if (t == 0) {
            // Action 0: fly back to the FIRST player.
            // Player 1 is always first, because we only ever insert
            // players AFTER someone, never before player 1.
            angel = 1;

        } else if (t == 1) {
            // Action 1: fly to the NEXT player.
            // Only move if there is a next player (0 means nobody).
            if (nextPlayer[angel] != 0) {
                angel = nextPlayer[angel];
            }

        } else if (t == 2) {
            // Action 2: insert a new player right AFTER the angel's player.
            count = count + 1;               // a new player joins
            int newPlayer = count;           // their number

            // Same two-step insert as a treasure hunt:
            // Step 1: the new player points to whoever the angel's
            //         player was pointing to.
            nextPlayer[newPlayer] = nextPlayer[angel];
            // Step 2: the angel's player now points to the new player.
            nextPlayer[angel] = newPlayer;
            // The angel does NOT move.

        } else {
            // Action 3: the only choice left. Read X and give it to
            // the current player.
            int x;
            cin >> x;
            bonus[angel] = bonus[angel] + x;
        }
    }

    // Print the final line. Start at player 1 and follow the notes
    // until we reach 0 (the end of the line).
    int current = 1;
    bool first = true;           // used so we put spaces BETWEEN numbers only
    while (current != 0) {
        if (!first) {
            cout << ' ';         // a space before every number except the first
        }
        cout << bonus[current];  // print this player's bonus
        first = false;
        current = nextPlayer[current];   // follow the note to the next player
    }
    cout << '\n';                // end the line

    return 0;                    // tells the computer the program finished successfully
}