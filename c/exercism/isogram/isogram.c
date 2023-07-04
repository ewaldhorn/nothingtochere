#include "isogram.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

bool is_isogram(const char phrase[])
{

    if (phrase == NULL)
    {
        return false;
    }

    // now compare as lowercase, to make things easier
    for (long unsigned int i = 0; i < strlen(phrase); i++)
    {
        char tmp = tolower(phrase[i]);
        if (tmp != '-' && tmp != ' ')
        {
            for (long unsigned int j = i + 1; j < strlen(phrase); j++)
            {
                if (tmp == tolower(phrase[j]))
                {
                    return false;
                }
            }
        }
    }

    return true;
}
