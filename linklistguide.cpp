/*
=====================================================================
LINKED LIST STUDY GUIDE
=====================================================================
WHAT IS A LINKED LIST?
 A normal list (vector) keeps items side by side. Inserting or deleting
 in the MIDDLE makes everything after it shift over: slow when there
 are 100,000+ items and many operations.

 A linked list keeps, for EVERY item, one note:
        "which item comes right AFTER me?"      (next[item])
 It is like a treasure hunt: each item holds a note pointing to the
 next item. Inserting or deleting only changes 1 or 2 notes, no matter
 how long the list is. That is FAST.

WHEN TO USE IT (words in the question)
   "insert a new item AFTER item X / after the k-th item"
   "remove the item after the current one"
   "a marker (angel / machine / current card) walks along the list"
   many operations (up to 100,000+) in the middle of a long list
 Use a plain vector instead when N or Q is small (about 5000 or less,
 like the Conductor's Magical Train). It is simpler.

THE 3 INGREDIENTS
   1) value[id]    : what each item holds (a number, a bonus, a color)
   2) nextNode[id] : the id of the item after it. 0 means "nobody",
                     so it is the LAST item.
   3) a start      : where the list begins (a "head")
 TIP: Give every item an ID: 1, 2, 3, ... Items that are inserted later
 get the next free ID (n + 1, n + 2, ...). The ID never changes, even
 when the item moves in the list. Use spot 0 as a FAKE head ("front")
 so that inserting at the very front works like any other insert.

THE OPERATIONS (memorize these 3!)
   INSERT newNode right AFTER p      (2 steps, ORDER MATTERS):
        nextNode[newNode] = nextNode[p];     // 1) new points to p's old next
        nextNode[p] = newNode;               // 2) p now points to new
   DELETE the item right AFTER p     (1 step):
        nextNode[p] = nextNode[ nextNode[p] ];   // p skips over it
   WALK / PRINT:
        cur = first;  while (cur != 0) { use cur;  cur = nextNode[cur]; }

WORKED TRACE (start list 1 -> 2 -> 3, fake head 0)
   nextNode[0]=1, nextNode[1]=2, nextNode[2]=3, nextNode[3]=0
   List:  1 2 3

   Insert 4 after 1:
        nextNode[4] = nextNode[1] = 2;   nextNode[1] = 4;
        List: 1 4 2 3
   Insert 5 after 2:
        nextNode[5] = nextNode[2] = 3;   nextNode[2] = 5;
        List: 1 4 2 5 3
   Insert 6 after 4:
        nextNode[6] = nextNode[4] = 2;   nextNode[4] = 6;
        List: 1 4 6 2 5 3
   Delete the item after 4 (that is 6):
        nextNode[4] = nextNode[6] = 2;
        List: 1 4 2 5 3
   (Item 6 is still in the arrays, but nobody points to it, so it is
    never reached when we walk the list.)

WHY THE ORDER OF THE 2 INSERT STEPS MATTERS
   If you do  nextNode[p] = newNode  FIRST, you lose p's old next and
   can never find the rest of the list. Always copy p's old next into
   the new item FIRST.

COMMON MISTAKES
   [ ] Doing the two insert steps in the wrong order.
   [ ] Forgetting that the LAST item must have nextNode = 0.
   [ ] Array too small: size must be (start items + number of inserts) + 2.
   [ ] Walking past the end: always check "!= 0" before following a note.
   [ ] Forgetting to READ all the input numbers of a command even when
       the command does nothing (the input gets out of sync).
   [ ] Using the fake head 0 as if it were a real item when printing.
       (Start printing at nextNode[0].)
   [ ] Deleting the CURRENT item without knowing the item BEFORE it
       (see Template 5 and Template 7).
=====================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

// =====================================================================
// TEMPLATE 1: BUILD A LIST FROM n STARTING ITEMS, THEN PRINT IT
// Used in: Zooma 1, Bonus points, Tiniest machines
// =====================================================================
void template1(int n, int extra) {
    // extra = the most items we might insert later.
    vector<int> value(n + extra + 2, 0);
    vector<int> nextNode(n + extra + 2, 0);

    // Link 0 -> 1 -> 2 -> ... -> n -> (nobody).
    // Spot 0 is the fake head: it is not a real item.
    nextNode[0] = 1;
    for (int i = 1; i < n; i++) {
        nextNode[i] = i + 1;
    }
    nextNode[n] = 0;                  // the last item has nobody after it

    // PRINT: start at the first REAL item (the one after the fake head).
    int cur = nextNode[0];
    while (cur != 0) {                // 0 means "no more items"
        cout << value[cur] << '\n';
        cur = nextNode[cur];          // follow the note
    }
}

// =====================================================================
// TEMPLATE 2: INSERT AFTER A GIVEN ITEM p   (Zooma 1, Bonus points)
// =====================================================================
// "created" = how many items exist so far. The new item gets the next ID.
int insertAfter(vector<int>& nextNode, int p, int created) {
    int newNode = created + 1;        // the ID of the new item
    nextNode[newNode] = nextNode[p];  // 1) new points to what p pointed to
    nextNode[p] = newNode;            // 2) p now points to new
    return newNode;                   // the caller sets created = newNode
}
// Zooma 1: "shoot ball n+j right after ball p[j]"  ->  insertAfter(.., p, ..)
// Insert at the FRONT: use p = 0 (the fake head).

// =====================================================================
// TEMPLATE 3: DELETE THE ITEM AFTER p   (Tiniest machines: remove K)
// =====================================================================
// Removes up to k items right after p. Stops early if the list ends.
void deleteAfter(vector<int>& nextNode, int p, int k) {
    for (int step = 0; step < k && nextNode[p] != 0; step++) {
        int victim = nextNode[p];             // the item to remove
        nextNode[p] = nextNode[victim];       // p skips over it
    }
}
// "Remove fewer if not enough items": that is the "nextNode[p] != 0" check.

// =====================================================================
// TEMPLATE 4: WALK k STEPS FROM THE FRONT   (A row of cookies)
// =====================================================================
// Returns the item you stand on after moving k steps from the fake head.
// If the list runs out first, you stop at the LAST item
// (that means "insert at the end").
int walkFromFront(const vector<int>& nextNode, int k) {
    int current = 0;                  // start at the fake head
    for (int step = 0; step < k; step++) {
        if (nextNode[current] == 0) {
            break;                    // no more items: stop at the end
        }
        current = nextNode[current];  // move to the next item
    }
    return current;
}
// Cookies, "insert after the k-th cookie":
//     p = walkFromFront(nextNode, k);   // k = 0 gives the fake head: front
//     insertAfter(nextNode, p, created);
// Cookies, "eat the k-th cookie": we need the item BEFORE it:
//     before = walkFromFront(nextNode, k - 1);
//     target = nextNode[before];        // the k-th cookie (0 = none)
//     if (target != 0) nextNode[before] = nextNode[target];

// =====================================================================
// TEMPLATE 5: A MARKER THAT WALKS ALONG THE LIST
// Used in: Bonus points (angel), Tiniest machines (machine)
// =====================================================================
// "cur" = the item the marker stands on. Typical commands:
//     move to the NEXT item (only if there is one):
//         if (nextNode[cur] != 0) cur = nextNode[cur];
//     go back to the FIRST item:
//         cur = head;                  // head = 1, or nextNode[0]
//     do something AFTER the marker (insert / delete):
//         insertAfter(nextNode, cur, created);
//         deleteAfter(nextNode, cur, k);
//     do something TO the marker's item (add points):
//         bonus[cur] += x;
// The marker does NOT move when you insert or delete after it.
// Because everything happens AFTER the marker, you never need the item
// BEFORE it, and the first item is never removed.

// =====================================================================
// TEMPLATE 6: INSERT SEVERAL ITEMS IN A ROW   (Tiniest machines: T = 4)
// =====================================================================
// Insert the values a[0..l-1] right after p, in the same order.
void insertMany(vector<int>& nextNode, vector<int>& value, int p,
                const vector<int>& a, int& created) {
    int after = nextNode[p];          // who used to come after p
    int tail = p;                     // the item we attach the next one to

    for (int j = 0; j < (int)a.size(); j++) {
        created = created + 1;        // make a new item
        value[created] = a[j];
        nextNode[tail] = created;     // the previous item points to it
        tail = created;               // it becomes the new tail
    }
    nextNode[tail] = after;           // the last new item reconnects the rest
}

// =====================================================================
// TEMPLATE 7: CIRCULAR LIST + DELETING THE CURRENT ITEM (Card game)
// =====================================================================
// A circle: the last item points back to the first.
//     for i in 0..n-1:  nextNode[i] = (i + 1) % n;
// To delete the CURRENT item we need the item BEFORE it ("before"):
//     nextNode[before] = nextNode[current];     // skip the current item
//     current = nextNode[current];              // move on
// To move forward WITHOUT deleting:
//     before = current;  current = nextNode[current];
// Keep a flag removed[i] = true so you can print the survivors in the
// original order at the end (loop i = 0..n-1 and skip removed ones).
// The Card game rounds look like this:
void cardGameRound(vector<int>& nextNode, vector<bool>& removed,
                   const vector<int>& value, int& current, int& before, int x) {
    int total = 0;
    while (true) {
        total = total + value[current];
        if (total >= x) {
            removed[current] = true;                 // discard this card
            nextNode[before] = nextNode[current];    // the card before skips it
            current = nextNode[current];             // next round starts here
            break;                                   // "before" stays the same
        }
        before = current;                            // move on, counting
        current = nextNode[current];
    }
}

// =====================================================================
// TEMPLATE 8: LAZY DELETION  (the easy alternative)
// =====================================================================
// Instead of really removing an item, just mark it:   removed[i] = true.
// When walking or printing, skip marked items.
// It is simple and safe when you do not have too many deletions (the
// hint in the "ZamooZooma" problem says the same).

// =====================================================================
// TEMPLATE 9: DOUBLY LINKED LIST  (when you must delete a GIVEN item)
// =====================================================================
// Keep ALSO prevNode[id] = the item before it. Then you can delete any
// item x directly, without searching for the one before it.
void deleteNode(vector<int>& nextNode, vector<int>& prevNode, int x) {
    nextNode[prevNode[x]] = nextNode[x];          // the one before skips x
    if (nextNode[x] != 0) {
        prevNode[nextNode[x]] = prevNode[x];      // the one after points back
    }
}
void insertAfterDouble(vector<int>& nextNode, vector<int>& prevNode,
                       int p, int newNode) {
    nextNode[newNode] = nextNode[p];
    prevNode[newNode] = p;
    if (nextNode[p] != 0) {
        prevNode[nextNode[p]] = newNode;
    }
    nextNode[p] = newNode;
}
// You only need this when the question gives you an item and asks to
// remove THAT item (not "the item after the marker").

// =====================================================================
// QUICK GUIDE: WHICH TEMPLATE FOR WHICH QUESTION?
// =====================================================================
//  Zooma 1           -> Templates 1 + 2. Shoot ball n+j after ball p:
//                       insertAfter. Print from nextNode[0].
//  Bonus points      -> Template 5 (angel = marker). Action 0: cur = 1.
//                       Action 1: next. Action 2: insertAfter. Action 3:
//                       bonus[cur] += x. Keep a separate bonus[] list.
//  A row of cookies  -> Template 4 (walk k steps from the fake head).
//                       k <= 5, so every operation is fast.
//  Tiniest machines  -> Templates 3 + 5 + 6 (remove K after, insert L
//                       items after, marker moves only on T = 1 / 2).
//  Card game         -> Template 7 (circle + before pointer).
//  ZamooZooma        -> use a deque, or lazy deletion (Template 8).
//  Conductor's Train -> small Q, so a plain vector with insert / erase.
//
// HOW TO DECIDE: vector or linked list?
//  1. Count: how many operations, and how long can the list get?
//  2. Operations at the END only (push/pop)?        -> vector or stack.
//  3. Operations at BOTH ends only?                 -> deque.
//  4. Many inserts/deletes in the MIDDLE, 100,000+? -> linked list.
//  5. Same but only ~5000 operations?               -> vector is fine.
//
// DECIDING WHAT THE "NOTE" MEANS (the hard part!)
//  1. What is ONE item? (a ball, a player, a cookie, a card)
//  2. Give each item a permanent ID (1, 2, 3, ... in creation order).
//  3. What do I need to find fast? "The item AFTER x"   -> nextNode.
//  4. Do I ever need "the item BEFORE x"? Keep a before pointer
//     (Template 7) or a prevNode list (Template 9).
//  5. What do I print? Walk from the head and print each value.

int main() {
    return 0;     // this file is a study guide; the templates are above
}
