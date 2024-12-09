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
        int left = q, right = q;
        int specialCount = prefix[right] - (left > 0 ? prefix[left] : 0);
        ans.push_back(specialCount == 0);
    }
    return ans;
}

