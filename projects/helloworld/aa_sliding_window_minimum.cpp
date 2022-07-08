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
    std::vector<int> array = {2, 1, 4, 5, 3, 4, 1, 2};

    std::queue<std::pair<int, int>> queue;

    const int SLIDING_WINDOW_SIZE = 4;
    
    int window_r = SLIDING_WINDOW_SIZE - 1;
    int window_l = window_r - (SLIDING_WINDOW_SIZE - 1);

    std::cout << "WR " << window_r << " WL " << window_l << endl;


    //Pre-fill the queue first, using the core idea of the sliding window minimum algorithm
    for (int i = 0; i < SLIDING_WINDOW_SIZE; i++)
    {
        while (queue.size() && queue.front().first > array[i])
            queue.pop();
        
        queue.push(std::make_pair(array[i], i));
    }

    std::cout << "Container " << queue.size() << endl;

    //Now the main part of the algo
    while (window_r < (int)array.size())
    {
        window_l = window_r - (SLIDING_WINDOW_SIZE - 1);
        std::cout << "L IS " << array[window_l] << endl;
        //since the window moved one to the right, remove first element
        if (queue.front().second < window_l)
            queue.pop();

        //now remove all elements from the left side that are larger than the new element
        while (queue.size() && queue.front().first >= array[window_r])
            queue.pop();
        
        std::cout << "R IS " << array[window_r] << endl;
        queue.push(std::make_pair(array[window_r], window_r));

        std::cout << "Smallest element is " << queue.front().first << endl;
        window_r++;
    }
}