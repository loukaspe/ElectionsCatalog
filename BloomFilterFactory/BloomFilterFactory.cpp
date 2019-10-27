#include "BloomFilterFactory.h"

BloomFilter* BloomFilterFactory::getFromRedBlackTree(RedBlackTree* Voters) {
    int numberOfVoters = Voters->getSize();

    // Optimal Size for the Bloom Filter according to http://cgi.di.uoa.gr/~ad/k22/Bloom_Filters.pdf
    // Section 6 is prime p >= 3 * R
    int size = Helper::findFirstPrimeLargerThan(3 * numberOfVoters);

    BloomFilter* bloomFilter = new BloomFilter(size);

    BloomFilterFactory::setBitsFromRedBlackTreeInOrder(
            Voters->getRoot(),
            bloomFilter
    );

    return bloomFilter;
}

/* This functions traverses the RBT in order and sets the according bits for
 * each value */
void BloomFilterFactory::setBitsFromRedBlackTreeInOrder (
        RedBlackTreeNode* node,
        BloomFilter* bloomFilter
) {
    if (node == NULL) {
        return;
    }

    setBitsFromRedBlackTreeInOrder(node->left, bloomFilter);
    //std::cout << "To insert " << endl;
    bloomFilter->add( node->voter->getId() );
    setBitsFromRedBlackTreeInOrder(node->right, bloomFilter);
}
