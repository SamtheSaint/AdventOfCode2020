#include <unordered_map>
#include <utility>
#include <iostream>
#include <regex>
#include <string>
#include <cstdint>
#include <stack>

#define floating 'X'

using namespace std;

int main(int argc, char const* argv[])
{
  unordered_map<uint64_t, uint64_t> mem;
  string mask;

  auto applyMask = [&mask](uint64_t address) {
    string addressMask = mask;
    for (int i = 0; i < mask.size(); i++) {
      if (mask[i] == '0') {
        bool bit = (address >> (mask.size() - i - 1)) & 1;
        addressMask[i] = bit ? '1' : '0';
      }
    }
    return addressMask;
  };

  auto writeToMemory = [&mem, &applyMask](const uint64_t address, uint64_t data) {
    string addressMask = applyMask(address);
    stack<string> tmp;
    tmp.push(addressMask);
    while (!tmp.empty()) {
      string cur = tmp.top();
      tmp.pop();

      size_t index = cur.find(floating);
      if (index == string::npos) {
        uint64_t addr = stoull(cur, 0, 2);
        mem[addr] = data;
      }
      else {
        string cur0 = cur;
        string cur1 = cur;
        cur0[index] = '0';
        cur1[index] = '1';
        tmp.push(cur0);
        tmp.push(cur1);
      }
    }
  };

  auto maskPattern = regex("mask = ([X10]{36})");
  auto dataPattern = regex("mem\\[(\\d+)\\] = (\\d+)");
  smatch m;
  string s;
  while (getline(cin, s)) {
    if (s.empty()) continue;
    if (regex_match(s, m, maskPattern)) {
      mask = m[1].str();
      continue;
    }
    if (regex_match(s, m, dataPattern)) {
      uint64_t address = stoul(m[1].str());
      uint64_t data = stoull(m[2].str());
      writeToMemory(address, data);
      continue;
    }
  }
  unsigned long long acc = 0;
  for (const auto& kv : mem) {
    acc += kv.second;
    // cout << kv.first << ": " << kv.second << endl;
  }
  cout << acc << endl;
  return 0;
}
