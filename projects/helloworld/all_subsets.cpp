#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

//Generating Subsets

//Elegant recursive approach
void allsubsets(std::vector<int>& currentSubset, int k, int n)
{
    if (k == n)
    {
        //Processing
        std::cout << "{";
        for (auto & it : currentSubset)
            std::cout << it << " ";
        std::cout << "}";
    } else
    {
        allsubsets(currentSubset, k + 1, n);
        currentSubset.push_back(k);
        allsubsets(currentSubset, k + 1, n);
        currentSubset.pop_back();
    }
}

//Bit-based approach
void allsubsets2(int n)
{
    //There are 2^n total subsets of numbers 0..n
    //Since bit-shifting produces powers of two, we use this hack to establish the iteration count of our for loop
    for (int i = 0; i < (1<<n); i++)
    {
        std::cout << "subset #" << i << endl;
        std::vector<int> subset;
        //To actually find which numbers are currently included in this particular subset, go through each bit -
        //and there are n bits - for example, for n = 3, i will go up to 7, which is 111 (3 bits) -
        //and include the number if a bit at its position in the current "subset" (the number) is 1
        for (int k = 0; k < n; k++)
            if ((1<<k)&i) subset.push_back(k);

        std::cout << "{";
        for (auto & it : subset)
            std::cout << it << " ";
        std::cout << "}";
    }
}

//Generating permutations


int n = 3;
std::vector<int> permutation;
int chosen[3];

void search() {
    if (permutation.size() == n) {
        // process permutation
        std::cout << "[";
        for (auto & it : permutation)
            std::cout << it << " ";
        std::cout << "]";

    } else {
        for (int i = 0; i < n; i++) {
            if (chosen[i]) continue;

            chosen[i] = true;
            permutation.push_back(i);
            search();
            chosen[i] = false;
            permutation.pop_back();
        }
    }
}

void printPermutations()
{
    vector<int> permutations = {0,1,2};

    do
    {
        std::cout << "<";
        for (auto & it : permutations)
            std::cout << it << " ";
        std::cout << ">";
    } while (std::next_permutation(permutations.begin(), permutations.end()));
}

int main(){
    std::vector<int> subsets;
    allsubsets(subsets, 0, 3);
    std::cout << endl;
    allsubsets2(3);
    std::cout << "\n\n\n";
    search();
    std::cout << "\n\n\n";

    printPermutations();
}