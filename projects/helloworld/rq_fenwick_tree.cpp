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

int largestPowerOfTwoThatDividesN(int n)
{
    return n & (~(n - 1)); 
}

int rangeMinimumQuerySmart(const std::vector<int>& array, int from, int to)
{
    return 0;
}

int main()
{
    std::cout << "largest power of two that divides 48 is " << largestPowerOfTwoThatDividesN(48) << endl;
    std::vector<int> items = {1, 3, 4, 8, 6, 1, 4, 2};
    

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

        //Make a bunch of queries
        for (int mq = 0; mq < 100; mq++)
        {
            //Generate random from - to
            int rFrom = indexDistr(gen);
            int rTo = indexDistr(gen);
            if (rTo < rFrom) std::swap(rFrom, rTo);
            int minTrue = rangeMinimumQueryDumb(items, rFrom, rTo);
            int minTest = rangeMinimumQuerySmart(items, rFrom, rTo);
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
