#include "isogram.h"
#include "stdio.h"
#include "strings.h"
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
    for (int i = 0; i < strlen(workPhrase); i++) {
        workPhrase[i] = tolower(workPhrase[i]);
    }

    // debug code
    // printf("Received '%s', converted to '%s'.\n", phrase, workPhrase);

    return false;
}