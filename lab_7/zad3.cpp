#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

struct Node {
  int value;
  Node *left;
  Node *right;
  int height;
};

int getHeight(Node *node) {
  return node == nullptr ? 0 : node->height;
}

int getBalance(Node *node) {
  return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node *node) {
  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

Node *createNode(int value) {
  Node *node = new Node;
  node->value = value;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 1;
  return node;
}

Node *rotateRight(Node *root) {
  Node *x = root->left;
  Node *y = x->right;

  x->right = root;
  root->left = y;

  updateHeight(root);
  updateHeight(x);
  return x;
}

Node *rotateLeft(Node *root) {
  Node *x = root->right;
  Node *y = x->left;

  x->left = root;
  root->right = y;

  updateHeight(root);
  updateHeight(x);
  return x;
}

Node *insert(Node *root, int value) {
  if (root == nullptr)
    return createNode(value);

  if (value < root->value)
    root->left = insert(root->left, value);
  else if (value > root->value)
    root->right = insert(root->right, value);
  else
    return root;

  updateHeight(root);
  int balance = getBalance(root);

  if (balance > 1 && value < root->left->value)
    return rotateRight(root);

  if (balance < -1 && value > root->right->value)
    return rotateLeft(root);

  if (balance > 1 && value > root->left->value) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }

  if (balance < -1 && value < root->right->value) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }

  return root;
}

Node *insertBST(Node *root, int value) {
  if (root == nullptr)
    return createNode(value);

  if (value < root->value)
    root->left = insertBST(root->left, value);
  else if (value > root->value)
    root->right = insertBST(root->right, value);

  return root;
}

int height(Node *root) {
  if (root == nullptr)
    return 0;
  return 1 + max(height(root->left), height(root->right));
}

void preorder(Node *root) {
  if (root == nullptr)
    return;
  cout << root->value << " ";
  preorder(root->left);
  preorder(root->right);
}

void inorder(Node *root) {
  if (root == nullptr)
    return;
  inorder(root->left);
  cout << root->value << " ";
  inorder(root->right);
}

void rotationCase(const char *name, int a, int b, int c) {
  Node *root = nullptr;
  root = insert(root, a);
  root = insert(root, b);
  root = insert(root, c);

  cout << name << ": preorder = ";
  preorder(root);
  cout << "| height = " << getHeight(root)
       << ", balance = " << getBalance(root) << endl;
}

void printRow(int n, const char *type, const vector<int> &data) {
  Node *bst = nullptr;
  Node *avl = nullptr;

  for (int value : data) {
    bst = insertBST(bst, value);
    avl = insert(avl, value);
  }

  cout << n << "\t" << type << "\t" << height(bst) << "\t" << getHeight(avl)
       << endl;
}

vector<int> ascendingData(int n) {
  vector<int> data(n);
  iota(data.begin(), data.end(), 1);
  return data;
}

vector<int> randomData(int n, unsigned seed) {
  vector<int> data = ascendingData(n);
  mt19937 generator(seed);
  shuffle(data.begin(), data.end(), generator);
  return data;
}

int main() {
  cout << "Rotacje AVL:" << endl;
  rotationCase("LL (30 20 10)", 30, 20, 10);
  rotationCase("RR (10 20 30)", 10, 20, 30);
  rotationCase("LR (30 10 20)", 30, 10, 20);
  rotationCase("RL (10 30 20)", 10, 30, 20);

  cout << endl;
  cout << "Porownanie BST i AVL:" << endl;
  cout << "n\tdane\tBST\tAVL" << endl;
  printRow(10, "rosnace", ascendingData(10));
  printRow(100, "rosnace", ascendingData(100));
  printRow(1000, "rosnace", ascendingData(1000));
  printRow(100, "losowe", randomData(100, 42));
  printRow(1000, "losowe", randomData(1000, 42));

  return 0;
}
