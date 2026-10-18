/*
=====================================================================
QUESTION SUMMARY: "Practice: Sorting" (write your own quick sort)
=====================================================================
You are given N integers (N up to 100,000). Sort them from smallest
to largest. But to save space, do NOT print the whole sorted list.
Print only every K-th element of the sorted list:
the K-th, the 2K-th, the 3K-th, and so on.
That is floor(N / K) numbers in total.

You must write the sorting function YOURSELF (quick sort), not use
the built-in sort.

INPUT:
 - Line 1: N and K (1 <= N <= 100,000, 1 <= K <= N)
 - Next N lines: one integer each (0 to 1,000,000,000)

OUTPUT:
 - floor(N / K) numbers, one per line.

SAMPLE INPUT:
7 2
10
20
4
23
17
20
100

SAMPLE OUTPUT:
10
20
23

WHY? (walking through the sample)
 Sorted list: 4, 10, 17, 20, 20, 23, 100
 Position:    1   2   3   4   5   6   7
 K = 2, so we print positions 2, 4, 6 -> 10, 20, 23.
 (7 / 2 = 3 numbers, rounded down.)

HOW QUICK SORT WORKS (in plain words):
 1) Pick one number from the list. Call it the PIVOT.
 2) Move numbers so that the list looks like this:
        [ smaller than pivot | equal to pivot | bigger than pivot ]
    The "equal" part is now in its final place.
 3) Do the same trick again on the "smaller" part and on the "bigger"
    part (the function calls itself: this is called RECURSION).
 4) A part with 0 or 1 numbers is already sorted, so we stop there.

 We pick the pivot at RANDOM. This avoids the very slow worst case
 (for example when the list is already sorted).
 We split into THREE parts (smaller / equal / bigger) so that lots of
 repeated numbers do not make the program slow.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <cstdlib>    // lets us use rand (a random number)
#include <utility>    // lets us use swap (swap two values)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

// Sorts the part of list "a" from position "low" to position "high"
// (both ends included). The "&" means we work on the REAL list, not a copy.
void quickSort(vector<int>& a, int low, int high) {

    // If this part has 0 or 1 numbers, it is already sorted. Stop.
    if (low >= high) {
        return;
    }

    // Pick a random position between low and high, and use that number
    // as the pivot.
    // "%" is the remainder operator: it keeps the random number inside
    // the size of this part.
    int pivot = a[low + rand() % (high - low + 1)];

    // We use three markers to split the part into 3 zones:
    //   a[low .. lt-1]   = numbers SMALLER than pivot
    //   a[lt .. i-1]     = numbers EQUAL to pivot
    //   a[i .. gt]       = numbers we have NOT looked at yet
    //   a[gt+1 .. high]  = numbers BIGGER than pivot
    int lt = low;    // the start of the "equal" zone
    int i = low;     // the number we are looking at right now
    int gt = high;   // the end of the "not looked at yet" zone

    // Keep going until we have looked at every number.
    while (i <= gt) {

        if (a[i] < pivot) {
            // Smaller than pivot: swap it into the "smaller" zone,
            // then move both markers forward.
            swap(a[lt], a[i]);
            lt++;
            i++;

        } else if (a[i] > pivot) {
            // Bigger than pivot: swap it to the "bigger" zone at the back.
            // We do NOT move i, because the number we just swapped in
            // from the back has not been checked yet.
            swap(a[i], a[gt]);
            gt--;

        } else {
            // Equal to pivot: it already belongs in the middle zone.
            i++;
        }
    }

    // Now the "equal" zone (lt .. gt) is in its final place.
    // Sort the "smaller" zone and the "bigger" zone the same way.
    quickSort(a, low, lt - 1);
    quickSort(a, gt + 1, high);
}

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading 100,000 numbers is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;         // n = how many numbers, k = the step size
    cin >> n >> k;    // read both numbers

    vector<int> a(n); // the list of numbers
    for (int i = 0; i < n; i++) {
        cin >> a[i];  // read each number
    }

    // Sort the whole list (from position 0 to position n-1).
    quickSort(a, 0, n - 1);

    // Print the K-th, 2K-th, 3K-th, ... elements.
    // Positions in the question start at 1, but C++ lists start at 0,
    // so the K-th element is at spot k - 1, the 2K-th at spot 2k - 1, etc.
    // "pos" is the question's position (k, 2k, 3k, ...).
    // We stop when pos goes past n.
    for (int pos = k; pos <= n; pos = pos + k) {
        cout << a[pos - 1] << '\n';   // print it ('\n' is faster than endl)
    }

    return 0;         // tells the computer the program finished successfully
}