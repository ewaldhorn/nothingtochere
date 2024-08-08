# Preprocessor Macros

`#define`: Defines a macro.
Example: `#define PI 3.14`

`#undef`: Undefines a previously defined macro.
Example: `#undef PI`

`#include`: Includes a file.
Example: `#include <stdio.h>`

`#if`: Conditional compilation directive.
Example: `#if DEBUG`

`#ifdef`: Checks if a macro is defined.
Example: `#ifdef DEBUG`

`#ifndef`: Checks if a macro is not defined.
Example: `#ifndef DEBUG`

`#elif`: Else if condition for #if.
Example: `#elif DEBUG == 2`

`#else`: Else condition for #if.
Example: `#else`

`#endif`: Ends a `#if`, `#ifdef`, or `#ifndef` block.
Example: `#endif`

`#error`: Generates a compiler error with a specified message.
Example: `#error "Error message"`

`#pragma`: Specifies diverse behavior depending on compiler.
Example: `#pragma once`

`#line`: Specifies the original line number and filename.
Example: `#line 20 "myfile.cpp"`

`#warning` (GCC): Generates a compiler warning with a specified message (GCC).
Example: `#warning "Warning message"`
