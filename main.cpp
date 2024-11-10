#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    std::string mergeAlternately(std::string word1, std::string word2)
    {
        int length;
        std::string ans="";
        std::string temp="";
        if (word1.length()<word2.length())
        {
            length=word1.length();
            for (int it=word1.length();it<word2.length();it++)
                temp.push_back(word2[it]);
        }
        if (word1.length()>word2.length())
        {
            length=word2.length();
            for (int it=word2.length();it<word1.length();it++)
                temp.push_back(word1[it]);
        }
        for (int it=0;it<length;it++)
        {

            ans.push_back(word1[it]);
            ans.push_back(word2[it]);
        }
        ans.append(temp);
        return ans;
    }
};

int main()
{
    int n=3, x=4;
    std::string a="abcdl";
    std::string b="ghj";
    Solution sol;
    std:: cout << "answer: \n" << sol.mergeAlternately(a,b);
}
