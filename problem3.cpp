#include <bits/stdc++.h>
using namespace std;

class Bitonic {
public:
    vector<int> data;
    long long bubble_comparisons = 0, bubble_swaps = 0;
    long long selection_comparisons = 0, selection_swaps = 0;

    Bitonic(const vector<int>& arr) : data(arr) {}

    void bubble_sort_left_half() {
        const int n = static_cast<int>(data.size());
        const int first_half = (n % 2 == 0 ? n / 2 : n / 2 + 1);
        for (int i = 0; i <= first_half; i++) {
            bool is_sorted = true;
            for (int j = first_half; j > i; --j) {
                bubble_comparisons++;
                if (data[j] < data[j - 1]) {
                    is_sorted = false;
                    bubble_swaps++;
                    swap(data[j], data[j - 1]);
                }
            }
            if (is_sorted)
                break;
        }
    }

    void selection_sort_right_half_desc() {
        const int n = static_cast<int>(data.size());
        const int first_half = (n % 2 == 0 ? n / 2 : n / 2 + 1);
        const int second_half = first_half;
        for (int i = second_half; i < n - 1; ++i) {
            int max_index = i;
            for (int j = i + 1; j < n; ++j) {
                selection_comparisons++;
                if (data[j] > data[max_index]) {
                    max_index = j;
                }
            }
            if (max_index != i) {
                selection_swaps++;
                swap(data[i], data[max_index]);
            }
        }
    }

    void make_bitonic() {
        bubble_sort_left_half();
        selection_sort_right_half_desc();
    }

    int linear_search(const int target) const {
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == target)
                return i;
        }
        return -1;
    }

    void print() const {
        for (auto& i : data)
            cout << i << " ";
        cout << endl;
    }

    void print_stats() const {
        cout << "BubbleSort - Comparisons: " << bubble_comparisons << ", Swaps: " << bubble_swaps << endl;
        cout << "SelectionSort - Comparisons: " << selection_comparisons << ", Swaps: " << selection_swaps << endl;
        cout << "Total Comparisons: " << (bubble_comparisons + selection_comparisons)
             << ", Total Swaps: " << (bubble_swaps + selection_swaps) << endl;
    }
};

void run_test_cases(const string& label, const vector<int>& arr, const int target){
    cout << "Test Case: " << label << endl;
    Bitonic b(arr);
    b.make_bitonic();
    b.print();
    b.print_stats();
    if (const int idx = b.linear_search(target); idx != -1)
        cout << "Found " << target << " at index " << idx << endl;
    else
        cout << target << " not found" << endl;
    cout << "-----------------------------------" << endl;
}

int main() {
    // 1) Target at the bitonic point (left max after sorting halves)
    run_test_cases(
        "Case 1: target at bitonic point",
        {7, 2, 11, 4, 9, 1, 6},
        11
    );

    // 2) Target in left half (ascending portion)
    run_test_cases(
        "Case 2: target in left half",
        {8, 3, 10, 1, 7, 2, 6},
        3
    );

    // 3) Target in right half (descending portion)
    run_test_cases(
        "Case 3: target in right half",
        {5, 12, 1, 9, 4, 11, 2, 7},
        7
    );

    // 4) Target not present
    run_test_cases(
        "Case 4: target not present",
        {14, 3, 8, 6, 10, 1, 5},
        99
    );

    // 5) Array with duplicate elements
    run_test_cases(
        "Case 5: duplicates",
        {4, 9, 4, 2, 9, 7, 2, 7},
        9
    );

    return 0;
}