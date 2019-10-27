#include "Helper.h"

const char* Helper::STRING_COPY_ERROR = "ERROR: Something went wrong with Helper Copy\n";
const char* Helper::STRING_CONCAT_ERROR = "ERROR: Something went wrong with Helper Concat\n";

void Helper::handleError(const char * errorMessage) {
    fprintf(
            stderr,
            "%s",
            errorMessage
    );
    exit(EXIT_FAILURE);
}


char* Helper::copyString(char* source) {
    char* destination;
    int stringLength = strlen(source);

    destination = (char*) malloc(
            stringLength * sizeof(char)
    );

    if(destination == nullptr) {
        fprintf(stderr, "%s",STRING_COPY_ERROR);
        exit(EXIT_FAILURE);
    }

    strcpy(destination, source);
    return destination;
}

/* Very Simple and Inefficient function. Did not give enough attention to this
 * part of the Assessment due to lack of time */
int Helper::findFirstPrimeLargerThan(int n) {
    int i = n;
    while(1) {
        if( isPrime(i) ) {
            return i;
        }

        i++;
    }
}

/* Source: https://codereview.stackexchange.com/questions/71212/find-smallest-prime-number-greater-than-given-n*/
bool Helper::isPrime(int n) {
    int i,root;

    if(n == 1) {
        return true;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    root = (int) sqrt(n);

    for (i = 5; i <= root; i += 6)
    {
        if ( n % i == 0 ) {
            return false;
        }
    }

    for (i = 7; i <= root; i += 6)
    {
        if (n%i == 0) {
            return false;
        }
    }

    return true;
}

bool Helper::inArray(char* needle, char** haystack, int haystackSize) {
    int i;
    for( i = 0; i < haystackSize; i++) {
        if( strcmp( needle, haystack[i] ) == 0 ) {
            return true;
        }
    }

    return false;
}

bool Helper::hasStringNewLineCharacterInTheEnd(char* string) {
    int length = strlen(string);
    return string[length - 1] == '\n';
}

char* Helper::removeNewLineCharacterFromString(char* string) {
    if( hasStringNewLineCharacterInTheEnd(string) ) {
        int length = strlen(string);
        char* stringWithoutNewLine = (char*) malloc(
                length * sizeof(char)
        );

        int i;
        for( i = 0; i < length; i++) {
            if(string[i] == '\n') {
                stringWithoutNewLine[i] = '\0';
                continue;
            }

            stringWithoutNewLine[i] = string[i];
        }

        return stringWithoutNewLine;
    }

    return string;
}