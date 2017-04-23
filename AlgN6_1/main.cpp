#include <iostream>
#include <cmath>
using std::cout;

unsigned pentagonal(int num) {
    return (num * (3 * num - 1)) / 2;
}

unsigned* getPentagonalNumbers(size_t limit, size_t& pent_count) {
    size_t sqrt_lim = (size_t)sqrt(limit) + 1;
    unsigned* arr = new unsigned[sqrt_lim * 2 + 1]();
    pent_count = 0;
    for(size_t i = 1; i <= sqrt_lim; i++) {
        unsigned temp = pentagonal(i);
        arr[pent_count++] = temp;
        temp = pentagonal(-(int)i);
        arr[pent_count++] = temp;
    }
    unsigned* result = new unsigned[pent_count];
    std::copy(arr, arr + pent_count, result);
    delete[] arr;
    return result;
}
unsigned long long getPartitions(unsigned long long *arr, size_t number, unsigned *pent, size_t pent_count) {
    arr[0] = 1;
    for (size_t i = 1; i <= number; i++) {
        for (size_t j = 0; pent[j] <= i; j++) {
            if (j % 4 < 2) {
                arr[i] += arr[i - pent[j]];
            }
            else {
                arr[i] -= arr[i - pent[j]];
            }
        }
    }
    return arr[number];
}

int main() {
    size_t pent_count = 0;
    size_t N = 0;
    std::cin >> N;
    unsigned* pent = getPentagonalNumbers(N, pent_count);
    unsigned long long* partitions = new unsigned long long[N+1]();

    cout << getPartitions(partitions, N, pent, pent_count);
    delete[] partitions;
    delete[] pent;
    return 0;
}