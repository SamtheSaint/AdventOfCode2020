#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

typedef vector<vector<char>> Layout;

#define empty 'L'
#define occupied '#'
#define floor '.'

bool changeEmpty(const Layout& layout, int i, int j) {
  // check N, NE, E, SE, S, SW, W, NW
  int rows = layout.size(), cols = layout[0].size();
  if (i > 0 && layout[i - 1][j] == occupied) return false; // N
  if (i > 0 && j < cols - 1 && layout[i - 1][j + 1] == occupied) return false; // NE
  if (j < cols - 1 && layout[i][j + 1] == occupied) return false; // E
  if (i < rows - 1 && j < cols - 1 && layout[i + 1][j + 1] == occupied) return false; // SE
  if (i < rows - 1 && layout[i + 1][j] == occupied) return false; // S
  if (i < rows - 1 && j > 0 && layout[i + 1][j - 1] == occupied) return false; // SW
  if (j > 0 && layout[i][j - 1] == occupied) return false; // W
  if (i > 0 && j > 0 && layout[i - 1][j - 1] == occupied) return false; // NW
  return true;
}

bool advancedChangeEmpty(const Layout& layout, int i, int j) {
  // check N, NE, E, SE, S, SW, W, NW
  int rows = layout.size(), cols = layout[0].size();
  for (int _i = i; _i > 0; _i--) {
    if (layout[_i - 1][j] == empty) break;
    if (layout[_i - 1][j] == occupied) return false;
  } // N
  for (int _j = j; _j < cols - 1; _j++) {
    if (layout[i][_j + 1] == empty) break;
    if (layout[i][_j + 1] == occupied) return false;
  } // E
  for (int _i = i; _i < rows - 1; _i++) {
    if (layout[_i + 1][j] == empty) break;
    if (layout[_i + 1][j] == occupied) return false;
  }// S
  for (int _j = j; _j > 0; _j--) {
    if (layout[i][_j - 1] == empty) break;
    if (layout[i][_j - 1] == occupied) return false;
  } // W

  for (int _i = i, _j = j; _i > 0 && _j < cols - 1; _i--, _j++) {
    if (layout[_i - 1][_j + 1] == empty) break;
    if (layout[_i - 1][_j + 1] == occupied) return false;
  }// NE
  for (int _i = i, _j = j; _i < rows - 1 && _j < cols - 1; _i++, _j++) {
    if (layout[_i + 1][_j + 1] == empty) break;
    if (layout[_i + 1][_j + 1] == occupied) return false;
  }// SE
  for (int _i = i, _j = j; _i < rows - 1 && _j > 0; _i++, _j--) {
    if (layout[_i + 1][_j - 1] == empty) break;
    if (layout[_i + 1][_j - 1] == occupied) return false;
  }// SW
  for (int _i = i, _j = j; _i > 0 && _j > 0; _i--, _j--) {
    if (layout[_i - 1][_j - 1] == empty) break;
    if (layout[_i - 1][_j - 1] == occupied) return false;
  }// NW

  return true;
}

bool changeOccupied(const Layout& layout, int i, int j) {
  // check N, NE, E, SE, S, SW, W, NW
  int rows = layout.size(), cols = layout[0].size();
  int numOccupied = 0;
  if (i > 0 && layout[i - 1][j] == occupied) numOccupied++; // N
  if (i > 0 && j < cols - 1 && layout[i - 1][j + 1] == occupied) numOccupied++; // NE
  if (j < cols - 1 && layout[i][j + 1] == occupied) numOccupied++; // E
  if (i < rows - 1 && j < cols - 1 && layout[i + 1][j + 1] == occupied) numOccupied++; // SE
  if (i < rows - 1 && layout[i + 1][j] == occupied) numOccupied++; // S
  if (i < rows - 1 && j > 0 && layout[i + 1][j - 1] == occupied) numOccupied++; // SW
  if (j > 0 && layout[i][j - 1] == occupied) numOccupied++; // W
  if (i > 0 && j > 0 && layout[i - 1][j - 1] == occupied) numOccupied++; // NW

  return numOccupied >= 4;
}

bool advancedChangeOccupied(const Layout& layout, const int i, const int j) {
  int rows = layout.size(), cols = layout[0].size();
  int numOccupied = 0;

  for (int _i = i; _i > 0; _i--) {
    if (layout[_i - 1][j] == empty) break;
    if (layout[_i - 1][j] == occupied) { numOccupied++; break; }
  } // N
  for (int _j = j; _j < cols - 1; _j++) {
    if (layout[i][_j + 1] == empty) break;
    if (layout[i][_j + 1] == occupied) { numOccupied++; break; }
  } // E
  for (int _i = i; _i < rows - 1; _i++) {
    if (layout[_i + 1][j] == empty) break;
    if (layout[_i + 1][j] == occupied) { numOccupied++; break; }
  }// S
  for (int _j = j; _j > 0; _j--) {
    if (layout[i][_j - 1] == empty) break;
    if (layout[i][_j - 1] == occupied) { numOccupied++; break; }
  } // W

  for (int _i = i, _j = j; _i > 0 && _j < cols - 1; _i--, _j++) {
    if (layout[_i - 1][_j + 1] == empty) break;
    if (layout[_i - 1][_j + 1] == occupied) { numOccupied++; break; }
  }// NE
  for (int _i = i, _j = j; _i < rows - 1 && _j < cols - 1; _i++, _j++) {
    if (layout[_i + 1][_j + 1] == empty) break;
    if (layout[_i + 1][_j + 1] == occupied) { numOccupied++; break; }
  }// SE
  for (int _i = i, _j = j; _i < rows - 1 && _j > 0; _i++, _j--) {
    if (layout[_i + 1][_j - 1] == empty) break;
    if (layout[_i + 1][_j - 1] == occupied) { numOccupied++; break; }
  }// SW
  for (int _i = i, _j = j; _i > 0 && _j > 0; _i--, _j--) {
    if (layout[_i - 1][_j - 1] == empty) break;
    if (layout[_i - 1][_j - 1] == occupied) { numOccupied++; break; }
  }// NW

  return numOccupied >= 5;
}

bool simulate(Layout& layout) {
  unordered_map<int, vector<int>> mem; // row, [columns that need to change]

  for (int i = 0; i < layout.size(); i++) {
    for (int j = 0; j < layout[0].size(); j++) {
      char cur = layout[i][j];
      if (cur == floor) continue;
      else if ((cur == empty) && advancedChangeEmpty(layout, i, j)) mem[i].push_back(j);
      else if ((cur == occupied) && advancedChangeOccupied(layout, i, j)) mem[i].push_back(j);
    }
  }

  if (mem.size() == 0) return false;

  for (const auto& kv : mem) {
    int i = kv.first;
    for (const int j : kv.second) {
      char prev = layout[i][j];
      layout[i][j] = prev == empty ? occupied : empty;
    }
  }

  return true;
}

int countOccupiedSeats(const Layout& layout) {
  int acc = 0;
  for (const vector<char>& xc : layout) {
    for (const char c : xc) {
      if (c == occupied) acc++;
    }
  }
  return acc;
}

int main(int argc, char const* argv[])
{
  Layout layout;
  string s; vector<char> xc;

  while (cin >> s) {
    for (const char c : s) xc.push_back(c);
    layout.push_back(xc);
    xc.clear();
  }

  int i = 0;
  while (simulate(layout)) {
    // for (const vector<char>& xc : layout) {
    //   for (const char c : xc) {
    //     cout << c << " ";
    //   }
    //   puts("");
    // }
    // puts("");
    i++;
  }

  cout << i << endl;
  cout << countOccupiedSeats(layout) << endl;
  return 0;
}
