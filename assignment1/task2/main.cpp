#include <iostream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;

// --- MY VECTOR ---
class MyVector {
private:
    int* data;
    size_t capacity;
    size_t length;
public:
    MyVector() : data(nullptr), capacity(0), length(0) {}
    ~MyVector() { delete[] data; }
    void push_back(int value) {
        if (length == capacity) {
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            int* newData = new int[newCapacity];
            for (size_t i = 0; i < length; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[length++] = value;
    }
};

int main() {
    int N = 1000000; // 1 mil elements
    cout << "Container,Time" << endl;

    // 1. MyVector
    {
        MyVector myVec;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) myVec.push_back(i);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "MyVector," << diff.count() << endl;
    }

    // 2. std::vector
    {
        vector<int> stdVec;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) stdVec.push_back(i);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "std::vector," << diff.count() << endl;
    }

    // 3. std::list
    {
        list<int> stdList;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++) stdList.push_back(i);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "std::list," << diff.count() << endl;
    }

    return 0;
}