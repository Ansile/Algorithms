#include <iostream>
template <class T>
class Stack {
private:
    T* stackPtr; //указатель на стек
    size_t size; //размер стека
    size_t count; //кол-во элементов
    void resize(size_t new_size);
    size_t expand_coeff = 2;
public:
    Stack(int = 10); //размер по умолчанию - 10 элементов
    Stack(const Stack<T> &); //конструктор копирования
    ~Stack();

    void push(const T &); //добавить элемент
    T top();
    void pop(); //выкинуть верхний элемент
    size_t getSize() const;
    size_t getCount() const;
    T *getPtr() const;
};

size_t finishSequence(char* input, size_t& length, char*& result);

int main() {
    Stack<char> stack;
    char tmp = 0;
    while (std::cin >> tmp) {
        stack.push(tmp);
    }
    char* sequence = stack.getPtr();
    size_t count = stack.getCount();
    char* result = nullptr;
    size_t result_len = finishSequence(sequence, count, result);
    if (result_len != 0) {
        for(size_t i = 0; i < result_len; i++) {
            std::cout << result[i];
        }
    }
    else {
        std::cout << "IMPOSSIBLE";
    }
    delete[] result;
    return 0;
}


//Возвращает длину итоговой последовательности или же 0, если таковой не существует
size_t finishSequence(char* input, size_t& length, char*& result) {
    Stack<char> pending, seq_beg;

    for(size_t i=0; i<length; i++) {
        switch(input[i]) {
            case '(':
            case '{':
            case '[':
                pending.push(input[i]); //добавляем в массив ожидающих проверки
                break;

            case ')':
                if(pending.getCount()==0) {
                    seq_beg.push('(');
                }
                else if(pending.top() == '(') {
                    pending.pop(); //убираем лишние скобки из ожидания
                } else {
                    return 0;
                }
                break;

            case '}':
                if(pending.getCount()==0) {
                    seq_beg.push('{');
                }
                else if(pending.top() == '{') {
                    pending.pop(); //убираем лишние скобки из ожидания
                } else {
                    return 0;
                }
                break;

            case ']':
                if(pending.getCount()==0) {
                    seq_beg.push('[');
                }
                else if(pending.top() == '[') {
                    pending.pop(); //убираем лишние скобки из ожидания
                } else {
                    return 0;
                }
                break;
        }
    }
    size_t count = seq_beg.getCount();
    size_t pending_count = pending.getCount();
    size_t sum_count = count + pending_count + length;
    result = new char[sum_count];
    for(size_t i = 0; i < count; i++) { //добавляем в вывод парные открывающие скобки
        result[i] = seq_beg.top();
        seq_beg.pop();
    }
    for (size_t i = 0; i < length; i++) { //добавляем в вывод основную последовательность
        result[i+count] = input[i];
    }
    count += length;
    for (size_t i = count; i < sum_count; i++) { //добавляем в вывод парные закрывающие скобки
        switch(pending.top()) {
            case '(':
                result[i] = ')';
                break;
            case '{':
                result[i] = '}';
                break;
            case '[':
                result[i] = ']';
                break;
        }
        pending.pop();
    }
    return sum_count;
}


template <typename T>
Stack<T>::Stack(int MaxSize) :
        size(MaxSize)
{
    stackPtr = new T[size];
    count = 0;
}

template <typename T>
Stack<T>::Stack(const Stack<T> & copyStack) :
        size(copyStack.getSize())
{
    stackPtr = new T[size];
    count = copyStack.getCount();
    for (int i = 0; i < count; i++)
        stackPtr[i] = copyStack.getPtr()[i];
}

template <typename T>
Stack<T>::~Stack() {
    delete[] stackPtr;
}

template <typename T>
void Stack<T>::push(const T &elem) {
    if (count == size) {
        resize(size * expand_coeff);
    }
    stackPtr[count++] = elem;
}

template <typename T>
void Stack<T>::pop() {
    --count;
}

template <typename T>
T Stack<T>::top() {
    return stackPtr[count-1];
}

template <typename T>
size_t Stack<T>::getCount() const {
    return count;
}

template <typename T>
size_t Stack<T>::getSize() const {
    return size;
}

template <typename T>
T* Stack<T>::getPtr() const {
    return stackPtr;
}

template <typename T>
void Stack<T>::resize(size_t new_size) {
    T* new_stack = new T[new_size];
    std::copy(stackPtr, stackPtr + size, new_stack);
    delete[] stackPtr;

    size = new_size;
    stackPtr = new_stack;
}

