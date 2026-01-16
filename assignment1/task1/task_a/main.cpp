#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

// --- 1. Bubble Sort ---
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

// --- 2. Insertion Sort ---
void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// --- 3. Merge Sort ---
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
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

// --- 4. Quick Sort ---
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
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

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);
    for(int &x : arr) x = distrib(gen);
    return arr;
}

int main() {
    vector<int> sizes = {10, 50, 100, 500, 1000, 5000};
    
    // ОСЬ ЦЕЙ РЯДОК ДУЖЕ ВАЖЛИВИЙ ДЛЯ PYTHON:
    cout << "Algorithm,Size,Time(seconds)" << endl;

    for (int n : sizes) {
        vector<int> data = generateRandomArray(n);

        // Bubble Sort
        if (n <= 5000) {
            auto start = chrono::high_resolution_clock::now();
            bubbleSort(data);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "BubbleSort," << n << "," << diff.count() << endl;
        }

        // Insertion Sort
        {
            auto start = chrono::high_resolution_clock::now();
            insertionSort(data);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "InsertionSort," << n << "," << diff.count() << endl;
        }

        // Merge Sort
        {
            auto start = chrono::high_resolution_clock::now();
            runMergeSort(data);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "MergeSort," << n << "," << diff.count() << endl;
        }

        // Quick Sort
        {
            auto start = chrono::high_resolution_clock::now();
            runQuickSort(data);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "QuickSort," << n << "," << diff.count() << endl;
        }
    }
    return 0;
}