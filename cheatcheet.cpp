/*
=====================================================================
C++ MIDTERM CHEAT SHEET  ("when I see THIS -> use THAT")
=====================================================================
Every example is a small function so the whole file compiles.
Copy the part you need into your own main().

QUICK DECISION TABLE
 - "N up to 100,000 / 200,000"     -> NO double loop over all pairs.
                                      Use sort / binary search / map /
                                      counting / BFS. Add fast I/O.
 - "N up to 1,000"                 -> a double loop is OK (1 million).
 - "answer can be big"             -> long long.
 - "input ends with 0"             -> while (cin >> n && n != 0)
 - "input ends at EOF"             -> while (cin >> x)
 - "undo / most recent / nested"   -> STACK
 - "first come first served"       -> QUEUE
 - "add/remove at BOTH ends"       -> DEQUE
 - "insert/remove in the middle"   -> small N: vector insert/erase
                                      big N:   linked list (next array)
 - "closest value / is it there?"  -> set + lower_bound
 - "count how many of each"        -> array count[] or map
 - "sort by rule / ties"           -> sort with a comparator,
                                      stable_sort for "keep input order"
 - "fewest steps / fewest tickets" -> BFS
 - "do the same thing smaller"     -> recursion (needs a BASE CASE)
 - "ages 1..99 / small range"      -> counting sort
=====================================================================
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
using namespace std;

// ---------------------------------------------------------------
// 1. FAST INPUT/OUTPUT  (use when there are 100,000+ numbers)
// ---------------------------------------------------------------
// Put these 2 lines at the START of main. Then print with '\n',
// NOT endl (endl is slow).
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

// ---------------------------------------------------------------
// 2. READING PATTERNS
// ---------------------------------------------------------------
void readingPatterns() {
    int n;

    // (a) Known count: first number says how many follow.
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // (b) Read until END OF FILE (no count given).
    int x;
    while (cin >> x) {
        // use x
    }

    // (c) Many test cases, a line with 0 ends everything.
    while (cin >> n && n != 0) {
        // handle one test case
    }

    // (d) Read a whole line (with spaces).
    string line;
    getline(cin, line);   // if you used cin >> before, call cin.ignore() first

    // (e) Read a word then maybe a number (commands like PUSH 5).
    string cmd;
    cin >> cmd;
    if (cmd == "PUSH") { long long v; cin >> v; }
}

// ---------------------------------------------------------------
// 3. OUTPUT PATTERNS
// ---------------------------------------------------------------
void outputPatterns() {
    vector<int> v = {1, 2, 3};

    // Numbers separated by spaces, NO trailing space:
    for (int i = 0; i < (int)v.size(); i++) {
        if (i > 0) cout << ' ';
        cout << v[i];
    }
    cout << '\n';

    // Exactly 4 decimals (e.g. 2.6667):
    double d = 8.0 / 3.0;
    cout << fixed << setprecision(4) << d << '\n';

    // Blank line BETWEEN test cases only: print '\n' before every
    // test case except the first.
}

// ---------------------------------------------------------------
// 4. SIMPLE SIMULATION (Ant Eaters, Climb, Stock Bot, Buckets...)
// ---------------------------------------------------------------
// Keep a few "state" variables OUTSIDE the loop, update them each step.
// Read the question's boundaries carefully: < vs <=, "at least" is >=,
// "more than" is >, "inclusive" means include both ends.
long long simulationExample(const vector<int>& ants) {
    long long total = 0;
    bool resting = false;                 // state that survives across days
    for (int i = 0; i < (int)ants.size(); i++) {
        if (resting) { resting = false; continue; }
        int eaten = min(ants[i], 1000);
        total += eaten;
        if (eaten == 1000) resting = true;
    }
    return total;
}

// "Every 4th day": use the remainder operator
//   if (day % 4 == 0) ...
// Wrap around a circle:  (pos + k) % size

// ---------------------------------------------------------------
// 5. STACK  (last in, first out)
//    Rails, Dream in a Dream, Postfix, Color rocks, Chemistry
// ---------------------------------------------------------------
void stackExample() {
    stack<int> s;
    s.push(5);                  // add on top
    if (!s.empty()) {           // ALWAYS check empty before top/pop
        int t = s.top();        // look at top
        s.pop();                // remove top (returns nothing)
        (void)t;
    }
}
// Postfix evaluation: number -> push; operator -> pop right, pop left,
//   push (left OP right). Use double for division.
// Color rocks: keep a "run length" next to each stack item.
// Valid-order checks (Rails): push 1,2,3.. until top == wanted, then pop.

// ---------------------------------------------------------------
// 6. QUEUE (first in, first out)   Throwing cards away
// ---------------------------------------------------------------
void queueExample() {
    queue<int> q;
    q.push(1);                  // add at back
    int f = q.front();          // look at front
    q.pop();                    // remove front
    (void)f;
    // q.size(), q.empty()
}

// ---------------------------------------------------------------
// 7. DEQUE (add/remove at both ends)   ZamooZooma
// ---------------------------------------------------------------
void dequeExample() {
    deque<int> d;
    d.push_front(1); d.push_back(2);
    d.pop_front();   d.pop_back();
    // d.front(), d.back(), d.size(), d.empty()
}

// ---------------------------------------------------------------
// 8. VECTOR (list that grows). Insert/erase in the middle shifts
//    everything: fine for N <= ~5000, too slow for 100,000.
//    The Conductor's Magical Train
// ---------------------------------------------------------------
void vectorExample() {
    vector<int> v;
    v.push_back(10);                   // add at back
    v.pop_back();                      // remove from back (check !empty())
    v.push_back(1); v.push_back(2);
    v.insert(v.begin() + 1, 99);       // insert 99 at index 1
    v.erase(v.begin() + 0);            // erase the item at index 0
    // find a value and erase the first match:
    for (int j = 0; j < (int)v.size(); j++)
        if (v[j] == 99) { v.erase(v.begin() + j); break; }
}

// ---------------------------------------------------------------
// 9. LINKED LIST with a "next" array (fast insert/delete anywhere)
//    Zooma 1, Bonus points, A row of cookies, Tiniest machines,
//    Card game
// ---------------------------------------------------------------
// nextNode[x] = which item comes right AFTER x. 0 = nobody (end).
// Use spot 0 as a fake "front" item so inserting at the front works.
void linkedListExample() {
    int n = 5;
    vector<int> nextNode(n + 100, 0);
    for (int i = 1; i < n; i++) nextNode[i] = i + 1;   // 1->2->3->4->5
    nextNode[n] = 0;

    // INSERT newNode right after p (2 steps):
    int p = 3, newNode = 6;
    nextNode[newNode] = nextNode[p];
    nextNode[p] = newNode;

    // DELETE the item after p (skip over it):
    nextNode[p] = nextNode[nextNode[p]];

    // PRINT: start at the first item and follow the notes.
    int cur = 1;
    while (cur != 0) {
        cout << cur << '\n';
        cur = nextNode[cur];
    }
}
// Circular list (Card game): nextNode[last] = first.
// Deleting the CURRENT item needs the item BEFORE it ("before").
// Or use lazy deletion: just mark removed[i] = true and skip it.

// ---------------------------------------------------------------
// 10. MAP and SET
//     map: lookup table (key -> value), keys can be huge (1e9).
//     set: sorted collection, no duplicates.
//     Fleet Selection, Practice: set
// ---------------------------------------------------------------
void mapSetExample() {
    map<int, int> cnt;
    cnt[1000000000]++;                 // count how many of each key
    // iterate in sorted key order:
    for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        int key = it->first, value = it->second;
        (void)key; (void)value;
    }

    set<long long> s;
    s.insert(10); s.insert(20); s.insert(35);
    // CLOSEST value to y (smaller one on a tie):
    long long y = 17;
    set<long long>::iterator right = s.lower_bound(y);   // first >= y
    long long ans;
    if (right == s.end()) ans = *s.rbegin();             // all smaller
    else if (right == s.begin()) ans = *right;           // none before
    else {
        set<long long>::iterator left = right; --left;
        ans = (y - *left <= *right - y) ? *left : *right;
    }
    (void)ans;
    // s.count(x) -> 1 if x is in the set, else 0
}

// ---------------------------------------------------------------
// 11. SORTING
// ---------------------------------------------------------------
void sortingExample() {
    vector<int> v = {5, 2, 9, 1};
    sort(v.begin(), v.end());                          // ascending
    sort(v.begin(), v.end(), greater<int>());          // descending

    // Sort pairs by a custom rule (Sorting by frequency):
    // bigger frequency first, tie -> smaller value first.
    vector< pair<int, int> > items;                    // (frequency, value)
    sort(items.begin(), items.end(),
         [](const pair<int,int>& x, const pair<int,int>& y) {
             if (x.first != y.first) return x.first > y.first;
             return x.second < y.second;
         });

    // KEEP INPUT ORDER among ties (DNA Sorting): stable_sort
    stable_sort(items.begin(), items.end(),
         [](const pair<int,int>& x, const pair<int,int>& y) {
             return x.first < y.first;
         });
}
// Write your OWN quick sort (Practice: Sorting): pick a random pivot,
// split into  < pivot | == pivot | > pivot, recurse on the two outer
// parts. (3-way split keeps it fast with many equal numbers.)

// ---------------------------------------------------------------
// 12. BINARY SEARCH on a SORTED list
//     Sport Tournament, Good pairs
// ---------------------------------------------------------------
void binarySearchExample() {
    vector<int> s = {1, 3, 3, 5, 8};                   // must be sorted
    int p = 3;
    int less  = lower_bound(s.begin(), s.end(), p) - s.begin(); // how many < p
    int upTo  = upper_bound(s.begin(), s.end(), p) - s.begin(); // how many <= p
    int equal = upTo - less;                                    // how many == p
    (void)equal;
}
// lower_bound = first spot with value >= p
// upper_bound = first spot with value >  p

// ---------------------------------------------------------------
// 13. COUNTING with an array (small value range)
//     Age sort (counting sort), Planting trees, Shadow, Accelerator
// ---------------------------------------------------------------
void countingExample() {
    int count[100] = {0};              // values 0..99
    count[42]++;
    // print sorted: for each value, print it count[value] times
    for (int v = 1; v < 100; v++)
        for (int k = 0; k < count[v]; k++) cout << v << ' ';
}
// Planting trees:  answer for a tree = rowCount[r] + colCount[c] - 1

// ---------------------------------------------------------------
// 14. PREFIX SUM  (sum of the first k items in O(1))   Big Bags
// ---------------------------------------------------------------
void prefixSumExample() {
    vector<long long> a = {0, 4, 2, 7};     // a[1..3]
    vector<long long> prefix(a.size(), 0);
    for (int i = 1; i < (int)a.size(); i++) prefix[i] = prefix[i - 1] + a[i];
    // sum of a[l..r] = prefix[r] - prefix[l-1]
}

// ---------------------------------------------------------------
// 15. GREEDY with a stack   (Smallest Number after removing k digits)
// ---------------------------------------------------------------
string removeKDigits(const string& digits, int k) {
    string result = "";
    int removed = 0;
    for (int i = 0; i < (int)digits.size(); i++) {
        char c = digits[i];
        while (removed < k && !result.empty() && result.back() > c) {
            result.pop_back(); removed++;
        }
        result.push_back(c);
    }
    while (removed < k) { result.pop_back(); removed++; }
    return result;
}

// ---------------------------------------------------------------
// 16. RECURSION  (multiplication, list sum, list max)
// ---------------------------------------------------------------
// Every recursive function needs:
//   1) a BASE CASE (stops the calls)
//   2) a call on a SMALLER problem
int multiply(int a, int b) {
    if (b == 0) return 0;                  // base case
    return a + multiply(a, b - 1);         // smaller problem
}
int listSum(const vector<int>& a, int index) {
    if (index >= (int)a.size()) return 0;  // base case
    return a[index] + listSum(a, index + 1);
}
int listMax(const vector<int>& a, int index) {
    if (index == (int)a.size() - 1) return a[index];   // base case
    int rest = listMax(a, index + 1);
    return a[index] > rest ? a[index] : rest;
}

// ---------------------------------------------------------------
// 17. BFS on a GRAPH (shortest number of edges)
//     Bicycle, Sea travel, Bus Routes, Failed update, Valid BFS?
// ---------------------------------------------------------------
// graph[u] = list of neighbors of u. dist = -1 means "not reached".
vector<int> bfsGraph(const vector< vector<int> >& graph, int source, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> line;
    dist[source] = 0;
    line.push(source);
    while (!line.empty()) {
        int u = line.front(); line.pop();
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                line.push(v);
            }
        }
    }
    return dist;
}
// Build the graph:  graph[a].push_back(b); graph[b].push_back(a);
// Ignore some edges (e.g. difficulty > B): "continue" inside the loop.
// Blocked node: skip it when exploring (Failed update: try each node).
// Groups like bus routes: make each route link all its stops, or mark
//   a route as used the first time you ride it.
// Valid BFS order of a TREE: parent[] from BFS, then for each v in the
//   sequence its children must be the next (children count) entries.

// ---------------------------------------------------------------
// 18. BFS on a GRID  (Crumbling Temple)
// ---------------------------------------------------------------
vector< vector<int> > bfsGrid(int n, const vector< vector<bool> >& hole) {
    vector< vector<int> > dist(n + 1, vector<int>(n + 1, -1));
    queue< pair<int,int> > line;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};            // up, down, left, right
    dist[1][1] = 0;
    line.push(make_pair(1, 1));
    while (!line.empty()) {
        pair<int,int> cur = line.front(); line.pop();
        for (int k = 0; k < 4; k++) {
            int nr = cur.first + dr[k], nc = cur.second + dc[k];
            if (nr < 1 || nr > n || nc < 1 || nc > n) continue;   // outside
            if (hole[nr][nc] || dist[nr][nc] != -1) continue;     // blocked/seen
            dist[nr][nc] = dist[cur.first][cur.second] + 1;
            line.push(make_pair(nr, nc));
        }
    }
    return dist;      // dist == -1 -> "Impossible"
}
// Run BFS ONCE, then answer every query by table lookup.

// ---------------------------------------------------------------
// 19. BRUTE FORCE over all choices (when the count is small)
//     Rotating slot machine: 4 columns x 4 rotations = 256 combos.
// ---------------------------------------------------------------
// Nested loops try every combination; keep the best result.
// Rotating a column by s steps: grid[(r + s) % 4][c]

// ---------------------------------------------------------------
// 20. MATH TRICKS
// ---------------------------------------------------------------
// Distinct prime factors (Prime Factors):
int distinctPrimeFactors(int n) {
    int count = 0;
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            count++;
            while (n % d == 0) n /= d;     // remove ALL copies
        }
    }
    if (n > 1) count++;                    // one big prime left over
    return count;
}
// Tens digit of x:  (x / 10) % 10   (use abs value if x can be negative)
// Sum 1..n = n * (n + 1) / 2
// Inversions (pairs i<j with a[i] > a[j]) = minimum adjacent swaps:
long long inversions(const vector<int>& a) {
    long long cnt = 0;
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = i + 1; j < (int)a.size(); j++)
            if (a[i] > a[j]) cnt++;
    return cnt;
}
// Median keeping a sorted vector: lower_bound to find spot, v.insert(spot, x).
//   odd size -> v[size/2];  even -> (v[size/2 - 1] + v[size/2]) / 2

// ---------------------------------------------------------------
// 21. "PICK THE BEST, ASK IF TIED" patterns
// ---------------------------------------------------------------
// Find the smallest index among ties: loop from the front and update
//   only when strictly better:   if (value > best) { best = value; ... }
// Find the smallest-numbered bucket among equal minimums:
//   if (bucket[j] < bucket[smallest]) smallest = j;   (strict <)

// ---------------------------------------------------------------
// 22. COMMON MISTAKES CHECKLIST
// ---------------------------------------------------------------
//  [ ] int overflow? Sums/products over ~2 billion need long long.
//  [ ] top()/pop()/front() on an EMPTY container crashes the program.
//  [ ] Off by one: C++ lists start at 0, the question often starts at 1.
//  [ ] < vs <= ; "at least" = >= ; "more than" = >.
//  [ ] Integer division drops decimals; use double when needed.
//  [ ] Declare state variables OUTSIDE loops if they must survive.
//  [ ] Read ALL input even for skipped cases (keeps input in sync).
//  [ ] Output format: spaces, blank lines, "Yes"/"No", exact words.
//  [ ] Use '\n' not endl for big output.
//  [ ] Check the sample by hand before submitting.
//  [ ] Time check: N=100,000 and a double loop = too slow.

// ---------------------------------------------------------------
// EMPTY main so this file compiles. Delete it and write your own.
// ---------------------------------------------------------------
int main() {
    return 0;
}
