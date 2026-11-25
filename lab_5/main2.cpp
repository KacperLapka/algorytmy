#include <vector>
#include <iostream>
#include <algorithm>

struct SortStats {
  long long int comparisons = 0;
  long long int swaps = 0;
};

struct Record {
  int key;
  char id;
};


void swap(Record &a, Record &b) {
  Record temp = a;
  a = b;
  b = temp;
}

void bubbleSort(std::vector<Record> &data, int n, SortStats &stats) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      stats.comparisons++;
      if (data[j].key > data[j + 1].key) {
        swap(data[j], data[j + 1]);
        stats.swaps++;
      }
    }
  }
}

void selection_sort(int n, std::vector<Record> &t)
{
   int i, j, k;
   for(i=0; i<n; i++) {
      k=i;
      for(j=i+1; j<n; j++) if(t[j].key<t[k].key) k=j;
      swap(t[k], t[i]);
   }
}

void selectionSort(std::vector<Record> &data, int n, SortStats &stats) {
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      stats.comparisons++;
      if (data[j].key < data[minIndex].key)
        minIndex = j;
    }
    if (minIndex != i) {
      swap(data[i], data[minIndex]);
      stats.swaps++;
    }
  }
}

void insertionSort(std::vector<Record> &data, int n, SortStats &stats) {
  for (int i = 1; i < n; i++) {
    Record key = data[i];
    int j = i - 1;
    while (j >= 0 && data[j].key > key.key) {
      stats.comparisons++;
      data[j + 1] = data[j];
      stats.swaps++;
      j--;
    }
    data[j + 1] = key;
  }
}

void printArray(const std::vector<Record> &data) {
  for (const auto &element : data) {
    std::cout << "(" << element.key << ", " << element.id << ")" << " ";
  }
  std::cout << std::endl;
}

std::vector<int> generateRandomArray(int size, int minValue, int maxValue) {
  std::vector<int> data(size);
  for (int i = 0; i < size; i++) {
    data[i] = minValue + rand() % (maxValue - minValue + 1);
  }
  return data;
}

void reverseArray(std::vector<int> &data) {
  std::reverse(data.begin(), data.end());
}

void printStats(SortStats stats) {
  std::cout << "Comparisons: " << stats.comparisons << "  ";
  std::cout << "Swaps: " << stats.swaps << std::endl;
}

int main() {
  std::vector<Record> data = { {3, 'A'}, {1, 'B'}, {3, 'C'}, {2, 'D'}, {1, 'E'}, {3, 'F'} };
  SortStats sort;
  printArray(data);
  //selectionSort(data, data.size(), sort);
  selectionSort(data, data.size(), sort);
  printArray(data);
}
