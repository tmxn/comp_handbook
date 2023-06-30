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

//Shoulda just called this a floating window approach
std::string SUM(const std::vector<int>& array, int targetSum)
{
    std::string res = "";
    int pointer1 = 0, pointer2 = 0;
    int len = (int)array.size();

    int sum = 0;
    //Each turn, pointer1 moves to the right
    for (pointer1 = 0; pointer1 < len; pointer1++)
    {
        while (true)
        {
            if (pointer2 >= pointer1)
            {
                if (sum + array[pointer2] > targetSum)
                    break;
                sum += array[pointer2];
                if (sum == targetSum)
                    return "From " + std::to_string(pointer1) + " to " + std::to_string(pointer2);
            }
            pointer2++;
        }
        sum -= array[pointer1];
    }

    return "null";
}

std::string two_sum(const std::vector<int>& array, int value)
{
    //Copy and Sort the array
    std::vector<int> sorted = array;
    std::sort(sorted.begin(), sorted.end());
    //Now use the two pointer method to find the needed sum
    //The trick is that the sorted array has largest two values at the end
    //The smallest two values at the beginning
    //And some needed sum value that is inbetween
    int si = 0;
    int ei = (int)sorted.size() - 1;
    while (true)
    {
        int sum_test = sorted[si] + sorted[ei];
        if (sum_test < value)
            si++;
        else if (sum_test > value)
            ei--;
        else if (sum_test == value) {
            return "Values are " + std::to_string(sorted[si]) + " and " + std::to_string(sorted[ei]);
        }
    }
    return "null";
}

//Basically solving 2SUM N times
std::string three_sum(const std::vector<int>& array, int value)
{
    std::vector<int> sorted = array;
    std::sort(sorted.begin(), sorted.end());
    int last_ind = ((int)sorted.size() - 1);

    for (int i = 0; i < sorted.size(); i++)
    {
        int target_sum = value - sorted[i];
        int si = 0;
        int ei = last_ind;
        if (si == i) si++;
        if (ei == i) ei--;
        while (true)
        {
            int sum_test = sorted[si] + sorted[ei];
            if (sum_test < target_sum)
            {
                si++;
                if (si == i) si++;
            }
            else if (sum_test > target_sum)
            {
                ei--;
                if (ei == i) ei--;
            }
            else if (sum_test == target_sum) {
                return "Values are " + std::to_string(sorted[si]) + " and " + std::to_string(sorted[ei]) + " and " + std::to_string(sorted[i]);
            }
            if (si > last_ind || ei < 0 || si == ei) break;
        }
    }
    return "null";
}

int main()
{
    std::vector<int> array = {1, 3, 2, 5, 1, 1, 2, 3};

    std::cout << SUM(array, 9) << endl;

    std::vector<int> array_2 = {4, 1, 7, 9, 5, 10, 6, 9};

    std::cout << two_sum(array_2, 12) << endl;

    std::cout << three_sum(array_2, 24) << endl;

    return 0;
}