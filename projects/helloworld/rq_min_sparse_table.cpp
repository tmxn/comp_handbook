#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <queue>

using namespace std;

template<typename T>
void dbgprint(bool debug, const T& entries)
{
    if (debug)
    {
        std::cout << "{";
        for (auto & it : entries)
        {
            std::cout << it.first << "-" << it.second << " ";
        }
        std::cout << "}";
    }
}

template<typename T>
void printSequence(const T& sequence)
{
    std::cout << "{";
    for (auto & it : sequence)
    {   
        std::cout << it << " ";
    }
    std::cout << "} ";
}

std::vector<std::vector<int>> buildSparseTable(const std::vector<int>& array)
{
    //bc 1 3 4 8 6 1 4 2
    //l1 1 3 4 6 1 1 2
    //l2 1 3 4 1 1 1
    //l4 1 3 1 1 1
    //l8 1 
    std::vector<std::vector<int>> res;

    int size = (int)array.size();
    //first item is just the array itself
    res.push_back(array);

    //to build other items, find out how many steps we need
    int maxpower = floor(log2(array.size()));
    std::cout << "Size is " << array.size() << " Steps are " << maxpower << endl;

    for (int power = 0; power <= maxpower; power++)
    {
        int step = 1 << power;
        std::cout << "Step " << step << endl;
        std::cout << "Previous minimum is ";
        printSequence(res.back());
        std::cout << endl;
    }

    return res;
}

int main()
{
    std::vector<int> items = {1, 3, 4, 8, 6, 1, 4, 2};
    auto sparseTable = buildSparseTable(items);
    for (auto & it : sparseTable)
    {
        printSequence(it);
    }
}