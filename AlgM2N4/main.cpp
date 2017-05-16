#include <iostream>
#include <memory>
#include <vector>
#include <cstddef>
#include <algorithm>

template <class T>
void mergeSort(T* start, T* end);

int main() {
    int N = 0;
    std::cin >> N;

    int K = 0;
    std::cin >> K;
    std::vector<int> vect(2*K);

    for (int i = K; i < 2*K; i++) {
        std::cin >> vect[i];
    }

    for (int i = K; i < N; i++) {
        int j = i % K;
        std::cin >> vect[j];
        if (j == K - 1) {
            mergeSort(vect.data(), vect.data() + 2 * K);
            for (int k = 0; k < K; k++) {
                std::cout << vect[k] << " ";
            }
        }
    }

    mergeSort(vect.data(), vect.data() + vect.size());

    std::rotate(vect.data(), vect.data() + K - N % K, vect.data() + 2 * K);

    for (int i = 0; i < vect.size() + N % K - K; i++) {
        std::cout << vect[i] << " ";
    }

    return 0;
}

template <class T>
void merge (T* start, T* end, long half_count) {
    long count = end - start;

    T* first_half = new T[half_count + 1];
    std::copy(start, start + half_count, first_half);

    T* second_half = new T[end - start - half_count];
    std::copy(start + half_count, end, second_half);

    long i = 0;
    long j = 0;
    long k = 0;

    while (i < half_count && j < count - half_count) {
        if (first_half[i] <= second_half[j]) {
            start[k] = first_half[i];
            i++;
        }
        else {
            start[k] = second_half[j];
            j++;
        }
        k++;
    }

    if (i < half_count) {
        std::copy(first_half + i, first_half + half_count, start + k);
    } else if (j < count - half_count) {
        std::copy(second_half + j, second_half + count - half_count, start + k);
    }

    delete[] first_half;
    delete[] second_half;

}

template <class T>
void mergeSort(T* start, T* end) {

    if (start == end) {
        return; //если 1 элемент, сортировать нечего
    }
    long half_count = (end - start) / 2;
    if (start + 1 == end) { //если 2 элемента - сортируем в 1 действие
        if (*start > *end) {
            std::swap(start, end);
            return;
        }
    }
    else {
        mergeSort(start,  start + half_count); //сортируем левую половину
        mergeSort(start + half_count, end); //сортируем правую половину
    }

    merge(start, end, half_count);//сливаем половины
}