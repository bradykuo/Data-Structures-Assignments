#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

template<typename T>
void insertionSort(vector<T>& arr) {
   for (size_t i = 1; i < arr.size(); i++) {
       T key = arr[i];
       int j = static_cast<int>(i) - 1;
       while (j >= 0 && arr[j] < key) {
           arr[j + 1] = arr[j];
           j--;
       }
       arr[j + 1] = key;
   }
}

template<typename T>
vector<T> generateRandomArray(size_t size, T max_value) {
   vector<T> arr(size);
   random_device rd;
   mt19937 gen(rd());
   
   if (is_same<T, double>::value) {
       uniform_real_distribution<double> dist(1.0, static_cast<double>(max_value));
       for (size_t i = 0; i < size; i++) {
           arr[i] = dist(gen);
       }
   } else if (is_same<T, int>::value) {
       uniform_int_distribution<int> dist(1, static_cast<int>(max_value));
       for (size_t i = 0; i < size; i++) {
           arr[i] = dist(gen);
       }
   }
   return arr;
}

template<typename T>
void printArray(const vector<T>& arr) {
   size_t count = 0;
   for (const T& num : arr) {
       cout << setw(8) << fixed << setprecision(2) << num << " ";
       count++;
       if (count % 10 == 0) cout << endl;
   }
   cout << endl;
}

template<typename T>
void runTests(T max_value) {
   cout << "\nMethod 1 - Single Run:\n";
   vector<T> arr = generateRandomArray(1000, max_value);
   cout << "Before sorting:\n";
   printArray(arr);

   high_resolution_clock::time_point start = high_resolution_clock::now();
   insertionSort(arr);
   high_resolution_clock::time_point end = high_resolution_clock::now();
   microseconds duration = duration_cast<microseconds>(end - start);

   cout << "\nAfter sorting:\n";
   printArray(arr);
   cout << "\nExecution time: " << duration.count() << " microseconds\n";

   cout << "\nMethod 2 - Running 10000 times:\n";
   start = high_resolution_clock::now();
   for (size_t i = 0; i < 10000; i++) {
       vector<T> arr2 = generateRandomArray(1000, max_value);
       insertionSort(arr2);
   }
   end = high_resolution_clock::now();
   duration = duration_cast<microseconds>(end - start);
   cout << "Average execution time: " << duration.count() / 10000.0 << " microseconds\n";

   cout << "\nMethod 3 - Running until 1 minute passes:\n";
   size_t count = 0;
   start = high_resolution_clock::now();
   high_resolution_clock::time_point current = start;
   while (duration_cast<seconds>(current - start).count() < 60) {
       vector<T> arr3 = generateRandomArray(1000, max_value);
       insertionSort(arr3);
       count++;
       current = high_resolution_clock::now();
   }
   duration = duration_cast<microseconds>(current - start);
   cout << "Total executions: " << count << endl;
   cout << "Average execution time: " << duration.count() / static_cast<double>(count) << " microseconds\n";
}

int main() {
   cout << "Choose data type (1: int, 2: double): ";
   int choice;
   cin >> choice;

   if (choice == 1) {
       int max_value;
       cout << "Enter maximum value: ";
       cin >> max_value;
       runTests(max_value);
   } else if (choice == 2) {
       double max_value;
       cout << "Enter maximum value: ";
       cin >> max_value;
       runTests(max_value);
   } else {
       cout << "Invalid choice\n";
   }
   
   return 0;
}