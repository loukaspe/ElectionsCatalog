#include "Voter.h"

Voter::Voter(
        char* id,
        char* firstName,
        char* lastName,
        int age,
        char gender,
        int postalCode,
        bool hasVoted
    ): age(age), gender(gender), postalCode(postalCode), hasVoted(hasVoted) {

    this->id = Helper::copyString(id);
    this->firstName = Helper::copyString(firstName);
    this->lastName = Helper::copyString(lastName);
}

Voter::Voter(
        Voter* voter
    ): age(voter->age),
    gender(voter->gender),
    postalCode(voter->postalCode),
    hasVoted(voter->hasVoted) {

    this->id = Helper::copyString(voter->id);
    this->firstName = Helper::copyString(voter->firstName);
    this->lastName = Helper::copyString(voter->lastName);
}

char* Voter::getId() const {
    return id;
}

char* Voter::getFirstName() const {
    return firstName;
}

char* Voter::getLastName() const {
    return lastName;
}

int Voter::getAge() const {
    return age;
}

char Voter::getGender() const {
    return gender;
}

int Voter::getPostalCode() const {
    return postalCode;
}

bool Voter::getHasVoted() const {
    return this->hasVoted;
}

void Voter::vote() {
    hasVoted = true;
}
