#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

// Single-pivot Quick Sort
int partitionSingle(vector<int>& arr, int low, int high) {
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

void quickSortSingle(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionSingle(arr, low, high);
        quickSortSingle(arr, low, pi - 1);
        quickSortSingle(arr, pi + 1, high);
    }
}

// Dual-pivot Quick Sort
void quickSortDual(vector<int>& arr, int low, int high) {
    if (low < high) {
        if (arr[low] > arr[high])
            swap(arr[low], arr[high]);

        int p1 = arr[low];
        int p2 = arr[high];

        int i = low + 1;
        int j = low + 1;
        int k = high - 1;

        while (j <= k) {
            if (arr[j] < p1) {
                swap(arr[j++], arr[i++]);
            } else if (arr[j] > p2) {
                swap(arr[j], arr[k--]);
            } else {
                j++;
            }
        }

        swap(arr[low], arr[i - 1]);
        swap(arr[high], arr[k + 1]);

        quickSortDual(arr, low, i - 2);
        quickSortDual(arr, i, k);
        quickSortDual(arr, k + 2, high);
    }
}

// Random array generator
vector<int> generateArray(int size) {
    vector<int> arr(size);
    mt19937 gen(random_device{}());
    uniform_int_distribution<> dist(1, 100000);
    for (int& x : arr)
        x = dist(gen);
    return arr;
}

int main() {
    vector<int> sizes = {1000, 10000, 100000, 200000};

    cout << left << setw(15) << "Size"
         << setw(20) << "1-Pivot Time (s)"
         << setw(20) << "2-Pivot Time (s)" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int n : sizes) {
        vector<int> data = generateArray(n);

        vector<int> copy1 = data;
        auto start1 = chrono::high_resolution_clock::now();
        quickSortSingle(copy1, 0, n - 1);
        auto end1 = chrono::high_resolution_clock::now();

        vector<int> copy2 = data;
        auto start2 = chrono::high_resolution_clock::now();
        quickSortDual(copy2, 0, n - 1);
        auto end2 = chrono::high_resolution_clock::now();

        cout << left << setw(15) << n
             << setw(20)
             << chrono::duration<double>(end1 - start1).count()
             << setw(20)
             << chrono::duration<double>(end2 - start2).count()
             << endl;
    }

    return 0;
}
