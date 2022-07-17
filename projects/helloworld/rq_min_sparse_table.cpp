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
    //std::cout << "Size is " << array.size() << " Steps are " << maxpower << endl;

    for (int power = 0; power <= maxpower; power++)
    {
        res.push_back(std::vector<int>());
        int step = 1 << power;
        //std::cout << "Step " << step << endl;
        int leftInd = 0;
        int rightInd = leftInd + step - 1;
        while (rightInd < size)
        {
            //std::cout << "Considering pair " << leftInd << " " << rightInd << endl;
            int minimum = 0;
            //
            if (res.size() == 1)
                minimum = array[leftInd];
            else
            {
                //
                int hafu = leftInd + step / 2;
                //dynamic programming. Use previous result to calculate next result efficiently
                //The idea is that a minimum in range of length 4 is minimum of two ranges of lengths 2
                //If indexes for range length 4 are (0..3) then we have to consider previous ranges
                //with indexes (0..1) and (2..3). These minimums will be stored in our previous res row
                //with indexes 0 and 2. At index 1 will be stored the minimum of range (1..2), which we don't need
                //Note that 2 happens to be 4 (our current range length) divided by 2
                minimum = std::min(res[res.size() - 2][leftInd], res[res.size() - 2][hafu]);
            }
            res.back().push_back(minimum);
            leftInd++;
            rightInd++;
        }
    }

    return res;
}

int rangeMinimumQuerySmart(const std::vector<std::vector<int>>& sparseTable, int from, int to)
{
    //Handle special case when log2 function fails
    if (from == to)
        return sparseTable[0][from];
    //builtin_clz is unreliable here (bit shifting could be useful here - to find the most significant bit)
    //Instead just use good ol' log2 to find the most significant bit
    int p = (int)floor(log2(to - from));
    
    return std::min(sparseTable[p][from], sparseTable[p][to - (1 << p) + 1]);
}

int main()
{
    std::vector<int> items = {1, 3, 4, 8, 6, 1, 4, 2};
    {
        auto sparseTable = buildSparseTable(items);
        for (auto & it : sparseTable)
        {
            printSequence(it);
        }
        std::cout << endl;

        int ms = rangeMinimumQuerySmart(sparseTable, 1, 5);
        int md = rangeMinimumQueryDumb(items, 1, 5);
        
        std::cout << "MS is " << ms << " md is " << md << endl;
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

    int successes = 0;
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
            } else
            {
                successes++;
            }
        }
    }
    std::cout << "Testing finished with " << successes << " successes!\n";
}