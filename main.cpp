#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

class Solution {
public:
    int maxMoves(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        int maxMoves = 0;

        for (int col = n - 2; col >= 0; --col) {
            for (int row = 0; row < m; ++row) {
                if (row > 0 && grid[row][col] < grid[row - 1][col + 1]) {
                    dp[row][col] = std::max(dp[row][col], dp[row - 1][col + 1] + 1);
                }
                if (grid[row][col] < grid[row][col + 1]) {
                    dp[row][col] = std::max(dp[row][col], dp[row][col + 1] + 1);
                }
                if (row < m - 1 && grid[row][col] < grid[row + 1][col + 1]) {
                    dp[row][col] = std::max(dp[row][col], dp[row + 1][col + 1] + 1);
                }
            }
        }

        for (int row = 0; row < m; ++row) {
            maxMoves = std::max(maxMoves, dp[row][0]);
        }
        return maxMoves;
    }
};

int main()
{
    std::vector<std::vector<int>> my_vec={{2,4,3,5},{5,4,9,3,},{3,4,2,11},{10,9,13,15}};
    Solution sol;
    sol.maxMoves(my_vec);
    return 0;
}
