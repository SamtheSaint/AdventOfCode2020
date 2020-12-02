#include <string>
#include <iostream>

using namespace std;

struct InputData {
  int lower;
  int upper;
  char target;
  string password;

  InputData(int _lower, int _upper, char _target, string _password) {
    lower = _lower;
    upper = _upper;
    target = _target;
    password = _password;
  }
};

bool isValidPartOne(const InputData data) {
  int count = 0;
  for (const char x : data.password) {
    if (x == data.target) count++;
  }
  if (count >= data.lower && count <= data.upper) return true;
  return false;
}

bool isValid(const InputData data) {
  char pos1 = data.password[data.lower - 1], pos2 = data.password[data.upper - 1];

  if (!(pos1 == data.target) != !(pos2 == data.target)) return true;
  return false;
}

int main(int argc, char const* argv[])
{
  int numValid = 0;

  int _lower, _upper;
  char _target;
  string _password;

  char dash = '-';
  char colon = ':';

  while (cin >> _lower >> dash >> _upper >> _target >> colon >> _password)
    if (isValid(InputData(_lower, _upper, _target, _password))) numValid++;

  cout << numValid << endl;
  return 0;
}