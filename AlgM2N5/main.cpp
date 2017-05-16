#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>

int GetRandom(int min, int max) {
    return std::rand() % (max - min + 1) + min;
}

template<class Iter>
Iter partition(Iter begin, Iter end) {
    if (begin == end) {
        return begin;
    }

    auto pivot = begin + GetRandom(0, std::distance(begin, end) - 1);
    std::iter_swap(begin, pivot);

    auto it = end - 1;
    auto jt = end - 1;
    while (jt != begin) {
        if (*jt >= *begin) {
            std::iter_swap(it, jt);
            --it;
        }
        --jt;
    }
    std::iter_swap(begin, it);

    return it;
}

template<class Iter>
auto findKStat(Iter begin, Iter end, int k) -> decltype(*begin) {
    auto first = begin;
    auto last = end;

    while (true) {
        auto pivot = partition(first, last);
        int pivot_pos = pivot - begin;

        if (pivot_pos == k) {
            return *(begin + k);
        } else if (pivot_pos > k) {
            last = pivot;
        } else {
            first = pivot + 1;
        }
    }
}

int main() {
    std::srand(time(NULL));

    int n, k;
    std::cin >> n >> k;

    int* data = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    std::cout << findKStat(data, data + n, k);

    delete[] data;

    return 0;
}