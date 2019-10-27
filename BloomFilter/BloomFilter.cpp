/* Implementation of Bloom Filter was based on:
 * 1. Your PDF http://cgi.di.uoa.gr/~ad/k22/Bloom_Filters.pdf
 * 2. https://www.geeksforgeeks.org/bloom-filters-introduction-and-python-implementation/
 * 3. http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
 *    which is help for Bit Array Implementation */

#include "BloomFilter.h"

//const char* BloomFilter::DIVISION_BY_ZERO_ERROR = "ERROR: Cannot divide by zero.\n";
const char* BloomFilter::MEMORY_ALLOCATION_ERROR = "ERROR: Cannot allocate memory for digests\n";

/* Const number of Hash Functions that will be used in the Bloom Filter
 * based on your propositions in section 6 of the given
 * PDF in http://cgi.di.uoa.gr/~ad/k22/Bloom_Filters.pdf */

const int BloomFilter::NUMBER_OF_HASH_FUNCTIONS = 3;

/* Returns the optimal size of the Bloom Filter based on section 4 of the given
 * PDF in http://cgi.di.uoa.gr/~ad/k22/Bloom_Filters.pdf */

//int BloomFilter::calculateOptimalSize(
//    int numberOfElements,
//    double desiredFalsePositivePropability
//) {
//    double dividend = -((double)numberOfElements) * log(desiredFalsePositivePropability);
//    double divisor = pow(log(2),2);
//    if(divisor == 0) {
//        Helper::handleError(BloomFilter::DIVISION_BY_ZERO_ERROR);
//    }
//
//    return (int) (dividend/divisor);
//}

//BloomFilter::BloomFilter(
//    int numberOfElements,
//    double desiredFalsePositivePropability
//): falsePositivePropability(desiredFalsePositivePropability)
//{
//    this->size = BloomFilter::calculateOptimalSize(
//        numberOfElements,
//        desiredFalsePositivePropability
//    );
//
//    this->bitArray = new BitArray(numberOfElements);
//}

BloomFilter::BloomFilter(int size): size(size)
{
    this->bitArray = new BitArray(size);
}

/* As Hash Functions I use djb2 and sdbm without implementing it myself. Source of
 * algorithms is: http://www.cse.yorku.ca/~oz/hash.html
 * Permission for this in: https://piazza.com/class/k1631q2t5o11rj?cid=6 */

unsigned long BloomFilter::firstHashFunction(char* key) {
    unsigned long hash = 5381;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

unsigned long BloomFilter::secondHashFunction(char* key) {
    unsigned long hash = 0;
    int c;

    while (c = *key++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

/* Based on the Kirsch-Mitzenmacher Optimization we only need 2 Hash Functions
 * and the we use the following transformation to compute the digests of the k
 * hash functions: g(x) = h1(x) + ih2(x) 0 ≤ i ≤ k − 1
 * The Function returns an array of the digests  */

unsigned long* BloomFilter::getHashDigests(char* key) {

   // unsigned long digests[BloomFilter::NUMBER_OF_HASH_FUNCTIONS] = {};
    unsigned long* digests = (unsigned long*) malloc( BloomFilter::NUMBER_OF_HASH_FUNCTIONS * sizeof(unsigned long) );

    int i;
    unsigned long hashFunctionsSum;
    for(i = 0; i < BloomFilter::NUMBER_OF_HASH_FUNCTIONS; i++) {
        hashFunctionsSum  = firstHashFunction(key) +
                     i * secondHashFunction(key);

        digests[i] = hashFunctionsSum % this->size;
    }

    return digests;
}

void BloomFilter::add(char* key) {
    unsigned long* digests = getHashDigests(key);
    
    for(int i = 0; i < NUMBER_OF_HASH_FUNCTIONS; i++) {
        bitArray->setBit(digests[i]);
        assert( bitArray->isSet( digests[i] ) );
        //std::cout << "Inserted" << std::endl;
    }
}

bool BloomFilter::check(char* key) {
    unsigned long* digests = getHashDigests(key);

    for(int i = 0; i < NUMBER_OF_HASH_FUNCTIONS; i++) {
        if( !bitArray->isSet( digests[i] ) ) {
            return false;
        }
    }

    return true;
}