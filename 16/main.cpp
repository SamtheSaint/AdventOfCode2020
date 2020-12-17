#include <unordered_map>
#include <utility>
#include <iostream>
#include <regex>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <queue>

using namespace std;

typedef vector<int> Ticket;
typedef unordered_map<string, vector<pair<int, int>>> Fields;
#define delimiter ','

Ticket parseTicket(const string& s) {
  Ticket newTicket;
  for (size_t start = 0, end = 0; end != string::npos; start = end + 1) {
    end = s.find(delimiter, start);
    newTicket.push_back(stoi(s.substr(start, end - start)));
    start = end + 1;
  }
  return newTicket;
}

bool inRange(const pair<int, int>& range, const int val) {
  return (val >= range.first) && (val <= range.second);
}

vector<Ticket> validate(const Fields& fields, const vector<Ticket>& tickets) {
  bool canBeValid;
  bool isValid;
  vector<Ticket> validTickets;
  for (const Ticket& ticket : tickets) {
    isValid = true;
    for (const int i : ticket) {
      canBeValid = false;
      for (const auto& kv : fields) {
        for (const auto& fs : kv.second) {
          if (inRange(fs, i)) canBeValid = true;
          if (canBeValid) break;
        }
        if (canBeValid) break; // don't need to check the other fields
      }
      if (!canBeValid) isValid = false;
      if (!isValid) break;
    }
    if (isValid) validTickets.push_back(ticket);
  }
  return validTickets;
}

void discoverFields(const vector<Ticket>& tickets, const Fields& fields) {
  unordered_map<string, int> fieldIndex;
  unordered_map<string, int> mem;
  unordered_map<int, unordered_map<string, int>> memi;

  int N = tickets[0].size();
  for (int i = 0; i < N; i++) {
    mem.clear();
    for (const auto& kv : fields) {
      const string& curField = kv.first;
      for (const Ticket& ticket : tickets) {
        if (inRange(kv.second[0], ticket[i]) || inRange(kv.second[1], ticket[i])) {
          // i column is valid for curField for a particular field
          mem[curField]++;
        }
      }
    }
    for (const auto& kv : mem) {
      if (kv.second == tickets.size())
      {
        memi[i][kv.first] = kv.second;
      }
    }
  }
  string cs;
  while (memi.size() > 0) {
    for (const auto& kv : memi) {
      if (kv.second.size() == 1) {
        cs = kv.second.begin()->first;
        fieldIndex[cs] = kv.first;


        cout << kv.first << ": " << cs << endl;

        memi.erase(kv.first);
        break;
      }
    }

    for (auto& kv : memi) {
      kv.second.erase(cs);
    }
  }
}

int main(int argc, char const* argv[])
{
  regex re = regex("([a-z\\s]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");

  string s;
  smatch m;
  Fields fields;

  Ticket myTicket;
  vector<Ticket> tickets;

  int state = 0;
  while (getline(cin, s)) {
    if (s.empty() || state == 1 || state == 3) { state++; continue; }
    if (state == 0 && regex_match(s, m, re)) {
      fields[m[1].str()] = {
        {stoi(m[2].str()), stoi(m[3].str())},
        {stoi(m[4].str()), stoi(m[5].str())}
      };
    }
    if (state == 2) {
      myTicket = parseTicket(s);
    }
    if (state == 4) {
      tickets.push_back(parseTicket(s));
    }
  }

  vector<Ticket> valid = validate(fields, tickets);
  discoverFields(valid, fields);

  vector<int> dept = { 0,    10,    5,    4,    12,    3 };
  long long acc = 1;
  for (const int i : dept) acc *= (long long)myTicket[i];
  cout << acc << endl;
  return 0;
}
