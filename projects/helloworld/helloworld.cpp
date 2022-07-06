#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

double binetsFormula (double n) {
    static const double rFive = sqrt(5);
    
    return (pow((1 + rFive), n) - pow((1 - rFive), n)) / (pow(2, n) * rFive);
}

int main(){
    int n;
    cin >> n;

    cout.precision(18);
    cout << "Nth fibonacci number is " << binetsFormula(n);
    cout << endl;

    //Second Test change to helloworld
}
