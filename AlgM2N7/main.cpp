#include <iostream>
#include <cstring>

bool inline getNum(unsigned &out, int &tmp_char, int &iter) {
    int pos = 0;
    out = 0;
    iter = 0;

    static unsigned int DECIMAL_BUFFER[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
                                             100000000, 1000000000};

    static int char_buf[16] = {0};

    while ((tmp_char = getchar_unlocked()) > ' ') {
        char_buf[pos++] = tmp_char;
    }

    while (pos != 0)
        out += DECIMAL_BUFFER[iter++] * (char_buf[--pos] - '0');
    return tmp_char != EOF;
}

void inline printNum(int var) {
    int pos = 0;
    static int char_buf[16] = {0};

    while (var != 0) {
        char_buf[pos++] = var % 10 + '0';
        var /= 10;
    }
    
    while (pos != 0)
        putchar_unlocked(char_buf[--pos]);
    putchar_unlocked(' ');
}

void msdSort (unsigned* arr, int arr_len);

int main() {
    
    int tmp_char = 0;
    int pos = 0;
    int iter = 0;

    unsigned* input_arr = new unsigned [25000000];

    while (getNum(input_arr[pos++], tmp_char, iter));

    msdSort(input_arr, pos);

    for (int i = 10; i < pos; i+=10) {
        printNum(input_arr[i]);
    }

    delete[] input_arr;

    return 0;
}

short inline getByte(unsigned number, short byte_num) {
    return (short) ((number >> (byte_num * 8)) & 255);
}


void msdSort (unsigned * arr, int arr_len) {
    unsigned* aux_arr = new unsigned[arr_len];
    for (int byte_num = 0; byte_num < 4; byte_num++) {

        int* count_arr = new int[256]();
        for (int i = 0; i < arr_len; i++) {
            count_arr[getByte(arr[i], byte_num)]++;
        }

        int prev_value = 0;
        for (int i = 0; i < 256; i++) {
            int tmp = count_arr[i];
            count_arr[i] = prev_value;
            prev_value += tmp;
        }
        for (int i = 0; i < arr_len; i++) {
            unsigned byte = getByte(arr[i], byte_num);
            aux_arr[count_arr[byte]++] = arr[i];
        }
        delete[] count_arr;
        std::copy(aux_arr, aux_arr + arr_len, arr);
    }

    delete[] aux_arr;
}