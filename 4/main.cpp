#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using namespace std;

typedef unordered_map<string, string> Passport;

const unordered_map<string, regex> requiredFields = {
  {"byr", regex("\\d{4}", regex_constants::ECMAScript)},
  {"iyr", regex("\\d{4}", regex_constants::ECMAScript)},
  {"eyr", regex("\\d{4}", regex_constants::ECMAScript)},
  {"hgt", regex("\\d{2,3}(cm|in)", regex_constants::ECMAScript)},
  {"hcl", regex("(#)[abcdef0-9]{6}", regex_constants::ECMAScript)},
  {"ecl", regex("(amb|blu|brn|gry|grn|hzl|oth)", regex_constants::ECMAScript)},
  {"pid", regex("\\d{9}", regex_constants::ECMAScript)}
};
// const unordered_set<string> optionalFields = { "cid" };

bool isValid(const Passport& p, const unordered_map<string, regex>& required) {
  for (const auto field : required) {
    const string& f = field.first;
    const auto re = field.second;
    auto it = p.find(f);
    if (it == p.end()) return false;
    const string& val = it->second;
    smatch m;
    if (!regex_match(val, m, re)) return false;
    if (f == "hgt") {
      const string& height = m[0].str();
      int height_val = stoi(height.substr(0, height.size() - 2));
      string height_unit = height.substr(height.size() - 2, height.size());

      if (height_unit == "cm" && (height_val > 193 || height_val < 150)) return false;
      if (height_unit == "in" && (height_val > 76 || height_val < 59)) return false;
    }
    if (f == "eyr" || f == "iyr" || f == "byr") {
      int year = stoi(m[0].str());
      if (f == "byr" && (year < 1920 || year > 2002)) return false;
      if (f == "iyr" && (year < 2010 || year > 2020)) return false;
      if (f == "eyr" && (year < 2020 || year > 2030)) return false;
    }
  }
  return true;
}

int main(int argc, char const* argv[])
{
  const string delim = " ";
  vector<Passport> passports;
  string s;
  Passport p;
  int acc = 0;

  while (getline(cin, s)) {
    if (s.empty()) {
      passports.push_back(p);
      p.clear();
      continue;
    }
    int start = 0, end = s.find(delim);
    while (true) {
      string sub = s.substr(start, end - start);
      string key = sub.substr(0, 3);
      string value = sub.substr(4, sub.length() - 4);

      p[key] = value;

      if (end == string::npos) break;
      start = end + delim.size();
      end = s.find(delim, start);
    }
  }

  for (const Passport p : passports) {
    if (isValid(p, requiredFields)) {
      acc++;
    }
  }

  printf("%d\n", acc);
  return 0;
}
