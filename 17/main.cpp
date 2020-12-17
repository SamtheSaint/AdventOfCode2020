#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <random>
#include <algorithm>
#include <utility>

using namespace std;

#define active '#'
#define inactive '.'

typedef vector<vector<vector<vector<char>>>> World;

// used for debugging
bool inRange(const World& world,
  const int w, const int z, const int x, const int y) {
  return w >= 0 && z >= 0 && y >= 0 && x >= 0
    && w < world.size() && z < world[0].size()
    && x < world[0][0].size() && y < world[0][0][0].size();
}

void printWorld(const World& world) {
  for (const auto& slice3 : world) {
    for (const auto& slice2 : slice3) {
      for (const auto& slice1 : slice2) {
        for (const char c : slice1) {
          cout << c << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
    cout << endl;
  }
}

int countActiveCells(const World& world) {
  int acc = 0;
  for (const auto& slice3 : world) {
    for (const auto& slice2 : slice3) {
      for (const auto& slice1 : slice2) {
        for (const char c : slice1) {
          if (c == active) acc++;
        }
      }
    }
  }
  return acc;
}

int countActiveNeighbours(const World& world,
  const int w, const int z, const int x, const int y) {
  int neighbours = 0;
  // check neighbours and count active ones
  for (int dw = -1; dw <= 1; dw++) {
    for (int dz = -1; dz <= 1; dz++) {
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          if ((dx == 0) && (dy == 0) && (dz == 0) && (dw == 0)) continue;
          if (!inRange(world, w + dw, z + dz, x + dx, y + dy)) continue;
          if (world[w + dw][z + dz][x + dx][y + dy] == active) neighbours++;
        }
      }
    }
  }

  return neighbours;
}

// cell will change
bool conwayRules(const World& world, const int w, const int z, const int x, const int y) {
  const char cur = world[w][z][x][y];
  int activeNeighbours = countActiveNeighbours(world, w, z, x, y);
  if (cur == active && (activeNeighbours < 2 || activeNeighbours > 3)) return true;
  if (cur == inactive && activeNeighbours == 3) return true;
  return false;
}

// Conway's game of life
World simulate(const World& world) {
  const int w = world.size(),
    z = world[0].size(),
    x = world[0][0].size(),
    y = world[0][0][0].size();
  // increase size
  World newWorld = World(w + 2);
  vector<vector<vector<char>>> newSlice3 = vector<vector<vector<char>>>(z + 2);
  vector<vector<char>> newSlice2 = vector<vector<char>>(x + 2);
  vector<char> newSlice1 = vector<char>(y + 2, inactive);

  for (int i = 0; i < x + 2; i++) newSlice2[i] = newSlice1;
  for (int i = 0; i < z + 2; i++) newSlice3[i] = newSlice2;
  for (int i = 0; i < w + 2; i++) newWorld[i] = newSlice3;

  for (int _w = 0; _w < w; _w++) {
    for (int _z = 0; _z < z; _z++) {
      for (int _x = 0; _x < x; _x++) {
        for (int _y = 0; _y < y; _y++) {
          newWorld[_w + 1][_z + 1][_x + 1][_y + 1] = world[_w][_z][_x][_y];
        }
      }
    }
  }


  // printWorld(newWorld);
  // exit(1);

  // for (int _z = 0; _z < z + 2; _z++) {
  //   for (int _x = 0; _x < x + 2; _x++) {
  //     for (int _y = 0; _y < y + 2; _y++) {
  //       cout << countActiveNeighbours(newWorld, _z, _x, _y) << " ";
  //     }
  //     cout << endl;
  //   }
  //   cout << endl;
  // }

  unordered_map<int,
    unordered_map<int,
    unordered_map<int,
    unordered_map<int, bool>>>> willChange;

  // check all directions for every element we placed in newWorld
  // because of +1 padding don't need to check in range
  // however function inRange exists so nothing goes wrong
  for (int _w = 0; _w < w + 2; _w++) {
    for (int _z = 0; _z < z + 2; _z++) {
      for (int _x = 0; _x < x + 2; _x++) {
        for (int _y = 0; _y < y + 2; _y++) {
          willChange[_w][_z][_x][_y] = conwayRules(newWorld, _w, _z, _x, _y);
        }
      }
    }
  }

  // change all should change elements
  for (const auto& wplane : willChange) {
    int _w = wplane.first;
    for (const auto& zplane : wplane.second) {
      int _z = zplane.first;
      for (const auto& xplane : zplane.second) {
        int _x = xplane.first;
        for (const auto& yplane : xplane.second) {
          int _y = yplane.first;
          const char cur = newWorld[_w][_z][_x][_y];
          if (yplane.second) newWorld[_w][_z][_x][_y] = (cur == active) ? inactive : active;
        }
      }
    }
  }

  return newWorld;
}

int main(int argc, char const* argv[])
{
  World world;
  vector<vector<vector<char>>> slice3;
  vector<vector<char>> slice2;
  vector<char> slice1;
  string s;

  while (getline(cin, s)) {
    slice1.clear();
    for (const char c : s) {
      slice1.push_back(c);
    }
    slice2.push_back(slice1);
  }
  slice3.push_back(slice2);
  world.push_back(slice3);

  const int numCycles = 6;
  // printWorld(world);
  for (int i = 0; i < numCycles; i++) {
    world = simulate(world);
    cout << "Cycle " << i + 1 << ": Active: "
      << countActiveCells(world) << endl;
    // printWorld(world);
  }
  return 0;
}
