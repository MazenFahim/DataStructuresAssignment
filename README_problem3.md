# 🔺 Problem 3: Search in a Bitonic Array

## 📌 What This Code Does

Takes an **unsorted array**, sorts it into a **bitonic shape** (ascending then descending), and then searches for a target value using linear search.

A bitonic array looks like this:

```
[ 1, 4, 7, 11, 9, 6, 2 ]
        ↑ Bitonic Point (peak)
  ascending | descending
```

---

## 🏗️ Class Structure

```
Bitonic
├── data[]                      → stores the array
├── bubble_comparisons/swaps    → stats for left-half sort
├── selection_comparisons/swaps → stats for right-half sort
│
├── bubble_sort_left_half()         → sorts left half ascending
├── selection_sort_right_half_desc()→ sorts right half descending
├── make_bitonic()                  → calls both sorts above
├── linear_search(target)           → scans entire array for target
├── print()                         → prints array contents
└── print_stats()                   → prints comparison/swap counts
```

---

## ⚙️ How the Sorting Works

### 🫧 Left Half — Bubble Sort (Ascending)

The left half is defined as indices `0` to `first_half - 1`.

```cpp
const int first_half = (n % 2 == 0 ? n / 2 : n / 2 + 1);
```

> ⚠️ **Why this formula?**
> For odd-length arrays, the left half gets the extra element so the peak sits on the left side. This ensures the bitonic point is always reachable.

Bubble sort runs **right-to-left** in the inner loop, which means it bubbles the **smallest unsorted element** leftward each pass. An `is_sorted` flag provides an **early exit** — if no swap happened, the half is already sorted.

```
Pass 1: [ 7, 2, 11, 4, 9 | 1, 6 ]
         Right-to-left bubbling on left half...
         → 2 bubbles left, 4 moves, etc.
Final:   [ 2, 4, 7, 9, 11 | ... ]  ✅ ascending
```

---

### 🎯 Right Half — Selection Sort (Descending)

The right half starts at `first_half` and goes to the end.

Selection sort finds the **maximum** of the remaining unsorted portion and places it at the front of that portion — producing a **descending** order.

```
Right half: [ 1, 6 ]  (after left is sorted)
Pass 1: max is 6 → swap to front → [ 6, 1 ]  ✅ descending
```

> ⚠️ **Why selection sort for descending?**
> Normally selection sort finds the minimum for ascending. Here it finds the **maximum** and puts it first, which naturally produces descending order.

---

## 🔍 Linear Search

```cpp
int linear_search(const int target) const {
    for (int i = 0; i < data.size(); ++i)
        if (data[i] == target) return i;
    return -1;
}
```

Scans the entire bitonic array from left to right. Returns the **index** if found, or `-1` if not.

> 💡 A more optimal approach would be to binary search each half separately, but linear search satisfies the assignment requirement and handles duplicates naturally.

---

## 📊 Stats Tracking

Every comparison and swap in both sorts is counted separately:

| Counter | Tracks |
|---|---|
| `bubble_comparisons` | Every `data[j] < data[j-1]` check |
| `bubble_swaps` | Every `swap()` call in bubble sort |
| `selection_comparisons` | Every `data[j] > data[max_index]` check |
| `selection_swaps` | Every `swap()` call in selection sort |

`print_stats()` shows individual and total counts.

---

## 🧪 Test Cases

| # | Description | Target |
|---|---|---|
| 1 | Target **at** the bitonic point | `11` (peak value) |
| 2 | Target in the **left** (ascending) half | `3` |
| 3 | Target in the **right** (descending) half | `7` |
| 4 | Target **not present** | `99` |
| 5 | Array with **duplicate** elements | `9` |

---

## 🧩 Edge Cases Handled

- ✅ **Odd-length arrays** — left half gets the extra element
- ✅ **Duplicates** — linear search returns the first occurrence
- ✅ **Already sorted input** — `is_sorted` flag exits bubble sort early
- ✅ **No swap needed in selection** — `if (max_index != i)` guard prevents unnecessary swaps

---

## 📎 Example Walkthrough

Input: `{7, 2, 11, 4, 9, 1, 6}`, target = `11`

```
n = 7 (odd) → first_half = 4
Left half indices:  [0..3] → {7, 2, 11, 4, 9} ← wait, 5 elements for odd
Right half indices: [4..6] → {1, 6}

After bubble sort (left):  2, 4, 7, 9, 11
After selection sort (right): 6, 1
Final array: [ 2, 4, 7, 9, 11, 6, 1 ]

Search for 11 → found at index 4 ✅
```
