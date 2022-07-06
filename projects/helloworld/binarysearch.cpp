#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

int binarySearchFind(const std::vector<int>& arr, int value)
{
    int a = 0, b = arr.size() - 1;
    while (a <= b) {
        int k = (a + b) / 2;
        if (arr[k] == value) return k;
        if (arr[k] > value) b = k - 1;
        if (arr[k] < value) a = k + 1;
    }
    return -1;
}

int binarysearchsecond(const std::vector<int>& arr, int value)
{
    int n = arr.size();
    int k = 0;
    int bb = 1;
    std::cout << "-------------------------------ENTRY---------------------------";
    for (int b = n/2; b >= 1; b /= 2) {
        std::cout << "ITER b=" << b << " k = " << k << endl;
        if (k + b < n)
            std::cout << "arr[k+b] is " << arr[k+b] << endl;
        else
            std::cout << "k + b is > arr.size() \n";
        while (k + b < n && arr[k + b] <= value) {
            k += b;
            std::cout << "WHILE k=" << k << endl;
        }
    }
    std::cout << "-------------------------------EXIT---------------------------";
    if (arr[k] == value) return k;
    return -1;
}

int binarysearch2(const std::vector<int>& arr, int value)
{
    int k = 0;
    int n = arr.size();
    //binary search
    for (int b = n / 2; b >= 1; b/=2)
    {
        while (k + b < n && arr[k + b] <= value) k += b;
    }
    return k;
}

int binarysearch3(const std::vector<int>& arr, int value){
    int k = 0;
    int n = arr.size();
    for (int b = n / 2; b >= 1; b/=2){
        while (k + b < n && arr[k + b] <= value) k += b;
    }
    return k;
}

int main()
{
    std::vector<int> nums = {-1, 2, 4, -3, 5, 2, -5, 2};

    std::sort(nums.begin(), nums.end());

    for (auto & it : nums)
    {
        std::cout << it <<  " ";
    }

    std::cout << std::endl;
    std::cout << "Enter value to find" << endl;
    int x;
    cin >> x;
    std::cout << "Found index is "  << binarySearchFind(nums, x) << endl;

    auto iter = std::lower_bound(nums.begin(), nums.end(), x);
    if (iter != nums.end())
        std::cout << "Lower bound index is " << iter - nums.begin() << std::endl;
    else
        std::cout << "Not found by lower bound" << endl;
    auto iter2 = std::upper_bound(nums.begin(), nums.end(), x);
    if (iter2 != nums.end())
        std::cout << "Upper bound index is " << iter2  - nums.begin() << std::endl;
    else
        std::cout << "Not found by upper bound" << endl;
    std::cout << "Value found by second binary search is " << binarysearchsecond(nums, x) << endl;

    std::cout << "Binarysearch2 " << binarysearch2(nums, x) << endl;
    std::cout << "Binarysearch2 " << binarysearch3(nums, x) << endl;
}