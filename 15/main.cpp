#include <unordered_map>
#include <utility>
#include <iostream>
#include <regex>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <queue>

using namespace std;

void simulate(const vector<int>& input, const int stop) {
  unordered_map<int, queue<int>> mem;
  int turn = 1;
  int prev;
  while (turn <= stop) {
    // handle starting numbers
    if (turn <= input.size()) {
      int spoken = input[turn - 1];
      // cout << turn << ": " << spoken << endl;
      mem[spoken].push(turn++);
      prev = spoken;
      continue;
    }
    queue<int>& prevMem = mem[prev];
    int spoken = prevMem.size() == 1 ? 0 : prevMem.back() - prevMem.front();
    // cout << turn << ": " << spoken << endl;
    queue<int>& spokenMem = mem[spoken];
    spokenMem.push(turn++);
    if (spokenMem.size() == 3) spokenMem.pop();
    prev = spoken;
  }
  cout << prev << endl;
}

int main(int argc, char const* argv[])
{
  vector<int> input = { 6,3,15,13,1,0 };
  const int stop = 30000000;
  simulate(input, stop);
  return 0;
}
