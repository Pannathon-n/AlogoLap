/*
=====================================================================
QUESTION SUMMARY: "What is the Median?"
=====================================================================
The MEDIAN is the middle value of a sorted list.
 - ODD amount of numbers: the median is the one exactly in the middle.
       {1, 2, 3, 6, 7} -> median is 3.
 - EVEN amount of numbers: no single middle number exists, so we take
       the AVERAGE of the two middle numbers and keep ONLY the integer
       part (drop the decimals).
       {1, 2, 3, 6, 7, 8} -> (3 + 6) / 2 = 4.5 -> we print 4.

The numbers arrive one at a time.
TASK: After EACH new number is read, print the median of ALL the
      numbers read so far.

INPUT:
 - A series of integers X (0 <= X < 2^31), fewer than 10,000 of them.
   They may have extra spaces around them (cin handles that for us).
 - The input ends at the end of the file (EOF).

OUTPUT:
 - After every number, one line with the current median (integer part).

SAMPLE INPUT:
1 3 4 60 70 50 2        (one number per line in the real input)

SAMPLE OUTPUT:
1 2 3 3 4 27 4          (one number per line in the real output)

WHY? (walking through the sample, list is kept sorted)
 read 1  -> [1]                    1 number, middle is 1          -> 1
 read 3  -> [1 3]                  (1+3)/2 = 2                    -> 2
 read 4  -> [1 3 4]                middle is 3                    -> 3
 read 60 -> [1 3 4 60]             (3+4)/2 = 3 (3.5 drops to 3)   -> 3
 read 70 -> [1 3 4 60 70]          middle is 4                    -> 4
 read 50 -> [1 3 4 50 60 70]       (4+50)/2 = 27                  -> 27
 read 2  -> [1 2 3 4 50 60 70]     middle is 4                    -> 4

KEY IDEA:
 Keep a list that is ALWAYS sorted. For each new number:
   1) Find the right spot for it (binary search: very fast).
   2) Insert it there.
   3) Look at the middle of the list to get the median.
 With fewer than 10,000 numbers, inserting into a vector is fast enough.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <algorithm>  // lets us use lower_bound (find the right spot)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    // Magic speed-up lines so reading and printing is fast.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // The sorted list of all numbers read so far.
    // "long long" is a BIG number box. Numbers can be almost 2 billion,
    // and adding two of them could be too big for a normal int,
    // so we use long long to be safe.
    vector<long long> sortedList;

    long long x;      // a box for the number we just read

    // Keep reading numbers until the file ends (reading fails).
    // Each time around the loop handles ONE new number.
    while (cin >> x) {

        // lower_bound finds the first spot in the sorted list whose
        // value is NOT smaller than x. That is exactly where x belongs
        // to keep the list sorted.
        vector<long long>::iterator spot =
            lower_bound(sortedList.begin(), sortedList.end(), x);

        // Insert x at that spot. Everything after it shifts one place.
        sortedList.insert(spot, x);

        int size = sortedList.size();   // how many numbers we have now

        if (size % 2 == 1) {
            // ODD amount: take the middle number.
            // "%" is the remainder operator: size % 2 == 1 means odd.
            // The middle spot is size / 2. (Lists start counting at 0.
            // Example: size 5, spots 0..4, middle is spot 2 = 5 / 2.)
            cout << sortedList[size / 2] << '\n';
        } else {
            // EVEN amount: average the two middle numbers.
            // Example: size 6, spots 0..5, middle two are spots 2 and 3.
            // Dividing whole numbers drops the decimal part,
            // which is exactly what the question wants.
            long long left = sortedList[size / 2 - 1];
            long long right = sortedList[size / 2];
            cout << (left + right) / 2 << '\n';
        }
    }

    return 0;         // tells the computer the program finished successfully
}