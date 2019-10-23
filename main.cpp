#include <iostream>
#include <getopt.h>
#include "BitArray.h"
#include "RedBlackTree.h"
#include "BloomFilterFactory.h"

using namespace std;

const char* PROGRAM_OPTIONS = "i:o:n:";
const char* WRONG_PROGRAM_USAGE_ERROR = "Usage %s -i [inputfile] -o [output file] -n [numOfUpdates]\n";
const char* NO_INPUT_FILE_ERROR = "ERROR: No Input File was found.\n";
const char* OPEN_FILE_ERROR = "ERROR: Could not open file ";                    // Not a const in order to be used in strcat
const char* OPEN_FILE_READ_MODE = "r";
const char* SPACE_DELIMITER = " ";
const char* ERROR_IN_READING_FILE = "ERROR: Cannot read file\n";
const bool INITIAL_HAS_VOTED_FALSE = false;

int main(int argc, char *argv[]) {
    int opt;

    char* inputFilename;
    char* outputFilename;
    int numOfUpdates;

    while ( (opt = getopt(argc, argv, PROGRAM_OPTIONS)) != -1 ) {
        switch (opt) {
            case 'i':
                inputFilename = Helper::copyString(optarg);
                //cout << inputFilename << endl;
                break;
            case 'o':
                outputFilename = Helper::copyString(optarg);
                //cout << outputFilename << endl;
                break;
            case 'n':
                numOfUpdates = atoi(optarg);
                //cout << numOfUpdates << endl;
                break;
            default:
                Helper::handleError(WRONG_PROGRAM_USAGE_ERROR);
        }
    }

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

    RedBlackTree* votersRBTree = new RedBlackTree();
    BloomFilter* votersBloomFilter;

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
    }

    votersRBTree->printInOrder();
    votersBloomFilter = BloomFilterFactory::getFromRedBlackTree(votersRBTree);

    if( ferror(inputFile) ) {
        Helper::handleError(ERROR_IN_READING_FILE);
    }

    free(line);
    fclose(inputFile);

    return 0;
}
