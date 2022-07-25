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

int p2tdn(int v)
{
    return v & (~(v - 1));
}

//Given an array of size N, builds a segment tree of size 2N, where first N elements are the tree
//Note that the output array will be padded with zeroes if the input array length is not a power of two
//The array will always have a power of two length. Data items start at index = length/2;
std::vector<int> buildSegmentTreeSum(const std::vector<int>& array)
{
    int osize = array.size();
    int osizeR = 1 << (int)(floor(log2(osize)) + (p2tdn(osize) == osize ? 0 : 1));
    std::cout << "osize is " << osize << " while osizeR is " << osizeR << endl;
    std::vector<int> res(osizeR * 2, 0);
    for (int i = 0; i < osizeR; i++)
    {
        int si = (i + osizeR);
        while (si >= 1)
        {
            //add value to the current tree index (start from the leafs)
            res[si] += i < array.size() ? array[i] : 0;
            //go up the treee
            si = si / 2;
        }
    }
    return res;
}

int main()
{
    //Segment tree Tree representation using a 1D array:
    //1 -> 2,3  2 -> 4,5  3 -> 6,7  4 -> 8,9  5 -> 10,11  6 -> 12,13  7 -> 14, 15 ...
    std::vector<int> array = {5, 8, 6, 3, 2, 7, 2, 6};
    //std::vector<int> array = {5, 8, 6};
    
    printSequence(buildSegmentTreeSum(array));
    
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
