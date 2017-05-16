#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using std::string;

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
    Stack(int = 128); //размер по умолчанию - 128 элементов
    Stack(const Stack<T> &); //конструктор копирования
    ~Stack();

    void push(const T &); //добавить элемент
    T pop(); //взять верхний элемент
    int getSize() const;
    int getCount() const;
    T *getPtr() const;
};

class MSD {
public:
    static void sort(std::string* a, int N);
private:
    void msd(std::string* sorting_arr, int lower_bound, int higher_bound, int index);
    static const int R = 256;        // размер алфавита
    string* aux;       // дополнительный массив для распределения

    static inline int charAt(string& s, int count) {
        return count < s.length() ? s[count] : -1;
    }
};
int main() {
    string input_tmp = "";
    Stack<string> input_stack;
    while (std::cin >> input_tmp) {
        input_stack.push(input_tmp);
    }
    int input_length = input_stack.getCount();
    string* input_arr = input_stack.getPtr();
    MSD::sort(input_arr, input_length);
    for (int i = 0; i < input_length ; i++)
    {
        std::cout << input_arr[i] << std::endl;
    }
    return 0;
}

void MSD::sort(std::string* a, int N) {
    MSD temp;
    temp.aux = new string[N];
    temp.msd(a, 0, N-1, 0);
    delete[] temp.aux;
}

void MSD::msd(std::string* sorting_arr,  int lower_bound, int higher_bound, int index) {
// Сортируем от sorting_arr[lower_bound] до sorting_arr[higher_bound], начиная с index-го символа.
    assert(index < 1000);
    if (higher_bound <= lower_bound)
        return;
    std::vector<int> count (R+2);        // Вычисляем количества повторений
    for (int i = lower_bound; i <= higher_bound; i++)
        count[charAt(sorting_arr[i], index) + 2]++;

    for (int r = 0; r < R+1; r++)      // Преобразуем количества в индексы
        count[r+1] += count[r];

    for (int i = lower_bound; i <= higher_bound; i++)     // Распределим в дополнительный массив
        aux[count[charAt(sorting_arr[i], index) + 1]++] = sorting_arr[i];

    for (int i = lower_bound; i <= higher_bound; i++)     // Скопируем обратно
        sorting_arr[i] = aux[i - lower_bound];
    // Произведём сортировку для каждого символа
    for (int r = 3; r < R; r++)
        msd(sorting_arr, lower_bound + count[r], lower_bound + count[r+1] - 1, index+1);
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