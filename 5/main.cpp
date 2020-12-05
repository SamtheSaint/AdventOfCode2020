#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <set>

using namespace std;

int getSeatID(const string& boardingPass) {
  assert((boardingPass.size() == 10) && "Invalid boarding pass");

  const string rowIndicator = boardingPass.substr(0, 6);
  const string colIndicator = boardingPass.substr(7, 2);

  int rowHigh = 127, rowLow = 0;
  int colHigh = 7, colLow = 0;

  for (const char c : rowIndicator) {
    int mid = (rowHigh + rowLow) / 2;

    if (c == 'F') rowHigh = mid;
    else rowLow = mid + 1;
  }

  for (const char c : colIndicator) {
    int mid = (colHigh + colLow) / 2;
    if (c == 'R') colLow = mid + 1;
    else colHigh = mid;
  }

  int row = boardingPass[6] == 'F' ? rowLow : rowHigh;
  int col = boardingPass[9] == 'R' ? colHigh : colLow;

  return (row * 8) + col;
}

int main(int argc, char const* argv[])
{
  vector<string> boardingPasses;
  set<int> seatIDs;
  string _s;
  while (cin >> _s) {
    // boardingPasses.push_back(_s);
    seatIDs.insert(getSeatID(_s));
  }

  // int maxID = 0;
  // for (const string& boardingPass : boardingPasses) {
  //   maxID = max(maxID, getSeatID(boardingPass));
  // }
  // printf("%d\n", maxID);

  auto it0 = seatIDs.begin();
  auto it1 = seatIDs.begin();
  advance(it1, 1);
  for (int i = 0; i < seatIDs.size() - 1; i++) {
    if (*it1 - *it0 > 1) {
      cout << *it0 << " " << *it1 << endl;
    }
    advance(it0, 1);
    advance(it1, 1);
  }
  return 0;
}
