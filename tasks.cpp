#include "tasks.h"

tasks::tasks()
{

}
// на входе целочисленный массив, необходимо удалить дубликаты(оставить макс 2) из отсортированного массива без увеличения памяти, т.е. и вернуть количество элементов после удаления дубликатов
// простым циклом проверяем является ли дубликатом два индекса назад, если нет, то записываем значение итое и увеличиваем на единицу счетчик
int tasks::task_80(std::vector<int>& nums)
{
    if (nums.size() < 3) return nums.size();
    int in=2;
    for (unsigned int i=2; i < nums.size();i++)
    {
        if(nums[i]!=nums[in-2])
        {
            nums[in++]=nums[i];
        }
    }
    return in;
}
// на входе массив целых чисел и таргет, нужно вернуть индексы двух чисел из массива, сумма которых равна таргету
// берем мапу, в нее вставляем в качестве ключа значение разницы таргет и числа из массива а значение соответствует индексу
// далее начинаем искать в мапе, по ключу, если поисковый индекс не равен концу мапы, то мы нашли совпадение и возвращаем тогда индекс
// найденный(i) и значение в мапе по ключу, т.е. тоже индекс
std::vector<int> tasks::task_1(std::vector<int> &nums, int target)
{
    std::unordered_map<int,int> my_map;
    for (int i=0;i<nums.size(); i++)
    {
        int temp=target - nums[i];
        if (my_map.find(temp)!=my_map.end())
        {
            return {my_map[temp],i};
        } else
        {
            my_map[nums[i]] = i;
        }
    }
    return {};
}
// на входе у нас массив интов, необходимо вернуть количество возможных комбинаций чисел, чтобы получилось максимальное побитовое и
//для начала нам необходимо выполнить побитово и(I) всех чисел, чтобы найти максимально возможное число
//после этого передаем в функцию, массив чисел, индекс, текущее число, максимально возможное число, и счетчик совпадений
//если у нас текущее число совпало с максимальным, то мы увеличиваем счетчик на 1
//после этого для каждого значения начинаем рекурсивно вызывать функцию, с индексом+1, складываем текущее значение с числом из массиво побитово и
// 5=101, 3=11, 5+3=8, побитово и 101+011=111=7
void tasks::task_2044_1(const std::vector<int> &nums, int index, int current_num, int max_num, int &count)
{
    if (current_num == max_num)
    {
        count++;
    }
    for (unsigned int i = index; i < nums.size(); ++i)
    {
        task_2044_1(nums, i + 1, current_num | nums[i], max_num, count);
    }
}

int tasks::task_2044_2(std::vector<int> &nums)
{
    int max_num = 0;
    int count = 0;
    for (auto num : nums)
    {
        max_num=max_num | num;
    }
    task_2044_1(nums, 0, 0, max_num, count);

    return count;
}
// на входе имеем 2 положительных числа n и k, нужно вернуть значение расположенное в к-ом индексе
//Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
//S1 = "0"
//S2 = "011"
//S3 = "0111001"
//S4 = "011100110110001"
// нам необходимо инвертировать, развернуть значение, потом конкатенацией посчитать всю строку, начиная с индекса n
std::string tasks::task_1545_1(int n, int index, std::string &str)
{
    // когда мы дошли до конца(n)
    if(index == n) return str; // возвращаем конечную строчку
    // создаем перевернутую и инвертированную строку
    std::string rev = "";
    for(auto c : str)
    {
        if(c == '0') rev += "1"; else rev += "0";
    }
    std::reverse(rev.begin(), rev.end()); // переворачиваем строку
    // приводим к условиям задачи Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
    std::string temp = str + "1" + rev;
    // рекурсивно строим строку для следующего уровня индекс+1
    return task_1545_1(n, index + 1, temp);
}

char tasks::task_1545_2(int n, int k)
{
    std::string s="0"; // S1="0"
    std::string res=task_1545_1(n,1,s);
    return res[k-1]; // возвращаем значение расположенное в к-ом индексе
}


/*
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
    }*/

//задача состоит в том, чтобы вычислить логическое выражение, представленное в виде строки, которая может содержать логические И/ИЛИ/НЕ/True/False
//начинаем с вставления в стак символов всех, кроме ',' и '('
//если у нас пришел оператор &/|/!/f/t кладем их в стак
//если ')' то мы должны вычислить значение
bool tasks::task_1106(std::string exp)
{
    std::stack<char> st;
    char temp = ' ', op = ' ';
    for (char ch : exp)
    { //повторяем до конца строки, если в верхней части стека есть T, возвращаем значение true иначе false;
        if (ch == '(' || ch == ',') continue;
        if (ch == 't' || ch == 'f' || ch == '!' || ch == '&' || ch == '|')
            st.push(ch);  //заполнение стека идет тут
        else if (ch == ')')  //встретили скобку, начали обрабатывать выражения с конца пока не дошли до операторов
        {
            bool hasTrue = false, hasFalse = false;
            while ((!st.empty()) && (st.top()!='!') && (st.top()!='&') && (st.top()!='|'))  //как только вышли из цикла, в верхней части стека должен быть один из операторов
            {
                char val = st.top(); //приравниваем значение к последнему значению стека
                st.pop(); //удаляем символ из стека
                if (val == 't') hasTrue = true; //
                if (val == 'f') hasFalse = true;
            }

            if (!st.empty())  op=st.top(), st.pop();
            if (op == '!') temp = hasTrue ? 'f' : 't'; // если не, то меняем
            else if (op == '&') temp = (hasTrue && !hasFalse) ? 't' : 'f'; // если и, то проверяем
            else if (op == '|') temp = hasTrue ? 't' : 'f';
            st.push(temp);
        }
    }
    return st.top() == 't';
}
