#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
#include <set>

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

void myKindaSlowImplementation(const std::vector<int>& items)
{
    int sum = 0;
    std::vector<std::pair<std::vector<bool>, bool>> usedItems;
    //Initialize the used items array
    for (auto & it : items)
        sum += it;

    for (int x = 0; x <= sum; x++)
    {
        std::vector<bool> localUsed(items.size(), false);   
        usedItems.push_back(std::make_pair(std::move(localUsed), false));
    }

    //Sum zero is always Possible
    usedItems[0].second = true;
    
    //For each number from 0 to sum
    for (int x = 1; x <= sum; x++)
    {
        for (int k = 0; k < (int)items.size(); k++)
        {
            int item = items[k];
            //Using knapsack item at index k we get to Possible and item[k] is free to use
            if ( x - item >= 0 && usedItems[x - item].second && usedItems[x - item].first[k] == false )
            {
                usedItems[x].first = usedItems[x - item].first; //copy used items of the subsum. This is slow and unnecessary, but saved by the fact that std::vector<bool> is a bitset
                usedItems[x].first[k] = true; //to construct current sum we used item[k], so mark it used
                usedItems[x].second = true; //this sum is also Possible now
                break; //no further lookup for this sum
            }
        }
    }

    int index = 0;
    for (auto & it : usedItems)
    {
        if (it.second)
        {
            std::cout << "Sum " << index << " is possible! Items:" << endl;
            for (int itemIndex = 0; itemIndex < items.size(); itemIndex++)
            {
                if (it.first[itemIndex])
                    std::cout << items[itemIndex] << "+";
                else
                std::cout << items[itemIndex] << "-";
            }
            
            std::cout << endl;
        }
        index++;
    }

/*
    x=1:
        1-1=0. Success. 1+3-3-5-
    x=2:
        2-1=1. But 1 uses 1. 2-3=-1. Nope. 2-3=-1. Nope. 2-5=-3. Nope
    x=3:
        3-1=2. Nope. 3-3=0. Success. 1-3+3-5-;
    x=4:
        4-1=3. Success. 1+3+3-5-;
    x=5:
        5-1=4. But 4 uses 1. 5-3=2. Nope. 5-3=2. Nope. 5-5=0. Success. 1-3-3-5+
    x=6:
        6-1=5. Success. 1+3-3-5+;
    x=7:
        7-1=6. But 6 uses 1. 7-3=4. Success. 1+3+3+5-;
    x=8:
        8-1=7, but 7 uses 1. 8-3=5. Success. 1-3+3-5+
    x=9:
        9-1=8. Success. 1+3+3-5+
    x=10:
        10-1=9. But 9 uses 1. 10-3=7. But 7 uses 3s. 10-3=7. But 7 uses both 3s. 10-5=5. But 5 uses 5. None
    x=11:
        11-1=10. Nope. 11-3=8. Success. 1-3+3+5+
    x=12:
        12-1=11. Success. 1+3+3+5+
    ..
*/
}

int textbook(const std::vector<int>& items)
{
    int sum = 0;
    std::vector<std::vector<bool>> possible;
    //Initialize the used items array
    for (auto & it : items)
        sum += it;

    for (int x = 0; x <= sum; x++)
    {
        std::vector<bool> localUsed(items.size() + 1, false);   
        possible.push_back(std::move(localUsed));
    }

    //Sum zero is always Possible
    possible[0][0] = true;
    
    for (int k = 1; k <= items.size(); k++) {
        for (int x = 0; x <= sum; x++) {
            if (x-items[k-1] >= 0) possible[x][k] = possible[x-items[k-1]][k-1] || possible[x][k];
            possible[x][k] = possible[x][k-1] || possible[x][k];
        }
    }

    sum = 0;
    for (auto & it : possible)
    {
        if (it.back())
            std::cout << "Sum " << sum << " is possible! " << endl;
        sum++;
    }
        
    return 0;
}

//This is the most elegant way of solving this particular knapsack problem
void textbook_fast(const std::vector<int>& items)
{
    int sum = 0;
    for (auto & it : items)
        sum += it;

    std::vector<bool> used(sum, false);
    used[0] = true;

    for (int k = 0; k < items.size(); k++)
    {
        for (int x = sum; x >= 0; x--)
        {
            if (used[x]) used[x + items[k]] = true;
        }
    }

    int ind = 0;
    for (const auto & it : used)
    {
        if (it) std::cout << "Item " << ind << " is possible!" << endl;
        ind++;
    }
        
}

int main()
{
    std::vector<int> items = {1, 3, 3, 5};
    myKindaSlowImplementation(items);
    //textbook(items);
    textbook_fast(items);
}