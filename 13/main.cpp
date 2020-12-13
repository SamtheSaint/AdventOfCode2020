#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <utility>
#include <numeric>
#include <execution>
#include <algorithm>

#define delim ','

using namespace std;

long long earliestTime(const vector<pair<long long, long long>>& timestamps, const long long arrivalTime) {
  long long minWaitTime = INT64_MAX;
  long long minId = -1;
  for (const auto kv : timestamps) {
    long long id = kv.second;
    long long acc = id;
    while (acc < arrivalTime) acc += id;
    long long waitTime = acc - arrivalTime;
    if (waitTime < minWaitTime) {
      minId = id;
      minWaitTime = waitTime;
    }
  }
  return minId * minWaitTime;
}

long long continuousTimestamp(const vector<pair<long long, long long>>& timestamps) {
  long long value = 0;
  long long runningProduct = 1;
  for (const auto& kv : timestamps) {
    while ((value + kv.first) % kv.second != 0) value += runningProduct;
    runningProduct *= kv.second;
  }
  return value;
}

int main(int argc, char const* argv[])
{
  long long arrivalTime;
  cin >> arrivalTime;

  vector<pair<long long, long long>> timestamps;
  string s;
  cin >> s;

  size_t start = 0, end = s.find(delim);
  long long pos = 0;

  while (end != string::npos) {
    string cur = s.substr(start, end - start);
    if (cur != "x") {
      timestamps.push_back({ pos, stoll(cur) });
    }
    start = end + 1;
    end = s.find(delim, start);
    pos++;
  }

  // for (const auto& kv : timestamps) cout << kv.first << " " << kv.second << endl;

  cout << earliestTime(timestamps, arrivalTime) << endl;
  cout << continuousTimestamp(timestamps) << endl;

  return 0;
}
