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

int rangeSumQueryDumb(const std::vector<int>& array, int from, int to)
{
    int result = 0;
    for (int i = from; i <= to; i++)
    {
        result += array[i];
    }
    return result;
}

//Largest power of two that divides N
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
    //std::cout << "osize is " << osize << " while osizeR is " << osizeR << endl;
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

int calcSum(const std::vector<int>& segmentTree, int fromIndex, int toIndex)
{
    int n = segmentTree.size() / 2;
    //std::cout << "N is " << n << endl;
    int l = fromIndex + n;
    int r = toIndex + n;
    int s = 0;
    
    while (l <= r)
    {
        //Include values in the sum if they're outside the 'normal' range
        //Normal range means left is even and right is odd. Therefore we don't have to include the value into the sum and just go up one level
        //So when values are not normal - ie if left is odd and right is even - we include them manually into the sum
        //The other trick is that when a 'normal' range eventually collapses to having both indexes being equal, we will automatically include it into the sum:
        //Both indexes being equal means that at least one of them is even or odd when it 'shouldn't' be
        if (l % 2 == 1) s+=segmentTree[l++];
        if (r % 2 == 0) s+=segmentTree[r--];
        l /= 2;
        r /= 2;
    }
    return s; 
}

void addValueToSegmentTreeSum(std::vector<int>& segmentTree, int index, int value)
{
    int n = segmentTree.size() / 2;
    int ind = index + n;
    while (ind >= 1)
    {
        segmentTree[ind] += value;
        ind /= 2;
    }
}

std::vector<int> buildSegmentTreeMin(const std::vector<int>& array)
{
    int osize = array.size();
    int size = 1 << ((int)floor(log2(osize)) + (p2tdn(osize) == osize ? 0 : 1));

    //The tree initially stores maximum values
    std::vector<int> res(size * 2, std::numeric_limits<int>::max());

    //Fill the tree
    for (int i = 0; i < size; i++)
    {
        int si = i + size;
        while (si >= 1)
        {
            res[si] = i < size ? std::min(res[si], array[i]) : 0;
            si = si / 2;
        }
    }

    return res;
}

int queryRangeMinimumSegmentTree(const std::vector<int>& segmentTree, int from, int to)
{
    int size = segmentTree.size();
    int asize = size / 2;

    from += asize;
    to += asize;

    int ans = std::numeric_limits<int>::max();
    while (from <= to)
    {
        if (from % 2 == 1) ans = std::min(ans, segmentTree[from++]);
        if (to % 2 == 0) ans = std::min(ans, segmentTree[to--]);

        from /= 2;
        to /= 2;
    }

    return ans;
}

int main()
{
    //Segment tree Tree representation using a 1D array:
    //1 -> 2,3  2 -> 4,5  3 -> 6,7  4 -> 8,9  5 -> 10,11  6 -> 12,13  7 -> 14, 15 ...
    std::vector<int> array = {5, 8, 6, 3, 2, 7, 2, 6};
    //std::vector<int> array = {5, 8, 6};
    
    std::cout << "Sum " << calcSum(buildSegmentTreeSum(array), 1, 3) << endl;

    printSequence(buildSegmentTreeMin(array));
    
    int n = 2, k = 3, f = 7, z = 1;
    std::cout << "Division test " << endl << 
    "2 / 2 = " << n / 2 << endl <<
    "3 / 2 = " << k / 2 << endl <<
    "7 / 2 = " << f / 2 << endl <<
    "1 / 2 = " << z / 2 << endl;
    
    std::cout << "Modulo test " << endl << 
    "2 % 2 = " << n % 2 << endl <<
    "3 % 2 = " << k % 2 << endl <<
    "7 % 2 = " << f % 2 << endl <<
    "1 % 2 = " << z % 2 << endl;
    
    auto segmentTreeMin = buildSegmentTreeMin(array);
    printSequence(segmentTreeMin);

    std::cout << "Minimum global " << queryRangeMinimumSegmentTree(segmentTreeMin, 0, 7) << endl;
    std::cout << "Minimum 1-3 " << queryRangeMinimumSegmentTree(segmentTreeMin, 1, 3) << endl;
    std::cout << "Minimum 0-2 " << queryRangeMinimumSegmentTree(segmentTreeMin, 0, 2) << endl;
    
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

        auto segmentTree = buildSegmentTreeSum(items);

        //Make a bunch of queries        
	    for (int mq = 0; mq < 100; mq++)
        {
            //Generate random from - to
            int rFrom = indexDistr(gen);
            int rTo = indexDistr(gen);
            if (rTo < rFrom) std::swap(rFrom, rTo);
            int sumTrue = rangeSumQueryDumb(items, rFrom, rTo);
            int sumTest = calcSum(segmentTree, rFrom, rTo);
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
