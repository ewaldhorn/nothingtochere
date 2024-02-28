#ifndef PERSON_H 
#define PERSON_H

typedef struct personStruct {
    int id;
    int score;
} person;

person Combine(person left, person right);

#endif