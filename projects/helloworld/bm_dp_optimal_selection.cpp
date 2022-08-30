#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <random>

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
        std::cout << "}\n";
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
    std::cout << "}\n";
}

int optimal(const std::vector<std::vector<int>>& prices)
{
    return 0;   
}

int main()
{
    //columns are days, rows are products, cells are price values
    std::vector<std::vector<int>> prices = {
        {6, 9, 5, 2, 8, 9, 1, 6},
        {8, 2, 6, 2, 7, 5, 7, 2},
        {5, 3, 9, 7, 3, 5, 1, 4}
    };
    
    auto sortedPrices = prices;
    for (auto & it : sortedPrices)
        std::sort(it.begin(), it.end());
       
    for (auto & it : sortedPrices)
        printSequence(it);

    return 0;
}
