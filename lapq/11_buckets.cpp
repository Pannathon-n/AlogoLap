/*
=====================================================================
QUESTION SUMMARY: "Buckets"
=====================================================================
You have 5 buckets (numbered 1 to 5). Each bucket can hold at most
1,000 units of water. All buckets start empty.

You receive N jars of water. For each jar, in order:
 1. Pour the WHOLE jar into the bucket that currently has the LEAST
    water. If several buckets tie for the least, pick the one with the
    smallest number.
 2. If the bucket cannot hold it all (it would go over 1,000), the
    extra water is thrown away. The bucket just becomes full (1,000).
 3. After pouring, if that bucket is FULL (exactly 1,000), you carry
    all 1,000 units to the water tank, and the bucket becomes empty
    again (0).

TASK: Print the total amount of water that ends up in the tank.
      (Only 1,000 is counted each time a bucket fills, not the extra
      water that was thrown away.)

INPUT:
 - Line 1: N = number of jars (1 <= N <= 1000)
 - Next N lines: Xi = units of water in the i-th jar (1 <= Xi <= 2000)

OUTPUT:
 - One integer: the total water put into the tank.

SAMPLE INPUT:
8
100
200
300
400
500
950
950
950

SAMPLE OUTPUT:
2000

WHY 2000? (walking through the sample)
 Buckets are shown as [B1 B2 B3 B4 B5]
 Jar 100: all are 0, tie -> bucket 1.          [100   0   0   0   0]
 Jar 200: smallest is 0, first one is bucket 2. [100 200   0   0   0]
 Jar 300: -> bucket 3.                          [100 200 300   0   0]
 Jar 400: -> bucket 4.                          [100 200 300 400   0]
 Jar 500: -> bucket 5.                          [100 200 300 400 500]
 Jar 950: smallest is bucket 1 (100).
          100 + 950 = 1050, too much, so it becomes 1000 (50 thrown
          away). It is full, so 1000 goes to the tank. Bucket 1 = 0.
          Tank = 1000.                          [  0 200 300 400 500]
 Jar 950: smallest is bucket 1 (0). 0 + 950 = 950, not full.
                                                [950 200 300 400 500]
 Jar 950: smallest is bucket 2 (200). 200 + 950 = 1150 -> full (1000).
          1000 goes to the tank. Bucket 2 = 0.
          Tank = 2000.                          [950   0 300 400 500]
 Final tank = 2000.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n;            // a box to hold N, the number of jars
    cin >> n;         // read N from the input

    // A list of 5 boxes, one for each bucket.
    // bucket[0] is bucket 1, bucket[1] is bucket 2, ... bucket[4] is bucket 5.
    // (C++ lists start counting at 0, not 1.)
    // "= {0}" makes every bucket start empty (0 water).
    int bucket[5] = {0};

    // A box to hold the total water put into the tank. Starts at 0.
    long long tank = 0;

    // Repeat once for each jar.
    for (int i = 0; i < n; i++) {

        int jar;      // a box for the water in THIS jar
        cin >> jar;   // read it from the input

        // STEP 1: find the bucket with the LEAST water.
        // We assume bucket 0 is the smallest, then check the others.
        int smallest = 0;
        for (int j = 1; j < 5; j++) {
            // We use "<" (strictly less), NOT "<=".
            // That way, if two buckets tie, we keep the earlier one,
            // which is the one with the smaller number. That is what
            // the question asks for.
            if (bucket[j] < bucket[smallest]) {
                smallest = j;
            }
        }

        // STEP 2: pour the whole jar into that bucket.
        bucket[smallest] = bucket[smallest] + jar;

        // If it went over 1000, the extra water is thrown away,
        // so the bucket just stays at 1000.
        if (bucket[smallest] > 1000) {
            bucket[smallest] = 1000;
        }

        // STEP 3: if the bucket is full, carry the water to the tank.
        if (bucket[smallest] == 1000) {
            tank = tank + 1000;      // 1000 units go into the tank
            bucket[smallest] = 0;    // the bucket is empty again
        }
    }

    cout << tank << endl;   // print the total water in the tank

    return 0;               // tells the computer the program finished successfully
}