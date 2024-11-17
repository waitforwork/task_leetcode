#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    int shortestSubarray(std::vector<int>& nums, int k) {
            const int n=nums.size();
            int sum[n];
            sum[0]=nums[0];
            int dp[n], front =0, back=-1,len=1e9; //deque dp
            for (int i=0;i<n;i++)
            {
                if (i>0) sum[i]=sum[i-1]+nums[i];
                if (sum[i]>=k) len=std::min(len, i+1);
                while(front<=back && sum[i]-sum[dp[front]]>=k)
                {
                    len=std::min(len, i-dp[front]);
                    front++;
                }
                while(front<=back && sum[i]<=sum[dp[back]]) back--;
                dp[++back]=i;
            }
            return len==1e9?-1:len;
        }
};

int main()
{
    int n=3, x=4;
    std::string a="abcdl";
    std::string b="ghj";
    std::vector<int> c={1, 2, 3, 4, 3, 2, 5};
    Solution sol;
    std:: cout << "answer: \n" << sol.shortestSubarray(c,4);
}
