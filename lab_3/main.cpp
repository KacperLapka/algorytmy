#include "queue.hpp"
#include "stack.hpp"
#include <iostream>
#include <string>

const char ALLOWED_OPENING_BRACKETS[] = {'{', '(', '['};
const char ALLOWED_CLOSING_BRACKETS[] = {'}', ')', ']'};

bool validateBrackets(std::string &input) {
  Node *head = nullptr;
  for (auto &c : input) {
    for (int i = 0; i < 3; i++) {
      if (ALLOWED_OPENING_BRACKETS[i] == c) {
        push(head, c);
      } else if (ALLOWED_CLOSING_BRACKETS[i] == c) {
        if (peek(head) == ALLOWED_OPENING_BRACKETS[i])
          pop(head);
        else {
          clear(head);
          return false;
        }
      }
    }
  }

  bool result = isEmpty(head);
  clear(head);
  return result;
}

bool getValues(int *a, int *b, Node *&top) {
  if (isEmpty(top))
    return false;
  *b = peek(top);
  pop(top);
  if (isEmpty(top))
    return false;
  *a = peek(top);
  pop(top);
  return true;
}

int solveONP(std::string &input) {
  Node *top = nullptr;
  int a, b, parsed;
  bool space = true;
  for (auto &c : input) {
    if (c == ' ') {
      space = true;
      continue;
    }

    if (c == '+') {
      if (!getValues(&a, &b, top))
        return -1;

      push(top, a + b);
      continue;
    }
    if (c == '-') {
      if (!getValues(&a, &b, top))
        return -1;

      push(top, a - b);
      continue;
    }
    if (c == '*') {
      if (!getValues(&a, &b, top))
        return -1;

      push(top, a * b);
      continue;
    }
    if (c == '/') {
      if (!getValues(&a, &b, top))
        return -1;

      push(top, a / b);
      continue;
    }

    parsed = c - '0';
    if (parsed >= 0 && parsed < 10) {
      if (!space) {
        parsed += peek(top) * 10;
        pop(top);
      }

      push(top, parsed);
      space = false;
    }
  }

  if (size(top) != 1) {
    return -1;
  }
  return peek(top);
}

int main() {
  Node *front = nullptr;
  Node *back = nullptr;
  enqueue(front, back, 5);
  std::cout << getFront(front) << std::endl;
  enqueue(front, back, 6);
  std::cout << getFront(front) << std::endl;
  dequeue(front, back);
  std::cout << getFront(front) << std::endl;
  std::cout << size(front) << std::endl;
}
