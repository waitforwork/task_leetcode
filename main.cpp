#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    std::string compressedString(std::string word)
    {
        int count =1;
        std::string comp="";
        for (int i=0;i<word.size();i++)
        {
            if (count<9 && word[i]==word[i+1])
            {
                count++;
            } else
            {
                comp+=std::to_string(count)+word[i];
                count=1;
            }
        }
        return comp;
    }
};

int main()
{
    Solution sol;
    std::string s="aabcddddddddddde";
    std::string goal="cdeab";
    std:: cout << sol.compressedString(s) << std::endl;
}

