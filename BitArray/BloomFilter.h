#ifndef UNTITLED_BLOOMFILTER_H
#define UNTITLED_BLOOMFILTER_H

#include "BitArray.h"
#include <cassert>

class BloomFilter {
    public:
    //BloomFilter(int, double);
    BloomFilter(int);
//        int calculateOptimalSize(
//                int numberOfElements,
//                double desiredFalsePositivePropability
//        );
        void add(char*);
    bool check(char*);
    private:
        //const static char* DIVISION_BY_ZERO_ERROR;
        const static char* MEMORY_ALLOCATION_ERROR;
        const static int NUMBER_OF_HASH_FUNCTIONS;
        int size;
        //double falsePositivePropability;
        BitArray* bitArray;
        unsigned long firstHashFunction(char*);
        unsigned long secondHashFunction(char*);
        unsigned long* getHashDigests(char*);
};


#endif //UNTITLED_BLOOMFILTER_H
