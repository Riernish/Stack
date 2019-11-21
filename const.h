#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

#define FULL_OKAY

typedef unsigned long canary_t;
/**
 * array of possible amounts for canaries
 */
const canary_t canary_arr[7] = {0xEDA0BEDA, 0xADD0BEEF,
 0xDAD0DEAD, 0xFEED0BEE, 0xBABA0BAD, 0xFADEBEEF,
 0xADD0EDA0};

/**
 *
 * @tparam T
 * template structure of stack
 * @params canary1, canary2 - all structure protection
 * @params canary3, canary4 - data protection
 * @param  canary_size size of 1 canary in blocks of data
 * @param  hash_ current amount for stack's hash sum
 */
template <typename T>
struct stack_t {

    private:

    #ifdef FULL_OKAY
        canary_t canary1_;

        unsigned long long hash_;
    #endif //FULL_OKAY

        int size_;
        int maxsize_;
        T *data_;

    #ifdef FULL_OKAY
        int canary_size_;
        canary_t * canary3_;
        canary_t * canary4_;
    #endif //FULL_OKAY

        bool okay();
    public:

        bool Dump(unsigned int);

    private:

    #ifdef FULL_OKAY
        unsigned long long hash_count();
    #endif //FULL_OKAY

        T* my_realloc();

    public:
        bool push(T val);
        T pop();//
        bool construct(unsigned size_need);
        bool destruct();

    private:

    #ifdef FULL_OKAY
        canary_t canary2_;
    #endif //FULL_OKAY

};

const unsigned int POP_EMPTY            = 0xC0001337;
const unsigned int STACK_CANARY_CHANGED = 0xC000BEDA;
const unsigned int STACK_HASH_CHANGED   = 0xC0000023;
const unsigned int ZERO_STACK_POINTER   = 0xC0000666;
const unsigned int DATA_CHANGED         = 0xC0006901;
const unsigned int ZERO_DATA_PTR        = 0xC0000505;
const unsigned int STACK_OVERFLOW       = 0xC0000DAD;



#endif // CONST_H_INCLUDED
