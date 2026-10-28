#include <iostream>   
#include <vector>     
using namespace std;  

vector<long long> value;      
vector<int> nextNode;
vector<int> prevNode;
vector<int> freeIds;

const int START = 0;          
const int END = 1;            

int makeNode(long long v) {
    int id;
    if (!freeIds.empty()) {
        id = freeIds.back();          
        freeIds.pop_back();
        value[id] = v;
    } else {
        id = (int)value.size();       
        value.push_back(v);
        nextNode.push_back(0);
        prevNode.push_back(0);
    }
    return id;
}

int insertAfter(int cur, long long v) {
    int id = makeNode(v);
    int after = nextNode[cur];        

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

            int first = nextNode[cur];   
            long long sum = 0;
            int node = first;

            for (int j = 0; j < k; j++) {
                sum = sum + value[node];          
                int following = nextNode[node];   
                if (node != first) {
                    freeIds.push_back(node);      
                }
                node = following;                 
            }
            
            value[first] = sum;           
            nextNode[first] = node;       
            prevNode[node] = first;
        }
    }

    bool firstPrinted = true;             
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

    return 0;         