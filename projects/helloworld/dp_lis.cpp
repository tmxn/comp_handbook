#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
#include <set>
#include <random>

using namespace std;

//Given a sequence of numbers, calculate Longest Increasing Subsequence
int lis(const std::vector<int>& sequence)
{
    //Since we're using dynamic programming, calculate answers iteratively by moving left-right
    std::vector<int> lengths(sequence.size(), 1);

    int maxlen = 0;

    for (int i = 1; i < (int)lengths.size(); i++)
    {
        //Go through the previous elements
        //If there is an element that is smaller than curent (subsequence is increasing)
        //we can use that element as part of current increasing subsequence
        //as long as it will increase the length of our subsequence
        for (int k = 0; k < i; k++)
        {
            if (sequence[k] < sequence[i])
            {
                lengths[i] = std::max(lengths[i], lengths[k] + 1);
                //Update maximum length
                if (maxlen < lengths[i])
                    maxlen = lengths[i];
            }
        }
    }

    return maxlen;
}

//Given a sequence of numbers, calculate Longest Increasing Subsequence
int lis_nlogn(const std::vector<int>& sequence, bool debug)
{
    //Since we're using dynamic programming, calculate answers iteratively by moving left-right
    //We need to find previous length that is largest but the linked value is smaller than x
    std::vector<int> lengths(sequence.size(), 1);

    struct Entry
    {
        int length;
        int usedBy;
    };

    struct Cmp {
        bool operator()(const int& lhs, const int& rhs) const { return lhs > rhs; }
    };
    
    std::map<int, Entry, Cmp> entries;

    entries.insert(std::make_pair(sequence[0], Entry {1, -1}));

    int maxlen = 0;

    for (int i = 1; i < (int)lengths.size(); i++)
    {
        if (debug)
        {
            std::cout << "{";
            for (auto & it : entries)
            {
                std::cout << it.first << "-" << it.second.length << " ";
            }
            std::cout << "}";
        }
        
        //Go through the previous elements
        //If there is an element that is smaller than curent (subsequence is increasing)
        //we can use that element as part of current increasing subsequence
        //as long as it will increase the length of our subsequence
        Entry newEntry({1, -1});
        
        auto iter = entries.upper_bound(sequence[i]);

        if (iter != entries.end())
        {
            //Found item. Update length
            newEntry.length = iter->second.length + 1;
            //Also see if we can remove the entry that uses to our upper bound
            //The new item is now used by us
            bool shouldUpdate = true;
            if (iter->second.usedBy != -1)
            {
                auto previousUserIter = entries.find(iter->second.usedBy);
                //Found previous user
                if (previousUserIter != entries.end())
                {
                    if (previousUserIter->second.length <= newEntry.length)
                        entries.erase(previousUserIter->first);
                    else
                        shouldUpdate = false; //probably shouldn't happen ever?
                }
            }
            //Update the upper bound's usedBy if we should
            if (shouldUpdate) iter->second.usedBy = sequence[i];

        } else
        {
            newEntry.length = 1;
            if (entries.rbegin()->second.length <= newEntry.length &&
                entries.rbegin()->first > sequence[i])
                entries.erase(std::prev(entries.end()));
        }

        maxlen = std::max(maxlen, newEntry.length);
        entries.insert(std::make_pair(sequence[i], newEntry));

        auto found = entries.find(sequence[i]);
        auto prev = std::prev(found);

        if (prev->first > sequence[i] && prev->second.length <= newEntry.length)
            entries.erase(prev);
    }

    if (debug)
    {
        std::cout << "{";
        for (auto & it : entries)
        {
            std::cout << it.first << "-" << it.second.length << " ";
        }
        std::cout << "}";
    }

    return maxlen;
}

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

int lis_nlogn2(const std::vector<int>& sequence, bool debug)
{
    //Since we're using dynamic programming, calculate answers iteratively by moving left-right
    //We need to find previous length that is largest but the linked value is smaller than x
    std::vector<int> lengths(sequence.size(), 1);

    struct Cmp {
        bool operator()(const int& lhs, const int& rhs) const { return lhs > rhs; }
    };
    
    std::map<int, int, Cmp> entries;

    entries.insert(std::make_pair(sequence[0], 1));

    int maxlen = 0;

    for (int i = 1; i < (int)lengths.size(); i++)
    {
        dbgprint(debug, entries);
        //The solution is an optimization of the DP solution, based on two observations:
        //1. We can use binary search since we really only want the largest previous number (sounds like upper_bound, right?)
        //2. We can remove numbers that are larger than the one we are going to insert if they don't have larger length. This also makes binary search approach valid
        int newLength = 1;
        
        //Do an upper bound. Since we're using DESC sorting, this will return the highest number that is lower [than current] from all the previous numbers
        auto iter = entries.upper_bound(sequence[i]);

        //Found such a number. [Dynamic programming] We can use its length to calculate our own lengh
        if (iter != entries.end()) newLength = iter->second + 1;

        //If we found a number to base our length on - iter points to it
        //if not - iter points to end. Either way, get the previous number
        auto prev = std::prev(iter);

        //See if we can remove the previous number [last or previous] - we can do it if it's larger but has same or worse length
        //The trick is that there is no point in having the bigger number in the list if a better smaller number exists
        //we can start a better subsequence from the smaller number
        if (prev->first > sequence[i] && prev->second <= newLength)
            entries.erase(prev);

        maxlen = std::max(maxlen, newLength);
        entries.insert(std::make_pair(sequence[i], newLength));
    }

    dbgprint(debug, entries);

    return maxlen;
}

void printSequence(const std::vector<int>& sequence)
{
    std::cout << "{";
    for (auto & it : sequence)
    {
        std::cout << it << " ";
    }
    std::cout << "} ";
}

int main(){
    //std::vector<int> sequence = {6,2,5,3,4,1,7,8};
    //std::vector<int> sequence = {13, 11, 5, 9, 18, 15, 3, 12, 6, 14 }; 
    std::vector<int> sequence;
    //std::cout << "Sequence " << lis_nlogn({9, 18, 20, 1, 16, 15, 6, 5, 11, 17}) << endl;
    std::cout << "Sequence " << lis_nlogn2({6, 2, 5, 1, 3, 4, 7}, true) << endl;

    //return 0;
    sequence.resize(100);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 200); // define the range

    int sameResults = 0;

    for (int i = 0; i < 100; i++)
    {
        //Randomize the list
        std::set<int> deduplicator;
        for (int k = 0; k < sequence.size(); k++)
        {
            bool inserted = false;
            do
            {
                int newnum = distr(gen);
                if (deduplicator.find(newnum) == deduplicator.end())
                {
                    sequence[k] = newnum;
                    deduplicator.insert(newnum);
                    inserted = true;
                }
            } while(!inserted);
            
        }
            

        int ans1 = lis(sequence);

        int ans2 = lis_nlogn2(sequence, false);

        if (ans1 != ans2)
        {
            std::cout << "Answers differ! " << ans1 << " " << ans2 << endl;
            printSequence(sequence);
        } else
        {
            sameResults++;
        }
            
    }

    std::cout << "Passed " << sameResults << " Tests" << endl;

}