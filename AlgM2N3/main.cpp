#include <iostream>
#include <vector>

using std::vector;
template <class T>
class MaxHeap {

public:
    MaxHeap(vector<T> &heap_array, bool is_heap = false) :
            buffer(heap_array),
            count(heap_array.size())
    {
        if (!is_heap) {
            this->buildHeap();
        }
    }

    int getCount() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    T extractMax();

    void siftDown(int i);
    void siftUp(int index);
    void add(T element);
    void buildHeap ();
    static void heapSort (vector<T> &arr);

private:
    T extract_no_shrinking();
    vector<T>& buffer;
    int count;
};

class Customer {
public:
    unsigned coming_time;
    unsigned leaving_time;

    bool canWatch(const unsigned time) const;

    bool operator< (const Customer& rhs) const;
    bool operator> (const Customer& rhs) const;
    bool operator<= (const Customer& rhs) const;

};

bool Customer::canWatch(const unsigned time) const {
    return (time <= leaving_time && time >= coming_time);
}

bool Customer::operator< (const Customer& rhs) const {
    return leaving_time == rhs.leaving_time ? coming_time < rhs.coming_time : leaving_time < rhs.leaving_time;
}

bool Customer::operator> (const Customer& rhs) const {
    return leaving_time == rhs.leaving_time ? coming_time > rhs.coming_time : leaving_time > rhs.leaving_time;
}

bool Customer::operator<= (const Customer& rhs) const {
    return !(*this > rhs);
}


unsigned countAdvertisments (vector<Customer>& customer_times) {
    if (customer_times.empty()) {
        return 0;
    }
    MaxHeap<Customer>::heapSort(customer_times);
    unsigned ad_time1 = customer_times[0].leaving_time - 1;
    unsigned ad_time2 = customer_times[0].leaving_time;
    unsigned ad_count = 2;
    for (int i = 1; i < customer_times.size(); i++) {
        Customer current_customer = customer_times[i];
        if (!current_customer.canWatch(ad_time1)) {
            // еcли leaving_time не занято рекламой, ad_time1 = current_customer.leaving time
            // если занято, ad_time1 = current_customer.leaving_time - 1
            ad_time1 = current_customer.leaving_time - (ad_time2 == current_customer.leaving_time);
            ad_count++;
        }
        if (!current_customer.canWatch(ad_time2)) {
            // еcли leaving_time не занято рекламой, ad_time2 = current_customer.leaving time
            // если занято, ad_time2 = current_customer.leaving_time - 1
            ad_time2 = current_customer.leaving_time - (ad_time1 == current_customer.leaving_time);
            ad_count++;
        }
    }
    return ad_count;
}


int main() {
    int N = 0;
    std::cin >> N;
    vector<Customer> input(N);
    for (int i = 0; i < N; i++) {
        Customer temp;
        std::cin >> temp.coming_time >> temp.leaving_time;
        if (temp.coming_time < temp.leaving_time) {
            std::swap(temp.coming_time, temp.leaving_time);
        }
        input[i]=temp;
    }
    std::cout << countAdvertisments(input);
    return 0;
}

template <class T>
void MaxHeap<T>::buildHeap() {
    for(int i = buffer.size() / 2 - 1; i >= 0; i--) {
        MaxHeap<T>::siftDown(i);
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
    T result = extract_no_shrinking();
    buffer.pop_back();
    return result;
}


//Забирает максимум из кучи, не уменьшая буфер
//для обеспечения работы HeapSort in-place
template <class T>
T MaxHeap<T>::extract_no_shrinking() {
    T result = buffer[0];
    // Переносим последний элемент в корень.
    buffer[0] = buffer[count - 1];
    // Вызываем SiftDown для корня.
    count--;
    if(count > 1) {
        siftDown(0);
    }
    return result;
}

template <class T>
void MaxHeap<T>::add(T element) {
    buffer.push_back(element);
    count++;
    siftUp(buffer.size() - 1);
}

template <class T>
void MaxHeap<T>::heapSort (vector<T> &arr) {
    MaxHeap heap (arr, false);
    for (int i = heap.count - 1; i >= 0; i--) {
        T elem = heap.extract_no_shrinking();
        arr[i] = elem;
    }

}