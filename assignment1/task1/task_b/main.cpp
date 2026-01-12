#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

// Credit card record
struct CardRecord {
    string rawData;   // Original data
    int sortKey;      // Sorting key (Date + PIN)
};

// Counting sort used by Radix Sort
void countingSortForRadix(vector<CardRecord>& arr, int exp) {
    int n = arr.size();
    vector<CardRecord> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i].sortKey / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i].sortKey / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Radix Sort — linear time algorithm
void radixSort(vector<CardRecord>& arr) {
    int maxVal = 99999999; // MMYY + PIN (8 digits)
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortForRadix(arr, exp);
}

// Generate test data
vector<CardRecord> generateOlsenData(int size) {
    vector<CardRecord> data(size);
    mt19937 gen(random_device{}());
    uniform_int_distribution<> dateDist(1024, 1230);
    uniform_int_distribution<> pinDist(1000, 9999);

    for (int i = 0; i < size; i++) {
        int date = dateDist(gen);
        int pin = pinDist(gen);
        data[i].sortKey = date * 10000 + pin;
        data[i].rawData =
            "Card_" + to_string(i) + "," +
            to_string(date) + "," +
            to_string(pin);
    }
    return data;
}

int main() {
    int size = 20000;
    cout << "Generating " << size << " records..." << endl;

    vector<CardRecord> data = generateOlsenData(size);

    cout << "Starting Radix Sort..." << endl;
    auto start = chrono::high_resolution_clock::now();

    radixSort(data);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    cout << "Sorted " << size << " records in "
         << diff.count() << " seconds." << endl;

    bool sorted = true;
    for (size_t i = 0; i + 1 < data.size(); i++) {
        if (data[i].sortKey > data[i + 1].sortKey) {
            sorted = false;
            break;
        }
    }

    cout << (sorted ? "SUCCESS: Data is sorted correctly!"
                    : "ERROR: Sorting failed.")
         << endl;

    return 0;
}
