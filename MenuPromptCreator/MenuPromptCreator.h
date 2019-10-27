/* This class is the one that will create and show the menu prompt for the commands
 * the user will give. According to this https://piazza.com/class/k1631q2t5o11rj?cid=20
 * all the answers and errors of these commands will be shown in the prompt and
 * not in the output file, which will only contain a "image" of the Registry at the
 * time. Also, according to this https://piazza.com/class/k1631q2t5o11rj?cid=37
 * errors will be shown in stdout*/

#ifndef ELECTIONSCATALOG_MENUPROMPTCREATOR_H
#define ELECTIONSCATALOG_MENUPROMPTCREATOR_H


#include "RedBlackTree/RedBlackTree.h"
#include "BloomFilter/BloomFilter.h"
#include "PostalCodesLinkedList/PostalCodesLinkedList.h"
#include "Helper/Helper.h"
#include "BloomFilterFactory/BloomFilterFactory.h"

class MenuPromptCreator {

    static const char* INSERT_YOUR_COMMAND_MESSAGE;
    static const char* NOT_VALID_COMMAND_MESSAGE;
    static const char* AVAILABLE_COMMANDS_MESSAGE;
    static const char* READING_COMMAND_ERROR_MESSAGE;
    static const int COMMANDS_NUMBER = 12;
    static const int COMMANDS_WITH_NO_ARGUMENT_NUMBER = 4;
    static char* AVAILABLE_COMMANDS[MenuPromptCreator::COMMANDS_NUMBER];
    static char* COMMANDS_WITH_NO_ARGUMENT[MenuPromptCreator::COMMANDS_WITH_NO_ARGUMENT_NUMBER];
    // I take as granted that the command size will not be bigger than 1024 chars
    static const size_t SIZE_OF_INPUT_BUFFER;

public:
    MenuPromptCreator(RedBlackTree*, BloomFilter*, PostalCodesLinkedList*, int);
    static void showAllOptions();
    void create();
private:
    int numOfUpdates;
    int currentNumberOfUpdates;
    RedBlackTree* votersTree;
    BloomFilter* votersBloomFilter;
    PostalCodesLinkedList* postalCodesList;
    static const char* NO_INPUT_FILE_ERROR;
    static const char* OPEN_FILE_ERROR;
    static const char* OPEN_FILE_READ_MODE;
    static const char* ERROR_IN_READING_FILE;
    int executeInputCommand();
    void readInput(char**&);
    void searchBloomFilterFor(char*);
    void searchRedBlackTreeFor(char*);
    void findRecord(char*);
    void insertRecord(char*, char*, char*, int, char, int);
    void voteOfVoter(char*);
    void deleteRecord(char*);
    void voteFromFile(char*);
    void showVotersThatHaveVoted();
    void showHowManyHaveVotedInPostalCode(int);
    void showPercentageOfHowManyHaveVotedForEveryPostalCode();
};


#endif //ELECTIONSCATALOG_MENUPROMPTCREATOR_H
