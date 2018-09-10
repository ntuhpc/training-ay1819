#include <unordered_set>
#include <iostream>

int main()
{
    std::unordered_set<std::string> myset {{"hello","stop-the-"}};

    for (auto wd: myset)
    {
        std::cout<<(wd+" world!")<<'\n';
    }

    return 0;
}

