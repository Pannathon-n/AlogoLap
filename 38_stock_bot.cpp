/*
=====================================================================
QUESTION SUMMARY: "Stock Bot"
=====================================================================
A bot trades one stock (GOOG) and holds at most 1 unit at a time.
It has a "panic threshold" K. Every day (starting from day 2) it
compares today's price with yesterday's price:

 - If today's price went UP by at least K compared with yesterday,
   AND the bot does NOT hold the stock -> it BUYS 1 unit at today's
   price.
 - If today's price went DOWN by at least K compared with yesterday,
   AND the bot DOES hold the stock -> it SELLS 1 unit at today's
   price.
 - Otherwise it does nothing. The bot does nothing on day 1.

TASK: Print the total money the bot makes:
          (sum of all selling prices) - (sum of all buying prices)
      counting only trades that are COMPLETE (bought AND sold).
      The result can be NEGATIVE.
      If the bot still holds a stock at the end, that last purchase
      is NOT taken into account (the question says to ignore it).

INPUT:
 - Line 1: N and K (1 <= N <= 1000, 1 <= K <= 1000)
 - Next N lines: Pi = the price on day i (0 to 1,000,000)

OUTPUT:
 - One integer: the money made.

SAMPLE INPUT 1:
10 2
1 2 4 5 6 10 9 7 8 15      (one price per line in the real input)
SAMPLE OUTPUT 1:
3

WHY 3? (walking through sample 1, K = 2)
 Day 2: 1 -> 2   up 1, not enough.
 Day 3: 2 -> 4   up 2 >= 2, no stock -> BUY at 4.
 Day 4: 4 -> 5   up 1, nothing.
 Day 5: 5 -> 6   up 1, nothing.
 Day 6: 6 -> 10  up 4, but we already hold the stock -> nothing.
 Day 7: 10 -> 9  down 1, not enough.
 Day 8: 9 -> 7   down 2 >= 2, we hold -> SELL at 7.
                 This trade made 7 - 4 = 3.
 Day 9: 7 -> 8   up 1, nothing.
 Day 10: 8 -> 15 up 7, no stock -> BUY at 15.
                 Never sold, so it is ignored.
 Total = 3.

SAMPLE INPUT 2:
6 10
100 120 119 118 117 80
SAMPLE OUTPUT 2:
-40
 (Day 2: 100 -> 120 up 20 -> BUY at 120.
  Days 3 to 5: each day drops only 1, so nothing happens.
  Day 6: 117 -> 80 down 37 -> SELL at 80. Trade = 80 - 120 = -40.)

SAMPLE INPUT 3:
7 5
100 120 110 120 110 120 110
SAMPLE OUTPUT 3:
-30
 (Three trades, each: buy at 120, sell at 110 = -10.
  3 trades x -10 = -30.)

KEY IDEA:
 Walk through the days once, remembering:
   - holding: true if the bot has the stock right now
   - buyPrice: the price it paid for that stock
 When the bot SELLS, add (sellPrice - buyPrice) to the total.
 When the bot BUYS, only remember the price (do not change the total
 yet). A stock that is never sold is therefore never counted, which
 matches the question.
=====================================================================
*/

#include <iostream>   // lets us use cin (read input) and cout (print output)
using namespace std;  // so we can write cin/cout instead of std::cin/std::cout

int main() {          // every C++ program starts running here

    int n, k;         // n = number of days, k = the panic threshold
    cin >> n >> k;    // read both numbers

    // A box for the total money made. It starts at 0.
    // "long long" is a big number box, to be safe.
    long long total = 0;

    bool holding = false;   // does the bot hold the stock right now? No.
    long long buyPrice = 0; // the price the bot paid for the stock it holds

    long long previous = 0; // yesterday's price (filled in on day 1)

    // Go through the days one by one. "day" counts from 1 to n.
    for (int day = 1; day <= n; day++) {

        long long price;    // today's price
        cin >> price;       // read it from the input

        // The bot does nothing on day 1, so we only act from day 2 on.
        if (day > 1) {

            if (price - previous >= k && !holding) {
                // Price went UP by at least K and we hold nothing: BUY.
                // "!" means NOT, so "!holding" means "not holding".
                holding = true;
                buyPrice = price;       // remember what we paid

            } else if (previous - price >= k && holding) {
                // Price went DOWN by at least K and we hold the stock: SELL.
                total = total + (price - buyPrice);   // profit (or loss)
                holding = false;                      // we hold nothing now
            }
        }

        previous = price;   // today becomes "yesterday" for the next round
    }

    cout << total << endl;  // print the money the bot made

    return 0;               // tells the computer the program finished successfully
}