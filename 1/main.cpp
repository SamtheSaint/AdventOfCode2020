#include <vector>
#include <cassert>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;


int multiplyTwoSum(const vector<int>& expenses, const int target, const int i = 0) {
  unordered_set<int> mem;
  for (int _i = i; _i < expenses.size(); _i++) {
    const int _expense = expenses[_i];
    auto it = mem.find(target - _expense);
    if (it != mem.end()) return *it * _expense;
    else mem.insert(_expense);
  }
  return -1;
}

int multiplyThreeSum(const vector<int>& expenses, const int target) {
  for (int i = 0; i < expenses.size(); i++) {
    const int _expense = expenses[i];
    const int twoSum = multiplyTwoSum(expenses, target - _expense, i + 1);
    if (twoSum != -1) return twoSum * _expense;
  }
  cerr << "Could not find three sum" << endl;
  exit(1);
}

int main(int argc, char const* argv[])
{
  assert(argc > 1 && "Target number input required");
  int target = stoi(argv[1]);
  vector<int> expenses;
  int _tmp;
  while (cin >> _tmp) {
    expenses.push_back(_tmp);
  }
  cout << multiplyThreeSum(expenses, target) << endl;
  return 0;
}
