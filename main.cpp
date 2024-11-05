#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    std::string compressedString(std::string word) {
        std::string comp = "";
        int cnt = 1;
        char ch = word[0];
        for(int i=1;i<word.size();i++){
            if(word[i] == ch && cnt < 9)cnt++;
            else{
                comp.push_back(cnt+'0');
                comp.push_back(ch);
                ch = word[i];
                cnt = 1;
            }
        }
        comp.push_back(cnt+'0');
        comp.push_back(ch);
        return comp;
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
