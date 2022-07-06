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

int main()
{
    std::vector<int> array = {1, 3, 4, 2, 5, 3, 4, 2};

    std::vector<int> stack;

    int pops = 0;

    //Go through each element in the stack
    for (int i = 0; i < (int)array.size(); i++)
    {
        while (stack.size() && stack.back() >= array[i])
        {
            stack.pop_back();
            pops++;
        }
        
        if (stack.size())
            std::cout << "Nearest to " << array[i] << " is " << stack.back() << "\n";
        stack.push_back(array[i]);
    }

    std::cout << "Pops " << pops << endl;

}