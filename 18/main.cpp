// Copyright 2020 Samuel-Adekunle.Software
// Project: AdventOfCode2020
// Author: Samuel Adekunle
// Created: 18/12/2020, 08:46:36

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <cstdint>
#include <cassert>

#define openBracket '('
#define closeBracket ')'
#define add '+'
#define multiply '*'

bool isOperator(const char c) {
  return (c == add) || (c == multiply);
}

bool isOperand(const char c) {
  return (c >= '0') && (c <= '9');
}

int precedence(const char c) {
  // change precedence between part one and two
  if (c == multiply) return 1;
  if (c == add) return 2;
  return -1;
}

std::string infixToPostfix(const std::string& expression) {
  std::stringstream res;
  std::stringstream ss(expression);
  std::stack<char> operators;
  char c;
  while (ss >> c) {
    if (isOperand(c)) {
      res << c;
      continue;
    }
    if (isOperator(c)) {
      if (operators.empty() || (precedence(c) > precedence(operators.top()))) {
        operators.push(c);
        continue;
      }
      while (!operators.empty()
        && (operators.top() != openBracket)
        && precedence(operators.top()) >= precedence(c)) {
        res << operators.top();
        operators.pop();
      }
      operators.push(c);
      continue;
    }
    if (c == openBracket) {
      operators.push(c);
      continue;
    }
    if (c == closeBracket) {
      while (operators.top() != openBracket) {
        res << operators.top();
        operators.pop();
      }
      operators.pop();
      continue;  // discard openBracket
    }
  }
  while (!operators.empty()) {
    res << operators.top();
    operators.pop();
  }

  return res.str();
}

int64_t applyOperation(const char c, int64_t num1, int64_t num2) {
  assert(isOperator(c) && "Cannot apply unknown operator");
  if (c == add) return num1 + num2;
  if (c == multiply) return num1 * num2;
  assert(false && "Operator not implemented");
}

int64_t evalPostfix(const std::string& equation) {
  std::stack<int64_t> operands;
  std::stringstream ss(equation);
  int64_t acc = 0;
  char c;

  while (ss >> c) {
    if (isOperand(c)) {
      operands.push(c - '0');
      continue;
    }
    if (isOperator(c)) {
      int64_t num1 = operands.top();
      operands.pop();
      int64_t num2 = operands.top();
      operands.pop();
      int64_t res = applyOperation(c, num1, num2);
      operands.push(res);
    }
  }

  assert(operands.size() == 1);
  return operands.top();
}

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

int main(int argc, char const* argv[]) {
  std::vector<std::string> equations;
  std::string s;

  while (getline(std::cin, s)) {
    equations.push_back(infixToPostfix(s));
  }

  int64_t acc = 0;
  for (const std::string& equation : equations) {
    int64_t cur = evalPostfix(equation);
    // int64_t cur = evalPostfix(equation);
    acc += cur;
  }
  std::cout << acc << std::endl;
  return 0;
}
