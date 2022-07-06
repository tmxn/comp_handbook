#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

//Given an array of n numbers, calculate the largest subarray sum
//ie the Largest Possible Sum of a Sequence of Consecutive Numbers in the Array


void findMaxSubSum(const std::vector<int>& vec){
    int maxSum = 0;
    int  l = -1, r = -1;
    for (int i = 0; i < vec.size(); i++)
    {
        int sum = 0;
        for (int j = i; j < vec.size(); j++)
        {
            sum += vec[j];
            if (maxSum < sum) {
                maxSum = sum;
                l = i; r = j;
            }
        }
    }
    std::cout << "Max Sum square is " << maxSum << " From " << l << " to " << r  << endl;
}


void maxSubSumLinear(const std::vector<int>& vec ){
    int maxsum = 0;
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum = max(vec[i], vec[i] + sum);
        maxsum = std::max(maxsum, sum);
    }
    std::cout << "max sum linear is " << maxsum << endl;
}

int main(){
    std::vector<int> nums = {-1, 2, 4, -3, 5, 2, -5, 2};

    findMaxSubSum(nums);
    maxSubSumLinear(nums);
}