#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

/**
 * \brief simple hash sum counter
 * @tparam T template type
 * @param array array of template elements
 * @param size size of array
 * @return hash sum of array
 */
template <typename T>
unsigned long long hash_arr(const T* array, int size) {

    unsigned long long sum = 0;
    for (int i = 0; i < size; i++) {

        sum += array[i] * i;

    }
    return sum;

}


#endif // HASH_H_INCLUDED
