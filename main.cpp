#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    std::vector<int> getMaximumXor(std::vector<int>& nums, int maximumBit) {

    }
};

int main()
{
    unsigned int year;
    std::cin >> year;
    if (year%400==0) std::cout << "YES";
    else if (year%100==0) std::cout << "NO";
    else if (year%4 ==0) std::cout << "YES";
    else std::cout << "NO";
}
