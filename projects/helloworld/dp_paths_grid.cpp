#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
#include <set>

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

int sum_recursive(std::vector<std::vector<int>>& paths, int x, int y)
{
    if (x==0 && y ==0) {
        return paths[0][0];
    } else {
        int sum1 = x - 1 >= 0 ? sum_recursive(paths, x - 1, y) : 0;
        int sum2 = y - 1 >= 0 ? sum_recursive(paths, x, y - 1) : 0;
        return std::max(sum1, sum2) + paths[x][y];
    }
}

int sum_NxN(std::vector<std::vector<int>>& paths, int x, int y)
{
    std::vector<std::vector<int>> sum;
    for (int i = 0; i < (int)paths.size(); i++)
    {
        std::vector<int> temp((int)paths[0].size(), 0);
        sum.push_back(std::move(temp));
    }

    for (int i = 0; i < (int)paths.size(); i++)
    {
        for (int k = 0; k < (int)paths[0].size(); k++)
        {
            if (i == 0 && k == 0) {
                sum[0][0] = paths[0][0];
            } else {
                int sum1 = i > 0 ? sum[i - 1][k] : 0;
                int sum2 = k > 0 ? sum[i][k - 1] : 0;
                sum[i][k] = std::max(sum1, sum2) + paths[i][k];
            }
        }
    }
    return sum.back().back();
}

int main(){
    std::vector<std::vector<int>> paths = {
        {3,7,9,2,7},
        {9,8,3,5,5},
        {1,7,9,8,5},
        {3,8,6,4,10},
        {6,3,9,7,8}
    };

    std::cout << "Recursive sum is " << sum_recursive(paths, 4, 4) << endl;
    std::cout << "Iterative sum is " << sum_NxN(paths, 4, 4) << endl;
}