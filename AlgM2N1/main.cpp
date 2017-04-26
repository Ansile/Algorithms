#include <iostream>
#include <string>

/*1_4. Строки.

Напишите программу, печатающую набор строк в лексикографическом порядке.
Строки разделяются символом перевода строки '\n'. Если последний символ в потоке ввода '\n',
считать, что после него нет пустой строки. Максимальная длина строки 255 символов. Написать
свою функцию сравнения строк.*/

template <class T>
void insertionSort (T*, int, bool (*)(const T, const T));
bool isLess(const std::string, const std::string);


int main() {
    using std::string;
    using std::cin;
    using std::cout;
    using std::endl;

    size_t N = 0;
    cin >> N;
    string a;

    string* input = new string[N]();
    for (int i = 0; i<N; i++) {
        cin >> input[i];
    }
    insertionSort(input, N, isLess);
    for (int i = 0; i<N; i++) {
        cout << input[i] << "\n";
    }
    delete [] input;
    return 0;
}

template <class T>
void insertionSort (T* arr, int arr_len, bool (*isLess)(T, T)) {
    if (arr_len < 2) { return; }
    for (int i = 1; i < arr_len; i++) {
        T tmp = arr[i];
        int j = i - 1;

        for ( ; j>=0 && isLess(tmp, arr[j]); --j) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }
}

bool isLess(const std::string first, const std::string second) {
    size_t first_len = first.length();
    size_t second_len = second.length();
    size_t min_len = std::min(first_len, second_len);

    for (size_t i = 0; i < min_len; i++) {
        if (first.at(i) < second.at(i)) {
            return true;
        }
        if (first.at(i) > second.at(i)) {
            return false;
        }
    }
    if (first_len < second_len) {
        return true;
    }
    else {
        return false;
    }
}
    