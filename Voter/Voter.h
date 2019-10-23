#ifndef UNTITLED_VOTER_H
#define UNTITLED_VOTER_H

#include "Helper.h"

class Voter {
public:
        Voter(char*, char*, char*, int, char, int, bool);
        Voter(Voter*);
        void vote();
        char* getId();
    private:
        char* id;
        char* firstName;
        char* lastName;
        int age;
        char gender;
        int postalCode;
        bool hasVoted;
};


#endif //UNTITLED_VOTER_H
