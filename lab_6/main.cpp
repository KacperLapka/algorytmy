// Laboratorium 6 — kompilacja:
// g++ -O2 -std=c++17 -DZAD1 main.cpp -o zad1
// g++ -O2 -std=c++17 -DZAD2 main.cpp -o zad2
// g++ -O2 -std=c++17 -DZAD3 main.cpp -o zad3
// g++ -O2 -std=c++17 -DZAD4 main.cpp -o zad4

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <string>
#include <utility>

#define USE_RANDOM_PIVOT 1

using namespace std;

std::random_device rd;
std::mt19937 gen(rd());

void printArray(const std::vector<int> &data);

void merge(vector<int> &data, int left, int mid, int right) {
  vector<int> leftPart(data.begin() + left, data.begin() + mid);
  vector<int> rightPart(data.begin() + mid, data.begin() + right);
  int i = 0;
  int j = 0;
  int k = left;

  for (const auto &element : leftPart) {
    std::cout << element << " ";
  }
  std::cout << "| ";
  for (const auto &element : rightPart) {
    std::cout << element << " ";
  }
  std::cout << std::endl;

  while (i < leftPart.size() && j < rightPart.size()) {
    if (leftPart[i] <= rightPart[j]) {
      data[k++] = leftPart[i++];
    } else {
      data[k++] = rightPart[j++];
    }
  }

  while (i < leftPart.size()) {
    data[k++] = leftPart[i++];
  }

  while (j < rightPart.size()) {
    data[k++] = rightPart[j++];
  }
}

void mergeSort(vector<int> &data, int left, int right) {
  if (right - left <= 1) {
    return;
  }

  int mid = left + (right - left) / 2;
  mergeSort(data, left, mid);
  mergeSort(data, mid, right);
  merge(data, left, mid, right);
}

void printArray(const std::vector<int> &data) {
  for (const auto &element : data) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

int partition(vector<int> &data, int left, int right) {
#if USE_RANDOM_PIVOT
  std::uniform_int_distribution<> dis(left, right - 1);
  int randomIndex = dis(gen);
  swap(data[randomIndex], data[right - 1]);
#endif
  int pivot = data[right - 1];
  int i = left;

  for (int j = left; j < right - 1; ++j) {
    if (data[j] <= pivot) {
      swap(data[i], data[j]);
      ++i;
    }
  }
  swap(data[i], data[right - 1]);
  return i;
}

void quickSort(vector<int> &data, int left, int right) {
  if (left < right) {
    int pivotIndex = partition(data, left, right);
    quickSort(data, left, pivotIndex);
    quickSort(data, pivotIndex + 1, right);
  }
}

int mergeSelect(vector<int> &data, int left, int right, int k) {
  mergeSort(data, left, right);
  return data[k - 1];
}

int quickSelect(vector<int> &data, int left, int right, int k) {
  if (left < right) {
    int pivotIndex = partition(data, left, right);
    if (pivotIndex == k - 1) {
      return data[pivotIndex];
    } else if (pivotIndex > k - 1) {
      return quickSelect(data, left, pivotIndex, k);
    } else {
      return quickSelect(data, pivotIndex + 1, right, k);
    }
  }
  return -1;
}

void insertionSort(std::vector<int> &data, int n) {
  for (int i = 1; i < n; i++) {
    int key = data[i];
    int j = i - 1;
    while (j >= 0 && data[j] > key) {
      data[j + 1] = data[j];
      j--;
    }
    data[j + 1] = key;
  }
}

std::vector<int> generateRandomArray(int size, int minValue, int maxValue) {
  std::vector<int> data(size);
  for (int i = 0; i < size; i++) {
    data[i] = minValue + rand() % (maxValue - minValue + 1);
  }
  return data;
}

namespace zad1 {
bool trace = false;

void printArray(const vector<int> &data) {
  if (data.empty()) {
    cout << "(pusta)";
    return;
  }
  for (const auto &element : data) {
    cout << element << " ";
  }
}

void merge(vector<int> &data, int left, int mid, int right) {
  vector<int> leftPart(data.begin() + left, data.begin() + mid);
  vector<int> rightPart(data.begin() + mid, data.begin() + right);

  if (trace) {
    cout << "  scalanie [" << left << "," << mid << ") + [" << mid << ","
         << right << "): ";
    for (const auto &element : leftPart) {
      cout << element << " ";
    }
    cout << "| ";
    for (const auto &element : rightPart) {
      cout << element << " ";
    }
    cout << "\n";
  }

  int i = 0;
  int j = 0;
  int k = left;

  while (i < (int)leftPart.size() && j < (int)rightPart.size()) {
    if (leftPart[i] <= rightPart[j]) {
      data[k++] = leftPart[i++];
    } else {
      data[k++] = rightPart[j++];
    }
  }

  while (i < (int)leftPart.size()) {
    data[k++] = leftPart[i++];
  }

  while (j < (int)rightPart.size()) {
    data[k++] = rightPart[j++];
  }

  if (trace) {
    cout << "  -> ";
    for (int p = left; p < right; ++p) {
      cout << data[p] << " ";
    }
    cout << "\n";
  }
}

void mergeSort(vector<int> &data, int left, int right) {
  if (right - left <= 1) {
    return;
  }

  int mid = left + (right - left) / 2;

  if (trace) {
    cout << "  podzial [" << left << "," << right << ") -> [" << left << ","
         << mid << ") i [" << mid << "," << right << ")\n";
  }

  mergeSort(data, left, mid);
  mergeSort(data, mid, right);
  merge(data, left, mid, right);
}

void testCase(const string &name, vector<int> data, bool showTrace = false) {
  cout << "\n== " << name << " ==\n";
  cout << "przed: ";
  printArray(data);
  cout << "\n";

  trace = showTrace;
  mergeSort(data, 0, (int)data.size());
  trace = false;

  cout << "po:    ";
  printArray(data);
  cout << "\n";
}
} // namespace zad1

namespace zad2 {
struct QuickStats {
  long long comparisons = 0;
  long long swaps = 0;
  int maxDepth = 0;
};

mt19937 rng(12345);

void printArray(const vector<int> &data) {
  if (data.empty()) {
    cout << "(pusta)";
    return;
  }
  for (const auto &element : data) {
    cout << element << " ";
  }
}

int partition(vector<int> &data, int left, int right, bool randomPivot,
              QuickStats &stats) {
  if (randomPivot) {
    uniform_int_distribution<int> dis(left, right - 1);
    int randomIndex = dis(rng);
    if (randomIndex != right - 1) {
      swap(data[randomIndex], data[right - 1]);
      stats.swaps++;
    }
  }

  int pivot = data[right - 1];
  int i = left;

  for (int j = left; j < right - 1; ++j) {
    stats.comparisons++;
    if (data[j] <= pivot) {
      if (i != j) {
        swap(data[i], data[j]);
        stats.swaps++;
      }
      ++i;
    }
  }

  if (i != right - 1) {
    swap(data[i], data[right - 1]);
    stats.swaps++;
  }

  return i;
}

void quickSort(vector<int> &data, int left, int right, bool randomPivot,
               QuickStats &stats, int depth = 1) {
  if (depth > stats.maxDepth) {
    stats.maxDepth = depth;
  }

  if (right - left <= 1) {
    return;
  }

  int pivotIndex = partition(data, left, right, randomPivot, stats);
  quickSort(data, left, pivotIndex, randomPivot, stats, depth + 1);
  quickSort(data, pivotIndex + 1, right, randomPivot, stats, depth + 1);
}

void testCase(const string &name, vector<int> data) {
  QuickStats stats;
  if (!data.empty()) {
    quickSort(data, 0, (int)data.size(), false, stats);
  }

  cout << left << setw(46) << name << "-> ";
  printArray(data);
  cout << " (porownania: " << stats.comparisons
       << ", zamiany: " << stats.swaps
       << ", maks. glebokosc: " << stats.maxDepth << ")\n";
}

vector<int> generateRandom(int n) {
  uniform_int_distribution<int> dis(1, 100000);
  vector<int> data(n);
  for (auto &element : data) {
    element = dis(rng);
  }
  return data;
}

vector<int> generateIncreasing(int n) {
  vector<int> data(n);
  iota(data.begin(), data.end(), 1);
  return data;
}

vector<int> generateDecreasing(int n) {
  vector<int> data(n);
  for (int i = 0; i < n; ++i) {
    data[i] = n - i;
  }
  return data;
}

vector<int> generateData(const string &type, int n) {
  if (type == "losowe") {
    return generateRandom(n);
  }
  if (type == "rosnace") {
    return generateIncreasing(n);
  }
  return generateDecreasing(n);
}
} // namespace zad2

namespace zad3 {
struct SortStats {
  long long comparisons = 0;
  long long swaps = 0;
};

struct Result {
  double ms = 0.0;
  long long comparisons = 0;
  bool sorted = false;
};

mt19937 rng(12345);

void insertionSort(vector<int> &data, SortStats &stats) {
  for (int i = 1; i < (int)data.size(); ++i) {
    int key = data[i];
    int j = i - 1;
    while (j >= 0) {
      stats.comparisons++;
      if (data[j] <= key) {
        break;
      }
      data[j + 1] = data[j];
      stats.swaps++;
      --j;
    }
    data[j + 1] = key;
  }
}

void merge(vector<int> &data, int left, int mid, int right, SortStats &stats) {
  vector<int> leftPart(data.begin() + left, data.begin() + mid);
  vector<int> rightPart(data.begin() + mid, data.begin() + right);

  int i = 0;
  int j = 0;
  int k = left;

  while (i < (int)leftPart.size() && j < (int)rightPart.size()) {
    stats.comparisons++;
    if (leftPart[i] <= rightPart[j]) {
      data[k++] = leftPart[i++];
    } else {
      data[k++] = rightPart[j++];
    }
  }

  while (i < (int)leftPart.size()) {
    data[k++] = leftPart[i++];
  }
  while (j < (int)rightPart.size()) {
    data[k++] = rightPart[j++];
  }
}

void mergeSort(vector<int> &data, int left, int right, SortStats &stats) {
  if (right - left <= 1) {
    return;
  }
  int mid = left + (right - left) / 2;
  mergeSort(data, left, mid, stats);
  mergeSort(data, mid, right, stats);
  merge(data, left, mid, right, stats);
}

int partition(vector<int> &data, int left, int right, SortStats &stats) {
  uniform_int_distribution<int> dis(left, right - 1);
  int randomIndex = dis(rng);
  swap(data[randomIndex], data[right - 1]);
  stats.swaps++;

  int pivot = data[right - 1];
  int i = left;

  for (int j = left; j < right - 1; ++j) {
    stats.comparisons++;
    if (data[j] <= pivot) {
      if (i != j) {
        swap(data[i], data[j]);
        stats.swaps++;
      }
      ++i;
    }
  }

  if (i != right - 1) {
    swap(data[i], data[right - 1]);
    stats.swaps++;
  }

  return i;
}

void quickSort(vector<int> &data, int left, int right, SortStats &stats) {
  if (left < right) {
    int pivotIndex = partition(data, left, right, stats);
    quickSort(data, left, pivotIndex, stats);
    quickSort(data, pivotIndex + 1, right, stats);
  }
}

vector<int> generateRandom(int n) {
  uniform_int_distribution<int> dis(1, 100000);
  vector<int> data(n);
  for (auto &element : data) {
    element = dis(rng);
  }
  return data;
}

vector<int> generateIncreasing(int n) {
  vector<int> data(n);
  iota(data.begin(), data.end(), 1);
  return data;
}

vector<int> generateDecreasing(int n) {
  vector<int> data(n);
  for (int i = 0; i < n; ++i) {
    data[i] = n - i;
  }
  return data;
}

vector<int> generateNearlySorted(int n) {
  vector<int> data(n);
  iota(data.begin(), data.end(), 1);
  uniform_int_distribution<int> dis(0, n - 2);
  for (int i = 0; i < n / 100; ++i) {
    int position = dis(rng);
    swap(data[position], data[position + 1]);
  }
  return data;
}

Result runInsertion(const vector<int> &original) {
  vector<int> data = original;
  SortStats stats;
  auto start = chrono::steady_clock::now();
  insertionSort(data, stats);
  auto stop = chrono::steady_clock::now();
  double ms = chrono::duration<double, milli>(stop - start).count();
  return {ms, stats.comparisons, is_sorted(data.begin(), data.end())};
}

Result runMerge(const vector<int> &original) {
  vector<int> data = original;
  SortStats stats;
  auto start = chrono::steady_clock::now();
  mergeSort(data, 0, (int)data.size(), stats);
  auto stop = chrono::steady_clock::now();
  double ms = chrono::duration<double, milli>(stop - start).count();
  return {ms, stats.comparisons, is_sorted(data.begin(), data.end())};
}

Result runQuick(const vector<int> &original) {
  vector<int> data = original;
  SortStats stats;
  auto start = chrono::steady_clock::now();
  quickSort(data, 0, (int)data.size(), stats);
  auto stop = chrono::steady_clock::now();
  double ms = chrono::duration<double, milli>(stop - start).count();
  return {ms, stats.comparisons, is_sorted(data.begin(), data.end())};
}

void printHeader(bool withData = false) {
  if (withData) {
    cout << left << setw(22) << "Dane";
  }
  cout << left << setw(9) << "n" << right << setw(16) << "Insertion [ms]"
       << setw(15) << "Porownania" << setw(13) << "Merge [ms]" << setw(15)
       << "Porownania" << setw(13) << "Quick [ms]" << setw(15)
       << "Porownania" << "\n";
  cout << string(withData ? 118 : 96, '-') << "\n";
}

void printRow(int n, const Result &insertion, const Result &merge,
              const Result &quick, const string &dataType = "") {
  if (!dataType.empty()) {
    cout << left << setw(22) << dataType;
  }
  cout << left << setw(9) << n << right << fixed << setprecision(3)
       << setw(16) << insertion.ms << setw(15) << insertion.comparisons
       << setw(13) << merge.ms << setw(15) << merge.comparisons << setw(13)
       << quick.ms << setw(15) << quick.comparisons << "\n";
}

void writeCsv(ofstream &csv, int experiment, const string &dataType, int n,
              const string &algorithm, const Result &result) {
  csv << experiment << "," << dataType << "," << n << "," << algorithm << ","
      << fixed << setprecision(6) << result.ms << "," << result.comparisons
      << "\n";
}
} // namespace zad3

namespace zad4 {
struct Stats {
  long long comparisons = 0;
};

mt19937 rng(12345);

void printArray(const vector<int> &data) {
  for (const auto &element : data) {
    cout << element << " ";
  }
}

void merge(vector<int> &data, int left, int mid, int right, Stats &stats) {
  vector<int> leftPart(data.begin() + left, data.begin() + mid);
  vector<int> rightPart(data.begin() + mid, data.begin() + right);

  int i = 0;
  int j = 0;
  int k = left;

  while (i < (int)leftPart.size() && j < (int)rightPart.size()) {
    stats.comparisons++;
    if (leftPart[i] <= rightPart[j]) {
      data[k++] = leftPart[i++];
    } else {
      data[k++] = rightPart[j++];
    }
  }

  while (i < (int)leftPart.size()) {
    data[k++] = leftPart[i++];
  }
  while (j < (int)rightPart.size()) {
    data[k++] = rightPart[j++];
  }
}

void mergeSort(vector<int> &data, int left, int right, Stats &stats) {
  if (right - left <= 1) {
    return;
  }
  int mid = left + (right - left) / 2;
  mergeSort(data, left, mid, stats);
  mergeSort(data, mid, right, stats);
  merge(data, left, mid, right, stats);
}

int mergeSelect(vector<int> &data, int left, int right, int k, Stats &stats) {
  mergeSort(data, left, right, stats);
  return data[left + k - 1];
}

int partition(vector<int> &data, int left, int right, Stats &stats) {
  uniform_int_distribution<int> dis(left, right - 1);
  int randomIndex = dis(rng);
  swap(data[randomIndex], data[right - 1]);

  int pivot = data[right - 1];
  int i = left;

  for (int j = left; j < right - 1; ++j) {
    stats.comparisons++;
    if (data[j] <= pivot) {
      swap(data[i], data[j]);
      ++i;
    }
  }
  swap(data[i], data[right - 1]);

  return i;
}

int quickSelect(vector<int> &data, int left, int right, int k, Stats &stats) {
  if (left >= right) {
    return -1;
  }

  int pivotIndex = partition(data, left, right, stats);

  if (pivotIndex == k - 1) {
    return data[pivotIndex];
  } else if (pivotIndex > k - 1) {
    return quickSelect(data, left, pivotIndex, k, stats);
  } else {
    return quickSelect(data, pivotIndex + 1, right, k, stats);
  }
}

void testArray(const string &name, const vector<int> &original,
               const vector<int> &positions) {
  vector<int> sorted = original;
  Stats sortStats;
  mergeSort(sorted, 0, (int)sorted.size(), sortStats);

  cout << "\n=== " << name << " ===\n";
  cout << "tablica:     ";
  printArray(original);
  cout << "\nposortowana: ";
  printArray(sorted);
  cout << "\n";

  for (int k : positions) {
    vector<int> mergeData = original;
    Stats mergeStats;
    int mergeResult =
        mergeSelect(mergeData, 0, (int)mergeData.size(), k, mergeStats);

    vector<int> quickData = original;
    Stats quickStats;
    int quickResult =
        quickSelect(quickData, 0, (int)quickData.size(), k, quickStats);

    cout << "k=" << k << ": mergeSelect=" << mergeResult << " (porownania: "
         << mergeStats.comparisons << "), quickSelect=" << quickResult
         << " (porownania: " << quickStats.comparisons << ")"
         << (mergeResult == quickResult ? "  OK" : "  BLAD") << "\n";
  }
}
} // namespace zad4

#if defined(ZAD1)
int main() {
  using namespace zad1;
  cout << "Demonstracja kolejnych podzialow i scalen:\n";
  testCase("8 3 6 2", {8, 3, 6, 2}, true);

  testCase("dane losowe: 7 2 9 4 1 8 3", {7, 2, 9, 4, 1, 8, 3});
  testCase("dane rosnace: 1 2 3 4 5 6 7", {1, 2, 3, 4, 5, 6, 7});
  testCase("dane malejace: 7 6 5 4 3 2 1", {7, 6, 5, 4, 3, 2, 1});
  testCase("powtarzajace sie wartosci: 5 2 8 2 1 5 8", {5, 2, 8, 2, 1, 5, 8});
  testCase("jeden element: 42", {42});
  testCase("pusta tablica", {});

  return 0;
}
#elif defined(ZAD2)
int main() {
  using namespace zad2;
  cout << "=== Czesc A: pivot = ostatni element ===\n";
  testCase("dane losowe: 7 2 9 4 1 8 3", {7, 2, 9, 4, 1, 8, 3});
  testCase("dane rosnace: 1 2 3 4 5 6 7", {1, 2, 3, 4, 5, 6, 7});
  testCase("dane malejace: 7 6 5 4 3 2 1", {7, 6, 5, 4, 3, 2, 1});
  testCase("powtarzajace sie: 5 2 8 2 1 5 8", {5, 2, 8, 2, 1, 5, 8});
  testCase("jeden element: 42", {42});
  testCase("pusta tablica", {});

  cout << "\n=== Czesc B: porownanie strategii wyboru pivota ===\n";
  cout << left << setw(12) << "Dane" << right << setw(7) << "n" << setw(10)
       << "Pivot" << setw(14) << "Porownania" << setw(11) << "Zamiany"
       << setw(18) << "Maks. glebokosc" << "\n";
  cout << string(72, '-') << "\n";

  vector<int> sizes = {100, 1000, 5000, 10000};
  vector<string> dataTypes = {"losowe", "rosnace", "malejace"};
  bool allSorted = true;

  for (const auto &type : dataTypes) {
    for (int n : sizes) {
      vector<int> original = generateData(type, n);

      for (bool randomPivot : {false, true}) {
        vector<int> data = original;
        QuickStats stats;
        quickSort(data, 0, (int)data.size(), randomPivot, stats);

        if (!is_sorted(data.begin(), data.end())) {
          allSorted = false;
        }

        cout << left << setw(12) << type << right << setw(7) << n << setw(10)
             << (randomPivot ? "losowy" : "ostatni") << setw(14)
             << stats.comparisons << setw(11) << stats.swaps << setw(18)
             << stats.maxDepth << "\n";
      }
    }
  }

  cout << "\nWeryfikacja: "
       << (allSorted ? "wszystkie tablice posortowane poprawnie."
                     : "BLAD - znaleziono nieposortowana tablice.")
       << "\n";

  return 0;
}
#elif defined(ZAD3)
int main() {
  using namespace zad3;
  ofstream csv("wyniki_zad3.csv");
  csv << "eksperyment,dane,n,algorytm,czas_ms,porownania\n";

  bool allSorted = true;

  cout << "=== Eksperyment 1: rozmiar danych (dane losowe) ===\n";
  printHeader();

  vector<int> sizes = {100, 1000, 5000, 10000, 50000};
  for (int n : sizes) {
    vector<int> original = generateRandom(n);

    Result insertion = runInsertion(original);
    Result merge = runMerge(original);
    Result quick = runQuick(original);

    allSorted = allSorted && insertion.sorted && merge.sorted && quick.sorted;
    printRow(n, insertion, merge, quick);

    writeCsv(csv, 1, "losowe", n, "insertion", insertion);
    writeCsv(csv, 1, "losowe", n, "merge", merge);
    writeCsv(csv, 1, "losowe", n, "quick", quick);
  }

  cout << "\n=== Eksperyment 2: charakter danych (n = 50000) ===\n";
  printHeader(true);

  int n = 50000;
  vector<pair<string, vector<int>>> datasets;
  datasets.push_back({"losowe", generateRandom(n)});
  datasets.push_back({"rosnace", generateIncreasing(n)});
  datasets.push_back({"malejace", generateDecreasing(n)});
  datasets.push_back({"prawie posortowane", generateNearlySorted(n)});

  for (const auto &[type, original] : datasets) {
    Result insertion = runInsertion(original);
    Result merge = runMerge(original);
    Result quick = runQuick(original);

    allSorted = allSorted && insertion.sorted && merge.sorted && quick.sorted;

    printRow(n, insertion, merge, quick, type);

    writeCsv(csv, 2, type, n, "insertion", insertion);
    writeCsv(csv, 2, type, n, "merge", merge);
    writeCsv(csv, 2, type, n, "quick", quick);
  }

  cout << "\nWeryfikacja: "
       << (allSorted ? "wszystkie tablice posortowane poprawnie."
                     : "BLAD - znaleziono nieposortowana tablice.")
       << "\n";
  cout << "Wyniki zapisano w pliku wyniki_zad3.csv\n";

  return 0;
}
#elif defined(ZAD4)
int main() {
  using namespace zad4;
  testArray("tablica z polecenia", {8, 3, 1, 7, 4, 9, 2}, {1, 3, 7});
  testArray("tablica z powtorzeniami", {5, 2, 8, 2, 1, 5, 8}, {1, 3, 7});

  cout << "\n=== Test na duzej tablicy (n = 100000, k = 50000) ===\n";
  int n = 100000;
  uniform_int_distribution<int> dis(1, 1000000);
  vector<int> data(n);
  for (auto &element : data) {
    element = dis(rng);
  }

  vector<int> mergeData = data;
  Stats mergeStats;
  auto start = chrono::steady_clock::now();
  int mergeResult =
      mergeSelect(mergeData, 0, (int)mergeData.size(), 50000, mergeStats);
  auto stop = chrono::steady_clock::now();
  double mergeMs = chrono::duration<double, milli>(stop - start).count();

  vector<int> quickData = data;
  Stats quickStats;
  start = chrono::steady_clock::now();
  int quickResult =
      quickSelect(quickData, 0, (int)quickData.size(), 50000, quickStats);
  stop = chrono::steady_clock::now();
  double quickMs = chrono::duration<double, milli>(stop - start).count();

  cout << fixed << setprecision(3);
  cout << "mergeSelect: wynik=" << mergeResult
       << ", porownania=" << mergeStats.comparisons << ", czas=" << mergeMs
       << " ms\n";
  cout << "quickSelect: wynik=" << quickResult
       << ", porownania=" << quickStats.comparisons << ", czas=" << quickMs
       << " ms\n";
  cout << "Weryfikacja: "
       << (mergeResult == quickResult ? "wyniki zgodne." : "wyniki rozne!")
       << "\n";

  return 0;
}
#else
int main() {
  std::vector<int> data = {3, 1, 5, 2, 4};
  // mergeSort(data, 0, data.size());
  int result = mergeSelect(data, 0, data.size(), 3);
  std::cout << result << std::endl;
  printArray(data);
}
#endif
