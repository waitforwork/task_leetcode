#ifndef TASKS
#define TASKS
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <queue>
#include <map>
#include <cmath>
#include <bitset>
#include <numeric> //для iota

#include <stdio.h>
#include <stdint.h>

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
    TreeNode* task_2641(TreeNode* root);                                                                            //2641. Бинарное дерево
    bool task_951(TreeNode* root1, TreeNode* root2);                                                                //951. Бинарное дерево
    int task_1406_1(int p,int i,int n,std::vector<int> &piles,std::vector<std::vector<int>> &dp);                   //1406. вектор векторов
    std::string task_1406_2(std::vector<int>& stones);                                                              //1406. вектор векторов
    std::vector<std::string> task_1233(std::vector<std::string>& folder);                                           //1233. парсинг в строке
    int task_910(std::vector<int>& nums, int k);                                                                    //910. математика
    double task_1344(int hour, int minutes);                                                                        //1344. математика
    std::string task_1374(int n);                                                                                   //1374. строки
    std::vector<int> task_2458_1(TreeNode * root, std::vector<int>&queries);                                        //2458. бинарное дерево и вектор
    int task_2458_2(TreeNode* root, int level);                                                                     //2458. бинарное дерево и вектор
    int task_1996(std::vector<std::vector<int>>& properties);                                                       //1996. вектор векторов
    int task_1277(std::vector<std::vector<int>>& matrix);                                                           //1277. вектор векторов
    int task_2501(std::vector<int>& nums);                                                                          //2501.вектор в мапу
    int task_2684(std::vector<std::vector<int>>& grid);                                                             //2684. вектор векторов
    int task_1671(std::vector<int>& nums);                                                                          //1671. массивы
    std::vector<std::vector<int>> task_542(std::vector<std::vector<int>>& mat);                                     //542 дерево, массивы
    long long task_2463(std::vector<int>& robot, std::vector<std::vector<int>>& factory);                           //2463. вектор векторов
    std::string task_1957(std::string s);                                                                           //1957 строки, удаление повторов
    bool task_2490(std::string sentence);                                                                           //2490. строки, поиск
    bool task_796(std::string s, std::string goal);                                                                 //796. строки, сдвиг и сравнение
    std::string task_3163(std::string word);                                                                        //3163. строки, парсинг
    int task_2914(std::string s);                                                                                   //2914. строки
    bool task_3011(std::vector<int>& nums);                                                                         //3011. вектор и сортировка
    int tssk_2275(std::vector<int>& candidates);                                                                    //2275. вектор
    std::vector<int> task_1829(std::vector<int>& nums, int maximumBit);                                             //1829. вектор бинарные операции
    long long task_3133(int n, int x);                                                                              //3133. побитовое сложение
    int task_921(std::string s);                                                                                    //921. строки, парсинг
    std::string task_1768(std::string word1, std::string word2);                                                    //1768. строки, сложение
    bool task_2601(std::vector<int>& nums);                                                                         //2601. сортировка массива
    std::vector<int> task_2601(std::vector<std::vector<int>>& items, std::vector<int>& queries);                    //2070. арифметика, массивы
    long long task_2563(std::vector<int>& nums, int lower, int upper);                                              //2563. арифметика, массив
    int task_2064_1(int n, std::vector<int>& quantities);                                                           //2064. арифметика, векторы
    int task_2064_2(int n,std::vector<int>&quantities,int mid);                                                     //2064. арифметика, векторы
    int task_1574(std::vector<int>& arr);                                                                           //1574. математика вектор
    std::vector<int> task_3254(std::vector<int> nums, int k);                                                       //3254. арифметика вектор
    int task_862(std::vector<int>& nums, int k);                                                                    //862. deque, и сумма чисел
    std::vector<int> task_1652(std::vector<int>& code, int k);                                                      //1652. вектор математика
    long long task_2461(std::vector<int>& nums, int k);                                                             //2461. вектор, математика
    int task_2516(std::string s, int k);                                                                            //2516. поиск в строке
    int task_2257(int m, int n, std::vector<std::vector<int>>& guards, std::vector<std::vector<int>>& walls);       //2257. вектора, игра
    int task_1072(std::vector<std::vector<int>>& matrix);                                                           //1072. вектор перестановка
    std::vector<std::vector<char>> task_1861(std::vector<std::vector<char>>& box);                                  //1861. вектор векторов
    long long task_1975(std::vector<std::vector<int>>& matrix);                                                     //1975. матрица, перемножение
    int task_773(std::vector<std::vector<int>>& board);                                                             //773. вектор векторов
    int task_2924(int n, std::vector<std::vector<int>>& edges);                                                     //2924. вектор векторов
    std::vector<int> task_3243(int n, std::vector<std::vector<int>>& queries);                                      //3243. вектор векторов
    int task_2290(std::vector<std::vector<int>>& grid);                                                             //2290. вектор векторов
    int task_2577(std::vector<std::vector<int>>& grid);                                                             //2577. вектор векторов
    std::vector<std::vector<int>> task_2097(std::vector<std::vector<int>>& pairs);                                  //2097. вектор векторов
    bool task_1346(std::vector<int>& arr);                                                                          //1346. поиск по вектору
    int task_1455(std::string sentence, std::string searchWord);                                                    //1455. поиск в строке
private:
    std::vector<int> result; //501
        int prev = 0;        //501
        int counter = 0;     //501
        int maxi = 0;        //501
        std::vector<int> depth, levelArr, max1, max2;   //2458
        int getMaxElement(std::vector<int>& nums);//2601
};

#endif // TASKS
