#include <iostream>
#include <algorithm>
#include <cassert>

template <class T>
class Stack
{
private:
    T* stackPtr; //указатель на стек
    size_t size; //размер стека
    int count; //кол-во элементов
    void resize(size_t new_size);
    size_t expand_coeff = 2;
public:
    Stack(int = 10); //размер по умолчанию - 10 элементов
    Stack(const Stack<T> &); //конструктор копирования
    ~Stack();

    void push(const T &); //добавить элемент
    T pop(); //взять верхний элемент
    int getSize() const;
    int getCount() const;
    T *getPtr() const;
};

class Athlete
{
public:
    unsigned mass;
    unsigned strength;
    friend bool operator< (const Athlete& a, const Athlete& b);
    friend bool operator> (const Athlete& a, const Athlete& b);
};

bool operator< (const Athlete& a, const Athlete& b) {
    return a.mass == b.mass ? a.strength < b.strength : a.mass < b.mass;
}

bool operator> (const Athlete& a, const Athlete& b) {
    return a.mass == b.mass ? a.strength > b.strength : a.mass > b.mass;
}

void quickSortR(Athlete* a, long size);

unsigned maxHeight(Athlete* athletes, size_t athletes_count) {

    if (athletes_count == 0) {
        return 0;
    }

    quickSortR(athletes, athletes_count);

    unsigned cur_height = 1;
    for (unsigned i = 1, cur_mass = athletes[0].mass; i < athletes_count; i++) {
        if (athletes[i].strength >= cur_mass) {
            cur_mass += athletes[i].mass;
            cur_height++;
        }
    }
    return cur_height;
}


int main() {
    size_t athl_count = 0;

    Stack <Athlete> input;
    unsigned temp_mass = 0;
    unsigned temp_strength = 0;
    while (std::cin >> temp_mass && std::cin >> temp_strength) {
        Athlete temp;
        temp.strength = temp_strength;
        temp.mass = temp_mass;
        athl_count++;
        input.push(temp);
    }

    auto arr = input.getPtr();
    unsigned result = maxHeight(arr, athl_count);
    delete[] arr;
    std::cout << result;
    return 0;
}

template <typename T>
Stack<T>::Stack(int capacity) :
        size(capacity)
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
Stack<T>::~Stack()
{
    delete[] stackPtr;
}

template <typename T>
void Stack<T>::push(const T &elem)
{
    if (count == size) {
        resize(size*expand_coeff);
    }
//проверка переполнения
    stackPtr[count++] = elem;
}

template <typename T>
T Stack<T>::pop()
{
    assert(count > 0); //проверка наличия элементов в стеке
    return stackPtr[--count];
}

template <typename T>
int Stack<T>::getCount() const
{
    return count;
}

template <typename T>
int Stack<T>::getSize() const
{
    return size;
}

template <typename T>
T* Stack<T>::getPtr() const
{
    return stackPtr;
}


template <typename T>
void Stack<T>::resize(size_t new_size)
{
    T* new_stack = new T[new_size];
    std::copy(stackPtr, stackPtr + size, new_stack);
    delete[] stackPtr;

    size = new_size;
    stackPtr = new_stack;
}

void quickSortR(Athlete* a, long size) {
    const size_t MAXSTACK = 1024;
    long i, j; // указатели, участвующие в разделении

    long lb, ub; // границы сортируемого в цикле фрагмента

    long lbstack[MAXSTACK], ubstack[MAXSTACK]; // стек запросов
// каждый запрос задается парой значений,
// а именно: левой(lbstack) и правой(ubstack)
// границами промежутка

    long stackpos = 1; // текущая позиция стека
    long ppos; // середина массива
    Athlete pivot; // опорный элемент
    Athlete temp;

    lbstack[1] = 0;
    ubstack[1] = size - 1;

    do {

// Взять границы lb и ub текущего массива из стека.

        lb = lbstack[stackpos];
        ub = ubstack[stackpos];
        stackpos--;

        do {
// Шаг 1. Разделение по элементу pivot

            ppos = (lb + ub) >> 1;
            i = lb; j = ub; pivot = a[ppos];

            do {
                while (a[i] < pivot) i++;
                while (pivot < a[j]) j--;

                if (i <= j) {
                    temp = a[i]; a[i] = a[j]; a[j] = temp;
                    i++; j--;
                }
            } while (i <= j);

// Сейчас указатель i указывает на начало правого подмассива,
// j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
// Возможен случай, когда указатель i или j выходит за границу массива

// Шаги 2, 3. Отправляем большую часть в стек и двигаем lb,ub

            if (i < ppos) { // правая часть больше

                if (i < ub) { // если в ней больше 1 элемента - нужно
                    stackpos++; // сортировать, запрос в стек
                    lbstack[stackpos] = i;
                    ubstack[stackpos] = ub;
                }
                ub = j; // следующая итерация разделения
// будет работать с левой частью

            }
            else { // левая часть больше

                if (j > lb) {
                    stackpos++;
                    lbstack[stackpos] = lb;
                    ubstack[stackpos] = j;
                }
                lb = i;
            }

        } while (lb < ub); // пока в меньшей части более 1 элемента

    } while (stackpos != 0); // пока есть запросы в стеке
}