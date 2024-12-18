#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>
#include <fstream>
#include <unordered_set>

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

class ArrayGenerator {
public:
    explicit ArrayGenerator(const int max_size = 10000, const int min_value = 0, const int max_value = 6000)
        : max_size_(max_size), min_value_(min_value), max_value_(max_value) {
        std::srand(std::time(nullptr));
        GenerateBaseArray();
    }

    std::vector<int> GenerateRandomArray(const int size) {
        ValidateSize(size);
        return {random_array_.begin(), random_array_.begin() + size};
    }

    std::vector<int> GenerateReversedArray(const int size) {
        ValidateSize(size);
        std::vector reversed_array(random_array_.begin(), random_array_.begin() + size);
        std::ranges::sort(reversed_array, std::greater<int>());
        return reversed_array;
    }

    std::vector<int> GenerateAlmostSortedArray(const int size, const int swap_count = 10) {
        ValidateSize(size);
        std::vector almost_sorted_array(random_array_.begin(), random_array_.begin() + size);
        std::ranges::sort(almost_sorted_array);
        PerformSwaps(almost_sorted_array, swap_count);
        return almost_sorted_array;
    }

private:
    int max_size_;
    int min_value_;
    int max_value_;
    std::vector<int> random_array_;

    void GenerateBaseArray() {
        random_array_.resize(max_size_);
        std::mt19937 rng(std::time(nullptr));
        std::uniform_int_distribution<int> dist(min_value_, max_value_);
        for (int& num : random_array_) {
            num = dist(rng);
        }
    }

    void ValidateSize(const int size) const {
        if (size <= 0 || size > max_size_) {
            throw std::invalid_argument("Invalid array size");
        }
    }

    static void PerformSwaps(std::vector<int>& array, const int swap_count) {
        const int n = static_cast<int>(array.size());
        for (int i = 0; i < swap_count; ++i) {
            const int idx1 = std::rand() % n;
            const int idx2 = std::rand() % n;
            std::swap(array[idx1], array[idx2]);
        }
    }
};

class SortTester {
public:
    static void Timer(std::vector<int>& array, std::ofstream& stream, bool hybrid) {
        const auto start = std::chrono::high_resolution_clock::now();
        if (hybrid) {
            HybridMergeSort(array, 0, static_cast<int>(array.size() - 1));
        } else {
            MergeSort(array, 0, static_cast<int>(array.size() - 1));
        }
        const auto elapsed = std::chrono::high_resolution_clock::now() - start;
        const uint32_t milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        stream << std::fixed << std::setprecision(15) << milliseconds << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ArrayGenerator generator;
    SortTester tester;
    std::vector<int> random_array = generator.GenerateRandomArray(10000);
    std::vector<int> reversed_array = generator.GenerateReversedArray(10000);
    std::vector<int> swap_array = generator.GenerateAlmostSortedArray(10000, 5);
    std::ofstream random;
    random.open("random.txt");
    std::ofstream reversed;
    reversed.open("reversed.txt");
    std::ofstream swap;
    swap.open("swap.txt");
    std::ofstream random_hybrid;
    random_hybrid.open("random_hybrid.txt");
    std::ofstream reversed_hybrid;
    reversed_hybrid.open("reversed_hybrid.txt");
    std::ofstream swap_hybrid;
    swap_hybrid.open("swap_hybrid.txt");
    for (int i = 500; i <= 10000; i += 100) {
        auto random_array_i = std::vector(random_array.begin(), random_array.end() - 10000 + i);
        auto reversed_array_i = std::vector(reversed_array.begin(), reversed_array.end() - 10000 + i);
        auto swap_array_i = std::vector(swap_array.begin(), swap_array.end() - 10000 + i);
        tester.Timer(random_array_i, random, false);
        tester.Timer(reversed_array_i, reversed, false);
        tester.Timer(swap_array_i, swap, false);
        tester.Timer(random_array_i, random_hybrid, true);
        tester.Timer(reversed_array_i, reversed_hybrid, true);
        tester.Timer(swap_array_i, swap_hybrid, true);
    }
    random.close();
    reversed.close();
    swap.close();
    random_hybrid.close();
    reversed_hybrid.close();
    swap_hybrid.close();
    return 0;
}
