#include <BloomFilterFactory/BloomFilterFactory.h>
#include "RegistryReader.h"

const char* RegistryReader::NO_INPUT_FILE_ERROR = "ERROR: No Input File was found.\n";
const char* RegistryReader::OPEN_FILE_ERROR = "ERROR: Could not open file ";
const char* RegistryReader::OPEN_FILE_READ_MODE = "r";
const char* RegistryReader::SPACE_DELIMITER = " ";
const char* RegistryReader::ERROR_IN_READING_FILE = "ERROR: Cannot read file\n";
const bool RegistryReader::INITIAL_HAS_VOTED_FALSE = false;

RegistryReader::RegistryReader(
        char* filename,
        RedBlackTree* votersRBTree,
        BloomFilter* votersBloomFilter,
        PostalCodesLinkedList* postalCodesLinkedList
){
    this->inputFilename = filename;
    this->votersRBTree = votersRBTree;
    this->votersBloomFilter = votersBloomFilter;
    this->postalCodesLinkedList = postalCodesLinkedList;
}

void RegistryReader::readAndUpdateStructures() {
    if(inputFilename == nullptr) {
        Helper::handleError(NO_INPUT_FILE_ERROR);
    }

    FILE* inputFile;
    char* line = nullptr;
    size_t length = 0;
    char* temp;
    char* id;
    char* firstName;
    char* lastName;
    int age;
    char gender;
    int postalCode;
    PostalCodesLinkedListNode* tempPostalCodesNode = (
            PostalCodesLinkedListNode*
    ) malloc( sizeof(PostalCodesLinkedListNode) );

    inputFile = fopen(inputFilename, OPEN_FILE_READ_MODE);
    if(inputFile == nullptr) {
        Helper::handleError(OPEN_FILE_ERROR);
    }

    // I consider that the inputFile is correctly formatted as per the way the
    // data is given
    while( getline(&line, &length, inputFile) != -1 ) {
        temp = strtok(line, SPACE_DELIMITER);
        id = Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        firstName = Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        lastName = Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        age = atoi( Helper::copyString(temp) );

        temp = strtok(nullptr, SPACE_DELIMITER);
        gender = *Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        postalCode = atoi( Helper::copyString(temp) );

        //cout << "\t" << id << " "  << firstName << " "  << lastName << " "  << age << " "  << gender << " "  << postalCode << endl;
        Voter* newVoter = new Voter (
                id,
                firstName,
                lastName,
                age,
                gender,
                postalCode,
                INITIAL_HAS_VOTED_FALSE
        );

        votersRBTree->insertVoterToTree(newVoter);

        tempPostalCodesNode = postalCodesLinkedList->findNodeWithPostalCode(
                postalCode
        );

        if(tempPostalCodesNode == nullptr) {
            postalCodesLinkedList->addAtStart(postalCode);
            tempPostalCodesNode = postalCodesLinkedList->findNodeWithPostalCode(
                    postalCode
            );
        }

        tempPostalCodesNode->list->addAtStart(
                votersRBTree->searchForVoter(newVoter)
        );
    }

    votersBloomFilter = BloomFilterFactory::getFromRedBlackTree(votersRBTree);

    if( ferror(inputFile) ) {
        Helper::handleError(ERROR_IN_READING_FILE);
    }

    free(line);
    fclose(inputFile);
}
