#pragma once
struct Node {
  int value;
  Node *next;
};

void push(Node *&top, int value);
bool pop(Node *&top);
int peek(Node *top);
bool isEmpty(Node *top);
int size(Node *top);
void clear(Node *&top);
