/*
=====================================================================
MOCK TEST  (6 problems)
=====================================================================
Each problem has 4 parts, in this order:
  1) QUESTION             : the problem statement + sample + trace
  2) SIMILAR / DIFFERENT  : which practice problem it looks like, and
                            how it is different
  3) PLAN                 : the idea in plain words, before any code
  4) CODE                 : the answer, with a comment on every step

HOW TO USE THIS FILE
 - Try to solve each problem YOURSELF first (read only part 1).
 - Each problem is its own function: problem1() ... problem6().
 - main() at the bottom calls ONE of them. Change which one to test.
 - All sample outputs were traced by hand.
=====================================================================
*/

#include <iostream>   // cin (read input) and cout (print output)
#include <vector>     // vector: a list that can grow and shrink
#include <string>     // string: a variable that holds text
#include <stack>      // stack: a pile where you only touch the top
#include <queue>      // queue: a line, add at the back, remove from the front
#include <map>        // map: a lookup table (key -> value)
#include <algorithm>  // sort
#include <utility>    // pair: two values stuck together, make_pair
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout


/*
#####################################################################
PROBLEM 1: "The Library Shelf"                         (difficulty: easy)
#####################################################################

---------------------------- 1) QUESTION ----------------------------
 A library shelf starts EMPTY. You get Q commands (Q <= 5000):
   ADD X        : put book X at the END of the shelf.
   DROP         : remove the FIRST book (the front). If the shelf is
                  empty, do nothing.
   AFTER Y X    : find book Y (search from the front). If found, put
                  book X right AFTER Y. If Y is not found, do nothing.
   DELETE X     : find the first book X (from the front) and remove it.
                  If not found, do nothing.
 Print the final shelf from front to back, separated by single spaces.
 If the shelf is empty, print: Empty

 Input : Q, then Q commands (one per line). Book IDs are up to 1e9.
 Output: one line.

 SAMPLE INPUT          SAMPLE OUTPUT
 7                     2 9 4
 ADD 1
 ADD 2
 ADD 3
 AFTER 2 9
 DROP
 DELETE 3
 ADD 4

 Trace (front -> back):
   ADD 1       -> 1
   ADD 2       -> 1 2
   ADD 3       -> 1 2 3
   AFTER 2 9   -> 1 2 9 3       (9 goes right after book 2)
   DROP        -> 2 9 3         (front book 1 removed)
   DELETE 3    -> 2 9
   ADD 4       -> 2 9 4

------------------------ 2) SIMILAR / DIFFERENT ---------------------
 SIMILAR TO: "The Conductor's Magical Train" (mock exam A) and
             "A row of cookies".
   - Both are "keep a list and obey commands" problems.
   - Same tool: a vector with insert / erase. N is small (5000), so
     shifting items is fast enough. No linked list is needed.
 DIFFERENT:
   - The Train used INSERT by INDEX (the I-th position). Here we
     insert AFTER A VALUE, so we must FIND the value first, and then
     insert at (its index + 1).
   - DROP removes from the FRONT. The Train's POP removed the BACK.
   - If the value Y is not found, we do nothing (but we must STILL
     read both numbers, or the input gets out of sync).

------------------------------ 3) PLAN ------------------------------
 1. Keep a vector "shelf". Index 0 is the front.
 2. Read a command word, then handle each command:
      ADD    -> push_back
      DROP   -> erase the first item (only if not empty)
      AFTER  -> loop to find Y; insert X at (index of Y) + 1
      DELETE -> loop to find X; erase it
 3. Print the shelf, or "Empty".
#####################################################################
*/
void problem1() {

    int q;                       // how many commands there are
    cin >> q;                    // read it

    // The shelf. shelf[0] is the FRONT book. The last item is the END.
    // "long long" is a big number box (IDs go up to 1,000,000,000).
    vector<long long> shelf;

    // Repeat once for each command.
    for (int c = 0; c < q; c++) {

        string cmd;              // a box for the command word
        cin >> cmd;              // read the first word of the line

        if (cmd == "ADD") {
            long long x;         // the book to add
            cin >> x;
            shelf.push_back(x);  // push_back adds at the END of the list

        } else if (cmd == "DROP") {
            // Only remove if there is something to remove. Erasing from
            // an empty list would crash the program.
            if (!shelf.empty()) {              // "!" means NOT
                // shelf.begin() points at the FIRST item. erase removes
                // it, and everything else slides one place forward.
                shelf.erase(shelf.begin());
            }

        } else if (cmd == "AFTER") {
            long long y, x;      // y = the book to look for, x = the new book
            cin >> y >> x;       // ALWAYS read both, even if y is not found

            // Search from the front for book y.
            for (int j = 0; j < (int)shelf.size(); j++) {
                if (shelf[j] == y) {
                    // "shelf.begin() + j + 1" means "the spot right
                    // AFTER index j". insert puts x there, and the
                    // books after it slide back one place.
                    shelf.insert(shelf.begin() + j + 1, x);
                    break;       // stop: we only use the FIRST match
                }
            }
            // If the loop ends without finding y, nothing happens.

        } else {
            // The only command left is DELETE.
            long long x;
            cin >> x;

            // Search from the front for the first book x.
            for (int j = 0; j < (int)shelf.size(); j++) {
                if (shelf[j] == x) {
                    shelf.erase(shelf.begin() + j);   // remove it
                    break;       // stop: we only remove ONE book
                }
            }
        }
    }

    // Print the result.
    if (shelf.empty()) {
        cout << "Empty" << endl;
    } else {
        for (int j = 0; j < (int)shelf.size(); j++) {
            if (j > 0) {
                cout << ' ';     // a space BETWEEN books only (none at the end)
            }
            cout << shelf[j];
        }
        cout << '\n';
    }
}


/*
#####################################################################
PROBLEM 2: "Scholarship Selection"                     (difficulty: easy)
#####################################################################

---------------------------- 1) QUESTION ----------------------------
 N students are listed from BEST to WORST. Each has an ID and a
 Department. You want to choose up to K students, but at most C
 students from the same department.
 Go down the list once, choosing a student if his/her department has
 fewer than C chosen students. Stop as soon as K students are chosen.
 Print the IDs of the chosen students, one per line, in list order.
 If nobody is chosen, print: None

 Input : N K C (N <= 100,000), then N lines: ID Dept (each up to 1e9).
 Output: the chosen IDs.

 SAMPLE INPUT          SAMPLE OUTPUT
 7 4 2                 10
 10 5                  11
 11 5                  13
 12 5                  15
 13 8
 14 5
 15 8
 16 9

 Trace (K = 4, C = 2):
   10 (dept 5, 0 chosen so far) -> choose
   11 (dept 5, 1 chosen)        -> choose
   12 (dept 5, 2 chosen)        -> skip (limit C = 2 reached)
   13 (dept 8, 0 chosen)        -> choose
   14 (dept 5, 2 chosen)        -> skip
   15 (dept 8, 1 chosen)        -> choose   -> 4 chosen, STOP choosing
   16                           -> ignored

------------------------ 2) SIMILAR / DIFFERENT ---------------------
 SIMILAR TO: "The Galactic Fleet Selection" (mock exam B).
   - Same story: a ranked list, a limit of C per group, choose K.
   - Same tool: map<int,int> to count how many chosen per department.
     (Department IDs go up to 1e9, so a plain array is impossible.)
 DIFFERENT:
   - Fleet Selection had a SECOND PASS that lifted the rule when fewer
     than K ships were chosen. Here there is only ONE pass, so we may
     end with fewer than K chosen, or nobody (then print None).
   - We output in list order automatically, because we choose from the
     top and never go back. No "chosen[]" flag array is needed.
   - We must keep READING lines even after K are chosen (we just stop
     choosing), or it is simpler to read everything in the same loop.

------------------------------ 3) PLAN ------------------------------
 1. Keep a map: department -> how many chosen from it.
 2. Keep a vector of chosen IDs.
 3. For each student: if we still need students AND the department
    count is below C, choose the student.
 4. Print the chosen IDs, or "None".
#####################################################################
*/
void problem2() {

    // Magic speed-up lines (N can be 100,000). Treat them as "make
    // reading and printing fast".
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, c;                 // n = students, k = how many to choose,
    cin >> n >> k >> c;          // c = limit per department

    // countInDept[d] = how many CHOSEN students are from department d.
    // A map gives 0 for a department it has not seen yet (when we use
    // the [ ] brackets), so no setup is needed.
    map<int, int> countInDept;

    vector<int> chosenIds;       // the IDs we chose, in list order

    // Go through the students from best to worst.
    for (int i = 0; i < n; i++) {

        int id, dept;
        cin >> id >> dept;       // read this student

        // "&&" means AND: both parts must be true.
        //   - we still need more students (fewer than k chosen)
        //   - this department has fewer than c chosen students
        if ((int)chosenIds.size() < k && countInDept[dept] < c) {
            countInDept[dept]++;         // one more chosen from this dept
            chosenIds.push_back(id);     // remember this student
        }
        // Otherwise the student is skipped (we still read the line).
    }

    if (chosenIds.empty()) {
        cout << "None" << '\n';
    } else {
        for (int i = 0; i < (int)chosenIds.size(); i++) {
            cout << chosenIds[i] << '\n';   // '\n' is faster than endl
        }
    }
}


/*
#####################################################################
PROBLEM 3: "Warehouse Robot"                          (difficulty: medium)
#####################################################################

---------------------------- 1) QUESTION ----------------------------
 A warehouse is a grid with R rows and C columns (R, C <= 1000).
 Each cell is one of:
   .  free floor          #  wall (cannot enter)
   S  the robot's start   E  the exit
 The robot moves up, down, left or right into a free cell (S and E
 count as free). Each move costs 1.
 Print the FEWEST moves from S to E, or -1 if E cannot be reached.

 Input : R C, then R lines each with C characters (no spaces).
 Output: one integer.

 SAMPLE INPUT 1        SAMPLE OUTPUT 1
 3 4                   5
 S.#.
 .#..
 ...E

 SAMPLE INPUT 2        SAMPLE OUTPUT 2
 2 3                   -1
 S#E
 .#.

 Trace of sample 1 (row, column, starting at 0):
   S(0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2) -> E(2,3) = 5 moves.
   The wall at (1,1) stops a shorter path.
 Sample 2: the column of walls (#) splits the grid, so E is unreachable.

------------------------ 2) SIMILAR / DIFFERENT ---------------------
 SIMILAR TO: "The Crumbling Temple" (mock exam C), and also "Bicycle"
             and "Sea travel" (BFS for the fewest steps).
   - Same tool: BFS (Breadth-First Search) with a distance table,
     where -1 means "not reached yet", and dr/dc arrays for the four
     directions.
 DIFFERENT:
   - The grid is RECTANGULAR (R x C), not square N x N.
   - The grid comes as TEXT lines. The start is not always (1,1): we
     must FIND 'S' and 'E' by scanning the grid.
   - Rows and columns start at 0 here (strings are 0-indexed), not 1.
   - Walls are the character '#' in the grid itself. There is no list
     of holes to read.
   - Only ONE target, so we print dist[E] directly.

------------------------------ 3) PLAN ------------------------------
 1. Read the grid, find S and E.
 2. BFS from S: explore in layers (1 move away, 2 moves away, ...).
    The first time we reach a cell is its shortest distance.
 3. Never step outside the grid, onto '#', or onto a visited cell.
 4. Print dist at E (it stays -1 if E was never reached).
#####################################################################
*/
void problem3() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int r, c;                    // r = number of rows, c = number of columns
    cin >> r >> c;

    // grid[i] is row i, written as a string. grid[i][j] is the
    // character at row i, column j.
    vector<string> grid(r);
    for (int i = 0; i < r; i++) {
        cin >> grid[i];          // a row has no spaces, so cin >> works
    }

    // Find where S and E are by checking every cell.
    int startR = 0, startC = 0, endR = 0, endC = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'S') { startR = i; startC = j; }
            if (grid[i][j] == 'E') { endR = i; endC = j; }
        }
    }

    // dist[i][j] = fewest moves from S to cell (i, j).
    // -1 means "not reached yet".
    vector< vector<int> > dist(r, vector<int>(c, -1));

    // The BFS waiting line. Each item is a cell (row, column).
    queue< pair<int, int> > line;

    dist[startR][startC] = 0;                 // S is 0 moves from itself
    line.push(make_pair(startR, startC));     // start exploring from S

    // The four directions: up, down, left, right.
    // For direction k, the row changes by dr[k] and the column by dc[k].
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    // Keep going while there are cells waiting to be explored.
    while (!line.empty()) {

        pair<int, int> cur = line.front();    // take the cell at the front
        line.pop();                           // remove it from the line

        // Try to step in each of the four directions.
        for (int k = 0; k < 4; k++) {

            int nr = cur.first + dr[k];       // the neighbor's row
            int nc = cur.second + dc[k];      // the neighbor's column

            // Skip neighbors that are outside the grid.
            if (nr < 0 || nr >= r || nc < 0 || nc >= c) continue;
            // Skip walls.
            if (grid[nr][nc] == '#') continue;
            // Skip cells we have already reached (we found a shorter or
            // equal way before).
            if (dist[nr][nc] != -1) continue;

            // One more move than the current cell.
            dist[nr][nc] = dist[cur.first][cur.second] + 1;
            line.push(make_pair(nr, nc));     // explore from it later
        }
    }

    // If E was never reached, dist is still -1, which is exactly what
    // the question wants us to print.
    cout << dist[endR][endC] << endl;
}


/*
#####################################################################
PROBLEM 4: "Popular Words"                             (difficulty: easy)
#####################################################################

---------------------------- 1) QUESTION ----------------------------
 You are given N words (N <= 100,000, each up to 20 lowercase letters).
 Print each DIFFERENT word once with how many times it appeared,
 sorted by:
   1) count: bigger first
   2) if counts are equal: alphabetical order
 Output format per line:  word count

 SAMPLE INPUT          SAMPLE OUTPUT
 7                     apple 3
 apple                 pear 2
 pear                  banana 1
 apple                 fig 1
 fig
 pear
 apple
 banana

 Trace: apple appears 3 times, pear 2 times, fig 1 time, banana 1 time.
        fig and banana tie at 1, so alphabetical: banana before fig.

------------------------ 2) SIMILAR / DIFFERENT ---------------------
 SIMILAR TO: "Sorting by frequency".
   - Same two steps: (1) count how many times each item appears,
     (2) sort by count (bigger first), and break ties with a rule.
   - Same tool: copy the counts into a vector of pairs and call sort
     with your own comparison rule.
 DIFFERENT:
   - The items are STRINGS, not numbers, so a plain count[] array
     (with one spot per number) does not work. We use map<string,int>.
   - The tie rule is ALPHABETICAL (comparing strings with <), not
     "smaller number first".
   - We print BOTH the word and its count on each line.

------------------------------ 3) PLAN ------------------------------
 1. map<string,int> countOf: countOf[word]++ for every word.
 2. Copy the map into a vector of (count, word) pairs.
 3. Sort: bigger count first; if equal, smaller word first.
 4. Print "word count" for each pair.
#####################################################################
*/
void problem4() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;                       // how many words
    cin >> n;

    // countOf[w] = how many times the word w appeared.
    // A map starts every new word at 0, so countOf[w]++ just works.
    map<string, int> countOf;
    for (int i = 0; i < n; i++) {
        string w;
        cin >> w;
        countOf[w]++;            // one more appearance of w
    }

    // Copy into a vector of pairs: first = count, second = word.
    // We need a vector because a map cannot be sorted by count.
    vector< pair<int, string> > items;
    for (map<string, int>::iterator it = countOf.begin(); it != countOf.end(); ++it) {
        // it->first is the word, it->second is its count.
        items.push_back(make_pair(it->second, it->first));
    }

    // Sort with our own rule (the small function inside the [ ]).
    // The rule answers: "should x come BEFORE y?"
    sort(items.begin(), items.end(),
         [](const pair<int, string>& x, const pair<int, string>& y) {
             if (x.first != y.first) {
                 return x.first > y.first;    // different counts: bigger first
             }
             return x.second < y.second;      // same count: alphabetical
         });

    // Print each word followed by its count.
    for (int i = 0; i < (int)items.size(); i++) {
        cout << items[i].second << " " << items[i].first << '\n';
    }
}


/*
#####################################################################
PROBLEM 5: "Matching Brackets"                         (difficulty: easy)
#####################################################################

---------------------------- 1) QUESTION ----------------------------
 A string is made only of the characters ( ) [ ] { }.
 It is BALANCED if every opening bracket is closed by the SAME kind of
 bracket, in the correct order (like nested boxes).
   ()[]{}  balanced        ([]){}  balanced
   ([)]    NOT balanced    ((      NOT balanced     )(   NOT balanced
 Input : T (number of strings, T <= 100), then T strings
         (each up to 100,000 characters, no spaces).
 Output: for each string, "Yes" if balanced, otherwise "No".

 SAMPLE INPUT          SAMPLE OUTPUT
 4                     Yes
 ([]){}                No
 ([)]                  No
 ((                    No
 )(

 Trace of ([)]: '(' push, '[' push, then ')' arrives but the top is
 '[' (not '(') -> No.
 Trace of )(  : ')' arrives but the stack is EMPTY -> No.
 Trace of ((  : both pushed, nothing closes them, the stack is not
 empty at the end -> No.

------------------------ 2) SIMILAR / DIFFERENT ---------------------
 SIMILAR TO: "Dream within a Dream", "Color rocks",
             "Postfix Evaluation", "Rails".
   - All of them use a STACK: the most recent thing is the first one
     we deal with (last in, first out).
 DIFFERENT:
   - We push only OPENING brackets. A CLOSING bracket must match the
     TOP of the stack, and then we pop it.
   - There are THREE ways to answer No:
       (a) a closing bracket of the wrong kind (a mismatch),
       (b) a closing bracket when the stack is EMPTY,
       (c) opening brackets still left on the stack at the end.
   - Postfix and Rails read numbers. Here we read a whole STRING and
     look at it one character at a time.

------------------------------ 3) PLAN ------------------------------
 1. For each string, make an empty stack<char> and a flag "ok = true".
 2. For each character:
      opening  -> push it
      closing  -> if the stack is empty, ok = false
                  else pop the top and check that it is the matching
                  opening bracket. If not, ok = false.
 3. At the end, if the stack is not empty, ok = false.
 4. Print Yes or No.
#####################################################################
*/
void problem5() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;                       // how many strings to check
    cin >> t;

    // Repeat once for each string.
    for (int tc = 0; tc < t; tc++) {

        string s;                // the bracket string
        cin >> s;

        stack<char> pile;        // remembers the opening brackets not yet closed
        bool ok = true;          // stays true unless we find a problem

        // Look at each character. "&& ok" stops the loop early as soon
        // as we already know the answer is No.
        for (int i = 0; i < (int)s.size() && ok; i++) {

            char ch = s[i];      // the current character

            if (ch == '(' || ch == '[' || ch == '{') {
                // "||" means OR. An opening bracket: remember it.
                pile.push(ch);

            } else {
                // A closing bracket: it needs an opening one to match.
                if (pile.empty()) {
                    ok = false;              // nothing to match (like  )( )
                } else {
                    char top = pile.top();   // the most recent opening bracket
                    pile.pop();              // it is now matched, so remove it

                    // Is the pair the same kind? If not, it is a mismatch.
                    if ((ch == ')' && top != '(') ||
                        (ch == ']' && top != '[') ||
                        (ch == '}' && top != '{')) {
                        ok = false;
                    }
                }
            }
        }

        // Opening brackets left over were never closed (like  (( ).
        if (!pile.empty()) {
            ok = false;
        }

        // "? :" is a short if/else: if ok is true print Yes, else No.
        cout << (ok ? "Yes" : "No") << '\n';
    }
}


/*
#####################################################################
PROBLEM 6: "Digit Sum (recursion)"                     (difficulty: easy)
#####################################################################

---------------------------- 1) QUESTION ----------------------------
 Given a non-negative integer N (0 <= N <= 1,000,000,000), print the
 sum of its digits.
 RULES: you may NOT use any loop (for, while) in the function that
 computes the sum. You MUST use recursion.

 SAMPLE INPUT 1        SAMPLE OUTPUT 1
 4096                  19      (4 + 0 + 9 + 6)

 SAMPLE INPUT 2        SAMPLE OUTPUT 2
 0                     0

 Trace of 4096:
   digitSum(4096) = 6 + digitSum(409)
   digitSum(409)  = 9 + digitSum(40)
   digitSum(40)   = 0 + digitSum(4)
   digitSum(4)    = 4 + digitSum(0)
   digitSum(0)    = 0                (base case)
   So the total is 6 + 9 + 0 + 4 + 0 = 19.

------------------------ 2) SIMILAR / DIFFERENT ---------------------
 SIMILAR TO: "Multiplication (recursion practice 1)", "List sum
             (practice 3)", "List max (practice 4)".
   - Same structure:  answer = (a small piece) + (answer for the REST).
   - Same must-haves: a BASE CASE that stops the calls, and a call on
     a SMALLER problem.
 DIFFERENT:
   - Those made the problem smaller by moving one position along a
     LIST (index + 1) or by lowering B by 1.
   - Here the problem gets smaller by CUTTING OFF THE LAST DIGIT:
         n % 10  = the last digit        (4096 % 10 = 6)
         n / 10  = the number without it (4096 / 10 = 409)
   - The base case is "n == 0" (no digits left), and there is no list.

------------------------------ 3) PLAN ------------------------------
 1. Base case: if n == 0, the sum is 0. Return it.
 2. Otherwise: return (last digit) + digitSum(n without its last digit).
#####################################################################
*/

// Returns the sum of the digits of n, using recursion (no loops).
int digitSum(int n) {

    // BASE CASE (the stop rule): no digits left, so the sum is 0.
    // Without this, the function would call itself forever.
    if (n == 0) {
        return 0;
    }

    // RECURSIVE CASE:
    //   n % 10 is the last digit.
    //   n / 10 is the number with the last digit removed (whole-number
    //   division drops the leftover part). It is SMALLER than n, so we
    //   get closer to the base case each time.
    return (n % 10) + digitSum(n / 10);
}

void problem6() {
    int n;
    cin >> n;                       // read the number
    cout << digitSum(n) << endl;    // compute and print its digit sum
}


// ---------------------------------------------------------------
// Change which function is called to run a different problem.
// Only ONE should be active (not starting with //).
// ---------------------------------------------------------------
int main() {
    problem1();
    // problem2();
    // problem3();
    // problem4();
    // problem5();
    // problem6();
    return 0;
}