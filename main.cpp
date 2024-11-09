#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    long long minEnd(int n, int x) {
        long result=x;
        long remaining=n-1;
        long position=1;
        while(remaining)
        {
            if (!(x&position))
            {
                result|=(remaining&1)*position;
                remaining>>=1;
            }
            position<<=1;
        }
        return result;
    }
};

int main()
{
    int n=3, x=4;
    Solution sol;
    std:: cout << "answer: \n" << sol.minEnd(n,x);
}
