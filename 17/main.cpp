#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <regex>
#include <ranges>
#include <cmath>
#include <random>
#include <algorithm>
#include <utility>

using namespace std;

#define active '#'
#define inactive '.'

typedef vector<vector<vector<char>>> World;

// used for debugging
bool inRange(const World& world, const int z, const int x, const int y) {
  return z >= 0 && y >= 0 && x >= 0
    && z < world.size() && x < world[0].size() && y < world[0][0].size();
}

void printWorld(const World& world) {
  for (const auto& slice : world) {
    for (const auto& row : slice) {
      for (const char c : row) {
        cout << c << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}

int countActiveCells(const World& world) {
  int acc = 0;
  for (const auto& slice : world) {
    for (const auto& row : slice) {
      for (const char c : row) {
        if (c == active) acc++;
      }
    }
  }
  return acc;
}

int countActiveNeighbours(const World& world, const int z, const int x, const int y) {
  int neighbours = 0;
  // check neighbours and count active ones
  for (int dz = -1; dz <= 1; dz++) {
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        if (inRange(world, z + dz, x + dx, y + dy)) {
          if (world[z + dz][x + dx][y + dy] == active) {
            if ((dx == 0) && (dy == 0) && (dz == 0)) neighbours += 0;
            else { neighbours += 1; }
          }
        }
      }
    }
  }
  return neighbours;
}

// cell will change
bool conwayRules(const World& world, const int z, const int x, const int y) {
  const char cur = world[z][x][y];
  int activeNeighbours = countActiveNeighbours(world, z, x, y);
  if (cur == active && (activeNeighbours < 2 || activeNeighbours > 3)) return true;
  if (cur == inactive && activeNeighbours == 3) return true;
  return false;
}

// Conway's game of life
void simulate(World& world) {
  const int z = world.size(), x = world[0].size(), y = world[0][0].size();
  // increase size
  World newWorld = World(z + 2);
  vector<vector<char>> newSlice = vector<vector<char>>(x + 2);
  vector<char> newRow = vector<char>(y + 2, inactive);

  for (int i = 0; i < x + 2; i++) newSlice[i] = newRow;
  for (int i = 0; i < z + 2; i++) newWorld[i] = newSlice;

  for (int _z = 0; _z < z; _z++) {
    for (int _x = 0; _x < x; _x++) {
      for (int _y = 0; _y < y; _y++) {
        newWorld[_z + 1][_x + 1][_y + 1] = world[_z][_x][_y];
      }
    }
  }

  // printWorld(newWorld);

  // for (int _z = 0; _z < z + 2; _z++) {
  //   for (int _x = 0; _x < x + 2; _x++) {
  //     for (int _y = 0; _y < y + 2; _y++) {
  //       cout << countActiveNeighbours(newWorld, _z, _x, _y) << " ";
  //     }
  //     cout << endl;
  //   }
  //   cout << endl;
  // }

  unordered_map<int, unordered_map<int, unordered_map<int, bool>>> willChange;

  // check all directions for every element we placed in newWorld
  // because of +1 padding don't need to check in range
  // however function inRange exists so nothing goes wrong
  for (int _z = 0; _z < z + 2; _z++) {
    for (int _x = 0; _x < x + 2; _x++) {
      for (int _y = 0; _y < y + 2; _y++) {
        willChange[_z][_x][_y] = conwayRules(newWorld, _z, _x, _y);
      }
    }
  }


  // change all should change elements
  for (const auto& zplane : willChange) {
    int _z = zplane.first;
    for (const auto& xplane : zplane.second) {
      int _x = xplane.first;
      for (const auto& yplane : xplane.second) {
        int _y = yplane.first;
        const char cur = newWorld[_z][_x][_y];
        if (yplane.second) newWorld[_z][_x][_y] = (cur == active) ? inactive : active;
      }
    }
  }

  world = newWorld;
}

int main(int argc, char const* argv[])
{
  World world;
  vector<vector<char>> slice;
  vector<char> row;
  string s;

  while (getline(cin, s)) {
    row.clear();
    for (const char c : s) {
      row.push_back(c);
    }
    slice.push_back(row);
  }
  world.push_back(slice);

  const int numCycles = 6;
  // printWorld(world);
  for (int i = 0; i < numCycles; i++) {
    simulate(world);
    cout << "Cycle " << i + 1 << ": Active: " << countActiveCells(world) << endl;
    printWorld(world);
  }
  return 0;
}
