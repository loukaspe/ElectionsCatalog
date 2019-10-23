/* BloomFilterFactory is a class that given a specific RedBlackTree of Voters,
 * it will calculate the size the BloomFilter must have (the first prime number
 * that is larger than the size of the RedBlackTree, which is also the number
 * of Voters) and will create it.
 *
 * This will have as result that we read the Registly file only once, to create
 * the RBT. Then we will use the BloomFilterFactory to create the BloomFilter
 * and not read the file another time. */

#ifndef UNTITLED_BLOOMFILTERFACTORY_H
#define UNTITLED_BLOOMFILTERFACTORY_H

#include "RedBlackTree.h"
#include "BloomFilter.h"

class BloomFilterFactory {
public:
    static BloomFilter* getFromRedBlackTree(RedBlackTree*);
private:
    static void setBitsFromRedBlackTreeInOrder(Node*, BloomFilter*);

};


#endif //UNTITLED_BLOOMFILTERFACTORY_H
