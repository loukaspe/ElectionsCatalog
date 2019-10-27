#ifndef UNTITLED_HELPER_H
#define UNTITLED_HELPER_H

/* Helper Class contains various function that should not technically be
 * part of other classes and have more general usage */

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>


class Helper {
    public:
        static char* copyString(char*);
        static void handleError(const char*);
        static int findFirstPrimeLargerThan(int);
        static bool inArray(char*, char**, int);
        static char* removeNewLineCharacterFromString(char*);
    private:
        static const char* STRING_COPY_ERROR;
        static const char* STRING_CONCAT_ERROR;
        static bool isPrime(int);
        static bool hasStringNewLineCharacterInTheEnd(char*);
};

#endif //UNTITLED_HELPER_H
