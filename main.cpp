#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    std::vector<int> resultsArray(std::vector<int>& nums, int k) {
        int n= nums.size();
        int count=1;
        std::vector<int> ans(n-k+1,-1); //создали массив заполненный -1, размером с n-k+1
        int i=0,j=0;
        while(j<n)
        {
            if(j>0 && nums[j]-nums[j-1]!=1)
            {
                i=j;
            }
            while(i<j && j-i+1>k)
            {
                i++;
            }
            if(j-i+1==k)
                ans[j-k+1]=nums[j];
            j++;
        }
        return ans;
    }
};

int main()
{
    int n=3, x=4;
    std::string a="abcdl";
    std::string b="ghj";
    std::vector<int> c={1, 2, 3, 4, 3, 2, 5};
    Solution sol;
    for (auto i:sol.resultsArray(c,3) )
    std:: cout << "answer: \n" << i;
}
