/**
 */
#ifndef STACKTRACER_H
#define STACKTRACER_H

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Includes - my shared libraries
////////////////////////////////////////////////////////////////////////////////
#include <headers/error.h>

////////////////////////////////////////////////////////////////////////////////
// Includes - posix
////////////////////////////////////////////////////////////////////////////////

#if defined(unix) || defined(__unix) || defined(__unix__) || (defined (__APPLE__) && defined (__MACH__)) // Unix (Linux, *BSD, Mac OS X)
#include <execinfo.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define StackTracer_Max_Signal 16

#define _TL StackTracer_Line(__FILE__, __func__, __LINE__); 

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Constructs
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////
extern void StackTracer_Init();
extern void StackTracer_Catch_Signal(const int signal);
extern int  StackTracer_Get_MaxTrace();
extern void StackTracer_Line(const char *file, const char *func, const int line);
// void stackTracer_Set_MaxTrace(const int maxTrace);



#ifdef __cplusplus
}
#endif
#endif // STACKTRACER_H

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////





