#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

// Bubble Sort — O(n^2)
void bubbleSort(vector<int> arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Insertion Sort — O(n^2), efficient for small arrays
void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort — O(n log n)
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void runMergeSort(vector<int> arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Quick Sort — average O(n log n)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void runQuickSort(vector<int> arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Generate random array
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    mt19937 gen(random_device{}());
    uniform_int_distribution<> dist(1, 10000);
    for (int& x : arr) x = dist(gen);
    return arr;
}

int main() {
    vector<int> sizes = {10, 50, 100, 500, 1000, 5000, 10000};

    cout << left << setw(15) << "Size"
         << setw(15) << "Bubble"
         << setw(15) << "Insertion"
         << setw(15) << "Merge"
         << setw(15) << "Quick" << endl;

    cout << string(70, '-') << endl;

    for (int n : sizes) {
        vector<int> data = generateRandomArray(n);
        cout << left << setw(15) << n;

        if (n <= 5000) {
            auto start = chrono::high_resolution_clock::now();
            bubbleSort(data);
            auto end = chrono::high_resolution_clock::now();
            cout << left << setw(15)
                 << chrono::duration<double>(end - start).count();
        } else {
            cout << left << setw(15) << "-";
        }

        auto start = chrono::high_resolution_clock::now();
        insertionSort(data);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(15)
             << chrono::duration<double>(end - start).count();

        start = chrono::high_resolution_clock::now();
        runMergeSort(data);
        end = chrono::high_resolution_clock::now();
        cout << left << setw(15)
             << chrono::duration<double>(end - start).count();

        start = chrono::high_resolution_clock::now();
        runQuickSort(data);
        end = chrono::high_resolution_clock::now();
        cout << left << setw(15)
             << chrono::duration<double>(end - start).count();

        cout << endl;
    }

    return 0;
}
