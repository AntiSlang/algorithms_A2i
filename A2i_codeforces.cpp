#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

void InsertionSort(std::vector<int>& array, const int left, const int right) {
    for (int i = left + 1; i <= right; ++i) {
        const int key = array[i];
        int j = i - 1;
        while (j >= left && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

void Merge(std::vector<int>& array, const int left, const int mid, const int right) {
    const int n1 = mid - left + 1;
    const int n2 = right - mid;
    std::vector<int> left_array(n1);
    std::vector<int> right_array(n2);
    for (int i = 0; i < n1; ++i) {
        left_array[i] = array[left + i];
}
    for (int j = 0; j < n2; ++j) {
        right_array[j] = array[mid + 1 + j];
}
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            ++i;
        } else {
            array[k] = right_array[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        array[k] = left_array[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        array[k] = right_array[j];
        ++j;
        ++k;
    }
}

void MergeSort(std::vector<int>& array, const int left, const int right) {
    if (left < right) {
        const int mid = left + (right - left) / 2;
        MergeSort(array, left, mid);
        MergeSort(array, mid + 1, right);
        Merge(array, left, mid, right);
    }
}

void HybridMergeSort(std::vector<int>& array, const int left, const int right) {
    if (right - left + 1 <= 15) {
        InsertionSort(array, left, right);
    } else if (left < right) {
        const int mid = left + (right - left) / 2;
        HybridMergeSort(array, left, mid);
        HybridMergeSort(array, mid + 1, right);
        Merge(array, left, mid, right);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0;
    std::cin >> n;
    std::vector<int> array(n);
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    HybridMergeSort(array, 0, static_cast<int>(array.size() - 1));
    for (int i : array) {
        std::cout << i << '\n';
    }
    return 0;
}
