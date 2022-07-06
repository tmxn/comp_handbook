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

template <class T> inline void hash_combine(size_t &seed, T const &v) {
    seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }
};

// 0 - L - 00
// 1 - U - 01
// 2 - R - 10
// 3 - D - 11

std::vector<std::vector<int>> possibleTilingsCache;
std::unordered_map<int, std::vector<int>> lastRowCache;
std::vector<bool> cacheds;
std::unordered_map<std::pair<int, int>, int, pair_hash> globalcache;

int countTilings(int prevRow, int columns, int rows, int row)
{
    static const int TILE_L = 0;
    static const int TILE_R = 2;
    static const int TILE_U = 1;
    static const int TILE_D = 3;
    //Use bits to count all possible tilings. Since there are only 2 bits required to represent 4 possible combinations
    //of cell directions, we only need to count from 0 to 4^columns to scan through all possible tilings for any row
    //We can easily calculate 4^columns by bit-shifting 1 by 2x the number of columns
    int cnt = 1 << (columns * 2);

    //Create the cache if it is not created
    if (possibleTilingsCache.empty())
    {
        possibleTilingsCache = std::vector<std::vector<int>>(cnt + 1);
        cacheds = std::vector<bool>(cnt + 1, false);
    }   

    bool cached = cacheds[prevRow];

    std::vector<int> * target = &possibleTilingsCache[prevRow];


    if (row == (rows - 1))
    {
        auto iter = lastRowCache.find(prevRow);
        if (iter != lastRowCache.end())
        {
            cached = true;
            target = &iter->second;
        }
    }


    std::vector<int> possibleTilings;
    if (!cached || row == 0)
    {
        for (int i = 0; i < cnt; i++)
        {
            //Is this set of bits a valid tiling?
            //Valid tilings:
            //R + L ==> []
            //If first, no U
            //If last, no D
            //No R without L next
            //No L without R prev
            //For N-th row:
            //U if prev is D
            
            bool bracketOpened = false;
            bool fail = false;
            int bracketCounter = 0;
            
            for (int col = 0; col < columns; col++)
            {
                //Check each tile in our tiling variant by bit-shifting "11" 2xcolumn times. DONT FORGET TO BIT-SHIFT BACK
                int tile = ((3 << (col * 2)) & i) >> (col * 2);
                //std::cout << "Tile value " << tile << "\n";
                //Bracket opened
                if (tile == TILE_R) {
                    //But bracket was already opened
                    if (bracketOpened) {
                        fail = true;
                        break;
                    }
                    bracketOpened = true;
                    bracketCounter++;
                    //std::cout << "Found R ";
                }
                //Bracket closed
                if (tile == TILE_L) {
                    //But bracket was not opened yet
                    if (!bracketOpened) {
                        fail = true;
                        break;
                    }
                    bracketOpened = false;
                    bracketCounter--;
                    //std::cout << "Found L ";
                }
                //Tile is Up or Down but we've just opened a bracket and are therefore ruining it
                if ((tile == TILE_U || tile == TILE_D) && bracketOpened) {
                    fail = true;
                    break;
                }
                //First row invalid condition
                if (tile == TILE_U && row == 0) {
                    fail = true;
                    break;
                }
                //Last row invalid condition
                if (tile == TILE_D && row == (rows - 1)) {
                    fail = true;
                    break;
                }
                //Nth row up / down validity condition
                if (row > 0) {
                    //Get the value of the same tile but on previous row
                    int tileUp = ((3 << (col * 2)) & prevRow) >> (col * 2);
                    //If upper tile is Down, current tile must be Up
                    if (tileUp == TILE_D && tile != TILE_U) {
                        fail = true;
                        break;
                    }
                    //If current tile is Up, upper tile must be Down
                    if (tile == TILE_U && tileUp != TILE_D) {
                        fail = true;
                        break;
                    }
                }
            }

            //All brackets must sum up to zero
            if (bracketCounter != 0) fail = true;

            //All checks passed. Row is good. Try returning the result or tiling rows below
            if (!fail) {
                possibleTilings.push_back(i);
            }
        }
        //auto a = possibleTilingsCache[prevRow];
        //if (a.size() != possibleTilings.size() && a.size())
        //{
        //    int x = 0;
        //    //std::cout << "SDf";
        //}
        //Do not store special cases in the cache
        if (row != (rows - 1) && row != 0)
        {
            possibleTilingsCache[prevRow] = possibleTilings;
            cacheds[prevRow] = true;
        }
        //cache last row separately
        if (row == (rows-1))
        {
            lastRowCache[prevRow] = possibleTilings;
        }

        target = &possibleTilings;
    }

    int result = 0;

    auto key = std::make_pair(prevRow, row);
    auto iter = globalcache.find(key);
    if (iter == globalcache.end())
    {
        for (auto & it : *target)
        {
            if (row == (rows - 1)) { //Last row?
                //total++;
                // auto printRow = [columns](int row){
                //     std::string res = "";
                //     for (int col = 0; col < columns; col++)
                //     {
                //         int tile = ((3 << (col * 2)) & row) >> (col * 2);
                //         if (tile == TILE_R)
                //             res += "R";
                //         if (tile == TILE_L)
                //             res += "L";
                //         if (tile == TILE_D)
                //             res += "D";
                //         if (tile == TILE_U)
                //             res += "U";
                //     }
                //     return res;
                // };
                // std::cout << "Found totals " << total << " good row " << printRow(i) << endl;
                return 1;
            } else {
                result += countTilings(it, columns, rows, row + 1);
            }
        }
        globalcache[key] = result;
    } else
    {
        result = iter->second;
    }

    return result;
}

int main()
{
    int total = countTilings(0, 10, 10, 0);

    std::cout << "Total is " << total << endl;
}