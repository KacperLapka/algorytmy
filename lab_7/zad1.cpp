#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
  int value;
  Node *left;
  Node *right;
};

Node *createNode(int value) {
  Node *node = new Node;
  node->value = value;
  node->left = nullptr;
  node->right = nullptr;
  return node;
}

void insert(Node *&root, int value) {
  if (root == nullptr) {
    root = createNode(value);
    return;
  }
  if (value == root->value)
    return;
  if (value < root->value)
    insert(root->left, value);
  else
    insert(root->right, value);
}

bool contains(Node *root, int value) {
  if (root == nullptr)
    return false;
  if (root->value == value)
    return true;
  if (value < root->value)
    return contains(root->left, value);
  return contains(root->right, value);
}

Node *findMin(Node *root) {
  while (root != nullptr && root->left != nullptr)
    root = root->left;
  return root;
}

Node *findMax(Node *root) {
  while (root != nullptr && root->right != nullptr)
    root = root->right;
  return root;
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

void postorder(Node *root) {
  if (root == nullptr)
    return;
  postorder(root->left);
  postorder(root->right);
  cout << root->value << " ";
}

int height(Node *root) {
  if (root == nullptr)
    return 0;
  return 1 + max(height(root->left), height(root->right));
}

int main() {
  Node *root = nullptr;
  int values[] = {8, 3, 12, 1, 6, 10, 15, 4, 7};
  for (int value : values)
    insert(root, value);

  cout << "Preorder: ";
  preorder(root);
  cout << endl;

  cout << "Inorder: ";
  inorder(root);
  cout << endl;

  cout << "Postorder: ";
  postorder(root);
  cout << endl;

  cout << "contains(6): " << contains(root, 6) << endl;
  cout << "contains(10): " << contains(root, 10) << endl;
  cout << "contains(15): " << contains(root, 15) << endl;
  cout << "contains(5): " << contains(root, 5) << endl;
  cout << "contains(100): " << contains(root, 100) << endl;

  cout << "findMin: " << findMin(root)->value << endl;
  cout << "findMax: " << findMax(root)->value << endl;
  cout << "height: " << height(root) << endl;

  return 0;
}
