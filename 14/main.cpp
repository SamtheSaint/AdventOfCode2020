#include <unordered_map>
#include <utility>
#include <iostream>
#include <regex>
#include <string>
#include <cstdint>

using namespace std;

int main(int argc, char const* argv[])
{
  unordered_map<uint64_t, uint64_t> mem;
  uint64_t ands = 0xFFFFFFFFF; // initally all ones
  uint64_t ors = 0x0; // initially all zeros

  auto updateMask = [&ands, &ors](const string& mask) {
    ands = 0xFFFFFFFFF; // reset mask
    ors = 0x0; // reset mask

    for (int i = 0; i < mask.size(); i++) {
      if (mask[i] == 'X') continue;
      else if (mask[i] == '1') ors |= (uint64_t)1 << (35 - i);
      else if (mask[i] == '0') ands &= ~((uint64_t)1 << (35 - i));
    }
  };

  auto writeToMemory = [&mem, &ands, &ors](const uint64_t address, uint64_t data) {
    data &= ands; // set zeros
    data |= ors; // set ones
    mem[address] = data;
  };

  auto maskPattern = regex("mask = ([X10]{36})");
  auto dataPattern = regex("mem\\[(\\d+)\\] = (\\d+)");
  smatch m;
  string s;
  while (getline(cin, s)) {
    if (s.empty()) continue;
    if (regex_match(s, m, maskPattern)) {
      updateMask(m[1].str());
      continue;
    }
    if (regex_match(s, m, dataPattern)) {
      uint64_t address = stoul(m[1].str());
      uint64_t data = stoull(m[2].str());
      writeToMemory(address, data);
      continue;
    }
  }
  long long acc = 0;
  for (const auto& kv : mem) {
    acc += kv.second;
    cout << kv.first << ": " << kv.second << endl;
  }
  cout << acc << endl;
  return 0;
}
