#include <iostream>
#include <tasks.h>
#include <algorithm>

class Solution {
public:
    char findKthBit(int n, int k) {
    if (n == 1)
    {
        return '0';
    }
    int len = (1 << n) - 1; //длинна равна, побитово сдвинутая единица на значение "n" 1<<3 1=>1000
    int mid = len / 2 + 1; // лен/2+1 вычисляем середину
    if (k == mid) //если к= середине, то возвращаем 1
    {
        return '1';
    }
    if (k < mid) // а пока к меньше середины вызываем функцию
    {
        return findKthBit(n - 1, k); // уменьшаем на единицу, и повторяем
    }
    char bit = findKthBit(n - 1, len - k + 1);
    return bit == '0' ? '1' : '0';
    }
};

int main()
{
    std::cout << "hello world" << std::endl;
    return 0;
}
/*tasks test;
std::vector<int> newvec = {1,1,1,2,2,3};
std::cout << test.task_80(newvec);*/
