#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

// Main structure for start
struct CardRecord {
    long long sortKey; // Date + PIN combined
};

// --- 1. Linear Radix Sort ---
void countingSort(vector<CardRecord>& arr, long long exp) {
    int n = arr.size();
    vector<CardRecord> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i].sortKey / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i].sortKey / exp) % 10] - 1] = arr[i];
        count[(arr[i].sortKey / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<CardRecord>& arr) {
    long long maxVal = 99999999; // Max 8 digits
    for (long long exp = 1; maxVal / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

// --- 2. Log-Linear Standard Sort ---
bool compareRecords(const CardRecord& a, const CardRecord& b) {
    return a.sortKey < b.sortKey;
}

// Data Generator
vector<CardRecord> generateData(int size) {
    vector<CardRecord> data(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dateDist(1024, 1230);
    uniform_int_distribution<int> pinDist(1000, 9999);
    
    for(int i = 0; i < size; i++) {
        long long date = dateDist(gen);
        long long pin = pinDist(gen);
        data[i].sortKey = date * 10000 + pin; 
    }
    return data;
}

int main() {
    // Test with great numbers
    vector<int> sizes = {10000, 50000, 100000, 500000, 1000000};
    
    cout << "Algorithm,Size,Time(seconds)" << endl;

    for (int n : sizes) {
        vector<CardRecord> data = generateData(n);
        
        // 1. Test Radix Sort (Linear)
        {
            vector<CardRecord> copy = data;
            auto start = chrono::high_resolution_clock::now();
            radixSort(copy);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "LinearSort(Radix)," << n << "," << diff.count() << endl;
        }

        // 2. Test Standard Sort (O(N log N))
        {
            vector<CardRecord> copy = data;
            auto start = chrono::high_resolution_clock::now();
            sort(copy.begin(), copy.end(), compareRecords);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "StdSort(Quick)," << n << "," << diff.count() << endl;
        }
    }

    return 0;
}