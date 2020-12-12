#include <iostream>
#include <vector>
#include <string>

using namespace std;

int simulate(const vector<string>& instructions, const int initialDirection = 0) {
  int north = 0, east = 0, direction = initialDirection;
  for (const string& s : instructions) {
    char action = s[0];
    int value = stoi(s.substr(1));
    switch (action)
    {
    case 'L':
      direction -= value;
      direction %= 360;
      break;
    case 'R':
      direction += value;
      direction %= 360;
      break;
    case 'N':
      north += value;
      break;
    case 'S':
      north -= value;
      break;
    case 'E':
      east += value;
      break;
    case 'W':
      east -= value;
      break;
    case 'F':
      if (direction < 0) direction += 360; // normalize
      switch (direction)
      {
      case 0:
        north += value;
        break;
      case 90:
        east += value;
        break;
      case 180:
        north -= value;
        break;
      case 270:
        east -= value;
        break;
      default:
        cerr << "Unknown Direction Angle: " << direction << endl;
        exit(1);
      }
      break;
    default:
      cerr << "Unknown Action Code: " << action << endl;
      exit(1);
    }
  }
  return abs(north) + abs(east);
}

int simulateWaypoint(const vector<string>& instructions, int initialWaypointNorth, int initialWaypointEast) {
  int north = 0, east = 0;
  int waypointNorth = initialWaypointNorth, waypointEast = initialWaypointEast;
  for (const string& s : instructions) {
    char action = s[0];
    int value = stoi(s.substr(1));
    auto swap = [](int& a, int& b) {int tmp = a; a = b; b = tmp;};
    auto quadrant = [&waypointNorth, &waypointEast]() {
      if (waypointNorth > 0) return waypointEast > 0 ? 0 : 3;
      return waypointEast > 0 ? 1 : 2;
    };
    switch (action)
    {
    case 'L':
    case 'R':
    {
      int initialQuadrant = quadrant();
      int finalQuadrant = initialQuadrant + (action == 'R' ? (value / 90) : -1 * (value / 90));
      finalQuadrant %= 4;
      if (finalQuadrant < 0) finalQuadrant += 4;
      if (value == 90 || value == 270) swap(waypointNorth, waypointEast);
      switch (finalQuadrant)
      {
      case 0:
        waypointNorth = abs(waypointNorth);
        waypointEast = abs(waypointEast);
        break;
      case 1:
        waypointNorth = -1 * abs(waypointNorth);
        waypointEast = abs(waypointEast);
        break;
      case 2:
        waypointNorth = -1 * abs(waypointNorth);
        waypointEast = -1 * abs(waypointEast);
        break;
      case 3:
        waypointNorth = abs(waypointNorth);
        waypointEast = -1 * abs(waypointEast);
        break;
      default:
        cerr << "Unknown Quadrant: " << finalQuadrant << endl;
        exit(1);
      }
      break;
    }
    case 'N':
      waypointNorth += value;
      break;
    case 'S':
      waypointNorth -= value;
      break;
    case 'E':
      waypointEast += value;
      break;
    case 'W':
      waypointEast -= value;
      break;
    case 'F':
      north += value * waypointNorth;
      east += value * waypointEast;
      break;
    default:
      cerr << "Unknown Action Code: " << action << endl;
      exit(1);
    }
  }
  return abs(north) + abs(east);
}

int main(int argc, char const* argv[])
{
  vector<string> instructions;
  string s;
  while (cin >> s) instructions.push_back(s);
  cout << simulateWaypoint(instructions, 1, 10) << endl;
  return 0;
}
