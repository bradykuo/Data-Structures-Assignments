#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

vector<int> generateRandomArray(int size, int max_value) {
    vector<int> arr(size);
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(1, max_value);  // 1到max_value之間
    
    for (int i = 0; i < size; i++) {
        arr[i] = dist(rng);
    }
    return arr;
}

void printArray(const vector<int>& arr) {
    int count = 0;
    for (const int& num : arr) {
        cout << setw(4) << num << " ";
        count++;
        if (count % 10 == 0) cout << endl;  // 每10個數字換行
    }
    cout << endl;
}

int main() {
    int max_value;
    cout << "請輸入數字上限: ";
    cin >> max_value;

    // 方法1: 單次執行
    cout << "\n方法1 - 單次執行:\n";
    vector<int> arr = generateRandomArray(1000, max_value);
    cout << "排序前結果:\n";
    printArray(arr);

    auto start = high_resolution_clock::now();
    insertionSort(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "\n排序後結果:\n";
    printArray(arr);
    cout << "\n執行時間: " << duration.count() << " 微秒\n";

    // 方法2: 執行10000次
    cout << "\n方法2 - 執行10000次:\n";
    start = high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        vector<int> arr2 = generateRandomArray(1000, max_value);
        insertionSort(arr2);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "平均執行時間: " << duration.count() / 10000.0 << " 微秒\n";

    // 方法3: 執行到超過1分鐘
    cout << "\n方法3 - 執行到超過1分鐘:\n";
        int count = 0;
        start = high_resolution_clock::now();
        auto current = start;
        while (duration_cast<seconds>(current - start).count() < 60) {
            vector<int> arr3 = generateRandomArray(1000, max_value);
            insertionSort(arr3);
            count++;
            current = high_resolution_clock::now();
        }
        duration = duration_cast<microseconds>(current - start);
        cout << "總執行次數: " << count << endl;
        cout << "平均執行時間: " << duration.count() / static_cast<double>(count) << " 微秒\n";

    return 0;
}
