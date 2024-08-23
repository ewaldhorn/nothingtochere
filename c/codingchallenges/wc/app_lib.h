#ifndef __APP_LIB_H__
#define __APP_LIB_H__

#include <stdint.h>

// ----------------------------------------------------------- Arguments Errors
#define ALL_GOOD             0
#define NOT_ENOUGH_ARGUMENTS 1

// ---------------------------------------------------------------- File Errors
#define FILE_ERROR -1

// ------------------------------------------------------------------ Functions
int64_t getCharacterCount(char *filename);

#endif
