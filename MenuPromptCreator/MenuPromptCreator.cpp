#include "MenuPromptCreator.h"

const size_t MenuPromptCreator::SIZE_OF_INPUT_BUFFER = 1024;
char* MenuPromptCreator::AVAILABLE_COMMANDS[MenuPromptCreator::COMMANDS_NUMBER] = {
        "lbf",
        "lrb",
        "ins",
        "find",
        "delete",
        "vote",
        "load",
        "voted",
        "voted",
        "votedperpc",
        "help",
        "exit"
};

char* MenuPromptCreator::COMMANDS_WITH_NO_ARGUMENT[
        MenuPromptCreator::COMMANDS_WITH_NO_ARGUMENT_NUMBER
    ] = {
        "voted",
        "votedperpc",
        "help",
        "exit"
};

const char* MenuPromptCreator::INSERT_YOUR_COMMAND_MESSAGE = "Please enter your "
                                                             "command: ";
const char* MenuPromptCreator::NOT_VALID_COMMAND_MESSAGE = "This is not a valid"
                                                           " command. "
           "To see the available command please type 'help'";
const char* MenuPromptCreator::READING_COMMAND_ERROR_MESSAGE = "ERROR: There was"
           " an error reading your command.";
const char* MenuPromptCreator::AVAILABLE_COMMANDS_MESSAGE = "Command list: \n"
            "1) lbf key (for lookup into bloom-filter for key)\n"
            "2) lrb key (for lookup into red-black tree for key)\n"
            "3) ins record (to insert record to red-black tree)\n"
            "4) find key (to check if record with key exists)\n"
            "5) delete key (to delete record with key)\n"
            "6) vote key (to set voter with key to vote)\n"
            "7) load fileofkeys (vote for every key in file fileofkeys)\n"
            "8) voted (to show how many have voted)\n"
            "9) voted postcode (to show how many have voted of postcode)\n"
            "10) votedperpc (to show percentage of how many have voted of "
                "postcode)\n"
            "11) help (to see all options)\n"
            "12) exit (to exit the program)\n\n" ;

const char* MenuPromptCreator::NO_INPUT_FILE_ERROR = "ERROR: No Input File was found.\n";
const char* MenuPromptCreator::OPEN_FILE_ERROR = "ERROR: Could not open file ";
const char* MenuPromptCreator::OPEN_FILE_READ_MODE = "r";
const char* MenuPromptCreator::ERROR_IN_READING_FILE = "ERROR: Cannot read file\n";

MenuPromptCreator::MenuPromptCreator(
        RedBlackTree* votersTree,
        BloomFilter* votersBloomFilter,
        PostalCodesLinkedList* postalCodesList,
        int numOfUpdates
)
{
    this->votersTree = votersTree;
    this->votersBloomFilter = votersBloomFilter;
    this->postalCodesList = postalCodesList;
    this->numOfUpdates = numOfUpdates;
    this->currentNumberOfUpdates = 0;
}

void MenuPromptCreator::showAllOptions() {
    cout << MenuPromptCreator::AVAILABLE_COMMANDS_MESSAGE << endl;
}

void MenuPromptCreator::readInput(char** &returnedCommand) {
    const char *SPACE_DELIMITER = " ";

    char *command = nullptr;
    char *commandArgument = nullptr;
    char *possibleUnwantedSecondCommandArgument = nullptr;

    char* temp;
    char* id;
    char* firstName;
    char* lastName;
    char* age;
    char* gender;
    char* postalCode;

    char *input = (char *) malloc(
            MenuPromptCreator::SIZE_OF_INPUT_BUFFER * sizeof(char)
    );

    if (input == nullptr) {
        Helper::handleError(MenuPromptCreator::READING_COMMAND_ERROR_MESSAGE);
    }

    cout << MenuPromptCreator::INSERT_YOUR_COMMAND_MESSAGE;

    /* READ WHOLE INPUT */

    if (
        fgets(
                input,
                MenuPromptCreator::SIZE_OF_INPUT_BUFFER,
                stdin
        ) == nullptr
    )
    {
        Helper::handleError(MenuPromptCreator::READING_COMMAND_ERROR_MESSAGE);
    };

    /* Fgets returns a '\n' character in the end of the input, so if one exists
     * we remove it. */
    input = Helper::removeNewLineCharacterFromString(input);

    /* READ COMMAND */

    command = strtok(input, SPACE_DELIMITER);
    // We check if there is a commands and if it is in the available array
    if (
        command == nullptr
        || !Helper::inArray(
                command,
                MenuPromptCreator::AVAILABLE_COMMANDS,
                MenuPromptCreator::COMMANDS_NUMBER
        )
    )
    {
        cout << MenuPromptCreator::NOT_VALID_COMMAND_MESSAGE << endl;
        free(input);
        returnedCommand = nullptr;
        return;
    }

    /* READ COMMAND ARGUMENT */

    commandArgument = strtok(nullptr, SPACE_DELIMITER);
    // We check if there is a command argument
    if (
        (
                Helper::inArray(
                        command,
                        MenuPromptCreator::COMMANDS_WITH_NO_ARGUMENT,
                        MenuPromptCreator::COMMANDS_WITH_NO_ARGUMENT_NUMBER
                )
                // 'voted' command can be called with or without argument
                && ( strcmp("voted", command) != 0 )
                && commandArgument != nullptr
        )
        ||
        (
                !Helper::inArray(
                        command,
                        MenuPromptCreator::COMMANDS_WITH_NO_ARGUMENT,
                        MenuPromptCreator::COMMANDS_WITH_NO_ARGUMENT_NUMBER
                )
                &&
                commandArgument == nullptr
        )
    )
    {
        cout << MenuPromptCreator::NOT_VALID_COMMAND_MESSAGE << endl;
        free(input);
        returnedCommand = nullptr;
        return;
    }

    /* If the command is insert then there will be many arguments for the creation
     * of the Voter, like in the RegistryReader. So the approach for this command
     * is different. I suppose the order of given arguments is the one I followed
     * in the RegistryReader */
    // Due to lack of time I consider that input for the insert command is right
    if( strcmp("ins", command ) == 0) {
        // We have already parsed id as the second token of the input
        id = commandArgument;

        temp = strtok(nullptr, SPACE_DELIMITER);
        firstName = Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        lastName = Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        age = Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        gender = Helper::copyString(temp);

        temp = strtok(nullptr, SPACE_DELIMITER);
        postalCode = Helper::copyString(temp);

        //cout << "\t" << id << " "  << firstName << " "  << lastName << " "  << age << " "  << gender << " "  << postalCode << endl;

        returnedCommand = (char**) malloc( 7 * sizeof(char*) );
        returnedCommand[0] = Helper::copyString(command);
        returnedCommand[1] = Helper::copyString(id);
        returnedCommand[2] = Helper::copyString(firstName);
        returnedCommand[3] = Helper::copyString(lastName);
        returnedCommand[4] = Helper::copyString(age);
        returnedCommand[5] = Helper::copyString(gender);
        returnedCommand[6] = Helper::copyString(postalCode);
        return;
    }

    // If the user has given a third word then the input is invalid
    possibleUnwantedSecondCommandArgument = strtok(nullptr, SPACE_DELIMITER);
    if (possibleUnwantedSecondCommandArgument != nullptr) {
        cout << MenuPromptCreator::NOT_VALID_COMMAND_MESSAGE << endl;
        free(input);
        returnedCommand = nullptr;
        return;
    }

    returnedCommand = (char**) malloc( 2 * sizeof(char*) );
    returnedCommand[0] = Helper::copyString(command);
    if(commandArgument != nullptr) {
        returnedCommand[1] = Helper::copyString(commandArgument);
        return;
    }

    returnedCommand[1] = nullptr;
}

int MenuPromptCreator::executeInputCommand() {
    const int CONTINUE_EXECUTION = 1;
    const int EXIT = 0;

    char** input = nullptr;
    this->readInput(input);
    while( input == nullptr )  {
        this->readInput(input);
    }

    char* command = Helper::copyString(input[0]);
    char* argument = nullptr;
    char* id;
    char* firstName ;
    char* lastName ;
    int age;
    char gender;
    int postalCode;

    if(strcmp( command, "ins" ) == 0) {
        id = Helper::copyString(input[1]);
        firstName = Helper::copyString(input[2]);
        lastName = Helper::copyString(input[3]);
        age = atoi(input[4]);
        gender = *input[5];
        postalCode = atoi(input[6]);
    } else if (input[1] != nullptr) {
        argument = Helper::copyString(input[1]);
    }

    // lbf key command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[0] ) == 0 ) {
        searchBloomFilterFor(argument);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // lrb key command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[1] ) == 0 ) {
        searchRedBlackTreeFor(argument);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // ins record command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[2] ) == 0 ) {
        insertRecord(id, firstName, lastName, age, gender, postalCode);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // find key command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[3] ) == 0 ) {
        findRecord(argument);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // delete key command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[4] ) == 0 ) {
        deleteRecord(argument);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // vote key command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[5] ) == 0 ) {
        voteOfVoter(argument);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // load fileofkeys command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[6] ) == 0 ) {
        voteFromFile(argument);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // voted postcodes command
    if(
        strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[7] ) == 0
        && argument != nullptr
    ) {
        postalCode = atoi(argument);
        showHowManyHaveVotedInPostalCode(postalCode);
        free(input);
        return CONTINUE_EXECUTION;
    }

    // voted command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[8] ) == 0 ) {
        showVotersThatHaveVoted();
        free(input);
        return CONTINUE_EXECUTION;
    }

    // votedperpc command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[9] ) == 0 ) {
        showPercentageOfHowManyHaveVotedForEveryPostalCode();
        free(input);
        return CONTINUE_EXECUTION;
    }

    // help command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[10] ) == 0 ) {
        showAllOptions();
        free(input);
        return CONTINUE_EXECUTION;
    }

    // exit command
    if( strcmp( command, MenuPromptCreator::AVAILABLE_COMMANDS[11] ) == 0 ) {
        free(input);
        return EXIT;
    }
}

void MenuPromptCreator::create() {
    // Continue execution until executeInputCommand() returns 0 (EXIT signal)
    while( executeInputCommand() ){}
}

void MenuPromptCreator::searchBloomFilterFor(char* key) {
    if( this->votersBloomFilter->check(key) ) {
        cout << "Possibly" << endl;
        return;
    }

    cout << "No" << endl;
}

void MenuPromptCreator::searchRedBlackTreeFor(char* key) {
    Voter* voter = this->votersTree->findVoterWith(key);
    if(voter == nullptr) {
        cout << "There is not RBT record with key: " << key << endl;
        return;
    }

    char* gender;
    if( voter->getGender() == 'F' ) {
        gender = "Female";
    } else {
        gender = "Male";
    };

    char* hasVotedString;
    if( voter->getHasVoted() ) {
        hasVotedString = "Voter HAS voted";
    } else {
        hasVotedString = "Voter has NOT voted";
    };

    cout << "Voter Info:" << endl
        << "Identity Number: " << voter->getId() << endl
        << "First Name: " << voter->getFirstName() << endl
        << "Last Name: " << voter->getLastName() << endl
        << "Age: " << voter->getAge() << endl
        << "Gender: " << gender << endl
        << "Postal Code: " << voter->getPostalCode() << endl
        << "Finally, " << hasVotedString << endl;
}

/* This function searches in the Bloom Filter for the Voter and only if it returns
 * true( which means Possibly ), searches the RBTree for the Voter. This way we
 * don't do unnecessary searches in the RBTree */
void MenuPromptCreator::findRecord(char* key) {
    if( this->votersBloomFilter->check(key) ) {
        searchRedBlackTreeFor(key);
    }

    searchRedBlackTreeFor(key);
}

void MenuPromptCreator::insertRecord(
        char* id,
        char* firstName,
        char* lastName,
        int age,
        char gender,
        int postalCode
)
{
    bool INITIAL_VALUE_FALSE = false;

    Voter* voter = new Voter(
            id,
            firstName,
            lastName,
            age,
            gender,
            postalCode,
            INITIAL_VALUE_FALSE
    );

    // Addition to RBTree
    votersTree->insertVoterToTree(voter);

    // Addition to BloomFilter

    /* If we reach numOfUpdates changes, then we destroy our current BloomFilter
     * and we create a new with BloomFilterFactory */
    this->currentNumberOfUpdates++;
    if(currentNumberOfUpdates == numOfUpdates) {
        free(votersBloomFilter);
        votersBloomFilter = BloomFilterFactory::getFromRedBlackTree(votersTree);
    } else {
        votersBloomFilter->add(voter->getId());
    }

    // Addition to PostalCodesLinkedList

    PostalCodesLinkedListNode* tempPostalCodesNode = postalCodesList
            ->findNodeWithPostalCode(postalCode);

    if(tempPostalCodesNode == nullptr) {
        postalCodesList->addAtStart(postalCode);
        tempPostalCodesNode = postalCodesList->findNodeWithPostalCode(
                postalCode
        );
    }

    tempPostalCodesNode->list->addAtStart(
            votersTree->searchForVoter(voter)
    );
}

void MenuPromptCreator::voteOfVoter(char* key) {
    this->votersTree->voteOfVoterWith(key);
}

void MenuPromptCreator::deleteRecord(char* key) {
    Voter* voter = this->votersTree->findVoterWith(key);
    if(voter == nullptr) {
        cout << "There is no Voter with id: " << key << endl;
        return;
    }

    char* id = Helper::copyString(voter->getId());
    int postalCode = voter->getPostalCode();
    /* We delete the voter from the RBTree and the PostalCodesLinkedList */
    postalCodesList->deleteVoterWithId(postalCode, id);
    votersTree->deleteVoterFromTree(voter);

    /* If we reach numOfUpdates changes, then we destroy our current BloomFilter
     * and we create a new with BloomFilterFactory */
    this->currentNumberOfUpdates--;
    if(currentNumberOfUpdates == numOfUpdates) {
        free(votersBloomFilter);
        votersBloomFilter = BloomFilterFactory::getFromRedBlackTree(votersTree);
        cout << "BloomFilter was rebuilt after " << numOfUpdates << " changes." << endl;
    }
}

void MenuPromptCreator::voteFromFile(char* fileOfKey) {
    if(fileOfKey == nullptr) {
        Helper::handleError(NO_INPUT_FILE_ERROR);
    }

    FILE* inputFile;
    char* line = nullptr;
    size_t length = 0;
    char* id;

    inputFile = fopen(fileOfKey, OPEN_FILE_READ_MODE);
    if(inputFile == nullptr) {
        Helper::handleError(OPEN_FILE_ERROR);
    }

    while( getline(&line, &length, inputFile) != -1 ) {
        id = Helper::copyString(line);
        this->voteOfVoter(id);
    }

    if( ferror(inputFile) ) {
        Helper::handleError(ERROR_IN_READING_FILE);
    }

    free(line);
    fflush(inputFile);
    fclose(inputFile);
}

void MenuPromptCreator::showVotersThatHaveVoted() {
    int votersThatHaveVotedNumber = this->votersTree
            ->getVotersThatHaveVoted();

    cout << votersThatHaveVotedNumber << " voters have voted." << endl;
}

void MenuPromptCreator::showHowManyHaveVotedInPostalCode(int postalCode) {
    int votersThatHaveVotedInPostalCode = postalCodesList
            ->getHowManyVotersHaveVotedInPostalCode(postalCode);

    if(votersThatHaveVotedInPostalCode == -1) {
        cout << "There are no voters in postal code "  << postalCode << endl;
        return;
    }

    cout << votersThatHaveVotedInPostalCode << " have voted in postal code "
        << postalCode << endl;
}

void MenuPromptCreator::showPercentageOfHowManyHaveVotedForEveryPostalCode()
{
    postalCodesList->getPercentageOfVotersThatHaveVotedForEveryPostalCode();
}