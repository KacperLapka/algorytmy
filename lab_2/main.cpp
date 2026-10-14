#include <cstddef>
#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *next;
};

void pushFront(Node *&head, int value);
void printList(Node *head);
int size(Node *head);
void clear(Node *&head);

void pushBack(Node *&head, int value);
bool contains(Node *head, int value);
bool removeFirst(Node *&head, int value);
void insertSorted(Node *&head, int value);

void reverse(Node *&head);

void reverse(Node *&head) {
  Node *n = head;
  Node *previous = nullptr;
  Node *next = nullptr;

  while (n != nullptr) {
    next = n->next;
    n->next = previous;
    previous = n;
    n = next;
  }

  head = previous;
}

void insertSorted(Node *&head, int value) {
  Node *n = head;
  Node *previous = nullptr;

  while (n != nullptr && value > n->data) {
    previous = n;
    n = n->next;
  }

  Node *v = new Node;
  v->data = value;
  v->next = n;

  if (previous == nullptr) {
    head = v;
    return;
  }

  previous->next = v;
}

void pushFront(Node *&head, int value) {
  Node *n = new Node;
  n->data = value;
  n->next = head;
  head = n;
}

bool removeFirst(Node *&head, int value) {
  Node *n = head;
  Node *previous = nullptr;
  while (n != nullptr) {
    if (n->data == value) {
      if (previous == nullptr) {
        head = n->next;
      } else { 
        previous->next = n->next;
      }
      delete n;
      return true;
    }
    previous = n;
    n = n->next;
  }
  return false;
}

bool contains(Node *head, int value) {
  Node *n = head;
  while (n != nullptr) {
    if (n->data == value) {
      return true;
    }
    n = n->next;
  }
  return false;
}

void pushBack(Node *&head, int value) {
  Node *end = head;
  while (end->next != nullptr) {
    end = end->next;
  }

  Node *n = new Node;
  n->data = value;
  end->next = n;
}

void printList(Node *head) {
  Node *n = head;
  while (n->next != nullptr) {
    cout << n->data << " -> ";
    n = n->next;
  }
  cout << n->data << endl;
}

int size(Node *head) {
  Node *end = head;
  int count = 1;
  while (end->next != nullptr) {
    count++;
    end = end->next;
  }
  return count;
}

void clear(Node *&head) {
  if (head->next != nullptr) {
    clear(head->next);
  }
  delete head;
}

int main() {
  Node *head = nullptr;
    pushFront(head, 1);
    pushFront(head, 2);
    pushFront(head, 1);
    pushFront(head, 1);
    printList(head);
    reverse(head);
    printList(head);
  
  clear(head);
}
