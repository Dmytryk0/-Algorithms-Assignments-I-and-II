#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <iomanip>

using namespace std;

// Custom dynamic array implementation
class MyVector {
private:
    int* data;
    size_t capacity;
    size_t length;

public:
    MyVector() : data(nullptr), capacity(0), length(0) {}

    ~MyVector() {
        delete[] data;
    }

    // Append element to the end
    void push_back(int value) {
        if (length == capacity) {
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            int* newData = new int[newCapacity];

            for (size_t i = 0; i < length; i++)
                newData[i] = data[i];

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[length++] = value;
    }

    int get(size_t index) {
        if (index >= length)
            throw out_of_range("Index out of bounds");
        return data[index];
    }

    size_t size() {
        return length;
    }
};

int main() {
    const int N = 1'000'000;

    cout << "Testing append performance (" << N << " elements)..." << endl;
    cout << left << setw(20) << "Container" << "Time (seconds)" << endl;
    cout << "------------------------------------" << endl;

    {
        MyVector myVec;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++)
            myVec.push_back(i);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(20) << "MyVector (Custom)"
             << chrono::duration<double>(end - start).count() << endl;
    }

    {
        vector<int> stdVec;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++)
            stdVec.push_back(i);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(20) << "std::vector (C++)"
             << chrono::duration<double>(end - start).count() << endl;
    }

    {
        list<int> stdList;
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < N; i++)
            stdList.push_back(i);
        auto end = chrono::high_resolution_clock::now();
        cout << left << setw(20) << "std::list (Linked)"
             << chrono::duration<double>(end - start).count() << endl;
    }

    return 0;
}
