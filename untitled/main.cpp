#include <iostream>
#include <cmath>
#include <deque>

int main() {
    int n = 0;
    std::cin >> n;
    std::deque<int> divisors;
    int sqr_lim = (int)sqrt(n) + 1;
    for (int i = 2; i < sqr_lim; i++) {
        if (n%i==0){
            divisors.push_back(i);
            n/=i;
            sqr_lim = (int)sqrt(n)+1;
            i=1;
        }
    }
    if (n>=2) {
        divisors.push_back(n);
    }
    while (!(divisors.empty())) {
        std::cout << divisors.front() << " ";
        divisors.pop_front();
    }
    return 0;
}