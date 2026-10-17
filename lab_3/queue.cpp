#include "queue.hpp"
#include "stack.hpp"

void enqueue(Node *&front, Node *&back, int value) {
  Node *n = new Node;
  n->value = value;

  if (front == nullptr) {
    front = n;
    back = n;
  } else {
    back->next = n;
    back = n;
  }
}

bool dequeue(Node *&front, Node *&back) {
  if (front == nullptr)
    return false;

  Node *toDelete = front;
  front = front->next;
  if (back == toDelete)
    back = nullptr;
  delete toDelete;
  return true;
}

int getFront(Node *front) {
  if (isEmpty(front))
    return -1;
  return front->value;
}

void clear(Node *&front, Node *&back) {
  clear(back);
  front = nullptr;
}
