#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

void queens_search(std::vector<bool>& columns, std::vector<bool>& diag1, std::vector<bool>& diag2, int y, int n, int& solutions)
{
    //The search has reached the end
    if (y == n)
    {
        solutions++;
    } else
    {
        //Attempt to place the queen at each point along the x (if possible)
        //Not possible if the column or one of the diagonals is 'occupied' by the queen
        for (int x = 0; x < n; x++)
        {
            //Check if we can place the queen at this position (x, y)
            if (columns[x] || diag1[x + y] || diag2[x + (n - 1 - y)]) continue;
            //Begin search. Mark current position as taken
            columns[x] = diag1[x + y] = diag2[x + (n - 1 - y)] = true;
            queens_search(columns, diag1, diag2, y + 1, n, solutions);
            //To continue search, revert the changes - unoccupy the position
            columns[x] = diag1[x + y] = diag2[x + (n - 1 - y)] = false;
        }
    }
}

int main(){
    int n;
    cout << "Enter n" << endl;
    cin >> n;
    std::vector<bool> columns;
    std::vector<bool> diag1;
    std::vector<bool> diag2;
    columns.resize(n, false);
    diag1.resize(2 * n, false);
    diag2.resize(2 * n, false);

    int count = 0;
    queens_search(columns, diag1, diag2, 0, n, count);

    std::cout << "There are " << count << " ways to arrange the queens" << endl;
}