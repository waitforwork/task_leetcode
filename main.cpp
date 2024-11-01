#include <iostream>
#include <tasks.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <cmath>

std::string makeFancyString(std::string s)
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

int main()
{
    std::string s="aaabc";
    std:: cout << makeFancyString(s) << std::endl;
    std::cout << "\nC++ is a general-purpose programming language with a bias towards systems programming that\n";
    std::cout << "  - is a better C\n  - supports data abstraction\n  - supports object-oriented programming\n  - supports generic programming.";
}

