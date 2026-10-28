/*
T

=====================================================================
QUESTION SUMMARY: "
=====================================================================
A tape is a row of cells, each holding a number. A "head" sits in a
GAP between cells (never on a cell). At the start it is BEFORE the
first cell. There are 7 commands:

 1 x          WRITE   : insert ONE new cell x into the head's gap.
                        The head ends up just AFTER the new cell.
 2 c x1..xc   BLOCK   : insert c cells (in that order) into the gap.
                        Same as c WRITE commands. Head ends after them.
 3            LEFT    : move the head one gap left (nothing at the start).
 4            RIGHT   : move the head one gap right (nothing at the end).
 5            REWIND  : move the head to the very start.
 6            FFWD    : move the head to the very end.
 7 k          COMPRESS: replace the k cells just RIGHT of the head by ONE
                        cell holding their sum. The head does NOT move.
                        (There are always at least k cells to the right.)

TASK: After all N commands, print the tape from left to right,
      separated by single spaces.

INPUT:
 - Line 1: N (commands) and M (cells at power-on), both up to 200,000
 - Line 2: the M starting numbers (0 to 1e9)
 - Next N lines: one command each
 - The tape can grow up to 500,000 cells. Memory limit is only 32 MB.

OUTPUT:
 - One line with the final tape.

SAMPLE INPUT 3:          SAMPLE OUTPUT 3:
9 3                      1 15 9 18
10 5 9
7 2
1 1
6
2 3 4 6 8
3
3
7 2
3
7 2

WHY? (walking through sample 3, | = the head)
 start:        | 10 5 9
 7 2 (compress 2 cells right of head: 10 + 5 = 15):  | 15 9
 1 1 (write 1):                                      1 | 15 9
 6 (fast forward):                                   1 15 9 |
 2 3 4 6 8 (block):                                  1 15 9 4 6 8 |
 3 (left):                                           1 15 9 4 6 | 8
 3 (left):                                           1 15 9 4 | 6 8
 7 2 (compress 6 + 8 = 14):                          1 15 9 4 | 14
 3 (left):                                           1 15 9 | 4 14
 7 2 (compress 4 + 14 = 18):                         1 15 9 | 18
 Final tape: 1 15 9 18

SAMPLE 1 (tape 10 20 30 40, 11 commands) gives 37 1 2 33 40.
SAMPLE 2 (tape 20 30, 7 commands) gives 0 10 20 30 40 50 60 70.
 (I traced all three samples by hand and they match.)

=====================================================================
SIMILAR / DIFFERENT
=====================================================================
SIMILAR TO: "Tiniest machines", "Bonus points", "Zooma 1",
            "A row of cookies".
   - A marker (the head) walks along a list, and we insert or remove
     things right next to it.
   - Same tool: a LINKED LIST (each cell remembers its neighbor).
 DIFFERENT:
   - LEFT means we must be able to go BACKWARDS, so each cell needs
     both a "next" note AND a "prev" note: a DOUBLY linked list.
     (Tiniest machines only moved forward.)
   - REWIND and FFWD must be instant. A vector would have to shift or
     copy the whole tape, which is too slow. (The hint says so.)
     With a linked list, REWIND is just "head = the start" and FFWD is
     "head = the cell before the end".
   - COMPRESS merges k cells into one, so it deletes cells. It costs
     k steps, but it removes k-1 cells. Each cell can only be removed
     once, so the TOTAL work over all commands stays small.
   - Sums can reach about 500,000 x 1,000,000,000, so values need
     long long.
   - Memory is only 32 MB, so we reuse the IDs of deleted cells
     (a "free list") instead of creating new ones forever.

=====================================================================
PLAN
=====================================================================
 1. Every cell is a numbered node with value[], nextNode[], prevNode[].
 2. Two SPECIAL nodes that are not real cells:
        START (id 0) : stands before the first cell
        END   (id 1) : stands after the last cell
    They remove all the special cases (empty tape, ends of the tape).
 3. "cur" = the node just LEFT of the head's gap.
        the cell right of the head = nextNode[cur]
        head at the very start     -> cur == START
        head at the very end       -> nextNode[cur] == END
 4. Commands:
        WRITE   : make a node, insert it after cur, cur = the new node
        BLOCK   : do WRITE for each number
        LEFT    : if cur != START, cur = prevNode[cur]
        RIGHT   : if nextNode[cur] != END, cur = nextNode[cur]
        REWIND  : cur = START
        FFWD    : cur = prevNode[END]
        COMPRESS: add up the k nodes after cur into the first of them,
                  skip over the rest, and free those nodes.
 5. Print by walking from nextNode[START] until we reach END.
=====================================================================
*/
/*
#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

// The three "notes" for every node, stored in lists.
// value[id]    = the number in the cell
// nextNode[id] = the node right AFTER it
// prevNode[id] = the node right BEFORE it
vector<long long> value;      // "long long" = big number box (sums get huge)
vector<int> nextNode;
vector<int> prevNode;

// IDs of deleted nodes that we can reuse (this saves memory).
vector<int> freeIds;

const int START = 0;          // special node before the first cell
const int END = 1;            // special node after the last cell

// Gives us a node ID: reuse a deleted one if there is one,
// otherwise make a brand new one at the end of the lists.
int makeNode(long long v) {
    int id;
    if (!freeIds.empty()) {
        id = freeIds.back();          // take a deleted ID
        freeIds.pop_back();
        value[id] = v;
    } else {
        id = (int)value.size();       // the next unused ID
        value.push_back(v);
        nextNode.push_back(0);
        prevNode.push_back(0);
    }
    return id;
}

// Inserts a new cell with number v right AFTER node "cur",
// and returns the new node (the head moves to just after it).
int insertAfter(int cur, long long v) {
    int id = makeNode(v);
    int after = nextNode[cur];        // who used to come after cur

    // Link: cur <-> id <-> after
    nextNode[id] = after;
    prevNode[id] = cur;
    prevNode[after] = id;
    nextNode[cur] = id;
    return id;
}

int main() {          // every C++ program starts running here

    // Magic speed-up lines: there can be about 700,000 numbers to read.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;         // n = number of commands, m = cells at power-on
    cin >> n >> m;

    // Create the two special nodes (IDs 0 and 1) and link them together:
    // START <-> END   (an empty tape).
    value.push_back(0);               // node 0 = START
    nextNode.push_back(END);
    prevNode.push_back(0);
    value.push_back(0);               // node 1 = END
    nextNode.push_back(0);
    prevNode.push_back(START);

    // Read the starting tape. We add each cell after "cur", so they end
    // up in the same left-to-right order as the input.
    int cur = START;
    for (int i = 0; i < m; i++) {
        long long a;
        cin >> a;
        cur = insertAfter(cur, a);
    }

    // At power-on the head is BEFORE the first cell.
    cur = START;

    // Run the N commands.
    for (int i = 0; i < n; i++) {

        int type;                     // the command number, 1 to 7
        cin >> type;

        if (type == 1) {
            // WRITE x: insert one cell, the head ends after it.
            long long x;
            cin >> x;
            cur = insertAfter(cur, x);

        } else if (type == 2) {
            // BLOCK c x1 ... xc: same as c WRITE commands, in order.
            int c;
            cin >> c;
            for (int j = 0; j < c; j++) {
                long long x;
                cin >> x;
                cur = insertAfter(cur, x);
            }

        } else if (type == 3) {
            // LEFT: move back one gap, unless we are already at the start.
            if (cur != START) {
                cur = prevNode[cur];
            }

        } else if (type == 4) {
            // RIGHT: move forward one gap, unless the next node is END
            // (that means no cell is right of the head).
            if (nextNode[cur] != END) {
                cur = nextNode[cur];
            }

        } else if (type == 5) {
            // REWIND: jump to the very start.
            cur = START;

        } else if (type == 6) {
            // FFWD: jump to the very end = just after the LAST real cell,
            // which is the node right BEFORE the END node.
            cur = prevNode[END];

        } else {
            // type == 7, COMPRESS k:
            // Add up the k cells right of the head into the FIRST of them,
            // and remove the other k-1 cells. The head does NOT move.
            int k;
            cin >> k;

            int first = nextNode[cur];    // the first cell right of the head
            long long sum = 0;
            int node = first;

            for (int j = 0; j < k; j++) {
                sum = sum + value[node];          // add this cell
                int following = nextNode[node];   // remember the next one
                if (node != first) {
                    freeIds.push_back(node);      // this cell is deleted: reuse its ID later
                }
                node = following;                 // move on
            }
            // After the loop, "node" is the cell right AFTER the k cells.

            value[first] = sum;           // the first cell now holds the total
            nextNode[first] = node;       // and links straight to what follows
            prevNode[node] = first;
        }
    }

    // Print the final tape: start at the first real cell and follow the
    // notes until we reach END.
    bool firstPrinted = true;             // so spaces go BETWEEN numbers only
    int p = nextNode[START];
    while (p != END) {
        if (!firstPrinted) {
            cout << ' ';
        }
        cout << value[p];
        firstPrinted = false;
        p = nextNode[p];
    }
    cout << '\n';

    return 0;         // tells the computer the program finished successfully
}
*/