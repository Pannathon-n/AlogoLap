/*
F
/*
=====================================================================
QUESTION SUMMARY: "Flood zone"
=====================================================================
A city has N intersections (nodes) joined by M two-way roads (edges).
Every road takes 1 unit of time. Each road is FLOODED (F = 1) or DRY
(F = 0).

You drive from intersection S to intersection T with a car of type B:
 - Type 1 (truck)   : can use ANY road.
 - Type 2 (city car): can NOT use flooded roads at all.
 - Type 3 (SUV)     : can use flooded roads, but NEVER two flooded
                      roads in a row. After a flooded road, the next
                      road must be DRY.

TASK: Print the FEWEST roads (shortest time) from S to T for that car.
      If it is impossible, print -1.

INPUT:
 - Line 1: N M S T B   (N <= 10,000, M <= 200,000)
 - Next M lines: U V F  (a road between U and V, flooded if F = 1)

OUTPUT:
 - One integer: the shortest time, or -1.

SAMPLE INPUT 1:           SAMPLE OUTPUT 1:
7 9 1 4 1                 2
1 2 0
1 3 1
7 2 0
3 7 0
3 6 0
3 4 1
4 6 1
5 6 0
4 5 0
(The same roads with B = 2 give 6, and with B = 3 give 3.)

SAMPLE INPUT 2: the same, but road 3-6 is flooded (F = 1), B = 2
SAMPLE OUTPUT 2: -1   (with B = 3 it gives 4, with B = 1 it gives 2)

WHY? (walking through sample 1, flooded roads: 1-3, 3-4, 4-6)
 Type 1: 1 -> 3 -> 4                      = 2 roads.
 Type 2: avoid flooded roads: 1-2-7-3-6-5-4 (all dry) = 6 roads.
 Type 3: 1 -> 3 (flooded), 3 -> 6 (dry), 6 -> 4 (flooded) = 3 roads.
         Flooded, dry, flooded: never two flooded roads in a row. OK.

WHY SAMPLE 2 WITH TYPE 3 GIVES 4 (this shows why we need "states"):
 1 -> 3 (flooded), 3 -> 7 (dry), 7 -> 3 (dry), 3 -> 4 (flooded) = 4.
 We arrive at intersection 3 TWICE: the first time after a flooded
 road (we may NOT take flooded 3-4 yet), the second time after a dry
 road (now we may). The same intersection is a different situation
 depending on the LAST road. So the "place" in BFS must include that.
 (I traced all of these by hand and they match.)

=====================================================================
SIMILAR / DIFFERENT
=====================================================================
SIMILAR TO: "Bicycle" (BFS ignoring some edges), "Failed update"
            (BFS with a rule about which nodes you may enter), and
            the BFS template in your BFS guide.
   - Same tool: BFS from S, dist = fewest roads, -1 = not reached.
   - Type 1 is plain BFS. Type 2 is "Bicycle": just skip flooded
     roads with `continue`.
 DIFFERENT:
   - Type 3 depends on the PREVIOUS road, so a BFS "place" is not just
     the intersection. It is a PAIR: (intersection, was the last road
     flooded?). That doubles the places (2 states per intersection).
   - The answer is the smaller of dist at (T, last road dry) and
     dist at (T, last road flooded). Whichever state reaches T first.
   - One BFS code handles all 3 car types by changing ONE rule: "may I
     take this road?".
   - This idea ("add extra information to the place") is the key
     trick for harder BFS questions.

=====================================================================
PLAN
=====================================================================
 1. Store the roads as graph[u] = list of (neighbor v, flooded f).
 2. The BFS place is (node, flag), where flag = 1 if the last road
    was flooded. For car types 1 and 2 the flag is always 0.
    Index it as node * 2 + flag in one dist list (size 2 * (n + 1)).
 3. Start: dist[(S, 0)] = 0 (we have not used any road yet, so the
    last road is NOT flooded).
 4. From (u, flag), try every road (v, f). The road is allowed if:
        type 1: always
        type 2: f == 0
        type 3: NOT (f == 1 and flag == 1)
 5. New flag: for type 3 it is f, otherwise 0.
 6. If the new place was never reached: dist = dist + 1, push it.
 7. Answer: smaller of the reached values of (T, 0) and (T, 1);
    -1 if neither was reached.
=====================================================================
*/
/*
#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <queue>      // lets us use "queue" (a line: add at back, remove from front)
#include <utility>    // lets us use "pair" (two values stuck together)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines: there can be 200,000 roads to read.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t, b;     // n = intersections, m = roads, s = start,
                           // t = target, b = car type
    cin >> n >> m >> s >> t >> b;

    // graph[u] = list of (neighbor, flooded) for every road at u.
    // Intersections are numbered from 1, so we make n + 1 lists.
    vector< vector< pair<int, int> > > graph(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, f;
        cin >> u >> v >> f;
        // Roads are two-way, so store it for BOTH intersections.
        graph[u].push_back(make_pair(v, f));
        graph[v].push_back(make_pair(u, f));
    }

    // dist[node * 2 + flag] = fewest roads to be at "node" where flag
    // says whether the LAST road was flooded (1) or not (0).
    // -1 means "this place has not been reached yet".
    vector<int> dist(2 * (n + 1), -1);

    // The BFS waiting line. Each item is a place, stored as node * 2 + flag.
    queue<int> line;

    dist[s * 2 + 0] = 0;   // at S, no road used yet: last road not flooded
    line.push(s * 2 + 0);

    while (!line.empty()) {

        int place = line.front();    // take the place at the front
        line.pop();

        int u = place / 2;           // the intersection  (whole-number division)
        int flag = place % 2;        // 1 if the last road was flooded
                                     // ("%" is the remainder operator)

        // Try every road leaving intersection u.
        for (int i = 0; i < (int)graph[u].size(); i++) {

            int v = graph[u][i].first;       // the intersection at the other end
            int f = graph[u][i].second;      // 1 = this road is flooded

            // Decide if THIS car may use THIS road.
            bool allowed;
            if (b == 1) {
                allowed = true;                      // truck: any road
            } else if (b == 2) {
                allowed = (f == 0);                  // city car: dry roads only
            } else {
                allowed = !(f == 1 && flag == 1);    // SUV: never 2 flooded in a row
                // "!" means NOT, "&&" means AND
            }

            if (!allowed) {
                continue;                            // skip this road
            }

            // The flag of the new place. Only the SUV needs to remember
            // whether the last road was flooded. The others always use 0
            // so they do not create extra duplicate places.
            int newFlag;
            if (b == 3) {
                newFlag = f;
            } else {
                newFlag = 0;
            }

            int newPlace = v * 2 + newFlag;

            // Only visit a place we have never reached before.
            if (dist[newPlace] == -1) {
                dist[newPlace] = dist[place] + 1;    // one more road
                line.push(newPlace);                 // explore from it later
            }
        }
    }

    // The answer is the smaller of the two ways of arriving at T:
    // after a dry road (flag 0) or after a flooded road (flag 1).
    int a0 = dist[t * 2 + 0];
    int a1 = dist[t * 2 + 1];

    int answer;
    if (a0 == -1 && a1 == -1) {
        answer = -1;                 // T can never be reached
    } else if (a0 == -1) {
        answer = a1;
    } else if (a1 == -1) {
        answer = a0;
    } else {
        answer = (a0 < a1) ? a0 : a1;   // the smaller one
    }

    cout << answer << endl;

    return 0;         // tells the computer the program finished successfully
}
*/