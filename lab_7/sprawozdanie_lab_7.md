# Laboratorium 7

## Drzewa binarne, drzewa BST i drzewa AVL

Kacper Łapka, gr. 4, ITE, nr albumu: 432177

## Zadanie 1

```cpp
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
```

Wynik:

```text
Preorder: 8 3 1 6 4 7 12 10 15
Inorder: 1 3 4 6 7 8 10 12 15
Postorder: 1 4 7 6 3 10 15 12 8
contains(6): 1
contains(10): 1
contains(15): 1
contains(5): 0
contains(100): 0
findMin: 1
findMax: 15
height: 4
```

## Zadanie 2

```cpp
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
```

Wynik:

```text
Drzewo A (1..10): height = 10, comparisons(10) = 10
Drzewo B (6 3 8 2 4 7 9 1 5 10): height = 4, comparisons(10) = 4
isBST(A): 1
isBST(B): 1
isBST(przyklad niepoprawny): 0
Po usunieciu liscia 4: 1 3 6 7 8 10 12 15 (isBST: 1)
Po usunieciu wezla z jednym dzieckiem 6: 1 3 7 8 10 12 15 (isBST: 1)
Po usunieciu wezla z dwoma dziecmi 3: 1 7 8 10 12 15 (isBST: 1)
```

### Odpowiedzi na pytania

1. Drzewa z tymi samymi wartościami mogą mieć różną wysokość, ponieważ o ich kształcie decyduje kolejność wstawiania elementów, a nie sam zbiór wartości.
2. Wstawianie danych rosnących lub malejących tworzy długą ścieżkę, natomiast wstawianie wartości w kolejności środkowej daje drzewo bardziej zrównoważone.
3. Koszt wyszukiwania jest proporcjonalny do wysokości drzewa, więc im większa wysokość, tym więcej porównań trzeba wykonać.
4. Pesymistyczna wysokość BST zawierającego n elementów wynosi n, gdy drzewo jest zdegenerowane do listy.
5. W takim przypadku złożoność wyszukiwania pogarsza się z O(log n) do O(n).

## Zadanie 3

```cpp
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
```

Wynik:

```text
Rotacje AVL:
LL (30 20 10): preorder = 20 10 30 | height = 2, balance = 0
RR (10 20 30): preorder = 20 10 30 | height = 2, balance = 0
LR (30 10 20): preorder = 20 10 30 | height = 2, balance = 0
RL (10 30 20): preorder = 20 10 30 | height = 2, balance = 0
```

Porównanie BST i AVL:

| n | dane | Wysokość BST | Wysokość AVL |
|---:|:---:|---:|---:|
| 10 | rosnące | 10 | 4 |
| 100 | rosnące | 100 | 7 |
| 1 000 | rosnące | 1 000 | 10 |
| 100 | losowe | 12 | 8 |
| 1 000 | losowe | 22 | 12 |

### Odpowiedzi na pytania

1. Zwykłe BST może ulec degeneracji, ponieważ przy wstawianiu posortowanych danych każdy nowy węzeł trafia jako dziecko poprzedniego, tworząc listę.
2. AVL nie przyjmuje takiego kształtu, ponieważ po każdym wstawieniu sprawdza współczynnik równowagi i wykonuje rotacje, utrzymując wysokość rzędu O(log n).
3. Rotacje zmieniają układ wskaźników w taki sposób, aby przywrócić warunek |BF| <= 1, nie zmieniając kolejności inorder.
4. Nie, rotacja zachowuje własność BST, ponieważ porządek inorder pozostaje taki sam.
5. Utrzymywanie równowagi wymaga przechowywania wysokości w węzłach oraz aktualizacji wysokości i wykonywania rotacji, co dodaje stały narzut do każdej operacji.
6. Warto ponosić ten koszt, ponieważ gwarantuje on wyszukiwanie, wstawianie i usuwanie w czasie O(log n) nawet w najgorszym przypadku.
7. W drzewie AVL oczekujemy złożoności wyszukiwania O(log n).
