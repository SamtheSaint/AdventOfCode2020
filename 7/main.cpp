#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <cassert>

using namespace std;

void parseBag(unordered_map<string, unordered_set<string>>& contains, string line) {
  const regex matchContainer = regex("^[a-z]+[ ][a-z]+");
  const regex matchContains = regex("\\d[ ][a-z]+[ ][a-z]+");
  smatch m;
  string containerBag;
  unordered_set<string> containedBags;

  assert(regex_search(line, m, matchContainer));
  containerBag = m[0].str();
  line = m.suffix().str();

  while (regex_search(line, m, matchContains)) {
    containedBags.insert(m[0].str());
    line = m.suffix().str();
  }

  contains[containerBag] = containedBags;
}

int canContain(const unordered_map<string, unordered_set<string>>& contains, const string& bag) {
  unordered_set<string> canContainTarget;
  while (true) {
    int inital = canContainTarget.size();
    for (const auto& kv : contains) {
      if (canContainTarget.find(kv.first) != canContainTarget.end()) continue;
      for (const auto& _bag : kv.second) {
        string bagName = _bag.substr(2);
        if ((bagName == bag) || canContainTarget.find(bagName) != canContainTarget.end()) {
          canContainTarget.insert(kv.first);
          break;
        }
      }
    }
    int final = canContainTarget.size();
    if (inital == final) break;
  }

  return canContainTarget.size();
}

int howManyBags(unordered_map<string, unordered_set<string>>& contains, const string& bag) {
  int acc = 0;
  for (const auto& _bag : contains[bag]) {
    int num = stoi(_bag.substr(0, 1));
    acc += num * howManyBags(contains, _bag.substr(2));
  }
  return 1 + acc;
}

int main(int argc, char const* argv[])
{
  unordered_map<string, unordered_set<string>> contains;
  string line;

  while (getline(cin, line)) {
    if (!line.empty()) parseBag(contains, line);
  }

  const string targetBag = "shiny gold";
  // cout << canContain(contains, targetBag) << endl;
  cout << howManyBags(contains, targetBag) << endl;

  return 0;
}
