#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    bool rotateString(std::string s, std::string goal)
    {
        bool ans;
        std::string temp=s+s;
        if (s.size()!=goal.size()) return false;
        return temp.find(goal)!=std::string::npos;
    }
};

int main()
{
    Solution sol;
    std::string s="abcde";
    std::string goal="cdeab";
    std:: cout << sol.rotateString(s,goal) << std::endl;
}

