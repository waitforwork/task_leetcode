#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    long long task_1975(std::vector<std::vector<int> > &matrix)
    {
        long long count_minus=0;
        long long sum=0;
        int min=INT_MAX;
        int height=matrix[0].size();
        int widht=matrix.size();
        if (height==0 & widht==0) return 0;
        for (int i=0;i<widht;i++)
            for (int j=0;j<height;j++)
            {
                if (matrix[i][j]<0) count_minus++;
                sum+=std::abs(matrix[i][j]);
                min=std::min(std::abs(matrix[i][j]),min);
            }
        if (count_minus==0) return sum;
        if (count_minus%2==0) return sum; else return (sum-min-min);
    }
};

int main()
{
    int n=3, x=4;
    std::string a="abcdl";
    std::string b="ghj";
    std::vector<std::vector<int>> c={{1, 2},{ 3, -4}, {-3, 2},{5,-2}};
    std::vector<std::vector<int>> c2={{1, -1},{-1, 1}};
    std::vector<std::vector<int>> c3={{1, 2,3},{-1,-2, -3}, {1, 2,3}};
    std::vector<std::vector<int>> c4={{1, 2},{3, -4}, {-3, 2},{5,-2}};
    std::vector<std::vector<int>> c5={{1, 2},{3, -4}, {-3, 2},{5,-2}};
    int koekak=5;
    std::cout << INT_MIN << std::endl;
    std::cout << " "<< INT_MAX << std::endl;
    if (!koekak%2) std::cout << "koekak: " << koekak%2 <<std::endl; else std::cout << "koekak2: " << koekak%2 << std::endl;
    Solution sol;
    std:: cout << "answer: \n" << sol.task_1975(c2);
}
