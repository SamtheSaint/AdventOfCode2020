#include <vector>
#include <string>
#include <iostream>

using namespace std;

typedef vector<vector<char>> Map;
#define tree '#'
#define space ' '

int countTrees(const Map& map, int right, int down, int x = 0, int y = 0) {
  if (x >= map.size()) return 0;
  int subCount = countTrees(map, right, down, x + down, (y + right) % map[0].size());
  return map[x][y] == tree ? 1 + subCount : subCount;
}


int main(int argc, char const* argv[])
{
  Map map;
  string _xc;

  while (cin >> _xc) {
    map.push_back(vector<char>(_xc.begin(), _xc.end()));
  }

  vector<pair<int, int>> slopes = {
    {1, 1},
    {3, 1},
    {5, 1},
    {7, 1},
    {1, 2}
  };

  long acc = 1;
  for (const pair<int, int>& slope : slopes) {
    acc *= countTrees(map, slope.first, slope.second);
    printf("%ld\n", acc);
  }

  cout << acc << endl;
  return 0;
}
