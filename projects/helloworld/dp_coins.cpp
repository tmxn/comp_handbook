#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

int inf = 2000000000;

int solve(std::vector<int>& coins, int x)
{
    if ( x < 0 ) return inf;
    if ( x == 0 ) return 0;
    
    int best = inf;
    for (auto & it : coins)
    {
        best = min(best, solve(coins, x - it) + 1);
    }
    return best;
}

int solveIterative(std::vector<int>& coins, int x)
{
    std::vector<int> minCoins(x + 1, inf);
    //0 coins to form 0
    minCoins[0] = 0;
    //Start from 1, since we've already constructed cost 0
    for (int i = 1; i <= x; i++)
    {
        for (auto & coin : coins)
        {
            //Can we use this coin?
            if (i - coin >= 0)
            {
                //Each sum i can be constructed by choosing a coin c
                //By choosing a coin, we can use a previously computed cost without the used coin,
                //but we have to add 1, since we did use up the coin
                minCoins[i] = std::min(minCoins[i], minCoins[i - coin] + 1);
            }
        }
    }
    return minCoins.back();
}

int printCoinsUsed(std::vector<int>& coins, int x)
{
    std::vector<int> firstCoin(x + 1, -1);
    std::vector<int> minCoins(x + 1, inf);
    minCoins[0] = 0;
    for (int i = 1; i <= x; i++)
    {
        for (auto & coin : coins)
        {
            //we can use this coin and we found a better coin option
            if (i - coin >= 0 && minCoins[i] > (minCoins[i - coin] + 1))
            {
                minCoins[i] = minCoins[i - coin] + 1;
                firstCoin[i] = coin;
            }
        }
    }

    std::cout << "Coins: ";
    while (x > 0)
    {
        std::cout << firstCoin[x] << " ";
        x -= firstCoin[x];
    }
    std::cout << endl;
    
    return minCoins.back();
}

int countNumberOfWaysToFormSum(std::vector<int>& coins, int sum)
{
    vector<int> ways(sum + 1, 0);
    ways[0] = 1;
    for (int i = 1; i <= sum; i++)
    {
        for (auto & coin : coins)
        {
            if (i - coin >= 0)
            {
                ways[i] += ways[i - coin];
            }
        }
    }
    return ways.back();
}

int main(){
    std::vector<int> coins = {1,3,4};
    std::cout << "Coin used " << printCoinsUsed(coins, 22) << endl;

    for (int i = 0; i < 20; i++)
    {
        std::cout << "Ways to form "  << i << " " << countNumberOfWaysToFormSum(coins, i) << endl;
    }
    
    return 0;
    for (int i = 0; i <= 20; i++)
    {
        std::cout << solve(coins, i) << endl;
        std::cout << solveIterative(coins, i) << endl;
        std::cout << "----------------------------------------------\n";
    }
    
}