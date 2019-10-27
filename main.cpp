#include <iostream>
#include <getopt.h>
#include <RegistryReader/RegistryReader.h>
#include "BitArray.h"
#include "RedBlackTree.h"
#include "BloomFilterFactory.h"
#include "PostalCodesLinkedList/PostalCodesLinkedList.h"
#include "MenuPromptCreator/MenuPromptCreator.h"

using namespace std;

const char* PROGRAM_OPTIONS = "i:o:n:";
const char* WRONG_PROGRAM_USAGE_ERROR = "Usage %s -i [inputfile] -o [output file] -n [numOfUpdates]\n";

int main(int argc, char *argv[]) {
    int opt;

    RedBlackTree* votersRBTree = new RedBlackTree();
    BloomFilter* votersBloomFilter;
    PostalCodesLinkedList* postalCodesLinkedList = new PostalCodesLinkedList();

    char* inputFilename;
    char* outputFilename;
    int numOfUpdates;

    while ( (opt = getopt(argc, argv, PROGRAM_OPTIONS)) != -1 ) {
        switch (opt) {
            case 'i':
                inputFilename = Helper::copyString(optarg);
                break;
            case 'o':
                outputFilename = Helper::copyString(optarg);
                break;
            case 'n':
                numOfUpdates = atoi(optarg);
                break;
            default:
                Helper::handleError(WRONG_PROGRAM_USAGE_ERROR);
        }
    }

    RegistryReader* registryReader = new RegistryReader(
        inputFilename,
        votersRBTree,
        votersBloomFilter,
        postalCodesLinkedList
    );
    votersBloomFilter = registryReader->readAndUpdateStructures();

    MenuPromptCreator* menuPromptCreator = new MenuPromptCreator(
        votersRBTree,
        votersBloomFilter,
        postalCodesLinkedList,
        numOfUpdates
    );
    menuPromptCreator->create();
    return 0;
}
