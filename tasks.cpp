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
// необходимо отрезать по очереди у дерева, ветку, которая начинается с значения вектора, после этого найти максимальную длинну
std::vector<int> tasks::task_2458_1(TreeNode *root, std::vector<int> &queries)
{
    depth.resize(100001, 0);    //размер вектора глубины
    levelArr.resize(100001, 0); //размер вектора уровней
    max1.resize(100001, 0);     //размер вектора максимальных значений 1
    max2.resize(100001, 0);     //размер вектора максимальных значений 2
    // вычисление глубины и максимальной глубины каждого уровня
    task_2458_2(root, 0);
    // обработка каждого запроса
    for (int i = 0; i < queries.size(); i++) //для каждого значения из вектора отрезаем ветку, и смотрим глубины
    {
        int q = queries[i];
        int level = levelArr[q];
        queries[i] = (max1[level] == depth[q] ? max2[level] : max1[level]) + level - 1;//приравниваем вектору значение глубины с отрезанной веткой
    }
    return queries;
}

int tasks::task_2458_2(TreeNode *root, int level)
{
    if (!root) return 0;
    levelArr[root->val] = level;
    depth[root->val] = 1 + std::max(task_2458_2(root->left, level + 1), task_2458_2(root->right, level + 1));
    if (max1[level] < depth[root->val])  //если максимальный уровень 1 меньше глубины,
    {
        max2[level] = max1[level];
        max1[level] = depth[root->val];
    } else if (max2[level] < depth[root->val])
    {
        max2[level] = depth[root->val];
    }
    return depth[root->val];
}
// игра, в которой дан вектор характеристик, атаки и защиты, нужно найти того, кто слабее
int tasks::task_1996(std::vector<std::vector<int> > &properties)
{
    //для начала отсортируем характеристики
    std::sort(properties.begin(),properties.end(), [](const auto& a, const auto& b)
    {
        return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0]; //если а=б(нулевые), то, если а(1)<б(1), то ввозращаем труе, в противном случае фолс
    });
    int out{}, topDef{};

    for(const auto& p : properties)
    {
        if (p[1] < topDef){ ++out;}
        else { topDef = p[1];}
    }
    return out;
}
// необходимо подсчитать сколько квадратных матриц из единичек есть в матрице
int tasks::task_1277(std::vector<std::vector<int> > &matrix)
{
    int n = matrix.size();    // количество строк
    int m = matrix[0].size(); // количество столбцов
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));    // создаем матрицу дп, таких же размеров
    int count = 0;
    for (int i = 0; i < n; i++)  //квадрт размером 1на1 столбцы
    {
        dp[i][0] = matrix[i][0];
        count += dp[i][0];
    }
    for (int j = 1; j < m; j++)  //квадрат размером 1на1 строки
    {
        dp[0][j] = matrix[0][j];
        count += dp[0][j];
    }
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            if(matrix[i][j] == 1)  //только если значение равно 1
            {
                dp[i][j] = 1 + std::min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]}); //левая, верхняя и диагональная ячейки единицы
            }
            count += dp[i][j];
        }
    }
    return count;
}
//необходимо узнать максимальную последовательность квадратов чисел в векторе 2,4,16 =3  4,16,3=2
int tasks::task_2501(std::vector<int> &nums)
{
    std::map<int, int>mp;
    std::sort(nums.begin(), nums.end());
    int res = -1;
    for(int num: nums)
    {
        int _sqrt = std::sqrt(num); //берем корень квадртаный от числа из вектора если это 2, то корень равен 1, т.к. идет округление всегда в меньшую сторону
        if(_sqrt*_sqrt == num && mp.find(_sqrt)!=mp.end()) //потом умножаем и если при умножении корня на самого себя равно числу, то число ок
        { //после этого ищем в мапе корень, если нашли, то мы увеличиваем у этого числа значение на единицу, чем у корня
            mp[num] = mp[_sqrt]+1;
            res = std::max(res, mp[num]); //находим максимальное значение из резов
        } else mp[num] = 1; //в противном случае добавляем в мапу это число с индексом 1, который означает последовательность корней
    }
    return res;
}
//игра, необходимо определить максимальное количество ходов, чтобы дойти до конца
int tasks::task_2684(std::vector<std::vector<int> > &grid)
{
    int m = grid.size(), n = grid[0].size(); //количество строк и столбцов
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0)); //вектор из м строк векторов, длинной н и заполненную нулями MxN=0
    int maxMoves = 0;

    for (int col = n - 2; col >= 0; --col)  //начинаем с конца двигаться(предпоследний столбец)
    {
        for (int row = 0; row < m; ++row)  //строка верхняя, движемся вниз
        {
            if (row > 0 && grid[row][col] < grid[row - 1][col + 1])  //если строка больше нуля и значение в ячейке меньше значения в ячейке ниже и правее
            {
                dp[row][col] = std::max(dp[row][col], dp[row - 1][col + 1] + 1); //то мы присваиваем значению дп, максимум из двух +1
            }
            if (grid[row][col] < grid[row][col + 1])  //меньше знаяения в ячейке в той же строке и правее
            {
                dp[row][col] = std::max(dp[row][col], dp[row][col + 1] + 1); // снова увеличиваем
            }
            if (row < m - 1 && grid[row][col] < grid[row + 1][col + 1])  //если значение строки меньше длинны -1 и меньше значения сверху и правее
            {
                dp[row][col] = std::max(dp[row][col], dp[row + 1][col + 1] + 1);
            }
        }
    }

    for (int row = 0; row < m; ++row) {
        maxMoves = std::max(maxMoves, dp[row][0]); //проходим по массиву и находим максимум
    }
    return maxMoves;
}
//необходимо понять, сколько надо удалить значений из вектора, чтобы получилась горка
int tasks::task_1671(std::vector<int> &nums)
{
    std::vector<int> leftDP(nums.size(), 1), rightDP(nums.size(), 1); //создаем два вектора, слева и справа, одинаковой длинны, заполненные единицами
    // сначала слева
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                leftDP[i] = std::max(leftDP[i], leftDP[j] + 1); //если некст элемент больше предыдущего, то мы в вектор левых значений добавляем значение слева+1
            }
        }
    }
    // теперь справа движемся справа к началу
    for (int i = nums.size() - 1; i >= 0; --i) {
        for (int j = nums.size() - 1; j > i; --j) {
            if (nums[i] > nums[j]) { //если слева, больше чем справа, значит добавляем значение +1
                rightDP[i] = std::max(rightDP[i], rightDP[j] + 1);
            }
        }
    }
    // находим самую большую сумму, это и будет большая горка
    int ans = 0;
    for (int i = 0; i < nums.size(); ++i) {
        // проверяем, что есть и левая часть горы и правая
        if (leftDP[i] != 1 && rightDP[i] != 1) {
            ans = std::max(ans, leftDP[i] + rightDP[i]);
        }
    }
    // возвращаем количество чисел, которое нужно убрать, чтобы получилась гора
    return nums.size() - ans + 1;
}
//днеобходимо определить, сколько нужно пройти расстояния по клеткам, от единички до ближайшего нуля, дана матрица нулей и единиц
std::vector<std::vector<int> > tasks::task_542(std::vector<std::vector<int> > &mat)
{
    std::vector<std::vector<int>>ans(mat.size(),std::vector<int>(mat[0].size()));
    std::vector<std::vector<bool>>visited(mat.size(),std::vector<bool>(mat[0].size(),false));
    std::queue<std::pair<std::pair<int,int>,int>>q;
    for(int i=0; i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++){
            if(mat[i][j]==0){
                q.push({{i,j},0});
                visited[i][j]=true;
            }
        }
    }
    while(!q.empty()){
        int a = q.front().first.first;
        int b = q.front().first.second;
        int dis = q.front().second;
        q.pop();
        ans[a][b]=dis;
        if(a!=0 && !visited[a-1][b]){
            visited[a-1][b]=true;
            q.push({{a-1,b},dis+1});
        }
        if(a!=mat.size()-1 && !visited[a+1][b]){
            visited[a+1][b]=true;
            q.push({{a+1,b},dis+1});
        }
        if(b!=0 && !visited[a][b-1]){
            visited[a][b-1]=true;
            q.push({{a,b-1},dis+1});
        }
        if(b!=mat[0].size()-1 && !visited[a][b+1]){
            visited[a][b+1]=true;
            q.push({{a,b+1},dis+1});
        }
    }
    return ans;
}
//необходимо роботов доставить до фабрик
long long tasks::task_2463(std::vector<int> &robot, std::vector<std::vector<int> > &factory)
{
    // сначала отсортируем фабрики и роботов
    sort(robot.begin(), robot.end());
    sort(factory.begin(), factory.end());

    int m = robot.size(), n = factory.size();
    // dp[i][j]: минимальное общее расстояние для роботов[i:] использующих фабрики[j:]
    std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(n + 1));
    // если нет доступных заводов, то расстояние равно бесконечность
    for (int i = 0; i < m; i++) {
        dp[i][n] = LLONG_MAX;
    }
    // обрабатываем фабрики с права, на лево
    for (int j = n - 1; j >= 0; j--) {
        // отслеживаем совокупное расстояние от текущего завода до роботов
        long long prefix = 0;
        // Deque хранит пары, индекс робота и минимальное расстояние
        std::deque<std::pair<int, long long>> qq;
        // базовые вариант инициация
        qq.push_back({m, 0});

        // обрабатываем робота справа на лево
        for (int i = m - 1; i >= 0; i--) {
            // добавляем расстояние от текущего робота до текущего завода
            prefix += abs(robot[i] - factory[j][0]);

            // удаляем записи, которые превышают возможности завода
            while (!qq.empty() && qq.front().first > i + factory[j][1]) {
                qq.pop_front();
            }

            // поддерживаем монотонность дека
            while (!qq.empty() && qq.back().second >= dp[i][j + 1] - prefix) {
                qq.pop_back();
            }

            // добавляем текущее расстояние в дек
            qq.push_back({i, dp[i][j + 1] - prefix});
            // подсчитываем минимальное расстояние для текущего состояния
            dp[i][j] = qq.front().second + prefix;
        }
    }

    // возвращаем минимальное общее расстояние начиная с первого робота и первой фаьрики
    return dp[0][0];
}

std::string tasks::task_1957(std::string s)
{
    if(s.length()<3)
    {
        return s;
    }
    int j = 2;
    for (int i = 2; i < s.size(); ++i)
        if (s[i] != s[j - 1] || s[i] != s[j - 2])
            s[j++] = s[i];
    s.resize(j);
    return s;
}

bool tasks::task_2490(std::string sentence)
{
    int count=0;
    bool for_ret=true;
    for (int i=0;i<sentence.size();i++)
    {
        if (sentence[i]==' ')
        {
            count++;
            if (sentence[i-1]!=sentence[i+1]) return false; else
            {
                if (sentence[0]!=sentence[sentence.size()-1]) return false; else for_ret=true;
            }
        }
    }
    if (count==0)
    {
        if(sentence[0]!=sentence[sentence.size()-1])
            return false;
    }
    return for_ret;
}

bool tasks::task_796(std::string s, std::string goal)
{
    if (s.size()!=goal.size()) return false;
    return (s+s).find(goal)<(s+s).size();    //есть индекс, не равен концу строки
}

std::string tasks::task_3163(std::string word)
{
    std::string comp = "";
    int cnt = 1;
    char ch = word[0];
    for(int i=1;i<word.size();i++){
        if(word[i] == ch && cnt < 9)cnt++;
        else{
            comp.push_back(cnt+'0');
            comp.push_back(ch);
            ch = word[i];
            cnt = 1;
        }
    }
    comp.push_back(cnt+'0');
    comp.push_back(ch);
    return comp;
}

int tasks::task_2914(std::string s)
{
    int count = 0;
    for (int i = 0; i < s.size() - 1; i += 2) {
        if (s[i] != s[i + 1]) {
            count++;
        }
    }
    return count;
}

int popcount(unsigned int n) { //в 20 версии появилось для задачи 2011
    int count = 0;
    while (n) {
        count += n & 1; // Увеличиваем счетчик, если младший бит равен 1
        n >>= 1;        // Сдвигаем число вправо
    }
    return count;
}

bool tasks::task_3011(std::vector<int> &nums)
{
    const uint8_t n = nums.size();
    uint16_t pmax = 0, cmin = 0, cmax = 0;
    uint8_t pcnt = 0;
    for (const uint16_t v : nums) {
        if (const uint8_t ccnt = popcount(v); pcnt == ccnt) {
            cmin = std::min(cmin, v);
            cmax = std::max(cmax, v);
        } else if (cmin < pmax) {
            return false;
        } else {
            pmax = cmax;
            cmin = cmax = v;
            pcnt = ccnt;
        }
    }
    return cmin >= pmax;
}
//побитовое сложение с единицей
int tasks::tssk_2275(std::vector<int> &candidates){
int n = candidates.size(),ans = 0;
for(int i=0;i<32;i++){
    int cnt = 0;
    for(auto candidate : candidates){
        if(candidate & (1<<i))cnt++;
    }
    ans = std::max(ans,cnt);
}
return ans;
}

std::vector<int> tasks::task_1829(std::vector<int> &nums, int maximumBit)
{
    int n = nums.size(),xorr = nums[0],maxxorr = pow(2,maximumBit)-1;
    for(int i=1;i<n;i++)xorr ^= nums[i];
    std::vector<int>ans(n);
    for(int i=0;i<n;i++){
        ans[i] = xorr^maxxorr;
        xorr ^= nums[n-1-i];
    }
    return ans;
}

long long tasks::task_3133(int n, int x)
{
    long result=x;
    long remaining=n-1;
    long position=1;
    while(remaining)
    {
        if (!(x&position)) // если побитовое и х и позиции не 1
        {
            result|=(remaining&1)*position; // то мы с результатом делаем или, возврат и 1, умножаем на позицию
            remaining>>=1; //сдвигаем направо на 1 регистр
        }
        position<<=1; //сдвигаем на лево на 1 регистр
    }
    return result;
}

int tasks::task_921(std::string s)
{
    int open_needed = 0;
    int close_needed = 0;
    for (char ch : s) {
        if (ch == '(')
        {
            close_needed++;
        } else if (ch == ')')
        {
            if (close_needed > 0)
            {
                close_needed--;
            } else
            {
                open_needed++;
            }
        }
    }
    return open_needed + close_needed;
}

std::string tasks::task_1768(std::string word1, std::string word2)
{
    int length;
    std::string ans="";
    std::string temp="";
    if (word1.length()<word2.length())
    {
        length=word1.length();
        for (int it=word1.length();it<word2.length();it++)
            temp.push_back(word2[it]);
    }
    if (word1.length()>word2.length())
    {
        length=word2.length();
        for (int it=word2.length();it<word1.length();it++)
            temp.push_back(word1[it]);
    }
    for (int it=0;it<length;it++)
    {

        ans.push_back(word1[it]);
        ans.push_back(word2[it]);
    }
    ans.append(temp);
    return ans;
}

bool tasks::task_2601(std::vector<int> &nums)
{
    int maxElement = getMaxElement(nums);

    // Create Sieve of Eratosthenes array to identify prime numbers
    std::vector<bool> sieve(maxElement + 1, true);
    sieve[1] = false;
    for (int i = 2; i <= sqrt(maxElement + 1); i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= maxElement; j += i) {
                sieve[j] = false;
            }
        }
    }

    // Check if array can be made strictly increasing by subtracting prime numbers
    int currValue = 1;
    int i = 0;
    while (i < nums.size()) {
        int difference = nums[i] - currValue;

        // Return false if current number is already smaller than required value
        if (difference < 0) {
            return false;
        }

        // Move to next number if difference is prime or zero
        if (sieve[difference] == true || difference == 0) {
            i++;
            currValue++;
        } else {
            currValue++;
        }
    }
    return true;
}
int tasks::getMaxElement(std::vector<int> &nums)
{
    int max = -1;
    for (int num : nums) {
        if (num > max) {
            max = num;
        }
    }
    return max;
}

std::vector<int> tasks::task_2601(std::vector<std::vector<int> > &items, std::vector<int> &queries)
{
    int maxI = INT_MAX;
    std::vector<std::vector<int>> res = {{0, 0, maxI}};
    sort(items.begin(), items.end());
    for (const auto& item : items) {
        int price = item[0];
        int beauty = item[1];
        if (beauty > res.back()[1]) {
            res.back()[2] = price;
            res.push_back({price, beauty, maxI});
        }    }

    std::vector<int> ans;
    for (int x : queries) {
        for (int i = res.size() - 1; i >= 0; i--) {
            if (res[i][0] <= x) {
                ans.push_back(res[i][1]);
                break;
            }
        }
    }
    return ans;
}

long long tasks::task_2563(std::vector<int> &nums, int lower, int upper)
{
    long long ans = 0;
    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 1; i++) {
        auto up = upper_bound(nums.begin() + i + 1, nums.end(), upper - nums[i]);
        auto low = lower_bound(nums.begin() + i + 1, nums.end(), lower - nums[i]);
        ans += (up - low);
    }
    return ans;
}

int tasks::task_2064_1(int n, std::vector<int> &quantities)
{
    int s=1,e=100000,ans=-1;
    while(s<=e){
        int mid=s+(e-s)/2;
        if(task_2064_2(n,quantities,mid)){
            ans=mid;
            e=mid-1;
        }
        else{
            s=mid+1;
        }
    }
    return ans;
}

int tasks::task_2064_2(int n, std::vector<int> &quantities, int mid)
{
    int stores=0;
    for(auto x:quantities){
        stores+=x/mid;
        if(x%mid) stores++;
        if(stores>n) return 0;
    }
    return stores<=n;
}
// Шаг 1: Найти самый длинный неубывающий префикс
// Если весь массив уже отсортирован
// Шаг 2: Найти самый длинный неубывающий суффикс
// Шаг 3: Найти минимальную длину для удаления, сравнив префикс и суффикс
// Шаг 4: Использовать два указателя, чтобы найти наименьшую среднюю часть для удаления
int tasks::task_1574(std::vector<int> &arr)
{
    int n = arr.size();
    //1
    int left = 0;
    while (left + 1 < n && arr[left] <= arr[left + 1]) {
        left++;
    }
    if (left == n - 1) return 0;
    //2
    int right = n - 1;
    while (right > 0 && arr[right - 1] <= arr[right]) {
        right--;
    }
    //3
    int result = std::min(n - left - 1, right);
    //4
    int i = 0, j = right;
    while (i <= left && j < n) {
        if (arr[i] <= arr[j]) {
            result = std::min(result, j - i - 1);
            i++;
        } else {
            j++;
        }
    }
    return result;
}

std::vector<int> tasks::task_3254(std::vector<int> nums, int k)
{
    int n= nums.size();
    int count=1;
    std::vector<int> ans(n-k+1,-1); //создали массив заполненный -1, размером с n-k+1
    int i=0,j=0;
    while(j<n)
    {
        if(j>0 && nums[j]-nums[j-1]!=1)
        {
            i=j;
        }
        while(i<j && j-i+1>k)
        {
            i++;
        }
        if(j-i+1==k)
            ans[j-k+1]=nums[j];
        j++;
    }
    return ans;
}

int tasks::task_862(std::vector<int> &nums, int k)
{
    const int n=nums.size();
    long long sum[n];
    sum[0]=nums[0];
    int dp[n], front =0, back=-1,len=1e9; //deque dp
    for (int i=0;i<n;i++)
    {
        if (i>0) sum[i]=sum[i-1]+nums[i];
        if (sum[i]>=k) len=std::min(len, i+1);
        while(front<=back && sum[i]-sum[dp[front]]>=k)
        {
            len=std::min(len, i-dp[front]);
            front++;
        }
        while(front<=back && sum[i]<=sum[dp[back]]) back--;
        dp[++back]=i;
    }
    return len==1e9?-1:len;
}

std::vector<int> tasks::task_1652(std::vector<int> &code, int k)
{
    int n=code.size();
    std::vector<int> ans(n,0);
    for (int i=0;i<n;i++)
    {
        if (k>0)
        {
            for(int j=i+1;j<(i+1+k);j++)
            {
                ans[i]+=code[j%n];
            }
        } else if (k<0)
        {
            for(int j=i-1;j>(i-1-abs(k));j--)
            {
                ans[i]+=code[((j % n) + n) % n];
            }
        }

    }
    return ans;
}

long long tasks::task_2461(std::vector<int> &nums, int k)
{
    int n = nums.size();
    std::unordered_set<int> elements;
    long long current_sum = 0;
    long long max_sum = 0;
    int begin = 0;
    for (int end = 0; end < n; end++) {
        if (elements.find(nums[end]) == elements.end()) {
            current_sum += nums[end];
            elements.insert(nums[end]);

            if (end - begin + 1 == k) {
                max_sum = std::max(max_sum, current_sum);
                current_sum -= nums[begin];
                elements.erase(nums[begin]);
                begin++;
            }
        } else {
            while (nums[begin] != nums[end]) {
                current_sum -= nums[begin];
                elements.erase(nums[begin]);
                begin++;
            }
            begin++;
        }
    }
    return max_sum;
}

int tasks::task_2516(std::string s, int k)
{
    // Total counts
    std::vector<int> count(3, 0);
    for (char c : s) {
        count[c - 'a']++;
    }

    if (*min_element(count.begin(), count.end()) < k) {
        return -1;
    }
    // Sliding Window
    int res = INT_MAX;
    int l = 0;
    for (int r = 0; r < s.length(); r++) {
        count[s[r] - 'a']--;

        while (*min_element(count.begin(), count.end()) < k) {
            count[s[l] - 'a']++;
            l++;
        }
        res = std::min(res, static_cast<int>(s.length()) - (r - l + 1));
    }
    return res;
}

int tasks::task_2257(int m, int n, std::vector<std::vector<int> > &guards, std::vector<std::vector<int> > &walls)
{
    std::vector<std::vector<int>> vis(m, std::vector<int>(n, 0));

    // Mark walls = 2
    for (auto val : walls) {
        vis[val[0]][val[1]] = 2;
    }

    // Mark guards = 3
    for (auto val : guards) {
        vis[val[0]][val[1]] = 3;
    }

    // Traverse in four directions to mark guarded cells
    for (auto val : guards) {
        int row = val[0], col = val[1];

        // Down
        for (int i = row + 1; i < m; i++) {
            if (vis[i][col] == 2 || vis[i][col] == 3) break; // Stop at wall or guard
            vis[i][col] = 1; // Mark as guarded
        }

        // Up
        for (int i = row - 1; i >= 0; i--) {
            if (vis[i][col] == 2 || vis[i][col] == 3) break;
            vis[i][col] = 1;
        }

        // Right
        for (int i = col + 1; i < n; i++) {
            if (vis[row][i] == 2 || vis[row][i] == 3) break;
            vis[row][i] = 1;
        }

        // Left
        for (int i = col - 1; i >= 0; i--) {
            if (vis[row][i] == 2 || vis[row][i] == 3) break;
            vis[row][i] = 1;
        }
    }

    // Count unguarded cells
    int unguarded = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (vis[i][j] == 0) unguarded++;
        }
    }

    return unguarded;
}

int tasks::task_1072(std::vector<std::vector<int> > &matrix)
{
    std::unordered_map<std::string, int> patFreq;

    for (const auto& row : matrix) {
        std::string pattern;
        if (row[0] == 0) {
            for (int bit : row) pattern += std::to_string(bit);
        } else {
            for (int bit : row) pattern += std::to_string(bit ^ 1);
        }
        patFreq[pattern]++;
    }

    int maxFreq = 0;
    for (const auto& pair : patFreq) {
        maxFreq = std::max(maxFreq, pair.second);
    }
    return maxFreq;
}

std::vector<std::vector<char> > tasks::task_1861(std::vector<std::vector<char> > &box)
{
    const int r=box.size(), c=box[0].size();
    std::vector<std::vector<char>> rotate(c, std::vector<char>(r, '.'));
    for(int i=0; i<r; i++){
        int bottom=c-1;
        for(int j=c-1; j>=0; j--){
            if (box[i][j]=='#'){
                rotate[bottom][r-1-i]='#';
                bottom--;
            }
            else if (box[i][j]=='*'){
                rotate[j][r-1-i]='*';
                bottom=j-1;
            }
        }
    }
    return rotate;
}

long long tasks::task_1975(std::vector<std::vector<int> > &matrix)
{
    int count_minus=0;
    int height=matrix[0].size();
    int weight=matrix.size();
    for (int i=0;i<weight;i++)
        for (int j=0;j<height;j++)
        {
            if (matrix[i][j]<0) count_minus++;
        }
}

int tasks::task_773(std::vector<std::vector<int> > &board)
{
    std::vector<std::vector<char>> adj = {{1, 3}, {0, 2, 4}, {1, 5},
                                          {0, 4}, {1, 3, 5}, {2, 4}};
    using info=std::pair<std::string, char>;
    std::string target = "123450";
    std::string start(6, '-');
    char pos0=-1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++){
            int index=i*3+j;
            start[index]= board[i][j]+'0';
            if (board[i][j]==0) pos0=index;
        }
    if (start == target)
        return 0;

    std::unordered_set<std::string> viz;
    viz.reserve(720);
    std::queue<info> q;
    q.emplace(start, pos0);

    for (int move= 0; !q.empty();  move++) {
        int qz = q.size();
        for (int i = 0; i < qz; i++) {
            auto [t, p0] = q.front();
                    //    cout<<t<<" p0="<<int(p0)<<endl;
                    q.pop();
                    if (t == target)
                    return move;
                    for (char p : adj[p0]) {
                std::string s = t;
                std::swap(s[p0], s[p]);

                if (viz.count(s))
                    continue;
                q.emplace(s, p);
                viz.insert(s);
            }
        }
    }
    return -1;
}

int tasks::task_2924(int n, std::vector<std::vector<int> > &edges)
{
    std::bitset<100> losses;

    for (const auto& edge : edges) {
        losses.set(edge[1]);
    }

    int champion = -1;
    for (int i = 0; i < n; i++) {
        if (!losses[i]) {
            if (champion != -1) return -1;
            champion = i;
        }
    }

    return champion;
}

std::vector<int> tasks::task_3243(int n, std::vector<std::vector<int> > &queries)
{
    std::vector<int> ans;
    std::vector<std::vector<int>> adj(n);
    std::vector<int> dist(n);
    std::iota(dist.begin(), dist.end(), 0); //fills the array with 0,1,2,3...
    for (int i = 0; i < n - 1; i++) {
        adj[i].push_back(i + 1);
    }
    for (auto it : queries) {

        int src = it[0], des = it[1];
        adj[src].push_back(des);

        if (dist[src] + 1 < dist[des]) {
            //BFS
            std::queue<int> q;
            q.push(des);
            dist[des] = dist[src] + 1;
            while (q.size()) {
                int idx = q.front();
                q.pop();
                for (auto e : adj[idx]) {
                    if (dist[idx] + 1 < dist[e]) {
                        dist[e] = dist[idx] + 1;
                        q.push(e);
                    }
                }
            }
        }
        ans.emplace_back(dist.back());
    }
    return ans;
}

int tasks::task_2290(std::vector<std::vector<int> > &grid)
{
    int m = grid.size(), n = grid[0].size();
    std::vector<std::vector<int>> distance(m, std::vector<int>(n, INT_MAX));
    std::deque<std::pair<int, int>> dq;

    distance[0][0] = 0;
    dq.push_front({0, 0});
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!dq.empty()) {
        auto [x, y] = dq.front();
                dq.pop_front();
                for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                int newDist = distance[x][y] + grid[nx][ny];
                if (newDist < distance[nx][ny]) {
                    distance[nx][ny] = newDist;
                    if (grid[nx][ny] == 0) {
                        dq.push_front({nx, ny});
                    } else {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }
    }
    return distance[m-1][n-1];
}

int tasks::task_2577(std::vector<std::vector<int> > &grid)
{
    if (grid[0][1] > 1 && grid[1][0] > 1) return -1;

    int rows = grid.size();
    int cols = grid[0].size();

    std::priority_queue<std::pair<int, std::pair<int, int>>,
            std::vector<std::pair<int, std::pair<int, int>>>,
            std::greater<std::pair<int, std::pair<int, int>>>> minHeap;

    minHeap.push({0, {0, 0}}); // time, row(x), col(y)

    std::vector<std::vector<int>> seen(rows, std::vector<int>(cols, 0));
    seen[0][0] = 1;

    std::vector<std::pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!minHeap.empty()) {
        auto curr = minHeap.top();
        int currTime = curr.first;
        int currRow = curr.second.first;
        int currCol = curr.second.second;

        minHeap.pop();

        if (currRow == rows - 1 && currCol == cols - 1)
            return currTime;

        for (auto move : moves) {
            int nextRow = move.first + currRow;
            int nextCol = move.second + currCol;

            if (nextRow >= 0 && nextCol >= 0 &&
                    nextRow < rows && nextCol < cols &&
                    !seen[nextRow][nextCol]) {

                int waitTime = ((grid[nextRow][nextCol] - currTime) % 2 == 0) ? 1 : 0;
                int nextTime =std:: max(currTime + 1, grid[nextRow][nextCol] + waitTime);

                minHeap.push({nextTime, {nextRow, nextCol}});
                seen[nextRow][nextCol] = 1;
            }
        }
    }
    return -1;
}

std::vector<std::vector<int> > tasks::task_2097(std::vector<std::vector<int> > &pairs)
{
    std::unordered_map<int, std::vector<int>> adjacencyList;
    std::unordered_map<int, int> inOutDegree;
    for (const auto& pair : pairs) {
        adjacencyList[pair[0]].push_back(pair[1]);
        inOutDegree[pair[0]]++;  // out-degree
        inOutDegree[pair[1]]--;  // in-degree
    }
    int startNode = pairs[0][0];
    for (const auto& [node, degree] : inOutDegree) {
        if (degree == 1) {
            startNode = node;
            break;
        }
    }
    std::vector<int> path;
    std::stack<int> nodeStack;
    nodeStack.push(startNode);
    while (!nodeStack.empty()) {
        auto& neighbors = adjacencyList[nodeStack.top()];
        if (neighbors.empty()) {
            path.push_back(nodeStack.top());
            nodeStack.pop();
        } else {
            int nextNode = neighbors.back();
            nodeStack.push(nextNode);
            neighbors.pop_back();
        }
    }
    std::vector<std::vector<int>> arrangement;
    int pathSize = path.size();
    arrangement.reserve(pathSize - 1);

    for (int i = pathSize - 1; i > 0; --i) {
        arrangement.push_back({path[i], path[i-1]});
    }
    return arrangement;
}

bool tasks::task_1346(std::vector<int> &arr)
{
    std::unordered_set<int> seen;
        for (auto i: arr)
        {
            if(seen.count(i*2) || ((i%2==0) && seen.count(i/2)))
                return true;
            seen.insert(i);
        }
        return false;
}

int tasks::task_1455(std::string sentence, std::string searchWord)
{
    int i = -1, wordIdx = 0;
    do {
        ++i, ++wordIdx;
        if(sentence.substr(i, searchWord.size()) == searchWord) return wordIdx;
    }while((i = sentence.find(' ', i)) != std::string::npos);
    return -1;
}

std::string tasks::task_2109(std::string s, std::vector<int> &spaces)
{
    const int m = spaces.size(), n = s.size();
    std::string t(n + m, ' ');

    int j = 0; // Pointer for spaces
    for (int i = 0; i < n; i++) {
        if (j < m && i == spaces[j]) {
            t[i+j] = ' ';
            j++;      // Move to the next space index
        }
        t[i+j]=s[i]; // Add the character from the original string
    }
    return t;
}

bool tasks::task_2825(std::string str1, std::string str2)
{
    int targetIdx = 0;
    int targetLen = str2.length();
    for (char currChar : str1) {
        if (targetIdx < targetLen && (str2[targetIdx] - currChar + 26) % 26 <= 1) {
            targetIdx++;
        }
    }
    return targetIdx == targetLen;
}

bool tasks::task_2337(std::string start, std::string target)
{
    if (start == target) {
        return true;
    }
    int waitL = 0;
    int waitR = 0;

    for (int i = 0; i < start.length(); i++) {
        char curr = start[i];
        char goal = target[i];
        if (curr == 'R') {
            if (waitL > 0) {
                return false;
            }
            waitR++;
        }
        if (goal == 'L') {
            if (waitR > 0) {
                return false;
            }
            waitL++;
        }
        if (goal == 'R') {
            if (waitR == 0) {
                return false;
            }
            waitR--;
        }
        if (curr == 'L') {
            if (waitL == 0) {
                return false;
            }
            waitL--;
        }
    }
    return waitL == 0 && waitR == 0;
}

int tasks::task_2554(std::vector<int> &banned, int n, int maxSum)
{
    // Create a set to mark banned numbers
    std::unordered_set<int> bannedSet(banned.begin(), banned.end());

    long long sum = 0; // Track cumulative sum
    int count = 0;     // Track count of valid numbers

    // Iterate through 1 to n
    for (int i = 1; i <= n; i++) {
        if (bannedSet.count(i)) continue; // Skip banned numbers
        sum += i; // Add current number to the sum
        if (sum > maxSum) break; // Stop if sum exceeds maxSum
        count++; // Increment count of valid numbers
    }

    return count; // Return the count of valid numbers
}

int tasks::task_1760(std::vector<int> &nums, int maxOperations)
{
    int low = 1, high = *max_element(nums.begin(), nums.end());
    while (low < high) {
        int mid = low + (high - low) / 2;
        int ops = 0;
        for (int n : nums) if ((ops += (n - 1) / mid) > maxOperations) break;
        ops <= maxOperations ? high = mid : low = mid + 1;
    }
    return high;
}

int tasks::task_2054(std::vector<std::vector<int> > &events)
{
    int n = events.size();

    sort(events.begin(), events.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[0] < b[0];
    });

    std::vector<int> suffixMax(n);
    suffixMax[n - 1] = events[n - 1][2];

    for (int i = n - 2; i >= 0; --i) {
        suffixMax[i] = std::max(events[i][2], suffixMax[i + 1]);
    }

    int maxSum = 0;

    for (int i = 0; i < n; ++i) {
        int left = i + 1, right = n - 1;
        int nextEventIndex = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (events[mid][0] > events[i][1]) {
                nextEventIndex = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (nextEventIndex != -1) {
            maxSum = std::max(maxSum, events[i][2] + suffixMax[nextEventIndex]);
        }

        maxSum = std::max(maxSum, events[i][2]);
    }

    return maxSum;
}

std::vector<bool> tasks::task_3152(std::vector<int> &nums, std::vector<int> &queries)
{
    int n = nums.size();
    std::vector<int> prefix(n, 0);
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1];
        if ((nums[i - 1] % 2 == 0 && nums[i] % 2 == 0) || (nums[i - 1] % 2 != 0 && nums[i] % 2 != 0)) {
            prefix[i]++;
        }
    }
    std::vector<bool> ans;
    for (auto& q : queries) {
        int left = q, right = q;// q[0] q[1]
        int specialCount = prefix[right] - (left > 0 ? prefix[left] : 0);
        ans.push_back(specialCount == 0);
    }
    return ans;
}

int tasks::task_2981(std::string s)
{
    int start = 0;
    std::unordered_map<std::string, int> mp;
    int n = s.length();
    for (int i = 0; i < n; ++i) {
        if (i == n - 1 || s[i] != s[i + 1]) {
            int len = i - start + 1;
            std::string t = s.substr(start, len);
            start = i + 1;
            mp[t]++;
            if (len >= 2) {
                mp[t.substr(0, len - 1)] += 2;
            }
            if (len >= 3) {
                mp[t.substr(0, len - 2)] += 3;
            }
        }
    }

    int ans = -1;
    for (auto& e : mp) {
        int len = e.first.length();
        if (e.second >= 3) ans = std::max(ans, len);
    }
    return ans;
}

int tasks::task_2779(std::vector<int> &nums, int k)
{
    int freq[100001]={0};
    int xMax=0, xMin=1e6;
    for(int x: nums){
        freq[x]++;
        xMax=std::max(x, xMax);
        xMin=std::min(x, xMin);
    }
    int cnt=0, maxCnt=0;
    for(int l=xMin, r=xMin; r<=xMax; r++){
        cnt+=freq[r];
        while(r-l>2*k){
            cnt-=freq[l];
            l++;
        }
        maxCnt=std::max(maxCnt, cnt);
    }
    return maxCnt;
}

long long tasks::task_2558(std::vector<int> &gifts, int k)
{
    make_heap(gifts.begin(), gifts.end());
    for (int i=0, x=INT_MAX; i<k && x>1; i++){
        pop_heap(gifts.begin(), gifts.end());
        x=gifts.back();
        gifts.back()=sqrt(gifts.back());
        push_heap(gifts.begin(), gifts.end());
    }
    return accumulate(gifts.begin(), gifts.end(), 0LL);
}

long long tasks::task_2593(std::vector<int> &nums)
{
    long long score = 0; // Change to long long to avoid overflow
    int n = nums.size();
    std::deque<int> q;

    // Traverse through the array
    for (int i = 0; i < n; i++) {
        // If queue is not empty and the current number is greater than or equal to the last in queue
        if (!q.empty() && nums[i] >= q.back()) {
            bool skip = false;
            // Process the elements in the queue
            while (!q.empty()) {
                int add = q.back();
                q.pop_back();
                if (!skip) {
                    score += add;
                }
                skip = !skip;
            }
            continue;
        }
        // Add current element to the queue
        q.push_back(nums[i]);
    }
    // Final processing of remaining elements in the queue
    bool skip = false;
    while (!q.empty()) {
        int add = q.back();
        q.pop_back();
        if (!skip) {
            score += add;
        }
        skip = !skip;
    }
    return score;
}

long long tasks::task_2762(std::vector<int> &nums)
{
    int l = 0;
    long long res = 0;
    std::deque<int> minD, maxD;

    for (int r = 0; r < nums.size(); r++) {
        while (!minD.empty() && nums[minD.back()] >= nums[r]) minD.pop_back();
        while (!maxD.empty() && nums[maxD.back()] <= nums[r]) maxD.pop_back();
        minD.push_back(r);
        maxD.push_back(r);

        while (nums[maxD.front()] - nums[minD.front()] > 2) {
            l++;
            if (minD.front() < l) minD.pop_front();
            if (maxD.front() < l) maxD.pop_front();
        }

        res += r - l + 1;
    }

    return res;
}

double tasks::task_1792(std::vector<std::vector<int> > &classes, int extraStudents)
{
    auto gain = [](double pass, double total) {
        return (pass + 1) / (total + 1) - pass / total;
    };

    std::priority_queue<std::pair<double, std::pair<int, int>>> maxHeap;

    double sum = 0.0;

    for (const auto& cls : classes) {
        int pass = cls[0], total = cls[1];
        sum += (double)pass / total;
        maxHeap.push({gain(pass, total), {pass, total}});
    }

    for (int i = 0; i < extraStudents; ++i) {
        auto [currentGain, data] = maxHeap.top(); maxHeap.pop();
                int pass = data.first, total = data.second;

                sum -= (double)pass / total;
                pass += 1;
                total += 1;
                sum += (double)pass / total;

                maxHeap.push({gain(pass, total), {pass, total}});
    }

    return sum / classes.size();
}

std::vector<int> tasks::task_3264(std::vector<int> &nums, int k, int multiplier)
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    for(int i = 0; i < nums.size(); i++) {
        pq.push({nums[i], i});
    }
    while(k--) {
        auto it = pq.top();
        pq.pop();
        nums[it.second] = multiplier * it.first;
        pq.push({multiplier * it.first, it.second});
    }
    return nums;
}

std::string tasks::task_2182(std::string s, int repeatLimit)
{
    sort(s.rbegin(), s.rend());

    std::string result;
    int freq = 1;
    int pointer = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (!result.empty() && result.back() == s[i]) {
            if (freq < repeatLimit) {
                result += s[i];
                freq++;
            } else {
                pointer = std::max(pointer, i + 1);
                while (pointer < s.size() && s[pointer] == s[i]) {
                    pointer++;
                }

                if (pointer < s.size()) {
                    result += s[pointer];
                    std::swap(s[i], s[pointer]);
                    freq = 1;
                } else {
                    break;
                }
            }
        } else {
            result += s[i];
            freq = 1;
        }
    }

    return result;
}

std::vector<int> tasks::task_1475(std::vector<int> &prices)
{
    const int n=prices.size();
    int stack[500], top=0;
    stack[top]=n-1;
    std::vector<int> ans=prices;
    for(int i=n-2; i>=0; i--){
        while(top>=0 && prices[i]<prices[stack[top]])
            top--;
        if (top>=0) ans[i]-=prices[stack[top]];
        stack[++top]=i;
    }
    return ans;
}

int tasks::task_769(std::vector<int> &arr)
{
    const int n=arr.size();
    int cnt=0, diff=0;
    for(int i=0; i<n; i++){
        diff+=arr[i]-i;
        cnt+=(diff==0);
    }
    return cnt;
}

TreeNode *tasks::task_2415(TreeNode *root)
{
    std::queue<TreeNode*> q;
    q.push(root);
    bool reversed=0;
    while(!q.empty()){
        int qz=q.size();
        std::vector<TreeNode*> arr(qz);
        for(int i=0; i<qz; i++){
            auto Node=q.front();
            q.pop();
            if (Node->left) q.push(Node->left);
            if (Node->right) q.push(Node->right);
            if (reversed){
                arr[i]=Node;
                if (i>=qz/2)
                    std::swap(arr[i]->val, arr[qz-1-i]->val);
            }
        }
        reversed=!reversed;
    }
    return root;
}

int tasks::task_2872(int n, std::vector<std::vector<int> > &edges, std::vector<int> &values, int k)
{
    std::vector<std::vector<int>> graph(n);
    std::vector<int> degree(n);
    if (n < 2) return 1;
    for (auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
        degree[edge[0]]++;
        degree[edge[1]]++;
    }

    std::vector<long long> nodeVal(values.begin(), values.end());
    std::queue<int> leafQ;
    for (int i = 0; i < n; i++)
        if (degree[i] == 1) leafQ.push(i);

    int compCnt = 0;
    while (!leafQ.empty()) {
        int curr = leafQ.front();
        leafQ.pop();
        degree[curr]--;
        long long carry = 0;
        if (nodeVal[curr] % k == 0) compCnt++;
        else carry = nodeVal[curr];
        for (int nbr : graph[curr]) {
            if (degree[nbr] == 0) continue;
            degree[nbr]--;
            nodeVal[nbr] += carry;
            if (degree[nbr] == 1) leafQ.push(nbr);
        }
    }
    return compCnt;
}

std::vector<int> tasks::task_2940(std::vector<int> &heights, std::vector<std::vector<int> > &queries)
{
    int n=heights.size(), qz=queries.size();
    std::vector<int> ans(qz, -1);
    std::vector<std::pair<int, int>> idx;

    for (int i= 0; i< qz; i++) {
        int& x=queries[i][0], & y=queries[i][1];
        if (x > y) // let x <= y
            std::swap(x, y);
        if (x == y|| heights[x]<heights[y])
            ans[i] = y;
        else idx.emplace_back(y, i);
    }

    sort(idx.begin(), idx.end(), std::greater<>());
    std::vector<std::pair<int, int>> stack;

    int j=n-1;
    for (auto [_, i] : idx) {
        int x = queries[i][0];
        int y = queries[i][1];
        for (; j >y; j--) {
            while (!stack.empty() && heights[stack.back().second] < heights[j])
                stack.pop_back();
            stack.emplace_back(heights[j], j);
        }

        // Check if accessing elements beyond the bounds of stack here
        auto it=upper_bound(stack.rbegin(), stack.rend(), std::make_pair(heights[x], n));
        ans[i]=(it==stack.rend()) ?-1 : it->second;
    }
    return ans;
}

int tasks::task_2471(TreeNode *root)
{
    std::queue<TreeNode*> q;
    q.push(root);
    int swaps=0;
    while(!q.empty()){
        int qz=q.size();
        std::vector<int> idx(qz, 0);
        iota(idx.begin(), idx.end(), 0);
        std::vector<int> arr(qz, 0);
        for(int i=0; i<qz; i++){
            auto node=q.front();
            q.pop();
            arr[i]=node->val;
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        // each value is unique, no need for stable_sort
        sort(idx.begin(), idx.end(), [&](int i, int j){
            return arr[i]<arr[j];
        });
        for(int i=0; i<qz; ){
            int j=idx[i];
            if (j!=i){// recheck
                swaps++;
                std::swap(idx[i], idx[j]);
            }
            else i++; // next iteration
        }
    }
    return swaps;
}

int tasks::task_3203(std::vector<std::vector<int> > &edges1, std::vector<std::vector<int> > &edges2)
{
    auto diameter = [](std::vector<std::vector<int>>& edges){
        int n = edges.size() + 1;
        std::vector<int> degree(n, 0);
        std::vector<std::vector<int>> adj(n);
        for (const auto& edge : edges){
            int v = edge[0], w = edge[1];
            adj[v].push_back(w);
            adj[w].push_back(v);
            degree[v]++;
            degree[w]++;
        }
        std::deque<int> q;
        for (int i = 0; i < n; i++){
            if (degree[i] == 1){
                q.push_back(i);
            }
        }
        int level = 0, left = n;
        while (left > 2){
            int size_q = q.size();
            left -= size_q;
            for (int i = 0; i < size_q; i++){
                int v = q.front();
                q.pop_front();
                for( int w : adj[v]){
                    degree[w]--;
                    if (degree[w] == 1){
                        q.push_back(w);
                    }
                }
            }
            level++;
        }
        return left == 2 ? 2 * level + 1 : 2 * level;
    };
    int d1 = diameter(edges1);
    int d2 = diameter(edges2);
    return std::max({d1, d2, ((d1 + 1) / 2) + ((d2 + 1) / 2) + 1});
}

std::vector<int> tasks::task_515(TreeNode *root)
{
    std::vector<int> ans;
    if (!root) return ans;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int L = q.size();
        int M = INT_MIN;

        for (int i = 0; i < L; i++) {
            TreeNode* x = q.front();
            q.pop();

            M = std::max(M, x->val);

            if (x->left != nullptr) {
                q.push(x->left);
            }
            if (x->right != nullptr) {
                q.push(x->right);
            }
        }

        ans.push_back(M);
    }

    return ans;
}

int tasks::task_494(std::vector<int> &nums, int target)
{
    const int n = nums.size();
    int sum=accumulate(nums.begin(), nums.end(), 0);
    int diff=sum-target;

    // Check if it's possible to achieve the target
    if (diff<0|| diff%2!=0) return 0;

    diff/=2;


    //dp[j][sum] represents the # of ways to get sum using the first j elements of nums
    int dp[21][2001]={{0}};

    // There's one way to get a sum of 0 without selecting any element
    dp[0][0] = 1;

    for (int j=1; j <= n; j++) {
        for (int sum=0; sum <= diff; sum++) {
            dp[j][sum] = dp[j-1][sum];

            if (sum >= nums[j-1])
                dp[j][sum]+=dp[j-1][sum-nums[j-1]];
        }
    }
    return dp[n][diff];
}

int tasks::task_1014(std::vector<int> &values)
{
    int n = values.size();
    if (n < 2) return values[0] + values[1] + 0 - 1;
    std::vector<int> suffixMax(n);
    suffixMax[n - 1] = values[n - 1] - (n - 1);
    for (int i = n - 2; i >= 0; i--) {
        suffixMax[i] = std::max(suffixMax[i + 1], values[i] - i);
    }
    int maxScore = INT_MIN;
    for (int i = 0; i < n - 1; i++) {
        maxScore = std::max(maxScore, values[i] + i + suffixMax[i + 1]);
    }

    return maxScore;
}

std::vector<int> tasks::task_689(std::vector<int> &nums, int k)
{
    const int n=nums.size();
    std::vector<int> ksum(n-k+1, 0), L(n-3*k+1, -1);
    int maxKsum=ksum[0]=accumulate(nums.begin(), nums.begin()+k, 0);
    L[0]=0;
    for(int i=1; i<n-k+1; i++){
        ksum[i]=ksum[i-1]-nums[i-1]+nums[i+k-1];
        if (i>n-3*k) continue;
        if (maxKsum<ksum[i]){
            maxKsum=ksum[i];
            L[i]=i;
        }
        else L[i]=L[i-1];
        //    cout<<i<<"->L->"<<L[i]<<" maxKsum="<<maxKsum<<endl;
    }
    std::vector<int> R(n-3*k+1, -1);
    maxKsum=ksum.back();
    R.back()=n-k;
    for(int i=n-k-1; i>=2*k; i--){
        if (maxKsum<=ksum[i]){// multiple answers, return the lexico smallest one
            maxKsum=ksum[i];
            R[i-2*k]=i;
        }
        else R[i-2*k]=R[i+1-2*k];
        //    cout<<i-2*k<<"->R->"<<R[i-2*k]<<" maxKsum="<<maxKsum<<endl;
    }
    std::vector<int> ans(3,-1);
    int max3K=0;
    for(int i=0; i<=n-3*k; i++){
        int sum3K=ksum[L[i]]+ksum[i+k]+ksum[R[i]];
        if (sum3K> max3K){
            max3K=sum3K;
            ans={L[i], i+k, R[i]};
        }
    }
    return ans;
}

int tasks::task_1639(std::vector<std::string> &words, std::string target)
{
    int m = target.size(), n = words[0].size(), MOD = 1e9 + 7;
    std::vector<std::vector<int>> freq(26, std::vector<int>(n, 0));
    for (auto& word : words)
        for (int i = 0; i < n; i++)
            freq[word[i] - 'a'][i]++;

    std::vector<long long> dp(m + 1, 0);
    dp[0] = 1;
    for (int j = 0; j < n; j++) {
        for (int i = m - 1; i >= 0; i--) {
            dp[i + 1] = (dp[i + 1] + dp[i] * freq[target[i] - 'a'][j]) % MOD;
        }
    }
    return dp[m];
}

int tasks::task_2466(int low, int high, int zero, int one)
{
    const int MOD = 1e9 + 7;
    std::vector<int> ways(high + 1, 0);
    ways[0] = 1;

    for (int length = 0; length <= high; ++length) {
        if (ways[length] == 0) continue;
        if (length + zero <= high) {
            ways[length + zero] = (ways[length + zero] + ways[length]) % MOD;
        }
        if (length + one <= high) {
            ways[length + one] = (ways[length + one] + ways[length]) % MOD;
        }
    }

    int count = 0;
    for (int i = low; i <= high; ++i) {
        count = (count + ways[i]) % MOD;
    }

    return count;
}

int tasks::task_983(std::vector<int> &days, std::vector<int> &costs)
{
    int n = days.size();
    int total_cost = 0;
    int left7 = 0, left30 = 0; // Pointers for 7-day and 30-day windows

    std::vector<int> dp(n, 0); // To store minimum cost for each day in days

    for (int right = 0; right < n; ++right) {
        // Adjust left7 pointer for the 7-day window
        while (days[right] - days[left7] >= 7) left7++;

        // Adjust left30 pointer for the 30-day window
        while (days[right] - days[left30] >= 30) left30++;

        // Calculate costs
        int cost1 = (right > 0 ? dp[right - 1] : 0) + costs[0];  // 1-day pass
        int cost7 = (left7 > 0 ? dp[left7 - 1] : 0) + costs[1];  // 7-day pass
        int cost30 = (left30 > 0 ? dp[left30 - 1] : 0) + costs[2]; // 30-day pass

        // Find the minimum cost
        dp[right] = std::min({cost1, cost7, cost30});
    }

    return dp[n - 1];
}

int tasks::task_1422(std::string s)
{
    int onesCount = 0;
    int zerosCount = 0;
    int bestScore = INT_MIN;

    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == '1') {
            onesCount++;
        } else {
            zerosCount++;
        }

        bestScore = std::max(bestScore, zerosCount - onesCount);
    }

    if (s[s.size() - 1] == '1') {
        onesCount++;
    }

    return bestScore + onesCount;
}

std::vector<int> tasks::task_2559(std::vector<std::string> &words, std::vector<std::vector<int> > &queries)
{
    int n = words.size();
    std::vector<int> Prefix(n + 1, 0);
    std::unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < n; i++) {
        Prefix[i + 1] = Prefix[i];
        if (vowels.count(words[i].front()) && vowels.count(words[i].back())) {
            Prefix[i + 1]++;
        }
    }
    std::vector<int> ANS;
    for (auto& query : queries) {
        int L = query[0], R = query[1];
        ANS.push_back(Prefix[R + 1] - Prefix[L]);
    }

    return ANS;
}

int tasks::task_2270(std::vector<int> &nums)
{
    long long leftSum = 0, rightSum = 0;
    for (int num : nums)
        rightSum += num;
    int count = 0;
    for (int i = 0; i < nums.size() - 1; i++)
    {
        leftSum += nums[i];
        rightSum -= nums[i];
        if (leftSum >= rightSum)
            count++;
    }
    return count;
}

int tasks::task_1930(std::string s)
{
    int ans = 0;
    int n = s.length();

    std::unordered_map<char, std::pair<int, int>> M;

    for (int i = 0; i < n; i++) {
        if (M.find(s[i]) == M.end()) {
            M[s[i]].first = i;
        }
        M[s[i]].second = i;
    }

    for (auto& [ch, positions] : M) {
        int left = positions.first;
        int right = positions.second;

        if (right - left <= 1) continue;  // No valid subsequences in this range

        std::unordered_set<char> uniqueChars;
        for (int i = left + 1; i < right; i++) {
            uniqueChars.insert(s[i]);
        }

        ans += uniqueChars.size();  // Count the unique characters between first and last occurrence
    }

    return ans;
}

std::string tasks::task_2381(std::string s, std::vector<std::vector<int> > &shifts)
{
    int n = s.size();
    std::vector<int> shift(n + 1, 0);

    // Process the shifts
    for (auto& shiftOp : shifts) {
        int start = shiftOp[0], end = shiftOp[1], direction = shiftOp[2];
        shift[start] += (direction == 1 ? 1 : -1);
        shift[end + 1] -= (direction == 1 ? 1 : -1);
    }

    int currentShift = 0;
    for (int i = 0; i < n; ++i) {
        currentShift += shift[i];
        shift[i] = currentShift;
    }

    for (int i = 0; i < n; ++i) {
        int netShift = (shift[i] % 26 + 26) % 26;
        s[i] = 'a' + (s[i] - 'a' + netShift) % 26;
    }

    return s;
}

std::vector<int> tasks::task_1769(std::string boxes)
{
    int n = boxes.size();
    std::vector<int> left(n, 0), right(n, 0), res(n, 0);
    int count = (boxes.at(0) == '1' ? 1 : 0);

    for (int i = 1; i < n; i++) {
        left[i] = left[i - 1] + count;
        count += (boxes.at(i) == '1' ? 1 : 0);
    }

    count = (boxes.at(n-1) == '1' ? 1 : 0);

    for (int i = n - 2; i >= 0; i--) {
        right[i] = right[i + 1] + count;
        count += (boxes.at(i) == '1' ? 1 : 0);
    }

    for (int i = 0; i < n; i++) {
        res[i] = left[i] + right[i];
    }

    return res;
}

std::vector<std::string> tasks::task_1408(std::vector<std::string> &words)
{
    int n = words.size();
    std::vector<std::string> ans;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && words[j].find(words[i]) != std::string::npos) {
                ans.push_back(words[i]);
                break;
            }
        }
    }

    return ans;
}

int tasks::task_3042(std::vector<std::string> &words)
{
    int n = words.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
        std::string s1 = words[i];

        for (int j = i + 1; j < n; j++) {
            std::string s2 = words[j];

            // Skip if s2 is shorter than s1
            if (s2.length() < s1.length())
                continue;

            // Extract prefix and suffix
            std::string pre = s2.substr(0, s1.length());
            std::string suf = s2.substr(s2.length() - s1.length());

            // Check if both prefix and suffix match s1
            if (pre == s1 && suf == s1) {
                ans++;
            }
        }
    }
    return ans;
}

int tasks::task_2185(std::vector<std::string> &words, std::string pref)
{
    int count = 0;
    for (const std::string& word : words) {
        if (word.find(pref) == 0) {
            count++;
        }
    }
    return count;
}

std::vector<std::string> tasks::task_916(std::vector<std::string> &words1, std::vector<std::string> &words2)
{
    int maxCount[26] = {0}; // To store the maximum frequency of each character needed

    // Calculate the maximum frequency of each character needed from words2
    for (const auto& word : words2) {
        int count[26] = {0}; // Frequency count for the current word in words2
        for (char ch : word) {
            count[ch - 'a']++;
        }
        for (int i = 0; i < 26; ++i) {
            maxCount[i] = std::max(maxCount[i], count[i]);
        }
    }

    std::vector<std::string> result; // To store the universal words

    // Check each word in words1
    for (const auto& word : words1) {
        int count[26] = {0}; // Frequency count for the current word in words1
        for (char ch : word) {
            count[ch - 'a']++;
        }

        // Check if this word can cover all character requirements from words2
        bool isUniversal = true;
        for (int i = 0; i < 26; ++i) {
            if (count[i] < maxCount[i]) {
                isUniversal = false;
                break;
            }
        }

        if (isUniversal) {
            result.push_back(word);
        }
    }

    return result;
}

bool tasks::task_1400(std::string s, int k)
{
    if (s.length() < k) return false;

    std::unordered_map<char, int> charCount;
    for (char c : s) {
        charCount[c]++;
    }

    int oddCount = 0;
    for (auto& entry : charCount) {
        if (entry.second % 2 != 0) oddCount++;
    }

    return oddCount <= k;
}

bool tasks::task_2116(std::string s, std::string locked)
{
    int n = s.length();
    if (n % 2 != 0) {
        return false; // Odd length cannot form valid parentheses
    }

    // Left-to-right pass: Ensure there are enough open brackets
    int openCount = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || locked[i] == '0') {
            openCount++;
        } else { // s[i] == ')' and locked[i] == '1'
            openCount--;
        }
        if (openCount < 0) {
            return false; // Too many ')' encountered
        }
    }

    // Right-to-left pass: Ensure there are enough close brackets
    int closeCount = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == ')' || locked[i] == '0') {
            closeCount++;
        } else { // s[i] == '(' and locked[i] == '1'
            closeCount--;
        }
        if (closeCount < 0) {
            return false; // Too many '(' encountered
        }
    }

    return true;
}

int tasks::task_3223(std::string s)
{
    std::vector<int> charFrequency(26, 0);
    int totalLength = 0;
    for (char currentChar : s) {
        charFrequency[currentChar - 'a']++;
    }
    for (int frequency : charFrequency) {
        if (frequency == 0) continue;
        if (frequency % 2 == 0) {
            totalLength += 2;
        } else {
            totalLength += 1;
        }
    }
    return totalLength;
}

std::vector<int> tasks::task_2657(std::vector<int> &A, std::vector<int> &B)
{
    int n = A.size();
    std::vector<int> freq(n + 1, 0);
    std::vector<int> ans;
    int common = 0;

    for (int i = 0; i < n; i++) {
        if (++freq[A[i]] == 2) common++;
        if (++freq[B[i]] == 2) common++;
        ans.push_back(common);
    }
    return ans;
}

int tasks::task_2429(int num1, int num2)
{
    int a = __builtin_popcount(num1);
    int b = __builtin_popcount(num2);
    int res = num1;
    for (int i = 0; i < 32; ++i) {
        if (a > b && (1 << i) & num1) {
            res ^= 1 << i;
            --a;
        }
        if (a < b && !((1 << i) & num1)) {
            res ^= 1 << i;
            ++a;
        }
    }
    return res;
}

int tasks::task_2425(std::vector<int> &nums1, std::vector<int> &nums2)
{
    int c1 = nums1.size();
    int c2 = nums2.size();
    int x1 = 0, x2 = 0;

    if (c1 % 2 != 0) {
        for (int num : nums2) {
            x2 ^= num;
        }
    }
    if (c2 % 2 != 0) {
        for (int num : nums1) {
            x1 ^= num;
        }
    }
    return x1 ^ x2;
}
// вычисления накопительной суммы элементов в диапазоне
bool tasks::task_2683(std::vector<int> &derived)
{
    return accumulate(derived.begin(), derived.end(), 0, std::bit_xor<>())==0;
}

int tasks::task_1368(std::vector<std::vector<int> > &grid)
{
    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {1, -1, 0, 0};
    int r = grid.size(), c = grid[0].size();
    std::vector<std::vector<int>> dist(r, std::vector<int>(c, INT_MAX));
    std::deque<std::pair<int, int>> dq;
    dq.emplace_front(0, 0);
    dist[0][0] = 0;

    while (!dq.empty()) {
        auto [x, y] = dq.front(); dq.pop_front();
                for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                int cost = (i + 1 == grid[x][y]) ? 0 : 1;
                if (dist[x][y] + cost < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + cost;
                    if (cost == 0) {
                        dq.emplace_front(nx, ny);
                    } else {
                        dq.emplace_back(nx, ny);
                    }
                }
            }
        }
    }
    return dist[r-1][c-1];
}

int tasks::task_407(std::vector<std::vector<int> > &heightMap)
{
    int n = heightMap.size();
    int m = heightMap[0].size();

    // pair<int, pair<int, int>>
    //{height, {r, c}}
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> pq;

    std::vector<std::vector<int>> vis(n, std::vector<int>(m));

    //first and last column
    for(int i=0; i<n; i++){
        vis[i][0] = 1;
        vis[i][m-1] = 1;
        pq.push({heightMap[i][0], {i, 0}});
        pq.push({heightMap[i][m-1], {i, m-1}});
    }
    //first and last row
    for(int i=0; i<m; i++){
        vis[0][i]=1;
        vis[n-1][i]=1;
        pq.push({heightMap[0][i], {0, i}});
        pq.push({heightMap[n-1][i], {n-1, i}});
    }
    int ans=0;
    while(!pq.empty()){
        int h = pq.top().first;
        int r = pq.top().second.first;
        int c = pq.top().second.second;
        pq.pop();

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, -1, 0, 1};
        for(int i=0; i<4; i++){
            int nr = r + dr[i];
            int nc = c + dc[i];
            if(nr>=0 && nr<n && nc>=0 && nc<m && !vis[nr][nc]){
                ans+=std::max(0, h-heightMap[nr][nc]);
                pq.push({std::max(h, heightMap[nr][nc]), {nr, nc}});
                vis[nr][nc] = 1;
            }
        }
    }
    return ans;
}

int tasks::task_2661(std::vector<int> &arr, std::vector<std::vector<int> > &mat)
{
    int rows = mat.size(), cols = mat[0].size();
    std::unordered_map<int, std::pair<int, int>> positionMap;
    std::vector<int> rowCount(rows, cols), colCount(cols, rows);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            positionMap[mat[r][c]] = {r, c};
        }
    }

    for (int idx = 0; idx < arr.size(); ++idx) {
        int val = arr[idx];
        auto [row, col] = positionMap[val];

                if (--rowCount[row] == 0 || --colCount[col] == 0) {
            return idx;
        }
    }

    return -1;
}

long long tasks::task_2017(std::vector<std::vector<int> > &grid)
{
    long long top = 0;
    for (int i = 0; i < grid[0].size(); i++) {
        top += grid[0][i];
    }

    long long bottom = 0, res = LLONG_MAX;
    for (int i = 0; i < grid[0].size(); i++) {
        top -= grid[0][i]; // First robot picks from the top row
        res = std::min(res, std::max(top, bottom)); // Minimize the maximum score for the second robot
        bottom += grid[1][i]; // Second robot picks from the bottom row 🤖
    }
    return res;
}

std::vector<std::vector<int> > tasks::task_1765(std::vector<std::vector<int> > &isWater)
{
    const int r=isWater.size(), c=isWater[0].size();
    const int d[5]={0, 1, 0, -1, 0};
    std::vector<std::vector<int>> H(r, std::vector<int>(c, -1));
    std::queue<int> q;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if (isWater[i][j]){
                int idx=(i<<10)+j;
                H[i][j]=0;
                q.push(idx);
            }
        }
    }
    for(int h=0; !q.empty(); h++){
        int qz=q.size();
        for(int a=0; a<qz; a++){
            int idx=q.front(), i=idx>>10, j=idx&((1<<10)-1);
            q.pop();
            for(int b=0; b<4; b++){
                int s=i+d[b], t=j+d[b+1];
                if (s<0||s>=r||t<0||t>=c|| H[s][t]!=-1) continue;
                q.push((s<<10)+t);
                H[s][t]=h+1;
            }
        }
    }
    return H;
}

int tasks::task_1267(std::vector<std::vector<int> > &grid)
{
    std::vector<int> Rows(grid.size());
    std::vector<int> Col(grid[0].size());

    // Calculate row and column sums
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            Rows[i] += grid[i][j];
            Col[j] += grid[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 1 && (Rows[i] > 1 || Col[j] > 1)) {
                ans++;
            }
        }
    }
    return ans;
}

std::vector<int> tasks::task_802(std::vector<std::vector<int> > &graph)
{
    const int n=graph.size();
    std::vector<int> indeg(n, 0);
    std::vector<std::vector<int>> adj(n);
    for(int i=0; i<n ; i++){
        for(int j=graph[i].size()-1; j>=0; j--){
            int v=graph[i][j];
            adj[v].push_back(i);
            indeg[i]++;
        }
    }

    std::queue<int> q;

    for(int i=n-1; i>=0; i--)
        if (indeg[i]==0) q.push(i);

    std::vector<bool> safe(n, 0);
    while(!q.empty()){
        int x=q.front();
        //    cout<<x<<"->";;
        q.pop();
        safe[x]=1;
        for(int y: adj[x]){
            //        cout<<y<<",";
            if (--indeg[y]==0)
                q.push(y);
        }
        //    cout<<endl;
    }
    std::vector<int> ans;
    for(int i=0; i<n; i++)
        if (safe[i]) ans.push_back(i);
    return ans;
}

std::vector<int> tasks::task_2948(std::vector<int> &nums, int limit)
{
    std::vector<std::pair<int, int>> valueIndexPairs;
    int size = nums.size();

    for (int i = 0; i < size; ++i) {
        valueIndexPairs.push_back({nums[i], i});
    }

    sort(valueIndexPairs.begin(), valueIndexPairs.end());

    std::vector<std::vector<std::pair<int, int>>> groupedPairs;
    groupedPairs.push_back({valueIndexPairs[0]});

    for (int i = 1; i < size; ++i) {
        if (valueIndexPairs[i].first - valueIndexPairs[i - 1].first <= limit) {
            groupedPairs.back().push_back(valueIndexPairs[i]);
        } else {
            groupedPairs.push_back({valueIndexPairs[i]});
        }
    }

    for (const auto& group : groupedPairs) {
        std::vector<int> indices;
        for (const auto& [value, index] : group) {
            indices.push_back(index);
        }

        sort(indices.begin(), indices.end());

        for (size_t i = 0; i < indices.size(); ++i) {
            nums[indices[i]] = group[i].first;
        }
    }

    return nums;
}

int tasks::task_2127(std::vector<int> &favorite)
{
    int n = favorite.size();
    std::vector<int> inDegree(n, 0), chainLengths(n, 0);
    std::vector<bool> visited(n, false);

    for (int fav : favorite) {
        inDegree[fav]++;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        visited[node] = true;

        int next = favorite[node];
        chainLengths[next] = chainLengths[node] + 1;
        if (--inDegree[next] == 0) {
            q.push(next);
        }
    }

    int maxCycle = 0, totalChains = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int current = i, cycleLength = 0;
            while (!visited[current]) {
                visited[current] = true;
                current = favorite[current];
                cycleLength++;
            }

            if (cycleLength == 2) {
                totalChains += 2 + chainLengths[i] + chainLengths[favorite[i]];
            } else {
                maxCycle = std::max(maxCycle, cycleLength);
            }
        }
    }

    return std::max(maxCycle, totalChains);
}

std::vector<bool> tasks::task_1462(int numCourses, std::vector<std::vector<int> > &prerequisites, std::vector<std::vector<int> > &queries)
{
    // Step 1: Initialize the reachability map
    std::unordered_map<int, std::unordered_set<int>> reachable;

    // Step 2: Build direct reachability chains
    for (auto& prereq : prerequisites) {
        reachable[prereq[1]].insert(prereq[0]);
    }

    // Step 3: Propagate reachability to account for indirect prerequisites
    for (int i = 0; i < numCourses; ++i) {
        for (int j = 0; j < numCourses; ++j) {
            if (reachable[j].count(i)) {
                reachable[j].insert(reachable[i].begin(), reachable[i].end());
            }
        }
    }

    // Step 4: Answer the queries
    std::vector<bool> result;
    for (auto& query : queries) {
        result.push_back(reachable[query[1]].count(query[0]) > 0);
    }
    return result;
}

int tasks::task_2658(std::vector<std::vector<int> > &grid)
{
    int Max = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] > 0) {
                int C = 0;
                std::queue<std::pair<int, int>> T;
                T.push({i, j});
                while (!T.empty()) {
                    auto [x, y] = T.front();
                            T.pop();
                            if (grid[x][y] > 0) {
                        C += grid[x][y];
                        grid[x][y] = 0; // Mark as visited
                        if (x > 0 && grid[x - 1][y] > 0) T.push({x - 1, y});
                        if (x + 1 < grid.size() && grid[x + 1][y] > 0) T.push({x + 1, y});
                        if (y > 0 && grid[x][y - 1] > 0) T.push({x, y - 1});
                        if (y + 1 < grid[0].size() && grid[x][y + 1] > 0) T.push({x, y + 1});
                    }
                }
                Max = std::max(Max, C);
            }
        }
    }
    return Max;
}

std::vector<int> tasks::task_684(std::vector<std::vector<int> > &edges)
{
    std::unordered_map<int, std::vector<int>> graph;

    auto isConnected = [&](int u, int v) {
        std::unordered_set<int> visited;
        std::stack<int> stack;
        stack.push(u);

        while (!stack.empty()) {
            int node = stack.top();
            stack.pop();

            if (visited.count(node)) continue;
            visited.insert(node);

            if (node == v) return true;

            for (int neighbor : graph[node]) {
                stack.push(neighbor);
            }
        }
        return false;
    };

    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1];

        if (graph.count(u) && graph.count(v) && isConnected(u, v)) {
            return edge;
        }

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    return {};
}

int tasks::task_2493(int n, std::vector<std::vector<int> > &edges)
{
    // Step 1: Construct adjacency list
    std::vector<std::vector<int>> g(n+1);
    for(auto &e: edges){
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    // Step 2: Color array for bipartite check
    std::vector<int> color(n+1, 0);

    // Step 3: Bipartite check with BFS
    auto bipBfs = [&](int start) {
        std::queue<int> q;
        q.push(start);
        color[start] = 1;
        std::vector<int> comp;

        while(!q.empty()){
            int u = q.front();
            q.pop();
            comp.push_back(u);
            for(int v : g[u]){
                if(!color[v]){
                    color[v] = -color[u];  // Alternate coloring
                    q.push(v);
                } else if(color[v] == color[u]) {
                    return std::vector<int>();  // Not bipartite
                }
            }
        }
        return comp;
    };

    int ans = 0;

    // Step 4: Process each component
    for(int i = 1; i <= n; i++) {
        if (!color[i]) {
            auto comp = bipBfs(i);
            if (comp.empty()) return -1;  // Not bipartite

            int best = 0;

            // Step 5: Find maximum BFS depth in the component
            for(auto &x: comp) {
                std::vector<int> dist(n+1, -1);
                dist[x] = 0;
                std::queue<int> q;
                q.push(x);

                while(!q.empty()){
                    int u = q.front();
                    q.pop();
                    for(int v : g[u]){
                        if (dist[v] < 0) {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                        }
                    }
                }

                // Compute max depth in the component
                int layers = 0;
                for(auto &cnode : comp)
                    if (dist[cnode] >= 0)
                        layers = std::max(layers, dist[cnode]);

                best = std::max(best, layers + 1);
            }
            ans += best;
        }
    }
    return ans;
}

int tasks::task_827(std::vector<std::vector<int> > &grid)
{
    if (grid.empty())
        return 0;

    int n = grid.size();
    std::vector<std::vector<int>> labels(n,std::vector<int>(n, 0));
    std::unordered_map<int, int> islandSizes;
    int label = 1;
    int maxSize = 0;

    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1 && labels[i][j] == 0) {
                int size = 0;
                std::vector<std::pair<int, int>> stack;
                stack.push_back({i, j});
                labels[i][j] = label;

                while (!stack.empty()) {
                    auto [x, y] = stack.back();
                            stack.pop_back();
                            size++;

                            for (auto [dx, dy] : dirs) {
                        int nx = x + dx, ny = y + dy;
                        if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                                grid[nx][ny] == 1 && labels[nx][ny] == 0) {
                            labels[nx][ny] = label;
                            stack.push_back({nx, ny});
                        }
                    }
                }

                islandSizes[label] = size;
                maxSize = std::max(maxSize, size);
                label++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 0) {
                std::unordered_set<int> neighborLabels;
                int total = 1;

                for (auto [dx, dy] : dirs) {
                    int nx = i + dx, ny = j + dy;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                            grid[nx][ny] == 1) {
                        neighborLabels.insert(labels[nx][ny]);
                    }
                }

                for (int lbl : neighborLabels) {
                    total += islandSizes[lbl];
                }

                maxSize = std::max(maxSize, total);
            }
        }
    }

    return maxSize;
}

bool tasks::task_3151(std::vector<int> &nums)
{
    for(int i = 0; i < nums.size() - 1; i++) {
        if (nums[i] % 2 == nums[i + 1] % 2) {
            return false;
        }
    }
    return true;
}

bool tasks::task_1752(std::vector<int> &nums)
{
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
        if (nums[i] > nums[(i+1)%nums.size()] && ++count > 1) return false;
    return true;
}

int tasks::task_3105(std::vector<int> &nums)
{
    int n=nums.size(), i=0, ans=0;
    int inc=1, dec=1;
    if (n==1) return 1;
    for(i=1 ;i<n; i++){
        if (nums[i]>nums[i-1]) inc++, dec=1;
        else if (nums[i]<nums[i-1]) inc=1, dec++;
        else inc=dec=1;
        ans=std::max({ans, dec, inc});
    }
    return ans;
}

int tasks::task_1800(std::vector<int> &nums)
{
    const int n=nums.size();
    int maxSum=0, sum=nums[0];
    for(int r=1; r<n; r++){
        if (nums[r]>nums[r-1]) sum+=nums[r];
        else{
            maxSum=std::max(maxSum, sum);
            sum=nums[r];
        }
    }
    return std::max(maxSum, sum);
}

bool tasks::task_1790(std::string s1, std::string s2)
{
    for(int i = 0, end = s1.length(), first, count = 0;i < end;i++)
    {
        if(s1[i] != s2[i])
        {
            count++;
            if(count == 1)
            {
                first = i;
            }
            else
            {
                char temp = s1[first];
                s1[first] = s1[i];
                s1[i] = temp;
                break;
            }
        }
    }

    if(s1 == s2)
    {
        return true;
    }

    return false;
}

int tasks::task_1726(std::vector<int> &nums)
{
    std::unordered_map<int, int> mp;
    int ans = 0, n = nums.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int product = nums[i] * nums[j];
            ans += 8 * mp[product];
            mp[product]++;
        }
    return ans;
}

std::vector<int> tasks::task_3160(int limit, std::vector<std::vector<int> > &queries)
{
    std::unordered_map<int,int> ball, color;
    std::vector<int> ans;
    ans.reserve(queries.size());
    int distinct = 0;
    for(auto &q : queries) {
        int pos = q[0], c = q[1];
        if(ball.count(pos))
            if(--color[ball[pos]] == 0) distinct--;
        ball[pos] = c;
        if(++color[c] == 1) distinct++;
        ans.push_back(distinct);
    }
    return ans;
}

long long tasks::task_2364(std::vector<int> &nums)
{
    std::unordered_map<int, int> freq;
    long long goodPairs = 0, n = nums.size();

    for (int i = 0; i < n; i++) {
        int key = nums[i] - i;
        goodPairs += freq[key];
        freq[key]++;
    }

    return (n * (n - 1)) / 2 - goodPairs;
}

std::string tasks::task_3174(std::string s)
{
    std::string stack;
    for (char c : s) {
        if (isdigit(c)) {
            if (!stack.empty()) stack.pop_back();
        } else {
            stack.push_back(c);
        }
    }
    return stack;
}

std::string tasks::task_1910(std::string s, std::string part)
{
    std::string resultStack;
    int targetLength = part.size();
    char targetEndChar = part.back();

    for (char currentChar : s) {
        resultStack.push_back(currentChar);

        if (currentChar == targetEndChar && resultStack.size() >= targetLength) {
            if (resultStack.substr(resultStack.size() - targetLength) == part) {
                resultStack.erase(resultStack.size() - targetLength);
            }
        }
    }
    return resultStack;
}

int tasks::task_2342(std::vector<int> &nums)
{
    int max[82] = {0};
    int ans = -1;
    for (int x : nums) {
        int sum = 0, temp = x;
        while (temp != 0) {
            sum += temp % 10;
            temp /= 10;
        }
        if (max[sum] != 0) ans = std::max(ans, x + max[sum]);
        max[sum] = std::max(max[sum], x);
    }
    return ans;
}

int tasks::task_3066(std::vector<int> &nums, int k)
{
    //приоритетная очередь, greater для того, чтобы на вершине очереди всегда находился наименьший элемент
        std::priority_queue<double,std::vector<double>,std::greater<double>>pq;
        //заполняем очередь элементами из вектора
        for(int &num:nums) {
            pq.push(num);
        }
        int result=0;
        //пока в очереди больше 1 элемента
        while(pq.size()>1){
            //извлекаем наименьший элемент из очереди
            double x = pq.top();
            //удаляем его из очереди
            pq.pop();
            double y = pq.top();
            pq.pop();
            //если наименьший из достаных чисел больше к, то возвращаем результат операций
            if(x>=k){return result;}
            double n = 2*(double)std::min(x,y)+(double)std::max(x,y);
            //пушим обратно в очередь новый элемент
            pq.push(n);
            result++;
        }
        return result;
}

int tasks::task_2698(int n)
{
    int arr[] = { 1, 9, 10, 36, 45, 55, 82, 91, 99, 100, 235, 297, 369, 370, 379, 414, 657, 675, 703, 756, 792, 909,
                  918, 945, 964, 990, 991, 999, 1000 };
    int res = 0;
    for (int i = 0; i < 29; i++) {
        if (arr[i] <= n) {
            res += arr[i] * arr[i];
        } else {
            break;
        }
    }
    return res;
}

std::vector<int> tasks::task_1718(int n)
{
    this->n = n;
    az = 2 * n - 1;
    ans1.assign(az, 0);
    dfs(0);
    return ans1;
}

bool tasks::dfs(int pos)
{
    if (pos==az) return viz1.count()==n;  // Base case: all numbers used
    if (ans1[pos]!= 0) return dfs(pos+1);  // Skip if already filled

    for (int j=n; j>= 1; j--) {  // larger first
        if (viz1[j]) continue;  // If j is used, skip
        int next_pos=(j>1)?pos+j:pos;  // should put j

        if (next_pos>=az || ans1[next_pos]!=0) continue;  // Ensure valid placement

        ans1[pos]=ans1[next_pos]= j;  // Place j
        viz1[j]=1;

        if (dfs(pos+1)) return 1;  // Recurse

        // Backtrack
        ans1[pos]=ans1[next_pos]=viz1[j]=0;
    }
    return 0;
}

int tasks::task_1079(std::string tiles)
{
    // Получаем длину строки плиток
        int n = tiles.length();

        // Вектор для подсчета количества каждой буквы (плитки)
        std::vector<int> counts(26, 0);

        // Вектор для хранения факториалов от 0 до n
        std::vector<int> fac(n + 1, 1);

        // Вычисляем факториалы от 1 до n
        for (int i = 1; i <= n; i++) {
            fac[i] = i * fac[i - 1];
        }

        // Подсчитываем количество каждой буквы в строке tiles
        for (char c : tiles) {
            counts[c - 'A']++;
        }

        // Вектор для хранения количества комбинаций для каждой длины
        std::vector<int> lengthcounts(n + 1, 0);
        lengthcounts[0] = 1; // Инициализируем количество комбинаций длины 0

        // Проходим по всем возможным буквам (A-Z)
        for (int i = 0; i < 26; i++) {
            if (counts[i] > 0) { // Если буква присутствует в плитках
                std::vector<int> temp(n + 1, 0); // Временный вектор для подсчетов

                // Проходим по всем длинам комбинаций, которые уже были подсчитаны
                for (int j = 0; j <= n && lengthcounts[j] > 0; j++) {
                    // Добавляем плитки текущей буквы
                    for (int k = 1; k <= counts[i]; k++) {
                        int totallength = j + k; // Общая длина комбинации
                        // Обновляем временный вектор с учетом новых комбинаций
                        temp[totallength] += lengthcounts[j] * fac[totallength] / (fac[k] * fac[j]);
                    }
                }
                // Обновляем основной вектор с учетом новых комбинаций
                for (int j = 0; j <= n; j++) {
                    lengthcounts[j] += temp[j];
                }
            }
        }

        // Суммируем все возможные комбинации длины от 1 до n
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += lengthcounts[i];
        }

        return ans; // Возвращаем общее количество комбинаций
}

std::string tasks::task_2375(std::string pattern)
{
    int n=pattern.size();
    std::string result = "";
    int stack[n+1];
    int index = 0;
    for (int i=0; i<=n; i++){
        stack[index++] = i+1; //stack[1]=1, stack[2]=2
        if (i==n || pattern[i]=='I'){ //если мы дошли до конца строки или символ в строке равен I
            while(index>0){  //пока индекс больше 0
                result += std::to_string(stack[--index]);
            }
        }
    }
    return result;
}

std::string tasks::task_1415(int n, int k)
{
    // Вычисляем общее количество счастливых строк длины n
    int sz = 3 * (1 << (n - 1)); // 3 * 2^(n-1)
    // Если k больше общего количества счастливых строк, возвращаем пустую строку
    if (k > sz) return "";
    // Делим (k-1) на 2^(n-1) для получения индекса первого символа и остатка
    auto [q, r] = div(k - 1, 1 << (n - 1)); // k-1
            // Создаем строку длины n, инициализируем пробелами
            std::string s(n, ' ');
            // Устанавливаем первый символ строки в 'a', 'b' или 'c' в зависимости от q
            s[0] = 'a' + q; // q может быть 0, 1 или 2
            // Создаем битовое представление остатка r
            std::bitset<9> bin(r);
            // Массив, который хранит возможные символы для каждого символа
            std::array<char, 2> xx[3] = {{'b', 'c'}, {'a', 'c'}, {'a', 'b'}};
    // Заполняем оставшиеся символы строки, начиная с конца
    for (int i = n - 2; i >= 0; i--) {
        // Получаем индекс текущего символа
        char idx = s[n - 2 - i] - 'a'; // Преобразуем символ в индекс (0, 1 или 2)
        // Устанавливаем следующий символ в зависимости от значения бита в bin
        s[n - 1 - i] = (bin[i]) ? xx[idx][1] : xx[idx][0];
    }
    // Возвращаем сформированную счастливую строку
    return s;
}

std::string tasks::task_1980(std::vector<std::string> &nums)
{
    std::string result;
    // Проходим по всем элементам вектора nums
    for (int i = 0; i < nums.size(); i++) {
        // Проверяем символ на позиции i в строке nums[i]
        if (nums[i][i] == '0') {          // Если символ равен '0', добавляем '1' в результат
            result += '1';
        } else {// Если символ равен '1', добавляем '0' в результат
            result += '0';
        }
    }
    return result;
}


void tasks::task_1261_1(TreeNode* root)
{
    if (!root) return;
    recoveredValues.insert(root->val);
    if (root->left) {
        root->left->val = 2 * root->val + 1;
        task_1261_1(root);
    }
    if (root->right) {
        root->right->val = 2 * root->val + 2;
        task_1261_1(root);
    }
}



void tasks::task_1261_2(TreeNode *root)
{
    root->val = 0;
    task_1261_1(root);
}

bool tasks::task_1261_3(int target)
{
    return recoveredValues.count(target);
}
std::string s;
    int idx = 0, level = 0;
TreeNode *tasks::task_1028(std::string traversal)
{
    s = traversal;
    TreeNode* node = new TreeNode(-1);
    task_1028_2(node, 0);
    return node->left;
}

void tasks::task_1028_2(TreeNode *parent, int lvl)
{
    while (idx < s.length() && lvl == level) {
        int num = 0;
        while (idx < s.length() && isdigit(s[idx])) {
            num = num * 10 + (s[idx++] - '0');
        }
        TreeNode* node = new TreeNode(num);
        if (!parent->left)
            parent->left = node;
        else
            parent->right = node;
        level = 0;
        while (idx < s.length() && s[idx] == '-') {
            level++;
            idx++;
        }
        task_1028_2(node, lvl + 1);
    }
}

TreeNode *tasks::task_889(std::vector<int> &preorder, std::vector<int> &postorder)
{
    std::stack<TreeNode*> nodes;
    TreeNode* root = new TreeNode(preorder[0]);
    nodes.push(root);

    int preIndex = 1, postIndex = 0;

    while (!nodes.empty()) {
        TreeNode* current = nodes.top();

        if (current->val == postorder[postIndex]) {
            nodes.pop();
            postIndex++;
        } else {
            TreeNode* newNode = new TreeNode(preorder[preIndex++]);
            if (!current->left) {
                current->left = newNode;
            } else {
                current->right = newNode;
            }
            nodes.push(newNode);
        }
    }
    return root;
}

int tasks::task_2467(std::vector<std::vector<int> > &edges, int bob, std::vector<int> &amount)
{

    int n = edges.size() + 1; // Количество вершин в графе (количество рёбер + 1)
    std::vector<std::vector<int>> adj(n); // Список смежности для представления графа
    std::vector<int> up(n); // Вектор для хранения родительских вершин

    // Заполнение списка смежности
    for(auto& e : edges) {
        adj[e[0]].push_back(e[1]); // Добавление ребра в обе стороны
        adj[e[1]].push_back(e[0]);
    }
    std::vector<int> bobTime(n, -1); // Вектор для хранения времени, когда Боб достигает каждой вершины

    // Лямбда-функция для выполнения DFS и заполнения родительских вершин
    //[&](this auto&& dfs, int v, int parent) -> void
    //{
    //    up[v] = parent; // Установка родительской вершины
    //    for(int ce : adj[v]) { // Проход по всем соседям
    //        if(ce != parent) { // Если сосед не является родителем
    //            dfs(ce, v); // Рекурсивный вызов DFS
    //        }
    //    }
   // }(0, -1); // Запуск DFS с начальной вершины 0 и без родителя

    // Заполнение времени достижения Бобом каждой вершины
    for(int second = 0; bob != -1; second++) {
        bobTime[bob] = second; // Установка времени для текущей вершины Боба
        bob = up[bob]; // Переход к родительской вершине
    }

    // Лямбда-функция для выполнения DFS и нахождения наиболее прибыльного пути
    //return [&](this auto&& dfs, int v, int second, int parent) -> int {
    //    int best = 0; // Переменная для хранения наилучшего результата

        // Проверка, если у вершины больше одного соседа или это корневая вершина
    //    if(adj[v].size() > 1 || parent == -1) {
    //        best = UF; // Инициализация наихудшего результата
    //        for(int ce : adj[v]) { // Проход по всем соседям
    //            if(ce != parent) { // Если сосед не является родителем
    //                best = max(best, dfs(ce, second + 1, v)); // Рекурсивный вызов DFS и обновление наилучшего результата
    //            }
    //        }
    //    }

        // Проверка времени достижения Бобом текущей вершины
    //    if(bobTime[v] != -1) {
    //        if(bobTime[v] == second) {
    //            best += amount[v] / 2; // Если Боб достигает вершину в то же время, что и мы, добавляем половину прибыли
    //        } else if(bobTime[v] > second) {
    //            best += amount[v]; // Если Боб достигает вершину позже, добавляем полную прибыль
    //        }
    //    } else {
    //        best += amount[v]; // Если Боб не достигает вершину, добавляем полную прибыль
    //    }
    //    return best; // Возвращаем наилучший результат для текущей вершины
    //}(0, 0, -1); // Запуск DFS с начальной вершины 0, временем 0 и без родителя
    return 5;
}

int tasks::task_1524(std::vector<int> &arr)
{
    long long result=0;
    long long sum=0;
    for (int i=0;i<arr.size();i++)
    {
        sum+=arr[i];
        // Увеличиваем результат на 1, если текущая сумма нечетная
        result+=sum%2;
    }
    // Добавляем к результату количество подмассивов, которые могут быть образованы
    // из четных сумм, умноженное на количество нечетных сумм
    result+=(arr.size()-result)*result;
    // Возвращаем результат по модулю 1000000007 для предотвращения переполнения
    return result%1000000007;
}

int tasks::task_1749(std::vector<int> &nums)
{
    int sum = 0, minSum = 0, maxSum = 0;
    for (int num : nums) {
        sum += num;
        if (sum > maxSum) maxSum = sum;
        if (sum < minSum) minSum = sum;
    }
    return abs(maxSum - minSum);
}

int tasks::task_873(std::vector<int> &arr)
{
    int n = arr.size();
    // Инициализируем двумерный вектор dp размером n x n, заполненный нулями
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    int maxLen = 0;
    // Проходим по всем элементам массива, начиная с третьего (curr = 2)
    for (int curr = 2; curr < n; curr++) {
        // Устанавливаем начальные индексы для поиска пар
        int start = 0, end = curr - 1;
        // Пока начальный индекс меньше конечного
        while (start < end) {
            // Вычисляем сумму пары элементов на позициях start и end
            int pairSum = arr[start] + arr[end];
            // Если сумма пары больше текущего элемента, сдвигаем конечный индекс влево
            if (pairSum > arr[curr]) {end--;}
            // Если сумма пары меньше текущего элемента, сдвигаем начальный индекс вправо
            else if (pairSum < arr[curr]) {start++;}
            // Если сумма пары равна текущему элементу
            else {
                // Обновляем значение dp для текущей пары
                dp[end][curr] = dp[start][end] + 1;
                // Обновляем максимальную длину, если найденная длина больше
                maxLen = std::max(dp[end][curr], maxLen);
                // Сдвигаем оба индекса
                end--;
                start++;
            }
        }
    }
    // Возвращаем максимальную длину последовательности, увеличенную на 2, если она больше 0
    return maxLen == 0 ? 0 : maxLen + 2;
}

std::string tasks::task_1092(std::string str1, std::string str2)
{
    int m = str1.size();
    int n = str2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    // Заполнение таблицы dp
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Построение результата
    std::string result;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            result += str1[i - 1];
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            result += str1[i - 1];
            --i;
        } else {
            result += str2[j - 1];
            --j;
        }
    }

    // Добавление оставшихся символов
    while (i > 0) {
        result += str1[i - 1];
        --i;
    }
    while (j > 0) {
        result += str2[j - 1];
        --j;
    }

    // Реверсируем результат, так как мы строили его в обратном порядке
    reverse(result.begin(), result.end());
    return result;
}

std::vector<int> tasks::task_2460(std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<int> newNums(n, 0);
    int count = 0;

    for (int i = 0; i < n - 1; i++) {
        if (nums[i] != 0) {
            if (nums[i] == nums[i + 1]) {
                newNums[count] = nums[i] * 2;
                nums[i + 1] = 0;
                i++;
            } else {
                newNums[count] = nums[i];
            }
            count++;
        }
    }
    if (nums[n - 1] != 0) {
        newNums[count++] = nums[n - 1];
    }

    return newNums;
}

std::vector<std::vector<int> > tasks::task_2570(std::vector<std::vector<int> > &nums1, std::vector<std::vector<int> > &nums2)
{
    int i = 0, j = 0;
    std::vector<std::vector<int>> result;

    // Traverse both arrays with two pointers
    while (i < nums1.size() && j < nums2.size()) {
        int id1 = nums1[i][0], val1 = nums1[i][1];
        int id2 = nums2[j][0], val2 = nums2[j][1];

        if (id1 < id2) {
            // Id1 is smaller, add it to result
            result.push_back({id1, val1});
            i++;
        } else if (id2 < id1) {
            // Id2 is smaller, add it to result
            result.push_back({id2, val2});
            j++;
        } else {
            // Ids are equal, sum the values
            result.push_back({id1, val1 + val2});
            i++;
            j++;
        }
    }

    // Add remaining elements from nums1, if any
    while (i < nums1.size()) {
        result.push_back(nums1[i]);
        i++;
    }

    // Add remaining elements from nums2, if any
    while (j < nums2.size()) {
        result.push_back(nums2[j]);
        j++;
    }

    return result;
}

std::vector<int> tasks::task_2161(std::vector<int> &nums, int pivot)
{
    std::vector<int>res(nums.size());
    int c=0;
    int pt=0;
    for(int i=0;i<nums.size();i++) {
        if(nums[i]<pivot) {
            res[pt++]=nums[i];
        }
        else if(nums[i]==pivot) {
            c++;
        }
    }
    while(c--) {
        res[pt++]=pivot;//equal to pivot
    }
    for(int i=0;i<nums.size();i++) {
        if(nums[i]>pivot) {
            res[pt]=nums[i];
            pt++;
        }
    }
    return res;
}

bool tasks::task_1780(int n)
{
    while (n>0) {
        //единственное число, которое нас не устроит это 2
        if (n%3 == 2) {
            return false;
        }
        n /= 3;
    }
    return true;
}

long long tasks::task_2579(int n)
{
    long long res = 1;
    if (n==1) {return res;}
    for (int i = 1; i < n; i++) {
        res += 4*i;
    }
    return res;
}

std::vector<int> tasks::task_2965(std::vector<std::vector<int> > &grid)
{
    int a, n = grid.size();
    std::vector<int> num_freq(n*n + 1, 0);
    for(std::vector<int> row : grid) {
        for(int num : row) {
            if(num_freq[num] == 1)
                a = num;
            num_freq[num]++;
        }
    }
    for(int num = 1; num <= n*n; num++)
        if(num_freq[num] == 0)
            return {a, num};
    return {-1, -1};
}

int tasks::task_2379(std::string blocks, int k)
{
    int black_count = 0, ans = INT_MAX;

    for (int i = 0; i < blocks.size(); i++) {
        if (i - k >= 0 && blocks[i - k] == 'B') black_count--;
        if (blocks[i] == 'B') black_count++;
        ans = std::min(ans, k - black_count);
    }

    return ans;
}

int tasks::task_3208(std::vector<int> &colors, int k)
{
    colors.insert(colors.end(), colors.begin(), colors.begin() + (k - 1));
    int count = 0;
    int left = 0;

    for (int right = 0; right < colors.size(); ++right) {
        if (right > 0 && colors[right] == colors[right - 1]) {
            left = right;
        }

        if (right - left + 1 >= k) {
            count++;
        }
    }

    return count;
}

long long tasks::task_3306(std::string word, int k)
{
    int frequencies[2][128] = {};
    frequencies[0]['a'] = frequencies[0]['e'] = frequencies[0]['i'] = frequencies[0]['o'] = frequencies[0]['u'] = 1;

    long long response = 0;
    int currentK = 0, vowels = 0, extraLeft = 0, left = 0;

    for (int right = 0; right < word.length(); right++) {
        char rightChar = word[right];

        if (frequencies[0][rightChar]) {
            if (++frequencies[1][rightChar] == 1) vowels++;
        } else {
            currentK++;
        }

        while (currentK > k) {
            char leftChar = word[left++];
            if (frequencies[0][leftChar]) {
                if (--frequencies[1][leftChar] == 0) vowels--;
            } else {
                currentK--;
            }
            extraLeft = 0;
        }

        while (vowels == 5 && currentK == k && left < right && frequencies[0][word[left]] && frequencies[1][word[left]] > 1) {
            extraLeft++;
            frequencies[1][word[left++]]--;
        }

        if (currentK == k && vowels == 5) {
            response += (1 + extraLeft);
        }
    }

    return response;
}

int tasks::task_1358(std::string s)
{
    int abc[3] = {-1, -1, -1};
    int count = 0, right = 0;
    while (right < s.length()) {
        abc[s[right] - 'a'] = right;
        int minIndex = INT_MAX;
        for (int i = 0; i < 3; i++) {
            minIndex = std::min(minIndex, abc[i]);
        }
        count += (minIndex + 1);
        right++;
    }
    return count;
}

int tasks::task_2529(std::vector<int> &nums)
{
    int plus=0,minus=0;
    for (auto i : nums) {
        if (i<0) minus++;
        if (i>0) plus++;
    }
    return (plus>=minus) ? plus : minus;
}

int tasks::task_3356(std::vector<int> &nums, std::vector<std::vector<int> > &queries)
{
    const int n=nums.size(), m=queries.size();
    std::vector<int> freq(n+1);
    int op=0, k=0;
    for(int i=0; i<n; i++){
        // Внутренний цикл выполняется, пока количество операций меньше разности
        // между текущим элементом nums[i] и значением freq[i]
        for( ; op < nums[i]-freq[i]; k++){
            if (k>=m) return -1;
            const int l=queries[k][0], r=queries[k][1], v=queries[k][2];
            if (r<i) continue;
            freq[std::max(l, i)]+=v;
            freq[r+1]-=v;
        }
        op+=freq[i];
    }
    return k;
}

int tasks::task_2226(std::vector<int> &candies, long long k)
{
    long long left = 1, right = *max_element(candies.begin(), candies.end());
    int result=0;
    while (left<=right) {
        long long mid = left+(right-left)/2;
        long long children_count = 0;
        for ( auto candi : candies) {
            children_count += candi/mid;
        }
        if (children_count >= k) {
            result=mid;
            left = mid+1;
        } else {
            right = mid-1;
        }
    }
    return result;
}

bool task_2560_2(std::vector<int> &nums, int k, int capability) {
    int count=0;
    for(int i=0; i<nums.size(); i++) {
        if (nums[i]<=capability) {
            count++;
            i++;
        }
        if (count>=k) return true;
    }
    return false;
}

int tasks::task_2560(std::vector<int> &nums, int k)
{
    int left = *min_element(nums.begin(), nums.end());
    int right = *max_element(nums.begin(), nums.end());
    while (left < right) {
        int mid = left +(right-left)/2;
        if (task_2560_2(nums,k,mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

long long tasks::task_2594(std::vector<int> &ranks, int cars)
{
    long long left = 1, right = (long long)*min_element(ranks.begin(), ranks.end()) * cars * cars;

    auto can_repair_all = [&](long long time) {
        long long total_cars_repaired = 0;
        for (int rank : ranks) {
            total_cars_repaired += sqrt(time / rank);
            if (total_cars_repaired >= cars) return true;
        }
        return false;
    };

    while (left < right) {
        long long mid = (left + right) / 2;
        if (can_repair_all(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

bool tasks::task_2206(std::vector<int> &nums)
{
    std::sort(nums.begin(),nums.end());
    for (int i=0; i<nums.size(); i+=2) {
        if (nums[i]!=nums[i+1]) return false;

    }
    return true;
}

int tasks::task_2401(std::vector<int> &nums)
{
    int n = nums.size();
    int max_length = 1;
    int left = 0;
    int used_bits = 0;

    for (int right = 0; right < n; ++right) {
        while ((used_bits & nums[right]) != 0) {
            used_bits ^= nums[left];
            ++left;
        }

        used_bits |= nums[right];
        max_length = std::max(max_length, right - left + 1);
    }

    return max_length;
}

int tasks::task_3191(std::vector<int> &nums)
{
    int count = 0;
    for (int i = 0;i<nums.size() - 2; i++) {
        if (nums[i] == 0) {
            nums[i] ^= 1;
            nums[i+1] ^= 1;
            nums[i+2] ^= 1;
            count++;
        }
    }
    return (nums[nums.size()-2] == 1 && nums[nums.size()-1] == 1) ? count : -1;
}

std::vector<int> parent, minPathCost;
int findRoot(int node) {
    if (parent[node] != node) {
        parent[node] = findRoot(parent[node]); // Path compression
    }
    return parent[node];
}

std::vector<int> tasks::task_3108(int n, std::vector<std::vector<int> > &edges, std::vector<std::vector<int> > &query)
{
    parent.resize(n);
    minPathCost.assign(n, -1);
    for (int i = 0; i < n; i++) parent[i] = i;

    for (auto& edge : edges) {
        int source = edge[0], target = edge[1], weight = edge[2];
        int sourceRoot = findRoot(source);
        int targetRoot = findRoot(target);

        if (minPathCost[sourceRoot] == -1) minPathCost[sourceRoot] = weight;
        else minPathCost[sourceRoot] &= weight;

        if (minPathCost[targetRoot] == -1) minPathCost[targetRoot] = weight;
        else minPathCost[targetRoot] &= weight;

        if (sourceRoot != targetRoot) {
            parent[sourceRoot] = targetRoot;
            minPathCost[targetRoot] &= minPathCost[sourceRoot];
        }
    }

    std::vector<int> result;
    for (auto& q : query) {
        int start = q[0], end = q[1];

        if (start == end) result.push_back(0);
        else if (findRoot(start) != findRoot(end)) result.push_back(-1);
        else result.push_back(minPathCost[findRoot(start)]);
    }

    return result;
}

std::vector<std::string> tasks::task_2115(std::vector<std::string> &recipes, std::vector<std::vector<std::string> > &ingredients, std::vector<std::string> &supplies)
{
    std::unordered_map<std::string, std::vector<std::string>> graph; // Объявляем граф, который будет хранить рецепты и их ингредиенты
        std::unordered_map<std::string, int> indegree;// Объявляем карту для хранения количества входящих зависимостей (ингредиентов) для каждого рецепта
        std::unordered_set<std::string> available(supplies.begin(), supplies.end());// Создаем множество доступных ингредиентов из вектора supplies
        std::vector<std::string> result;// Вектор для хранения результатов (рецептов, которые можно приготовить)

        // Step 1: Build graph and indegree map
        for (int i = 0; i < recipes.size(); i++) {
            std::string recipe = recipes[i];
            indegree[recipe] = ingredients[i].size();// Устанавливаем количество необходимых ингредиентов для рецепта

            for (std::string& ing : ingredients[i]) {
                graph[ing].push_back(recipe);// Добавляем рецепт в список рецептов, которые зависят от данного ингредиента
            }
        }

        // Step 2: Perform BFS
        std::queue<std::string> q;//(supplies.begin(), supplies.end());// Инициализируем очередь доступными ингредиентами

        while (!q.empty()) {// Пока очередь не пуста
            std::string item = q.front();
            q.pop();
            if (!graph.count(item)) continue;

            for (std::string& recipe : graph[item]) {
                indegree[recipe]--;
                if (indegree[recipe] == 0) {
                    result.push_back(recipe);
                    q.push(recipe);
                }
            }
        }

        return result;
}

int tasks::task_2685(int n, std::vector<std::vector<int> > &edges)
{
    std::vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0);

    std::function<int(int)> find = [&](int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };

    auto unionSets = [&](int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    };

    for (auto& edge : edges) {
        unionSets(edge[0], edge[1]);
    }

    std::unordered_map<int, std::unordered_set<int>> componentVertices;
    std::unordered_map<int, int> componentEdges;

    for (int i = 0; i < n; ++i) {
        int root = find(i);
        componentVertices[root].insert(i);
    }

    for (auto& edge : edges) {
        int root = find(edge[0]);
        componentEdges[root]++;
    }

    int completeCount = 0;
    for (auto& [root, vertices] : componentVertices) {
        int numVertices = vertices.size();
        int expectedEdges = numVertices * (numVertices - 1) / 2;
        if (componentEdges[root] == expectedEdges) {
            completeCount++;
        }
    }

    return completeCount;
}

int tasks::task_1976(int n, std::vector<std::vector<int> > &roads)
{
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    for (const auto& road : roads) {
        int u = road[0], v = road[1], time = road[2];
        graph[u].emplace_back(v, time);
        graph[v].emplace_back(u, time);
    }

    std::vector<long long> dist(n, LLONG_MAX);
    std::vector<int> ways(n, 0);

    dist[0] = 0;
    ways[0] = 1;

    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> pq;
    pq.emplace(0, 0);

    const int MOD = 1e9 + 7;

    while (!pq.empty()) {
        auto [d, node] = pq.top();
                pq.pop();

                if (d > dist[node]) continue;

                for (const auto& [neighbor, time] : graph[node]) {
            if (dist[node] + time < dist[neighbor]) {
                dist[neighbor] = dist[node] + time;
                ways[neighbor] = ways[node];
                pq.emplace(dist[neighbor], neighbor);
            } else if (dist[node] + time == dist[neighbor]) {
                ways[neighbor] = (ways[neighbor] + ways[node]) % MOD;
            }
        }
    }

    return ways[n - 1];
}

int tasks::task_3169(int days, std::vector<std::vector<int> > &meetings)
{
    // Сортируем встречи по времени начала
    std::sort(meetings.begin(), meetings.end());

    int meetingDaysCount = 0; // Переменная для подсчета количества дней, занятых встречами
    int currentStart = -1, currentEnd = -1; // Переменные для хранения начала и конца текущего диапазона встреч

    // Проходим по всем встречам
    for (const auto& meeting : meetings) {
        int start = meeting[0], end = meeting[1]; // Извлекаем время начала и конца встречи
        // Если начало текущей встречи больше конца последней встречи
        if (start > currentEnd) {
            // Если у нас уже была встреча, добавляем дни к общему счетчику
            if (currentEnd != -1) {
                meetingDaysCount += currentEnd - currentStart + 1; // Увеличиваем счетчик на количество дней между текущим началом и концом
            }
            // Обновляем текущие начало и конец на новые значения
            currentStart = start;
            currentEnd = end;
        } else {
            // Если встречи пересекаются, обновляем конец, если это необходимо
            currentEnd = std::max(currentEnd, end);
        }
    }

    // Если есть активные встречи, добавляем их дни к общему счетчику
    if (currentEnd != -1) {
        meetingDaysCount += currentEnd - currentStart + 1; // Увеличиваем счетчик на количество дней для последней встречи
    }

    // Возвращаем количество свободных дней, вычитая занятые дни из общего количества дней
    return days - meetingDaysCount;
}

bool tasks::task_3394(int n, std::vector<std::vector<int> > &rectangles)
{
    // Лямбда-функция для проверки валидности разреза
    auto isValidCut = [&](int sortIndex, int start, int end) {
        // Сортируем прямоугольники по указанному индексу (ширина или высота)
        sort(rectangles.begin(), rectangles.end(), [&](const std::vector<int>& a, const std::vector<int>& b) {
            return a[sortIndex] < b[sortIndex];
        });

        // Инициализируем текущие границы интервала
        int currentStart = rectangles[0][start];
        int currentEnd = rectangles[0][end];
        int intervals = 0; // Счетчик интервалов

        // Проходим по всем прямоугольникам
        for (const auto& rect : rectangles) {
            // Если текущий прямоугольник пересекается с текущим интервалом
            if (rect[start] < currentEnd) {
                // Обновляем конец интервала
                currentEnd = std::max(rect[end], currentEnd);
            } else {
                // Если нет пересечения, увеличиваем счетчик интервалов
                intervals++;
                // Обновляем границы нового интервала
                currentStart = rect[start];
                currentEnd = rect[end];
            }
        }
        // Увеличиваем счетчик интервалов на 1 для последнего интервала
        intervals++;

        // Возвращаем true, если количество интервалов больше 2
        return intervals > 2;
    };

    // Проверяем валидность разрезов для двух случаев: по ширине и по высоте
    return isValidCut(0, 0, 2) || isValidCut(1, 1, 3);
}

int tasks::task_2033(std::vector<std::vector<int> > &grid, int x)
{
    std::vector<int> values;
    for (const auto& row : grid) {
        for (int val : row) {
            values.push_back(val);
        }
    }
    sort(values.begin(), values.end());
    for (int val : values) {
        if (abs(val - values[0]) % x != 0) {
            return -1;
        }
    }
    int median = values[values.size() / 2];
    int operations = 0;
    for (int val : values) {
        operations += abs(val - median) / x;
    }
    return operations;
}

int tasks::task_2780(std::vector<int> &nums)
{
    // Определяем лямбда-функцию для поиска доминирующего элемента в массиве
    auto find_dominant_element = [](const std::vector<int>& arr) {
        int candidate = -1; // Кандидат на доминирующий элемент
        int count = 0;      // Счетчик для отслеживания количества вхождений кандидата
        // Проходим по всем элементам массива
        for (int num : arr) {
            // Если счетчик равен 0, выбираем текущий элемент как кандидата
            if (count == 0) {
                candidate = num;
                count = 1; // Устанавливаем счетчик на 1
            }
            // Если текущий элемент равен кандидату, увеличиваем счетчик
            else if (num == candidate) {
                count++;
            }
            // Если текущий элемент не равен кандидату, уменьшаем счетчик
            else {
                count--;
            }
        }
        // Подсчитываем количество вхождений кандидата в массив
        count = count_if(arr.begin(), arr.end(), [&](int num) { return num == candidate; });
        // Проверяем, является ли кандидат доминирующим элементом (больше половины массива)
        return (count > arr.size() / 2) ? candidate : -1;
    };
    // Вызываем функцию для нахождения доминирующего элемента в массиве nums
    int dominant = find_dominant_element(nums);
    // Если доминирующий элемент не найден, возвращаем -1
    if (dominant == -1) return -1;
    // Инициализируем счетчик для левой части массива
    int left_count = 0;
    // Подсчитываем общее количество доминирующего элемента в массиве
    int total_dominant_count = count(nums.begin(), nums.end(), dominant);
    // Проходим по массиву, исключая последний элемент
    for (int i = 0; i < nums.size() - 1; i++) {
        // Если текущий элемент равен доминирующему, увеличиваем счетчик левой части
        if (nums[i] == dominant) {
            left_count++;
        }
        // Количество доминирующего элемента в левой и правой частях
        int left_subarray_count = left_count;
        int right_subarray_count = total_dominant_count - left_count;
        // Проверяем, удовлетворяют ли обе части условиям доминирования
        if (left_subarray_count > (i + 1) / 2 &&
                right_subarray_count > (nums.size() - i - 1) / 2) {
            return i; // Возвращаем индекс, если условия выполнены
        }
    }
    // Если ни один индекс не удовлетворяет условиям, возвращаем -1
    return -1;
}

std::vector<int> tasks::task_2503(std::vector<std::vector<int> > &grid, std::vector<int> &queries)
{
    // Получаем количество строк и столбцов в сетке (grid)
    int rows = grid.size(), cols = grid[0].size();
    // Вектор для хранения запросов в виде пар (значение запроса, индекс запроса)
    std::vector<std::pair<int, int>> sortedQueries;
    // Заполняем sortedQueries значениями из queries и их индексами
    for (int i = 0; i < queries.size(); i++) {
        sortedQueries.emplace_back(queries[i], i);
    }
    // Сортируем запросы по их значениям
    sort(sortedQueries.begin(), sortedQueries.end());
    // Вектор для хранения результатов для каждого запроса, инициализируем нулями
    std::vector<int> result(queries.size(), 0);
    // Минимальная куча для хранения пар (значение, позиция) с наименьшим значением вверху
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<>> minHeap;
    // Вектор для отслеживания посещенных ячеек в сетке
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    // Начинаем с верхнего левого угла сетки
    minHeap.emplace(grid[0][0], std::make_pair(0, 0));
    visited[0][0] = true; // Отмечаем верхний левый угол как посещенный
    int points = 0; // Счетчик для количества посещенных ячеек
    // Направления для перемещения по сетке (вправо, вниз, влево, вверх)
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    // Обрабатываем каждый запрос в порядке возрастания значений
    for (auto& [queryVal, queryIdx] : sortedQueries) {
        // Пока минимальная куча не пуста и наименьшее значение меньше текущего запроса
        while (!minHeap.empty() && minHeap.top().first < queryVal) {
            // Извлекаем наименьшее значение и его позицию
            auto [val, pos] = minHeap.top();
                    minHeap.pop(); // Удаляем элемент из кучи
                    int row = pos.first, col = pos.second; // Получаем координаты ячейки
                    points++; // Увеличиваем счетчик посещенных ячеек
                    // Проверяем все четыре направления (вправо, вниз, влево, вверх)
                    for (auto& [dr, dc] : directions) {
                int nr = row + dr, nc = col + dc; // Новые координаты
                // Проверяем, находятся ли новые координаты в пределах сетки и не посещены ли они
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc]) {
                    // Добавляем новую ячейку в минимальную кучу
                    minHeap.emplace(grid[nr][nc], std::make_pair(nr, nc));
                    visited[nr][nc] = true; // Отмечаем ячейку как посещенную
                }
            }
        }
        // Сохраняем количество посещенных ячеек для текущего запроса
        result[queryIdx] = points;
    }
    // Возвращаем вектор с результатами для всех запросов
    return result;
}

std::vector<int> tasks::task_763(std::string s)
{
    std::unordered_map<char, int> last_occurrence;
    for (int i = 0; i < s.size(); i++) {
        last_occurrence[s[i]] = i;
    }

    std::vector<int> result;
    int start = 0, end = 0;

    for (int i = 0; i < s.size(); i++) {
        end = std::max(end, last_occurrence[s[i]]);
        if (i == end) {
            result.push_back(end - start + 1);
            start = i + 1;
        }
    }

    return result;
}

long long tasks::task_2551(std::vector<int> &weights, int k)
{
    // Проверяем, равно ли значение k единице
    if (k == 1) {
        return 0;
    }
    // Создаем вектор для хранения сумм пар соседних элементов
    std::vector<int> pair_sums;
    // Проходим по вектору weights, чтобы вычислить суммы пар соседних элементов
    for (size_t i = 0; i < weights.size() - 1; ++i) {
        // Добавляем сумму текущего элемента и следующего в вектор pair_sums
        pair_sums.push_back(weights[i] + weights[i + 1]);
    }
    // Сортируем вектор pair_sums для упрощения поиска минимальных и максимальных значений
    sort(pair_sums.begin(), pair_sums.end());
    // Вычисляем минимальную сумму из первых (k - 1) элементов в отсортированном векторе
    long long min_score = accumulate(pair_sums.begin(), pair_sums.begin() + (k - 1), 0LL);
    // Вычисляем максимальную сумму из последних (k - 1) элементов в отсортированном векторе
    long long max_score = accumulate(pair_sums.end() - (k - 1), pair_sums.end(), 0LL);
    // Возвращаем разницу между максимальной и минимальной суммами
    return max_score - min_score;
}

