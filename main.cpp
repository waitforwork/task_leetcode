#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat)
    {

    }
};

int main()
{
    std::vector<std::vector<int>> my_vec={{0,0,0},{0,1,0},{0,0,0}};
    std::unordered_map<int,int> map;
    for (int i=0;i<my_vec[0].size();i++)
    {
        for (int j=0;j<my_vec.size();j++)
        {
            if(my_vec[i][j]==1) std::cout << i << " " << j << std::endl;
        }
    }
    Solution sol;
    sol.updateMatrix(my_vec);
    return 0;
}
