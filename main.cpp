#include <iostream>
#include "stack.h"

using namespace std;

const int NUM = 17;

int main() {

    stack_t<int> stk;
    stk.construct(0);
    stack_t<char> stk2;
    stk2.construct(0);
    stack_t <unsigned long long> u_stk;
    u_stk.construct(0);
    for (int i = 0; i < NUM; i -= -1) {

        stk.push(i+5);
        stk2.push(i + 50);
        u_stk.push(i);

    }
    for (int i = 0; i < NUM; i++)
        cout << hex << stk.pop()<< ' ' << stk2.pop() << endl;
    stk.pop();

    stk.destruct();
    return 0;
}
