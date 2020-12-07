#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

int main(int argc, char const* argv[])
{
  string s;
  unordered_set<char> mem;
  unordered_set<char> _mem;
  bool isFirstLine = true;
  int acc = 0;
  while (getline(cin, s)) {
    if (s.empty()) {
      cout << mem.size() << endl;
      acc += mem.size();
      mem.clear();
      isFirstLine = true;
      continue;
    }

    if (mem.empty() && isFirstLine) {
      for (const char c : s) mem.insert(c);
      isFirstLine = false;
      continue;
    }

    _mem.clear();
    for (const char c : mem) {
      if (s.find(c, 0) == string::npos) {
        _mem.insert(c);
      }
    }

    for (const char c : _mem) mem.erase(c);

  }

  printf("%d\n", acc);
  return 0;
}
