#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int findPathTo(map<int, vector<int>>& graph, const int target) {
  int dif1 = 0, dif3 = 0;
  int cur = 0;
  while (cur != target) {
    int next = *min_element(graph[cur].begin(), graph[cur].end());
    if ((next - cur) == 1) dif1++;
    if ((next - cur) == 3) dif3++;
    cur = next;
  }
  return dif1 * dif3;
}

long helper(map<int, vector<int>>& graph, map<int, long>& mem, const int target, const int current) {
  if (current == target) return 1;
  auto it = mem.find(current);
  if (it != mem.end()) return it->second;
  long acc = 0;
  for (const auto& i : graph[current]) {
    acc += helper(graph, mem, target, i);
  }
  mem[current] = acc;
  return acc;
}

long numberOfPaths(map<int, vector<int>>& graph, const int target) {
  map<int, long> mem;
  return helper(graph, mem, target, 0);
}

int main(int argc, char const* argv[])
{
  vector<int> adaptors = { 0 };
  map<int, vector<int>> compatible;

  for (int i = 0; cin >> i; ) adaptors.push_back(i);
  sort(adaptors.begin(), adaptors.end()); // n log n

  int deviceRating = adaptors.back() + 3;
  adaptors.push_back(deviceRating);

  for (const int& i : adaptors) {
    for (int k = 1; k <= 3; k++) {
      auto it = compatible.find(i - k);
      if (it != compatible.end()) {
        it->second.push_back(i);
      }
    }
    compatible[i] = {};
  }

  cout << findPathTo(compatible, deviceRating) << endl;
  cout << numberOfPaths(compatible, deviceRating) << endl;
  return 0;
}
