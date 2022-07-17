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

int rangeMinimumQueryDumb(const std::vector<int>& array, int from, int to)
{
    int minimum = std::numeric_limits<int>::max();
    for (int i = from; i <= to; i++)
    {
        if (minimum > array[i])
            minimum = array[i];
    }
    return minimum;
}

std::vector<std::vector<int>> buildSparseTable(const std::vector<int>& array)
{
    //c1 1 3 4 8 6 1 4 2
    //c2 1 3 4 6 1 1 2
    //c4 1 3 1 1 1
    //c8 1
    std::vector<std::vector<int>> res;

    int size = (int)array.size();

    //find out how many steps we need
    int maxpower = floor(log2(array.size()));
    std::cout << "Size is " << array.size() << " Steps are " << maxpower << endl;

    for (int power = 0; power <= maxpower; power++)
    {
        res.push_back(std::vector<int>());
        int step = 1 << power;
        std::cout << "Step " << step << endl;
        int leftInd = 0;
        int rightInd = leftInd + step - 1;
        while (rightInd < size)
        {
            std::cout << "Considering pair " << leftInd << " " << rightInd << endl;
            leftInd++;
            rightInd++;
        }
    }

    return res;
}

int rangeMinimumQuerySmart(const std::vector<std::vector<int>>& sparseTable, int from, int to)
{
    return 0;
}

int main()
{
    std::vector<int> items = {1, 3, 4, 8, 6, 1, 4, 2};
    auto sparseTable = buildSparseTable(items);
    for (auto & it : sparseTable)
    {
        printSequence(it);
    }

    std::cout << "Perform a randomized full test ? (y/n)\n";

    char yn = 'n';

    std::cin >> yn;

    if (yn != 'y') return 0;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 200); // define the range
    std::uniform_int_distribution<> indexDistr(0, 99); // define the range

    items.resize(100);
    for (int c = 0; c < 100; c++)
    {
        //Generate a random list
        for (auto & it : items)
            it = distr(gen);

        //Build sparse table
        std::vector<std::vector<int>> sparseTable = buildSparseTable(items);

        //Make a bunch of queries
        for (int mq = 0; mq < 100; mq++)
        {
            //Generate random from - to
            int rFrom = indexDistr(gen);
            int rTo = indexDistr(gen);
            if (rTo < rFrom) std::swap(rFrom, rTo);
            int minTrue = rangeMinimumQueryDumb(items, rFrom, rTo);
            int minTest = rangeMinimumQuerySmart(sparseTable, rFrom, rTo);
            if (minTrue != minTest)
            {
                std::cout << "Failed test ";
                printSequence(items);
                std::cout << " from " << rFrom << " to " << rTo << endl;
            }
        }
    }
}