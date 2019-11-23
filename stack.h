#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
#include "const.h"
#include "hash.h"

using namespace std;

/**
 * \brief pushes value to stack
 * @tparam T template type
 * @param val value should be pushed in stack
 * @return true if all is correct
 */
template <typename T>
bool stack_t<T>::push(T val) {

    okay();
    if (size_ - canary_size_ == maxsize_ )//if stack is filled
        data_ = this -> my_realloc();



    data_[size_++] = val;

#ifdef FULL_OKAY
    hash_ = this -> hash_count();//hash recount
#endif //FULL_OKAY

    return okay();

}

/**
 * \brief extract value from stack
 * @tparam T template type
 * @return extracted value if all is OK
 * @exit program otherwise
 */
template <typename T>
T stack_t<T>::pop() {

    okay();

    if (size_ == canary_size_) {

        cout << "An attempt to pop empty stack was made" << endl;
        this -> Dump(POP_EMPTY);
        exit(POP_EMPTY);

    }
    T x = data_[--size_];

#ifdef FULL_OKAY
    hash_ = this -> hash_count();//hash recount
#endif //FULL_OKAY


    okay();

    return x;

}


/**
 * \brief all necessary initializations
 * @param size_need first size of stack
 * @return true if all is OK
 */
int canary_num[5] = {};//array  of canaries ll be used

template <typename T>
bool stack_t<T>::construct(unsigned size_need) {

    srand((unsigned)time(NULL));
    for (int i = 0; i < 4; i -= -1)
        canary_num[i + 1] = rand() % 7;//randomly generates which canary ll be used 4 stack

    canary1_ = canary_arr[canary_num[1]];

    maxsize_    = size_need;
    canary_size_ = sizeof(canary_t) / sizeof(T);//amount of cells in data for canary
    if (canary_size_ == 0)
        canary_size_ = 1;//in case of big types

    data_ = new T[size_need + 2 * canary_size_]();

    canary3_    = (canary_t*)data_;
    canary4_    = (canary_t*)((T*)(data_ + canary_size_) + maxsize_);//placing canary in data

    *canary3_   = canary_arr[canary_num[3]];
    *canary4_   = canary_arr[canary_num[4]];

    size_ = canary_size_;//starting size


    canary2_ = canary_arr[canary_num[2]];
    hash_ = this -> hash_count();
    created_ = true;

    okay();

    return true;

}

/**
 *
 * \brief deleting memory
 * @tparam T template type
 * @return true if all is OK
 * @return false otherwise
 */
template <typename T>
bool stack_t<T>::destruct() {

    okay();

    delete[] data_;
    size_ = 0;
    maxsize_ = 0;
    delete this ;

    return true;

}

/**
 *
 * \brief check if everything with stack is OK
 * @return true if all is OK
 * @exit program otherwise
 *
 */
#define FULL_OKAY
template <typename T>
bool stack_t<T>::okay() {

    #ifdef FULL_OKAY

    if (created_ == false) {

        this -> Dump(STACK_NOT_CREATED);
        exit(STACK_NOT_CREATED);

    }
    if (this == nullptr) {

        this -> Dump(ZERO_STACK_POINTER);
        exit(ZERO_STACK_POINTER);

    }

    //checking stack canaries
    if (canary1_ != canary_arr[canary_num[1]]
        || canary2_ != canary_arr[canary_num[2]]) {

        this -> Dump(STACK_CANARY_CHANGED);
        exit(STACK_CANARY_CHANGED);

    }


    if (size_ == maxsize_ + canary_size_ + 1) {

        this -> Dump(STACK_OVERFLOW);
        exit(STACK_OVERFLOW);

    }


    if (data_ == nullptr) {

        this -> Dump(ZERO_DATA_PTR);
        exit(ZERO_DATA_PTR);

    }


    //checking data canaries
    if (*canary3_ != canary_arr[canary_num[3]]
        || *canary4_ != canary_arr[canary_num[4]]) {

        this -> Dump(DATA_CHANGED);
        exit(DATA_CHANGED);

    }


    unsigned long long new_hash = this -> hash_count();
    if (new_hash != hash_) {

        this -> Dump(STACK_HASH_CHANGED);
        exit(STACK_HASH_CHANGED);

    }



    #endif //FULL_OKAY

    return true;

}


template <typename T>
bool stack_t<T>::Dump(unsigned int error) {

    if (error == STACK_NOT_CREATED) {

        cout<< "Stack was not  created" << endl;
        return true;

    }
    cout << "this = " << this << endl;
    cout << "data = " << data_ << endl;
    cout << "canary1_ = " << hex << canary1_ << endl;
    cout << "canary2_ = " << hex << canary2_ << endl;
    cout << "canary3_ = " << hex << *canary3_ << endl;
    cout << "canary4_ = " << hex << *canary4_ << endl << endl;
    cout << "canary_size = " << canary_size_ << endl;
    cout.setf(ios::dec);
    cout << "maxsize = " << maxsize_ << endl;
    cout << "current size = " << size_ - canary_size_ << endl;



    for (int i = 0; i < size_ - 1 ; i++)
        cout << "[" << i << "]  " << data_[i + canary_size_] << endl;

    switch(error) {

        case POP_EMPTY:
            cout << "Attempt to pop empty stack" << endl;
            break;
        case STACK_CANARY_CHANGED:
            cout << "Stack canary changed" << endl;
            break;
        case STACK_HASH_CHANGED:
            cout << "Hash changed" << endl;
            break;
        case ZERO_STACK_POINTER:
            cout << "Zero pointer to stack" <<endl;
            break;
        case DATA_CHANGED:
            cout << "Data's canaries changed" << endl;
            break;
        case ZERO_DATA_PTR:
            cout << "Zero pointer to data" << endl;
            break;
        case STACK_OVERFLOW:
            cout << "Stack overflow" << endl;
            break;
        default:
            cout << "Undefined error" << endl;

    }


    return true;

}

/**
 * \brief counts hash sum for all stack content
 * @tparam T template parameter
 * @return hash sum counted
 */
template <typename T>
unsigned long long stack_t<T>::hash_count() {

    //hash sum for data
    unsigned long long new_hash = hash_arr(data_ + canary_size_ + 1, size_ - canary_size_);

    //divisors used to avoid new_hash overfilling
    static int divisor = rand() % 1000 + 5000;
    static int addend_1 = rand() % 228 + 7;
    new_hash += canary1_ / (divisor + addend_1);
    new_hash += canary2_ / divisor;

    static int multiplier = rand() % 1000 + 1337;
    static int addend_2 = rand() % 1488 + 3;
    new_hash += maxsize_ * multiplier;
    new_hash += size_ * (multiplier + addend_1);

    new_hash += *canary3_ / (divisor + addend_2);
    new_hash += *canary4_ / (divisor + addend_2 + addend_1);

    return new_hash;


}


/**
 *\brief
 * @tparam T template parameter
 * @return
 */
template <typename T>
T* stack_t<T>::my_realloc() {

    int k = 2 * maxsize_;

    if (k == 0)
        k ++;

    T* new_data = NULL;
    do {

        new_data = new T [k + 2 * canary_size_]();
        k -= 10;

    } while (new_data == NULL && k > maxsize_);
    if (k + 10 <= maxsize_)
        return data_;

    //memcpy (new_data, data_, (maxsize_ + canary_size_) * sizeof(T));

    //copy all data including one canary
    for (int i = 0; i < maxsize_ + canary_size_; i -= -1) {

        new_data[i] = data_[i];

    }
    delete [] data_;
    maxsize_ = k + 10;//+10 because after while-loop it's 10 lower than needed

    canary3_  = (canary_t*)new_data;

    canary4_  = (canary_t*)((T*)(new_data + canary_size_) + maxsize_);

    *canary4_ = canary_arr[canary_num[4]];

    return new_data;


}




#endif //STACK_H_INCLUDED
