#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
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

int editDistance(std::string s1, std::string s2)
{
    int MAX_VAL = 1000000;
    std::vector<std::vector<int>> v;
    //make sure s1 is longer
    if (s1.length() < s2.length()) std::swap(s1, s2);
    //Prepare DP array
    for (int i = 0; i < s1.length(); i++)
    {
        v.push_back(std::vector<int>());
        for (int k = 0; k < s2.length(); k++)
        {
            v.back().push_back(0);
        }
    }
    //Fill dp array
    for (int i = 0; i < s1.length(); i++)
    {
        for (int k = 0; k < s2.length(); k++)
        {
            int leftScore = i > 0 ? v[i - 1][k] : MAX_VAL;
            int topScore = k > 0 ? v[i][k - 1] : MAX_VAL;
            int ltScore = (i > 0 && k > 0) ? v[i - 1][k - 1] : MAX_VAL;
            int chosenScore = std::min(leftScore, std::min(topScore, ltScore));
            if (i == 0 && k == 0) chosenScore = 0;
            
            int toAdd = s1[i] == s2[k] ? 0 : 1;
            v[i][k] = chosenScore + toAdd;
        }
    }

    return v.back().back();
}

int main()
{
    std::string w1, w2;
    w1 = "abcdefg";
    w2 = "cdefg";
    std::cout << "Edit distance between words " << w1 << " and " << w2 << " is " << editDistance(w1, w2) << endl;
    w1 = "LOVE";
    w2 = "MOVIE";
    std::cout << "Edit distance between words " << w1 << " and " << w2 << " is " << editDistance(w1, w2) << endl;
    w1 = "AAA";
    w2 = "AAA";
    std::cout << "Edit distance between words " << w1 << " and " << w2 << " is " << editDistance(w1, w2) << endl;
    w1 = "BANGGOD";
    w2 = "JAMEOD";
    std::cout << "Edit distance between words " << w1 << " and " << w2 << " is " << editDistance(w1, w2) << endl;
    w1 = "hippo";
    w2 = "elephant";
    std::cout << "Edit distance between words " << w1 << " and " << w2 << " is " << editDistance(w1, w2) << endl;
}