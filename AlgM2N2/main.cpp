#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::vector;
template <class T>
class MaxHeap {

public:
    MaxHeap(vector<T> &heap_array) :
            buffer(heap_array),
            count(heap_array.size()) {}

    int getCount() const {
        return count;
    }
    bool empty() const {
        return count == 0;
    }
    void siftDown(int i);
    void siftUp(int index);
    T extractMax();
    void add(T element);
    void buildHeap ();
    vector<T> buffer;
private:

    int count;
};

unsigned greedyCounter (vector<unsigned>& input, unsigned max_weight) {
    MaxHeap<unsigned> heap(input);
    heap.buildHeap();
    unsigned counter = 0;
    while (!heap.empty()) {
        counter++;
        vector<unsigned> temp_arr;
        unsigned current_weight = 0; //вес фруктов, которые уже взяты
        while (!heap.empty()) {
            unsigned temp_max = heap.extractMax();
            if (current_weight + temp_max <= max_weight) {
                current_weight += temp_max;
                temp_arr.push_back(temp_max / 2);
                if (current_weight == max_weight) {
                    break;
                }
            }
            else {
                heap.add(temp_max);
                break;
            }
        }

        while(!temp_arr.empty()) {
            if (temp_arr.back() != 0) {
                heap.add(temp_arr.back());
                temp_arr.pop_back();
            }
            else {
                temp_arr.pop_back();
            }
        }
    }
    return counter;
}

int main() {
    int N = 0;
    std::cin >> N;
    vector<unsigned> vect(N);
    for (int i = 0; i < N; i++) {
        std::cin >> vect[i];
    }
    int K = 0;
    std::cin >> K;
    std::cout << greedyCounter(vect, K);
    return 0;
}

template <class T>
void MaxHeap<T>::buildHeap() {
    //std::make_heap(buffer.begin(), buffer.end());

    for(int i = buffer.size() / 2 - 1; i >=0; i--) {
        MaxHeap::siftDown(i);
    }

}

template <class T>
void MaxHeap<T>::siftUp(int index) {
    while(index > 0) {
        int parent = (index - 1) / 2;
        if (buffer[index] <= buffer[parent])
            return;
        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

template <class T>
void MaxHeap<T>::siftDown(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем большего сына, если такой есть.
    size_t largest = i;
    if (left < count && buffer[left] > buffer[i])
        largest = left;
    if (right < count && buffer[right] > buffer[largest])
        largest = right;
    // Если больший сын есть, то проталкиваем корень в него.
    if (largest != i) {
        std::swap(buffer[i], buffer[largest]);
        siftDown(largest);
    }
}

template <class T>
T MaxHeap<T>::extractMax() {
    // Запоминаем значение корня.
    int result = buffer[0];
    // Переносим последний элемент в корень.
    buffer[0] = buffer[count - 1];
    buffer[count - 1] = 0;
    buffer.pop_back();
    // Вызываем SiftDown для корня.
    if(!count != 1) {
        siftDown(0);
    }
    count--;
    return result;
}

template <class T>
void MaxHeap<T>::add(T element) {
    buffer.push_back(element);
    count++;
    siftUp(buffer.size() - 1);
}