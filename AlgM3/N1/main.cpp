#include <iostream>
#include <string>
#include <climits>
#include <sstream>
#include <cassert>

#define MDebug

class HashMap {
public:
    HashMap(size_t max_size = 8):
            size(max_size), count(0), buffer(new MapElem[max_size]()) {}

    unsigned long getHash(std::string input) const;
    unsigned long getHash2(std::string input) const;
    long indexOf(std::string elem) const; //returns -1 if elem is not found
    bool addElem(std::string);
    bool deleteElem(std::string);

    void expand();

    ~HashMap() {
        delete [] buffer;
    }

private:
    static const char empty = 0;
    static const char deleted = 1;
    static const char filled = 2;

    struct MapElem {
        MapElem(): status(empty) {}
        char status;
        std::string data;
    };

    const unsigned coeff_a = 3;
    const unsigned expand_coeff = 2;
    const double fill_coeff = 3.0/4.0;
    bool inline is_filled() const;

    MapElem* buffer;
    size_t count;
    size_t size;
};

void HashMap::expand() {
    size_t old_size = size;
    MapElem* old_buf = buffer;

    size *= expand_coeff;
    buffer = new MapElem[size];

    for (long current = 0; current < size; current++) {
        if (old_buf[current].status == filled) {
            assert(addElem(buffer[current].data));
        }
    }
}

unsigned long HashMap::getHash(std::string input) const{
    unsigned long hash = 0;
    for (int i = 0; i < input.length(); i++) {
        hash += input[i];
        hash *= coeff_a;
//        if (hash > ULONG_MAX / (coeff_a + 1)) {
//            hash %= table_size;
//        }
    }

    if (hash % 2 == 0) {
        --hash;
    }

    hash %= size;
#ifdef MDebug
    std::cout << "hash of " << input << " is " << hash << std::endl;
#endif
    return hash;
}

unsigned long HashMap::getHash2 (std::string input) const{
    input.push_back(input[0]);
    return getHash(input);
}

bool HashMap::addElem(std::string elem) {
    unsigned long hash1 = getHash(elem);
    unsigned long hash2 = getHash2(elem);
    long counter = -1;
    unsigned long current = hash1;
    do {
        counter++;
        current = (hash1 + counter * hash2);
        if (buffer[current].status == HashMap::empty ||
                buffer[current].status == HashMap::deleted)
        {
            buffer[current].status = HashMap::filled;
            buffer[current].data = elem;
            count++;
            if (this->is_filled()) {
                expand();
            }
            return true;
        } else {
            if (buffer[current].data == elem) {
                return false;
            }
        }
    } while (buffer[current].status != HashMap::empty);
    assert(false);
}

long HashMap::indexOf(std::string elem) const {
    unsigned long hash1 = getHash(elem);
    unsigned long hash2 = getHash2(elem);
    long counter = -1;
    unsigned long current = hash1;
    do {
        counter++;
        current = (hash1 + counter * hash2);
        if (buffer[current].status == HashMap::filled)
        {
            if(buffer[current].data == elem) {
                return current;
            }
        }
    } while (buffer[current].status != HashMap::empty);
    return -1;
}

bool HashMap::deleteElem(std::string elem) {
    long element_index = 0;
    if ((element_index = indexOf(elem)) == -1) {
        return false;
    }
    else {
        buffer[element_index].status = deleted;
        buffer[element_index].data.clear();
        return true;
    }
}

bool inline HashMap::is_filled() const {
    return size * fill_coeff > count;
}


int main() {
    std::string input;
    std::cin >> input;
    HashMap temp;
    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0) {
            input.push_back(char(rand()%64));
        } else {
            input.pop_back();
        }
        temp.addElem(input);
    }
    temp.addElem(input);
    std::cout << temp.indexOf(input);
//    std::stringstream temp;
//    temp << getHash(input, LONG_MAX);
//    std::cout << temp.getHash(input);
    return 0;
}