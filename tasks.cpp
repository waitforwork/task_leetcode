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
// Задача: разделить строку на максимальное количество уникальных подстрок
// решение, нужно начиная с 1(старт) символа, до последнего символва добавляем все возможные варианты в унордеред сет
// и рекурсивно начинаем проверять следующую часть строки, возвращая инт и сравнивая, стало ли больше
// максимальное количество уникальных подстрок= макссплитс
//после подсчета, мы удаляем подстроку из набора, чтобы можно было изучить другие варианты.
//и когда старт = длинне строки, значит мы долшли до конца строки и не можем ее больше разделить, возвращаем 0
// сложность О(N*2^N) время O(N)
int tasks::task_1593_1(int start, const std::string &s, std::unordered_set<std::string> &seen)
{
    if (start == s.size())
    {
        return 0;
    }
    int maxSplits = 0;
    for (int end = start + 1; end <= s.size(); ++end) {
        std::string substring = s.substr(start, end - start);
        if (seen.find(substring) == seen.end()) {
            seen.insert(substring);
            maxSplits = std::max(maxSplits, 1 + task_1593_1(end, s, seen));
            seen.erase(substring);
        }
    }
    return maxSplits;
}
int tasks::task_1593_2(std::string s)
{
    std::unordered_set<std::string> seen;
    return task_1593_1(0, s, seen);
}
// необходимо вернуть наиболее часто встречающийся элемент в дереве
//левое поддерево узла содержит только узлы с ключами, меньшими или равными ключу узла
// правое поддерево узла содержит только узлы с ключами
std::vector<int> tasks::task_501_1(TreeNode *root)
{
    if(!root) return result;

    task_501_1(root->left); //рекурсивно вызываем функцию,  передаем левую ветку

    if(prev == root->val) counter++; // если прев,= значению, увеличиваем счетчик
    else counter = 1;



    if(counter == maxi){    //если счетчик = максимальному, в вектор вставляем текущее значение
        result.push_back(root->val);
    }

    else if(counter > maxi){ // если счетчик больше максимального, то макси делаем счетчиком
        maxi = std::max(maxi, counter); // а результат приравниваем к текущему значению дерева
        result = {root->val};
    }

    prev = root->val; //прев делаем равным текущему значению
    task_501_1(root->right); // рекурсивно вызываем функцию, в качестве аргумента передаем правую ветку


}

std::vector<int> tasks::task_501_2(TreeNode *root)
{
    task_501_1(root);
    return result;// возвращаем значение вектора
}

// необходимо вычислить сумму значений узлов, на каждом уровне двоичного дерева, а затем найти к-ую по величине сумму,
//двоичное дерево можно обрабатывать уровень за уровнем с помощью поиска в ширину, BFS, потом сортируем в конце и выдаем к-ое по величине значение
// сложность О(N)-BFS сортировка сумм уровней О(LogN) итого O(N+LogN)
// временная сложность O(N)
long long tasks::task_2583(TreeNode *root, int k)
{
    std::vector<long long> res;      // Для хранения суммы каждого уровня
    std::queue<TreeNode*> q;         // Очередь для обхода по уровням (BFS)

    q.push(root);               // Запустить BFS с корневого узла   //*мои:вот тут мы поместили начало, в очереди, только корень
    while (!q.empty()) {
        int n = q.size();       // Количество узлов на текущем уровне
        long long sum = 0;      // Сумма значений узлов на текущем уровне

        // Обработать все узлы на текущем уровне
        while (n--) {
            TreeNode* node = q.front(); q.pop();   // Получить передний узел из очереди и удалить его
            sum += (long long)node->val;           // Добавить значение узла к сумме уровня //*мои:посчитали сумму

            // Поместить левые и правые дочерние элементы узла в очередь (если они существуют) //*мои:вставили в очередь, левую ветку и правую
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        } //*мои:и теперь у нас в очереди 2 элемента, while(n--) 2 раза,
        res.push_back(sum);     // Сохранить сумму текущего уровня //*мои: записываем в рез сумму корня и очередь уже не пустая, в ней 2 ветки
    }
    // Если k больше количества уровней, вернуть -1
    if (k > res.size()) return -1;

    // Сортировать суммы уровней в порядке убывания
    sort(res.begin(), res.end(), std::greater<long long>());

    // Возвращает k-ю наибольшую сумму уровня (k-1 из-за индексации, начинающейся с 0)
    return res[k-1];
}

// поиск и подсчет звездочек между палочками |
int tasks::task_2315(std::string &s)
{
    int start=0;
    int count=0;
    int end=0;
    bool find=true;
    for (int i=0;i<s.length(); i++)
    {
        if (s[i]=='|' && find)
        {
            start=i;
            find=false;
        } else
            if (s[i]=='|')
            {
                end=i;
                s.erase(start, end-start+1);
                i=0;
                find=true;
            }
    }
    for (auto i : s)
    {
        if(i=='*') count++;
    }
    return count;
}
//на входе вектор, нужно взять суммы слева и справа, а потом по модулю посчитать их разницу, вывести результаты в вектор
std::vector<int> tasks::task_2574(std::vector<int> &nums)
{
    std::vector<int> for_ret;
    int temp=0;
    for (int i=0;i<nums.size();i++)
    {
        for_ret.push_back(temp);
        temp+=nums[i];
    }
    temp=0;
    for (int i=nums.size()-1;i>=0;i--)
    {
        for_ret[i]=std::abs(for_ret[i]-temp);
        temp+=nums[i];
    }
    return for_ret;
}
// на входе вектор, нужно все элементы по очереди, приравнять к минимальному
int tasks::task_1887(std::vector<int> &nums)
{
    sort(nums.begin(),nums.end());
    int count=0;
    for(int i=nums.size()-1;i>=1;i--){
        if(nums[0]==nums[i]) break;
        else if(nums[i]==nums[i-1])continue;
        else
        {
            count+=nums.size()-i;
        }
    }
    return count;
}
//необходимо заменить значение каждого узла в дереве на сумму значений всех его соседей.

TreeNode *tasks::task_2641(TreeNode *root)
{
    if (!root) return nullptr;

    std::queue<TreeNode*> q;
    int prev = root->val;// вводим переменную прев, и присваиваем ей значение текущего элемента
    q.push(root);

    while (!q.empty()) //пока очередь не пустая
    {
        int size = q.size(); //размер очереди, каждый раз
        int curr = 0; //текущая сумма
        while (size > 0) // пока размер больше нуля
        {
            TreeNode* temp = q.front(); //в временную переменную переписываем очередь,
            q.pop(); //и удаляем из очереди
            int leftRight = (temp->left ? temp->left->val : 0) + (temp->right ? temp->right->val : 0); //сумма левого и правого значения
            if (temp->left) //если у темпа есть левое значение
            {
                temp->left->val = leftRight; //то мы левому текущему значению присваиваем сумму левого+правого
                q.push(temp->left); //толкаем в очередь, новое значение левого и правого
            }
            if (temp->right) //аналогично
            {
                temp->right->val = leftRight;
                q.push(temp->right);
            }
            curr += leftRight; //обновляем значение текущей суммы
            temp->val = prev - temp->val; //обновляем значение текущего у темпа за
            size--;
        }
        prev = curr;
    }
    return root;
}
// необходимо перевернуть эквивалентные двоичные деревья,
//возвращаем труе, если два дерева эквивалентны при перестановке и фалсе в противном случае
//Левое поддерево первого дерева эквивалентно левому поддереву второго дерева, а правое поддерево первого дерева эквивалентно правому поддереву второго дерева.
//Левое поддерево первого дерева эквивалентно правому поддереву второго дерева, а правое поддерево первого дерева эквивалентно левому поддереву второго дерева.
bool tasks::task_951(TreeNode *root1, TreeNode *root2)
{
    if (root1 == NULL || root2 == NULL) //если только одно дерево нулл, то они не могут быть эквивалентны
        return root1 == root2;
    if (root1->val != root2->val) //если значение корня рут1, не равно значению корня рут2, то возвращаем false
        return false; //в противном случае рекурсивно повторяем операцию сравнения для каждой ветки
    return ((task_951(root1->left, root2->left) && //левая ветка у обоих деревьев и
             task_951(root1->right, root2->right)) || //правая ветка у обоих деревьев или
            task_951(root1->left, root2->right) && //левая у 1 и правая у 2 и
            task_951(root1->right, root2->left)); //правая у 1 и левая у 2.
}
// игра в камни, необходимо вытаскивать камни двум людям, и вывести победителя
int tasks::task_1406_1(int p, int i, int n, std::vector<int> &piles, std::vector<std::vector<int> > &dp)
{
    if(i>=n) //если на вход пришел пустой вектор, то возвращаем ноль
        return 0;
    if(dp[p][i]!=-1)
        return dp[p][i];
    int mi=INT_MAX,ma=INT_MIN;
    int sum=0;
    //игроки могут взять от 1 до 3 камней
    for(int x=1;x<=std::min(3,n-i);x++)
    {
        sum+=piles[i+x-1];
        //если ход алисы, то она попытается набрать максимум очков
        if(p==0)
            ma=std::max(ma,sum+task_1406_1(1,i+x,n,piles,dp));
        //если ход боба, то он попытается набрать максимум и сделать так, чтобы алиса набрала минимум
        else
            mi=std::min(mi,task_1406_1(0,i+x,n,piles,dp));
    }
    if(p==0)
        return dp[p][i]=ma;
    return dp[p][i]=mi;

}

std::string tasks::task_1406_2(std::vector<int> &stones)
{
    {
        int tot=0; //всего очков
        for(auto x:stones)
            tot+=x;
        int n=stones.size(); // количество камней
        std::vector<std::vector<int>> dp(2,std::vector<int>(n+1,-1)); //создаем двумерный вектор, в котором будет 2 строки, и n+1 столбцов и каждый будет инициирован -1
        int alice=task_1406_1(0,0,n,stones,dp); // подсчитываем алисины очки
        int bob=tot-alice; // счет боба будет общее количество, минус алисины очки
        if(bob==alice)//ничья
            return "Tie";
        if(bob>alice)
            return "Bob";//победа боба
        return "Alice"; // победа алисы
    }
}
// необходимо убрать подкаталоги, сначала выясним какие папки корни, а потом поищем подпапки
std::vector<std::string> tasks::task_1233(std::vector<std::string> &folder)
{
    // Сортируем папки лексикографически, чтобы родительские папки располагались перед подпапками
    std::sort(folder.begin(), folder.end());
    // Инициализируем вектор результата с первой папкой
    std::vector<std::string> ans;
    ans.push_back(folder[0]);
    // Проходим по оставшимся папкам, начиная с индекса 1
    for(int i = 1; i < folder.size(); i++) {
        // Получить последний добавленный путь к папке и добавить завершающий слеш
        // Это помогает сравнить, является ли текущая папка подпапкой
        std::string lastFolder = ans.back();
        lastFolder.push_back('/');
        // Сравнивает текущую папку с последней добавленной папкой
        // compare(0, lastFolder.size(), lastFolder) проверяет, начинается ли папка[i] с lastFolder
        // Если она не начинается с lastFolder (возвращает != 0), то это не подпапка
        if(folder[i].compare(0, lastFolder.size(), lastFolder) != 0) {
            // Если не подпапка, добавить в результат
            ans.push_back(folder[i]);
        }
    }
    return ans;
}
//необходимо найти минимальное и максимальные значения nums[i] + k or nums[i] - k и вывести минимальное значение из чисел нового массива
int tasks::task_910(std::vector<int> &nums, int k)
{
    int n=nums.size();
    std::sort(nums.begin(), nums.end());
    int diff=nums[n-1]-nums[0];
    for(int i=1; i<n; i++){
        int mn=std::min(nums[0]+k, nums[i]-k);
        int mx=std::max(nums[i-1]+k, nums[n-1]-k);
        diff=std::min(diff, mx-mn);
    }
    return diff;
}
// определение угла между часовой и минутной стрелкой
double tasks::task_1344(int hour, int minutes)
{
    double angle_between = std::abs((60*hour+minutes)*0.5-minutes*6);
    return angle_between>180 ? 360 - angle_between : angle_between;
}
//необходимо вывести строку, в которую случайно вставить буквы, нечетное количество
std::string tasks::task_1374(int n)
{
    std::string for_ret;
    if (n%2!=0)
        while(n--) for_ret.push_back('a');
    if(n%2==0)
    {
        n=n-1;
        while(n--) for_ret.push_back('b');
        for_ret.push_back('a');
    }
    return for_ret;
}
