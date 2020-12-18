// Copyright 2020 Samuel-Adekunle.Software
// Project: AdventOfCode2020
// Author: Samuel Adekunle
// Created: 18/12/2020, 08:46:36

#include <iostream>
#include <string>
#include <sstream>
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

#define openBracket '('
#define closeBracket ')'
#define add '+'
#define multiply '*'

int64_t eval(const std::string& equation) {
  std::stack<int64_t> operands;
  std::stack<char> operators;
  int64_t acc;
  std::stringstream ss(equation);
  char c;

  operands.push(0);
  operators.push(add);

  // Assumption that all numbers are positive single digit integers
  while (ss >> c) {
    if ((c == add)
      || (c == multiply)
      || (c == openBracket)) {
      operators.push(c);
      continue;
    }

    int64_t currentOperand = c - '0';
    char currentOperator = operators.top();
    operators.pop();

    if (c == closeBracket) {
      currentOperand = operands.top();
      operands.pop();
    }

    switch (currentOperator) {
    case add:
    {
      int64_t previousOperand = operands.top();
      operands.pop();
      operands.push(currentOperand + previousOperand);
      break;
    }
    case multiply:
    {
      int64_t previousOperand = operands.top();
      operands.pop();
      operands.push(currentOperand * previousOperand);
      break;
    }
    case openBracket:
    {
      operands.push(currentOperand);
      break;
    }
    }
  }
  return operands.top();
}

int main(int argc, char const* argv[])
{
  std::vector<std::string> equations;
  std::string s;

  while (getline(std::cin, s)) {
    equations.push_back(s);
  }

  int64_t acc = 0;
  for (const std::string& equation : equations) {
    int64_t cur = eval(equation);
    std::cout << cur << std::endl;
    acc += cur;
  }
  std::cout << acc << std::endl;

  // TODO(SamtheSant) - implement full infix to postfix for part two
  return 0;
}
