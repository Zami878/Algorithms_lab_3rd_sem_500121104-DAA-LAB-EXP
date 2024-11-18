#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>


void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Utility function to generate random data
std::vector<int> generateRandomData(int n) {
    std::vector<int> data(n);
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 10000; // Random integers between 0 and 9999
    }
    return data;
}

double measureSortTime(void (*sortFunc)(std::vector<int>&, int, int), std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}
  

int main() {
    srand(time(0));

    
    long long  sizes[] = {10 , 100 , 1000 , 10000 , 100000,1000000 ,10000000};


    for (long long n : sizes) {
        std::cout << "For " << n << " elements:" << std::endl;

       
        std::vector<int> data = generateRandomData(n);
        
        std::vector<int> data_copy1 = data;
        std::vector<int> data_copy2 = data;

     
        auto start_merge = std::chrono::high_resolution_clock::now();
        mergeSort(data_copy1, 0, data_copy1.size() - 1);
        auto end_merge = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> merge_duration = end_merge - start_merge;
        std::cout << "  Merge Sort Time: " << merge_duration.count() << " seconds" << std::endl;

       
        auto start_quick = std::chrono::high_resolution_clock::now();
        quickSort(data_copy2, 0, data_copy2.size() - 1);
        auto end_quick = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> quick_duration = end_quick - start_quick;
        std::cout << "  Quick Sort Time: " << quick_duration.count() << " seconds" << std::endl;

        std::cout << std::endl;
    }

    return 0;
} 
