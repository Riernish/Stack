#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED


typedef unsigned long canary_t;

const canary_t canary_arr[7] = {0xEDA0BEDA, 0xADD0BEEF,
 0xDAD0DEAD, 0xFEED0BEE, 0xBABA0BAD, 0xFADEBEEF,
 0xADD0EDA0};

const int MAXSIZE = 69;

template <typename T>
struct stack_t {

    private:
        canary_t canary1_;

        unsigned long long hash_;

        int size_;
        int maxsize_;
        T *data_;
        int canary_size_;
        canary_t * canary3_;
        canary_t * canary4_;

        bool okay();
        bool Dump(unsigned int);
        unsigned long long hash_count();
        T* my_realloc();

    public:
        bool push(T val);
        T pop();
        bool construct(int size_need);
        bool destruct();

    private:
        canary_t canary2_;

};

const unsigned int POP_EMPTY            = 0xC0001337;
const unsigned int STACK_CANARY_CHANGED = 0xC000BEDA;
const unsigned int STACK_HASH_CHANGED   = 0xC0000023;
const unsigned int ZERO_STACK_POINTER   = 0xC0000666;
const unsigned int DATA_CHANGED         = 0xC0006901;
const unsigned int ZERO_DATA_PTR        = 0xC0000505;
const unsigned int STACK_OVERFLOW       = 0xC0000DAD;



#endif // CONST_H_INCLUDED
