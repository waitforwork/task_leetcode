#ifndef TASKS
#define TASKS
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <queue>

struct TreeNode //501,2583
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class tasks
{
public:
    tasks();
    int task_80(std::vector<int>& nums);                                                                            //80. удаление дубликатов
    void task_88(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);                                   //88. объединение массивов
    std::vector<int> task_1(std::vector<int>& nums, int target);                                                    //1. сложение
    void task_2044_1(const std::vector<int> &nums, int index, int current_num, int max_num, int &count);            //2044. подсчет максимума
    int task_2044_2(std::vector<int> &nums);                                                                        //2044. подсчет максимума
    std::string task_1545_1(int n, int index, std::string &str);                                                    //1545. парсинг в строке
    char task_1545_2(int n, int k);                                                                                 //1545. парсинг в строке
    bool task_1106(std::string exp);                                                                                //1106. парсинг строки
    int task_1593_1(int start, const std::string& s, std::unordered_set<std::string>& seen);                        //1593. разбиение строки
    int task_1593_2(std::string s);                                                                                 //1593. разбиение строки
    std::vector<int> task_501_1(TreeNode* root);                                                                    //501. Бинарное дерево
    std::vector<int> task_501_2(TreeNode* root);                                                                    //501. Бинарное дерево
    long long task_2583(TreeNode* root, int k);                                                                     //2583. Бинарное дерево
    int task_2315(std::string &s);                                                                                  //2315. парсинг строки
    std::vector<int> task_2574(std::vector<int>& nums);                                                             //2574. разность сумм слева и справа
    int task_1887(std::vector<int>& nums);                                                                          //1887. выравнивание вектора, все элементы д.б. равны
    TreeNode* task_2641(TreeNode* root);                                                                            //Бинарное дерево
    bool task_951(TreeNode* root1, TreeNode* root2);                                                                //Бинарное дерево
private:
    std::vector<int> result; //501
        int prev = 0;        //501
        int counter = 0;     //501
        int maxi = 0;        //501
};

#endif // TASKS
