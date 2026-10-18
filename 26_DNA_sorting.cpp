/*
=====================================================================
QUESTION SUMMARY: "DNA Sorting"
=====================================================================
"Unsortedness" of a string is the number of INVERSIONS: pairs of
letters that are out of order. A pair (left letter, right letter) is
an inversion if the LEFT letter is alphabetically GREATER than the
RIGHT letter.
Example: "DAABEC" has 5 inversions:
   D is greater than A, A, B, C (4 pairs), E is greater than C (1 pair).

We get several datasets. Each has m DNA strings (letters A, C, G, T),
all with the same length n.

TASK: For each dataset, print the strings from "most sorted" (fewest
      inversions) to "least sorted" (most inversions).
      If two strings have the SAME number of inversions, keep them in
      the order they appeared in the input.
      Print a blank line BETWEEN datasets (not after the last one).

INPUT:
 - Line 1: M = number of datasets.
 - Then each dataset has:
     n and m (n = string length <= 50, m = number of strings <= 100)
     followed by m strings.
   (Blank lines between datasets are skipped automatically by cin.)

OUTPUT:
 - For each dataset, the m strings in sorted order.
 - A blank line between consecutive datasets.

SAMPLE INPUT:
1
10 6
AACATGAAGG
TTTTGGCCAA
TTTGGCCAAA
GATCAGATTT
CCCGGGGGGA
ATCGATGCAT

SAMPLE OUTPUT:
CCCGGGGGGA
AACATGAAGG
GATCAGATTT
ATCGATGCAT
TTTTGGCCAA
TTTGGCCAAA

WHY? (inversion count of each string in the sample)
 CCCGGGGGGA : 9   (3 C's each beat the last A = 3, 6 G's each beat
                   the last A = 6, total 9)
 AACATGAAGG : 10  (C > A,A,A = 3; T > G,A,A,G,G = 5; first G > A,A = 2)
 GATCAGATTT : 11
 ATCGATGCAT : 17
 TTTTGGCCAA : 36
 TTTGGCCAAA : 37
 Sorted from fewest to most inversions, this gives exactly the
 sample output order.

KEY IDEAS:
 1) Count inversions for a string by checking EVERY pair of positions
    (i, j) with i before j. Strings are at most 50 long, so that is
    at most about 1225 pairs per string. Very small.
 2) Sort the strings by their inversion count. We use "stable_sort",
    which keeps the original order of strings that tie. That is
    exactly what the question asks for.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
#include <string>     // lets us use "string" (a variable that holds text)
#include <vector>     // lets us use "vector" (a list that can grow)
#include <algorithm>  // lets us use stable_sort
#include <utility>    // lets us use "pair" (two values stuck together)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int datasets;     // a box to hold M, the number of datasets
    cin >> datasets;  // read M from the input

    // Repeat once for each dataset.
    for (int d = 0; d < datasets; d++) {

        int n, m;         // n = length of each string, m = how many strings
        cin >> n >> m;    // read both numbers

        // Each item in this list is a PAIR:
        //   first  = the inversion count of the string
        //   second = the string itself
        vector< pair<int, string> > items;

        // Read the m strings and count the inversions of each one.
        for (int i = 0; i < m; i++) {

            string s;     // a box for this DNA string
            cin >> s;     // read it from the input

            int inversions = 0;   // inversion count for this string, starts at 0

            // Look at every pair of positions (a, b) with a before b.
            // "a" is the left letter's position, "b" is the right one.
            for (int a = 0; a < (int)s.size(); a++) {
                for (int b = a + 1; b < (int)s.size(); b++) {
                    // Letters compare alphabetically: A < C < G < T.
                    // If the left letter is greater than the right one,
                    // they are out of order, so it is one inversion.
                    if (s[a] > s[b]) {
                        inversions = inversions + 1;
                    }
                }
            }

            // Store the count together with the string.
            items.push_back(make_pair(inversions, s));
        }

        // Sort by the inversion count only (the "first" part of each pair).
        // stable_sort keeps the input order for strings with equal counts.
        // The small function inside the [ ] is a rule that says:
        // "item x goes before item y if x has FEWER inversions".
        stable_sort(items.begin(), items.end(),
                    [](const pair<int, string>& x, const pair<int, string>& y) {
                        return x.first < y.first;
                    });

        // Print a blank line BETWEEN datasets: before every dataset
        // except the first one.
        if (d > 0) {
            cout << '\n';
        }

        // Print the strings in their new order, one per line.
        for (int i = 0; i < (int)items.size(); i++) {
            cout << items[i].second << '\n';
        }
    }

    return 0;         // tells the computer the program finished successfully
}