#ifndef UNTITLED_REGISTRYREADER_H
#define UNTITLED_REGISTRYREADER_H

#include "RedBlackTree/RedBlackTree.h"
#include "BloomFilter/BloomFilter.h"
#include "PostalCodesLinkedList/PostalCodesLinkedList.h"

/* Helpful Source:
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html */

class RegistryReader {
    public:
        RegistryReader(
            char*,
            RedBlackTree*,
            BloomFilter*,
            PostalCodesLinkedList*
        );
    BloomFilter* readAndUpdateStructures();
    private:
        char* inputFilename;
        RedBlackTree* votersRBTree;
        BloomFilter* votersBloomFilter;
        PostalCodesLinkedList* postalCodesLinkedList;
    static const char* NO_INPUT_FILE_ERROR;
    static const char* OPEN_FILE_ERROR;
    static const char* OPEN_FILE_READ_MODE;
    static const char* SPACE_DELIMITER;
    static const char* ERROR_IN_READING_FILE;
    static const bool INITIAL_HAS_VOTED_FALSE;

};


#endif //UNTITLED_REGISTRYREADER_H
