#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

struct Node {
  int data;
  int time;
  char id;
  Node *next;
};

void insertSorted(Node *&head, int value, char id) {
  Node *n = head;
  Node *previous = nullptr;

  time_t now;
  while (n != nullptr && value <= n->data) {
    previous = n;
    n = n->next;
  }
  Node *v = new Node;
  v->data = value;
  v->id = id;
  v->time = now;
  v->next = n;

  if (previous == nullptr) {
    head = v;
    return;
  }

  previous->next = v;
}

void printList(Node *head) {
  Node *n = head;
  while (n->next != nullptr) {
    cout << "(" << n->id << ", " << n->data << ")" << " -> ";
    n = n->next;
  }
cout << "(" << n->id << ", " << n->data << ")" << endl;
}

void removeFirst(Node *&head) {
  Node *n = head;
  head = head->next;
  delete n;
}

int main() {
    Node *root = nullptr;
    insertSorted(root, 5, 'A');
    insertSorted(root, 10, 'B');
    insertSorted(root, 1, 'C');
    insertSorted(root, 12, 'D');
    insertSorted(root, 12, 'E');
    insertSorted(root, 12, 'F');
    printList(root);
    removeFirst(root);
    printList(root);
}
