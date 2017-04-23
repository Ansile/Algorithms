#include <iostream>
#include <memory.h>
#include <malloc.h>
class Deque {
public:
    Deque(size_t capacity = 32);
    Deque(Deque& deque);
    ~Deque();

    void pushFront(int item);
    int popFront();
    void pushBack(int item);
    int popBack();

private:
    int* buffer = NULL;
    size_t size = 0;
    size_t head = 0;
    size_t tail = 0;
    const unsigned int expand_coeff = 2;

    size_t decr_index(size_t index); //сдвигаем индекс назад по буферу
    size_t incr_index(size_t index); //сдвигаем индекс вперед по буферу
    void expand_buf();
};

Deque::Deque(size_t capacity)
        : size(capacity),
          buffer((int*)malloc(sizeof(int) * capacity)),
          head(0),
          tail(0) {}

Deque::Deque(Deque& deque) {
    size = deque.size;
    head = deque.head;
    tail = deque.tail;
    if (buffer != NULL) {
        free(buffer);
    }
    buffer = (int*)malloc(sizeof(int) * size);
    memcpy(buffer, deque.buffer, sizeof(int) * size);
}

Deque::~Deque() { free(buffer); }

void Deque::pushFront(int item) {
    size_t newIndex = decr_index(head);
    if (newIndex == tail) {
        expand_buf();
        newIndex = decr_index(head);
    }
    head = newIndex;
    buffer[head] = item;
}

int Deque::popFront() {
    if (head == tail) {
        return -1;
    }
    int item = buffer[head];
    head = incr_index(head);
    return item;
}

void Deque::pushBack(int item) {
    size_t newIndex = incr_index(tail);
    if (newIndex == head) {
        expand_buf();
        newIndex = incr_index(tail);
    }
    buffer[tail] = item;
    tail = newIndex;
}

int Deque::popBack() {
    if (head == tail) {
        return -1;
    }
    tail = decr_index(tail);
    return buffer[tail];
}

size_t Deque::incr_index(size_t index) {
    if (index + 1 != size) {
        return index + 1;
    } else {
        return 0;
    }
}

size_t Deque::decr_index(size_t index) {
    if (index != 0) {
        return index - 1;
    } else {
        return size - 1;
    }
}

void Deque::expand_buf() {
    unsigned int added_memory = size * (expand_coeff - 1);
    size *= expand_coeff;
    buffer = (int*)realloc(buffer, sizeof(int) * size);
    if (tail < head) { //перенос данных
        memmove(buffer + head + added_memory, buffer + head, sizeof(int) * (size - added_memory - head));
        head += added_memory;
    }
}

bool dequeTest(Deque &test_deque, int cmd, int value) {
    switch (cmd) {
        case 1:
            test_deque.pushFront(value);
            return true;

        case 2:
            return test_deque.popFront() == value;

        case 3:
            test_deque.pushBack(value);
            return true;

        case 4:
            return test_deque.popBack() == value;

        default:
            return false;
    }
}

int main() {
    Deque deque;

    size_t n;
    std::cin >> n;
    
    bool answer = true;
    int value, command;
    
    for (int i = 0; i < n; i++) {
        std::cin >> command;
        std::cin >> value;
        
        answer = answer && dequeTest(deque, command, value);
    }
    
    if (answer) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
