#include <iostream>
#include "stack.h"

using namespace std;

const int NUM = 17;

int main() {

    stack_t<unsigned long long> stk;
    stk.construct(3);
    for (int i = 0; i < NUM; i -= -1)
        stk.push(i+32);
    for (int i = 0; i < NUM; i++)
        cout << hex << stk.pop() << endl;
    stk.pop();

    stk.destruct();
    return 0;
}
