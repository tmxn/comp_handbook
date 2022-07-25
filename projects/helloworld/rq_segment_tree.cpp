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

int rangeSumQueryDumb(const std::vector<int>& array, int from, int to)
{
    int result = 0;
    for (int i = from; i <= to; i++)
    {
        result += array[i];
    }
    return result;
}

int largestPowerOfTwoThatDividesN(int n)
{
    return n & (~(n - 1)); 
}

int main()
{
    //Segment tree Tree representation using a 1D array:
    //1 -> 2,3  2 -> 4,5  3 -> 6,7  4 -> 8,9  5 -> 10,11  6 -> 12,13  7 -> 14, 15 ...
    std::vector<int> array = {5, 8, 6, 3, 2, 7, 2, 6};
    //~~~Randomized test~~~
    std::cout << "Perform a randomized full test ? (y/n)\n";

    char yn = 'n';

    std::cin >> yn;

    if (yn != 'y') return 0;

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 200); // define the range
    std::uniform_int_distribution<> indexDistr(0, 99); // define the range

    std::vector<int> items(100, 0);

    int successes = 0;
    for (int c = 0; c < 100; c++)
    {
        //Generate a random list
        for (auto & it : items)
            it = distr(gen);

        //Make a bunch of queries        for (int mq = 0; mq < 100; mq++)
        {
            //Generate random from - to
            int rFrom = indexDistr(gen);
            int rTo = indexDistr(gen);
            if (rTo < rFrom) std::swap(rFrom, rTo);
            int sumTrue = 0;//rangeSumQueryDumb(items, rFrom, rTo);
            int sumTest = 0;//rangeSumQuerySmart(fenwickTree, rFrom, rTo);
            if (sumTrue != sumTest)
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
