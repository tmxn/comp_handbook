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

//updates the tree, modifies logN values in total
void fenwickTreeAdd(std::vector<int>& fenwickTree, int index, int value)
{
    while (index <= fenwickTree.size())
    {
        //Update the initial index always
        fenwickTree[index] += value;
        //Now go to other affected indexes
        index += largestPowerOfTwoThatDividesN(index); //1->2->4->8; odd -> even, even goes to nearest power of two (eventually)
    }
}

//Builds a fenwick tree from a given array of values
std::vector<int> buildFenwickTree(const std::vector<int>& array)
{
    //Prepare the storage for the tree. Tree is indexed from 1, so has size larger than the input array by 1
    std::vector<int> res(array.size() + 1, 0);
    
    //Tree[k] = rangeSum(k-p(k) + 1, k)
    //Each element in the tree-array stores a sum from index k-p(k)+1 up to k
    //Numbers that are powers of two store the longest ranges. Odd numbers store just 1 sum

    //Will build the full tree in NlogN time
    for (int i = 0; i < array.size(); i++)
    {
        fenwickTreeAdd(res, i + 1, array[i]);
    }
    
    return res;
}

//gets a range sum in the fenwick tree from index 1 to the specified in logN time
int fenwickTreeGet(const std::vector<int>& fenwickTree, int to)
{
    int res = 0;
    while (to > 0)
    {
        res += fenwickTree[to];
        to -= largestPowerOfTwoThatDividesN(to);
    }
    return res;
}

int rangeSumQuerySmart(const std::vector<int>& fenwickTree, int from, int to)
{
    return fenwickTreeGet(fenwickTree, to + 1) - fenwickTreeGet(fenwickTree, from);
}

int main()
{
    //~~~Driver code~~~
    std::cout << "largest power of two that divides 48 is " << largestPowerOfTwoThatDividesN(48) << endl;
    std::cout << "largest power of two that divides 6 is " << largestPowerOfTwoThatDividesN(6) << endl;
    std::cout << "largest power of two that divides 10 is " << largestPowerOfTwoThatDividesN(10) << endl;
    std::vector<int> items = {1, 3, 4, 8, 6, 1, 4, 2};

    printSequence(buildFenwickTree(items));
    
    std::cout << "Sum from 1 to 4 is " << rangeSumQuerySmart(buildFenwickTree(items), 1, 4) << " and dum sum is " << rangeSumQueryDumb(items, 1, 4) << endl;


    //~~~Randomized test~~~
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

        auto fenwickTree = buildFenwickTree(items);

        //Make a bunch of queries
        for (int mq = 0; mq < 100; mq++)
        {
            //Generate random from - to
            int rFrom = indexDistr(gen);
            int rTo = indexDistr(gen);
            if (rTo < rFrom) std::swap(rFrom, rTo);
            int sumTrue = rangeSumQueryDumb(items, rFrom, rTo);
            int sumTest = rangeSumQuerySmart(fenwickTree, rFrom, rTo);
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
