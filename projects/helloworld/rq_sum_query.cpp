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

std::vector<int> buildPreixSumArray(const std::vector<int>& array)
{
    std::vector<int> res;

    for (auto & it : array)
        res.push_back(it + (res.empty() ? 0 : res.back()));
    
    return res;
}

int calcSumStatic(const std::vector<int>& array, int fromInd, int toInd)
{
    int prefixSumFrom = fromInd > 0 ? array[fromInd - 1] : 0;
    int prefixSumTo = array[toInd];
    return prefixSumTo - prefixSumFrom;
}

int main()
{
    std::vector<int> items = {1, 3, 4, 8, 6, 1, 4, 2};
    auto prefixArr = buildPreixSumArray(items);
    std::cout << "Sum 3, 6 is " << calcSumStatic(prefixArr, 3, 6) << endl;
}