#include "person.h"

person Combine(person left, person right) {
    person result;

    result.id = left.id;
    result.score = left.score + right.score;

    return result;
}