#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

struct SortStats {
  long long int comparisons = 0;
  long long int swaps = 0;
};

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void bubbleSort(std::vector<int> &data, int n, SortStats &stats) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      stats.comparisons++;
      if (data[j] > data[j + 1]) {
        swap(data[j], data[j + 1]);
        stats.swaps++;
      }
    }
  }
}

void selectionSort(std::vector<int> &data, int n, SortStats &stats) {
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      stats.comparisons++;
      if (data[j] < data[minIndex])
        minIndex = j;
    }
    if (minIndex != i) {
      swap(data[i], data[minIndex]);
      stats.swaps++;
    }
  }
}

void insertionSort(std::vector<int> &data, int n, SortStats &stats) {
  for (int i = 1; i < n; i++) {
    int key = data[i];
    int j = i - 1;
    while (j >= 0 && data[j] > key) {
      stats.comparisons++;
      data[j + 1] = data[j];
      stats.swaps++;
      j--;
    }
    if (j >= 0) {
      stats.comparisons++;
    }
    data[j + 1] = key;
  }
}

void printArray(const std::vector<int> &data) {
  for (const auto &element : data) {
    std::cout << element << " ";
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
  std::vector<int> data = generateRandomArray(50000, 1, 100000);
  std::vector<int> data2(data);
  std::vector<int> data3(data);
  SortStats stats;
  SortStats stats2;
  SortStats stats3;

  std::cout << "Bubble sort" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  bubbleSort(data, data.size(), stats);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Duration: " << duration.count() << " ms" << std::endl;
  printStats(stats);

  std::cout << "Insert sort" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  insertionSort(data2, data2.size(), stats2);
  stop = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Duration: " << duration.count() << " ms" << std::endl;
  printStats(stats2);

  std::cout << "Selection sort" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  selectionSort(data3, data3.size(), stats3);
  stop = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Duration: " << duration.count() << " ms" << std::endl;
  printStats(stats3);
}
