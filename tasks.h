#ifndef TASKS
#define TASKS
#include <vector>
#include <unordered_map>
#include <algorithm>

class tasks
{
public:
    tasks();
    int task_80(std::vector<int>& nums);        //80. Remove Duplicates from Sorted Array II
    void task_88(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);   //88. Merge Sorted Array
    std::vector<int> task_1(std::vector<int>& nums, int target); //1. Two Sum
    void task_2044_1(const std::vector<int> &nums, int index, int current_num, int max_num, int &count); //2044. Count Number of Maximum Bitwise-OR Subsets
    int task_2044_2(std::vector<int> &nums); //2044. Count Number of Maximum Bitwise-OR Subsets
    std::string task_1545_1(int n, int index, std::string &str);
    char task_1545_2(int n, int k);
};

#endif // TASKS
