/*
=====================================================================
QUESTION SUMMARY: "Last one"
=====================================================================
N people stand in a circle, numbered 1 to N clockwise.
They pick a number K and play an introduction game:
 - Start counting from person 1: "1, 2, 3, ... K".
 - The person who is counted as K introduces themselves, then LEAVES
   the circle.
 - Counting then continues from the next person after the one who
   left, starting again at 1.
 - Because it is a circle, counting wraps around from the last person
   back to the first.
 - This repeats until everyone has introduced themselves.

TASK: Print the number of the LAST person to introduce themselves.

INPUT:
 - One line with two integers: N and K
   (1 <= N <= 150, 1 <= K <= 200)

OUTPUT:
 - One integer: the number of the last person to introduce themselves.

SAMPLE INPUT 1:
7 3

SAMPLE OUTPUT 1:
4

WHY 4? (walking through the sample, N = 7, K = 3)
 Circle: 1 2 3 4 5 6 7
 Round 1: count 1,2,3 -> person 3 leaves.   Left: 1 2 4 5 6 7
 Round 2: count from 4: 4,5,6 -> 6 leaves.  Left: 1 2 4 5 7
 Round 3: count from 7: 7,1,2 -> 2 leaves.  Left: 1 4 5 7
 Round 4: count from 4: 4,5,7 -> 7 leaves.  Left: 1 4 5
 Round 5: count from 1: 1,4,5 -> 5 leaves.  Left: 1 4
 Round 6: count from 1: 1,4,1 -> 1 leaves.  Left: 4
 Round 7: only person 4 remains -> 4 leaves LAST.
 Order: 3, 6, 2, 7, 5, 1, 4  -> the last one is 4.

SAMPLE INPUT 2:
9 2

SAMPLE OUTPUT 2:
3

(This is a famous puzzle called the "Josephus problem".)
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <vector>     // lets us use "vector" (a list that can grow and shrink)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n, k;         // two boxes: n = number of people, k = counting number
    cin >> n >> k;    // read both numbers from the input

    // A "vector" is a list of numbers. This list is our circle of people.
    // We fill it with 1, 2, 3, ..., n (the person numbers).
    vector<int> people;
    for (int i = 1; i <= n; i++) {
        people.push_back(i);   // push_back adds a number to the END of the list
    }

    // "position" is the spot (index) in the list where counting starts.
    // Lists in C++ start counting spots at 0 (not 1), so spot 0 is the
    // first person. Counting starts at the first person, so we begin at 0.
    int position = 0;

    // This box will remember who left most recently.
    // When the loop finishes, it holds the LAST person to leave.
    int lastPerson = 0;

    // Keep going while there is still anyone in the circle.
    // people.size() tells us how many are left in the list.
    while (people.size() > 0) {

        // Find who gets counted as "K".
        // The person we start on counts as 1, so we only need to move
        // forward (k - 1) more spots to reach the person who counts as K.
        //
        // "%" is the "remainder" operator. It makes us wrap around the
        // circle: if we walk past the end of the list, we come back to
        // the start. Example: with 6 people, spot 6 wraps back to spot 0
        // because 6 % 6 = 0.
        position = (position + k - 1) % people.size();

        // This person is the one who introduces themselves now.
        // Save their number (so the final value is the last person).
        lastPerson = people[position];

        // Remove that person from the circle.
        // "begin() + position" means "the spot number 'position' in the list".
        // After erasing, the next person slides into the same spot, so
        // "position" already points at the person where the NEXT counting
        // starts. We do not need to move it.
        people.erase(people.begin() + position);

        // Note: if we removed the person at the very end of the list,
        // "position" now points past the end. That is fine, because the
        // "%" on the next round wraps it back to the start.
        // (When the list becomes empty, the while loop stops, so we never
        // divide by zero.)
    }

    cout << lastPerson << endl;   // print the number of the last person

    return 0;                     // tells the computer the program finished successfully
}