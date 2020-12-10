#include <iostream>
#include <vector>
#include <unordered_set>
#include <deque>
#include <algorithm>

using namespace std;

bool twoSum(const vector<int>& mem, const int start, const int length) {
  const int target = mem[start + length];
  unordered_set<int> dp;

  for (int i = start; i < start + length; i++) {
    const int cur = mem[i];
    if (dp.find(target - cur) != dp.end()) return true;
    dp.insert(cur);
  }

  return false;
}

int contiguousSum(const vector<int>& mem, const int target) {
  deque<int> dp;
  int sum = 0;

  for (const int i : mem) {
    dp.push_back(i);
    sum += i;

    while (sum > target) {
      sum -= dp.front();
      dp.pop_front();
    }

    if (sum == target) {
      return *max_element(dp.begin(), dp.end()) + *min_element(dp.begin(), dp.end());
    }
  }

  return -1;
}

int main(int argc, char const* argv[])
{
  const int preambleLength = 25;
  vector<int> mem;
  int i;
  int invalid;

  while (cin >> i) mem.push_back(i);
  for (int i = 0; i < mem.size() - preambleLength; i++) {
    if (!twoSum(mem, i, preambleLength)) {
      invalid = mem[i + preambleLength];
      break;
    }
  }
  cout << invalid << endl;
  cout << contiguousSum(mem, invalid) << endl;

  return 0;
}
