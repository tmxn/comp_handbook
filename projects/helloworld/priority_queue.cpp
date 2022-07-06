#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include <queue>

using namespace std;


int main(){
    std::priority_queue<int> pqueue;

    pqueue.push(1);
    pqueue.push(3);
    pqueue.push(5);
    pqueue.push(7);

    pqueue.push(1);

    std::cout << "Size is " << pqueue.size() << endl;
}