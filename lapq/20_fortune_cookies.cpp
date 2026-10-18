/*
=====================================================================
QUESTION SUMMARY: "A row of cookies"
=====================================================================
You keep a row of cookies (left to right). Each cookie has a number
on it. At the start the row is empty.

Two operations:
 - Insert (L = 1, with k and x): put a new cookie with number x right
   AFTER the k-th cookie (k is 0 to 5).
       * k = 0 means the new cookie becomes the FIRST cookie.
       * If the row has fewer than k cookies, the new cookie goes
         at the END of the row.
 - Eat (L = 2, with k): eat the k-th cookie (k is 1 to 5).
       * If the row has fewer than k cookies, nothing happens.

TASK: Do all T operations, then print the final row, one number per
      line, from left to right.

INPUT:
 - Line 1: T = number of operations (1 <= T <= 100,000)
 - Next T lines: either "1 k x" (insert) or "2 k" (eat).

OUTPUT:
 - The cookie numbers left, one per line, left to right.

SAMPLE INPUT:
10
2 3
1 1 1
1 0 3
1 1 7
1 3 29
2 3
1 0 90
2 1
1 5 100
2 5

SAMPLE OUTPUT:
3
7
29
100

WHY? (walking through the sample)
 2 3     -> eat 3rd cookie, there is none           row: (empty)
 1 1 1   -> insert 1 after 1st (row empty -> end)   row: 1
 1 0 3   -> insert 3 at the front                   row: 3, 1
 1 1 7   -> insert 7 after 1st cookie               row: 3, 7, 1
 1 3 29  -> insert 29 after 3rd cookie              row: 3, 7, 1, 29
 2 3     -> eat 3rd cookie (the 1)                  row: 3, 7, 29
 1 0 90  -> insert 90 at the front                  row: 90, 3, 7, 29
 2 1     -> eat 1st cookie (the 90)                 row: 3, 7, 29
 1 5 100 -> only 3 cookies, so insert at the end    row: 3, 7, 29, 100
 2 5     -> no 5th cookie, nothing happens          row: 3, 7, 29, 100

KEY IDEA (a "linked list"):
 Inserting or removing in the middle of a normal list is slow because
 everything shifts. Instead, for every cookie we remember one note:
 "which cookie comes right after me?" (like a treasure hunt).
   - To INSERT, we change just two notes.
   - To EAT, we make the cookie BEFORE it point past it (one note).
 Since k is at most 5, we only ever walk at most 5 steps from the
 front, so every operation is very fast.

 We use a special "fake cookie" at spot 0, standing at the very front.
 It is not a real cookie. It lets us handle "insert at the front"
 (k = 0) in the same way as every other insert.
 The number 0 in a note also means "nothing after me" (end of row).
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list of numbers)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 lines is fast.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;            // a box to hold T, the number of operations
    cin >> t;         // read T from the input

    // Each cookie we ever create gets an ID: 1, 2, 3, ... (in the order
    // they are created). There are at most t cookies, plus spot 0 for
    // the fake front cookie, so we need t + 1 spots.
    //   nextCookie[id] = the ID of the cookie right after cookie id
    //                    (0 means nobody, so it is the last cookie)
    //   number[id]     = the number printed on cookie id
    vector<int> nextCookie(t + 2, 0);
    vector<int> number(t + 2, 0);

    int created = 0;  // how many cookies have been created so far

    // Repeat once for each operation.
    for (int i = 0; i < t; i++) {

        int op;       // 1 = insert, 2 = eat
        cin >> op;

        if (op == 1) {
            // ---------- INSERT ----------
            int k, x;         // k = after which cookie, x = new number
            cin >> k >> x;

            // Walk forward k cookies, starting from the fake front cookie.
            // "current" is the cookie we stand on. If we run out of
            // cookies (the next one is 0 = nobody), we stop early,
            // which means "insert at the end".
            int current = 0;
            for (int step = 0; step < k; step++) {
                if (nextCookie[current] == 0) {
                    break;                       // no more cookies, stop
                }
                current = nextCookie[current];   // move to the next cookie
            }

            // Create the new cookie.
            created = created + 1;
            int newCookie = created;
            number[newCookie] = x;

            // Insert it right after "current" in two steps:
            // Step 1: the new cookie points to what "current" pointed to.
            nextCookie[newCookie] = nextCookie[current];
            // Step 2: "current" now points to the new cookie.
            nextCookie[current] = newCookie;

        } else {
            // ---------- EAT ----------
            int k;
            cin >> k;

            // We want the cookie BEFORE the k-th one, so that we can
            // make it skip over the k-th cookie.
            // Start at the fake front cookie and move forward (k - 1)
            // times. After that, nextCookie[before] is the k-th cookie.
            int before = 0;
            for (int step = 0; step < k - 1; step++) {
                if (nextCookie[before] == 0) {
                    break;                       // ran out of cookies
                }
                before = nextCookie[before];
            }

            int target = nextCookie[before];     // the k-th cookie (or 0)

            // If target is 0, there is no k-th cookie, so do nothing.
            if (target != 0) {
                // Skip over it: "before" now points to whatever came
                // after the eaten cookie.
                nextCookie[before] = nextCookie[target];
            }
        }
    }

    // Print the final row. Start from the fake front cookie, follow the
    // notes, and stop when we reach 0 (nobody).
    int current = nextCookie[0];     // the first real cookie
    while (current != 0) {
        cout << number[current] << '\n';   // print this cookie's number
        current = nextCookie[current];     // follow the note to the next one
    }

    return 0;         // tells the computer the program finished successfully
}