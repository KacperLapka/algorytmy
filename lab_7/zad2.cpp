#include <algorithm>
#include <climits>
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

Node *findMin(Node *root) {
  while (root != nullptr && root->left != nullptr)
    root = root->left;
  return root;
}

Node *remove(Node *root, int value) {
  if (root == nullptr)
    return nullptr;

  if (value < root->value) {
    root->left = remove(root->left, value);
  } else if (value > root->value) {
    root->right = remove(root->right, value);
  } else {
    if (root->left == nullptr) {
      Node *temp = root->right;
      delete root;
      return temp;
    }
    if (root->right == nullptr) {
      Node *temp = root->left;
      delete root;
      return temp;
    }

    Node *successor = findMin(root->right);
    root->value = successor->value;
    root->right = remove(root->right, successor->value);
  }

  return root;
}

bool isBST(Node *root, long long minValue, long long maxValue) {
  if (root == nullptr)
    return true;
  if (root->value <= minValue || root->value >= maxValue)
    return false;
  return isBST(root->left, minValue, root->value) &&
         isBST(root->right, root->value, maxValue);
}

bool isBST(Node *root) {
  return isBST(root, LLONG_MIN, LLONG_MAX);
}

int countComparisons(Node *root, int value) {
  int comparisons = 0;
  while (root != nullptr) {
    comparisons++;
    if (value == root->value)
      break;
    if (value < root->value)
      root = root->left;
    else
      root = root->right;
  }
  return comparisons;
}

void inorder(Node *root) {
  if (root == nullptr)
    return;
  inorder(root->left);
  cout << root->value << " ";
  inorder(root->right);
}

int height(Node *root) {
  if (root == nullptr)
    return 0;
  return 1 + max(height(root->left), height(root->right));
}

Node *buildBST(const int values[], int size) {
  Node *root = nullptr;
  for (int i = 0; i < size; i++)
    insert(root, values[i]);
  return root;
}

int main() {
  int ascending[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int balanced[] = {6, 3, 8, 2, 4, 7, 9, 1, 5, 10};

  Node *treeA = buildBST(ascending, 10);
  Node *treeB = buildBST(balanced, 10);

  cout << "Drzewo A (1..10): height = " << height(treeA)
       << ", comparisons(10) = " << countComparisons(treeA, 10) << endl;
  cout << "Drzewo B (6 3 8 2 4 7 9 1 5 10): height = " << height(treeB)
       << ", comparisons(10) = " << countComparisons(treeB, 10) << endl;
  cout << "isBST(A): " << isBST(treeA) << endl;
  cout << "isBST(B): " << isBST(treeB) << endl;

  Node *invalid = createNode(10);
  invalid->left = createNode(5);
  invalid->right = createNode(15);
  invalid->right->left = createNode(6);
  cout << "isBST(przyklad niepoprawny): " << isBST(invalid) << endl;

  int sample[] = {8, 3, 12, 1, 6, 10, 15, 4, 7};
  Node *tree = buildBST(sample, 9);

  remove(tree, 4);
  cout << "Po usunieciu liscia 4: ";
  inorder(tree);
  cout << "(isBST: " << isBST(tree) << ")" << endl;

  remove(tree, 6);
  cout << "Po usunieciu wezla z jednym dzieckiem 6: ";
  inorder(tree);
  cout << "(isBST: " << isBST(tree) << ")" << endl;

  remove(tree, 3);
  cout << "Po usunieciu wezla z dwoma dziecmi 3: ";
  inorder(tree);
  cout << "(isBST: " << isBST(tree) << ")" << endl;

  return 0;
}
