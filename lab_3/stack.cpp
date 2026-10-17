#include "stack.hpp"

void push(Node *&top, int value) {
  Node *n = new Node;
  n->value = value;
  n->next = top;
  top = n;
}

bool pop(Node *&top) {
  if (top == nullptr) {
    return false;
  }
  Node *toDelete = top;
  top = top->next;
  delete toDelete;

  return true;
}

int peek(Node *top) {
  if (top == nullptr) {
    return -1;
  }
  return top->value;
}

bool isEmpty(Node *top) { return top == nullptr; }

int size(Node *top) {
  int size = 0;
  Node *n = top;
  while (n != nullptr) {
    size++;
    n = n->next;
  }
  return size;
}

void clear(Node *&top) {
  if (top == nullptr)
    return;
  if (top->next != nullptr) {
    clear(top->next);
  }
  delete top;
  top = nullptr;
}
