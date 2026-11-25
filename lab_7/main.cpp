#include <algorithm>
#include <iostream>
#include <pstl/glue_algorithm_defs.h>

using namespace std;

struct Node {
  int value;
  Node *left;
  Node *right;
};

int height(Node *root) {
  if (root == nullptr)
    return 0;

  int leftHeight = height(root->left);
  int rightHeight = height(root->right);

  return 1 + max(leftHeight, rightHeight);
}

int getBalance(Node *root) {
  int leftHeight = height(root->left);
  int rightHeight = height(root->right);

  return leftHeight - rightHeight;
}

Node *rotatateLeft(Node *root) {
  if (!root || !root->right)
    return root;
  Node *x = root->right;
  Node *y = x->left;

  x->left = root;
  root->right = y;
  return x;
}

Node *rotatateRight(Node *root) {
  if (!root || !root->left)
    return root;
  Node *x = root->left;
  Node *y = x->right;

  x->right = root;
  root->left = y;
  return x;
}

void preorder(Node *root) {
  if (root == nullptr)
    return;
  cout << root->value << " ";
  preorder(root->left);
  preorder(root->right);
}

void insert(Node *&root, int value) {
  if (root == nullptr) {
    Node *newNode = new Node;
    newNode->value = value;
    root = newNode;
  } else if (value == root->value)
    return;
  else if (value < root->value) {
    if (root->left == nullptr) {
      Node *newNode = new Node;
      newNode->value = value;
      root->left = newNode;
    } else
      insert(root->left, value);
  } else {
    if (root->right == nullptr) {
      Node *newNode = new Node;
      newNode->value = value;
      root->right = newNode;
    } else
      insert(root->right, value);
  }

  int balance = getBalance(root);
  if (balance > 1) {
    root = rotatateRight(root);
  } else if (balance < -1) {
    root = rotatateLeft(root);
  }
}

bool contains(Node *root, int value) {
  if (root->value == value)
    return true;
  else if (value < root->value) {
    if (root->left == nullptr)
      return false;
    else
      return contains(root->left, value);
  } else if (value > root->value) {
    if (root->right == nullptr)
      return false;
    else
      return contains(root->right, value);
  }
  return false;
}

Node *findMin(Node *root) {
  if (root->left != nullptr)
    return findMin(root->left);
  return root;
}

Node *findMax(Node *root) {
  if (root->right != nullptr)
    return findMax(root->right);
  return root;
}

void inorder(Node *root) {
  if (root->left != nullptr)
    inorder(root->left);
  cout << root->value << " ";
  if (root->right != nullptr)
    inorder(root->right);
}
void postorder(Node *root) {
  if (root->left != nullptr)
    inorder(root->left);
  if (root->right != nullptr)
    inorder(root->right);
  cout << root->value << " ";
}

Node *remove(Node *root, int value) {
  if (root == nullptr)
    return nullptr;

  if (value < root->value) {
    root->left = remove(root->left, value);
  } else if (value > root->value) {
    root->right = remove(root->right, value);
  } else {
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      return nullptr;
    } else if (root->left == nullptr) {
      Node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      Node *temp = root->left;
      delete root;
      return temp;
    } else {
      Node *temp = findMin(root->right);
      root->value = temp->value;
      root->right = remove(root->right, temp->value);
    }
  }

  return root;
}

int main() {
  Node *root = nullptr;
  insert(root, 1);
  insert(root, 2);
  insert(root, 3);
  insert(root, 4);
  insert(root, 5);
  insert(root, 6);
  preorder(root);
  cout << endl;
  inorder(root);
  cout << endl;
  postorder(root);
  cout << endl;
  auto min = findMin(root);
  auto max = findMax(root);
  cout << min->value << endl;
  cout << max->value << endl;
  cout << height(root) << endl;
  cout << getBalance(root) << endl;
}
