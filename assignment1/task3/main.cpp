#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

// --- 1. SINGLE PIVOT QUICKSORT ---
int partitionSingle(vector<int>& arr, int low, int high) {
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

void quickSortSingle(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionSingle(arr, low, high);
        quickSortSingle(arr, low, pi - 1);
        quickSortSingle(arr, pi + 1, high);
    }
}

// --- 2. DUAL PIVOT QUICKSORT ---
void quickSortDual(vector<int>& arr, int low, int high) {
    if (low < high) {
        if (arr[low] > arr[high]) swap(arr[low], arr[high]);
        int p1 = arr[low], p2 = arr[high];
        int i = low + 1, k = high - 1, j = low + 1;
        while (j <= k) {
            if (arr[j] < p1) {
                swap(arr[j], arr[i]); i++; j++;
            } else if (arr[j] > p2) {
                swap(arr[j], arr[k]); k--;
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

vector<int> generateArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 1000000);
    for(int &x : arr) x = distrib(gen);
    return arr;
}

int main() {
    // Great arreys to see difference
    vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    
    cout << "Algorithm,Size,Time(seconds)" << endl;

    for (int n : sizes) {
        vector<int> data = generateArray(n);
        
        // 1-pivot
        {
            vector<int> copy = data;
            auto start = chrono::high_resolution_clock::now();
            quickSortSingle(copy, 0, n - 1);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "1-Pivot," << n << "," << diff.count() << endl;
        }

        // 2-pivot
        {
            vector<int> copy = data;
            auto start = chrono::high_resolution_clock::now();
            quickSortDual(copy, 0, n - 1);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "2-Pivots," << n << "," << diff.count() << endl;
        }
    }
    return 0;
}