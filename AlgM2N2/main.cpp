#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
template <class T>
class BinaryHeap {

public:
    BinaryHeap(vector<T>& heap_array):
            buffer(heap_array),
            count(heap_array.size())
    {}

    void siftDown(int i);
    void SiftUp(int index);

    void buildHeap ();

private:
    vector<T> buffer;
    int count;
};

    unsigned greedyCounter (vector<unsigned>& input, unsigned max_weight) {

        BinaryHeap<unsigned> heap(input);
        heap.buildHeap();

        unsigned counter = 0;
        return counter;
    }

int main() {
    vector<unsigned> vect = {1, 2, 4, 5, 6, 8, 9, 10, 11, 16};
    std::cout << vect.size() << std::endl;
    BinaryHeap<unsigned> heap(vect);
    heap.buildHeap();
    for (int i = 0; i < vect.size(); i++) {
        std::cout << heap.buffer.at(i) << " ";
    }
    return 0;
}

template <class T>
void BinaryHeap<T>::buildHeap() {
    //std::make_heap(buffer.begin(), buffer.end());

    for(int i = buffer.size() / 2 - 1; i >=0; i--) {
        BinaryHeap::siftDown(i);
    }

}

void BinaryHeap::SiftUp(int index) {
    while(index > 0) {
        int parent = (index - 1) / 2;
        if (buffer[index] <= buffer[parent])
            return;
        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

void BinaryHeap::siftDown(int i) {
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