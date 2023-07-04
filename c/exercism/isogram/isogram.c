#include "isogram.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

int main() 
{
    char phrase[] = "loOP";
    printf("%12s is an isogram %d.\n", phrase, is_isogram(phrase)); // no

    char phraseTwo[] = "lumBErjack";
    printf("%12s is an isogram %d.\n", phraseTwo, is_isogram(phraseTwo)); // yes

    char phraseThree[] = "raCEcar";
    printf("%12s is an isogram %d.\n", phraseThree, is_isogram(phraseThree)); // no

    char phraseFour[] = "Six-Year-Old";
    printf("%12s is an isogram %d.\n", phraseFour, is_isogram(phraseFour)); // yes

    return 0;
}

bool is_isogram(const char phrase[])
{
    if (strlen(phrase) == 0)
    {
        return false;
    }

    // make a copy of the phrase
    char workPhrase[strlen(phrase)+1];
    strcpy(workPhrase, phrase);

    // now make it lowercase, to make things easier
    for (long unsigned int i = 0; i < strlen(workPhrase); i++) {
        workPhrase[i] = tolower(workPhrase[i]);
    }

    bool state = true;

    return state;
}

// bool is_isogram(const char phrase[])
// {
//     if (strlen(phrase) == 0)
//     {
//         return false;
//     }

//     // make a copy of the phrase
//     char workPhrase[strlen(phrase)+1];
//     strcpy(workPhrase, phrase);

//     // now make it lowercase, to make things easier
//     for (long unsigned int i = 0; i < strlen(workPhrase); i++) {
//         workPhrase[i] = tolower(workPhrase[i]);
//     }

//     bool state = true;

//     for (long unsigned int i = 0; i < strlen(workPhrase); i++) {
//         if (workPhrase[i] != '-' && workPhrase[i] != ' ')
//         {
//             // we don't have a hyphen or a space
//             for (long unsigned int j = i+1; j < strlen(workPhrase); j++) {
//                 if (workPhrase[i] == workPhrase[j])
//                 {
//                     state = false;
//                     break;
//                 }
//             }
//         }
//     }

//     return state;
// }