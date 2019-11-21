#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

template <typename T>
unsigned long long hash_arr(const T* array, int size) {

    unsigned long long sum = 0;
    for (int i = 0; i < size; i++) {

        sum += array[i] * i;

    }
    return sum;

}


#endif // HASH_H_INCLUDED
