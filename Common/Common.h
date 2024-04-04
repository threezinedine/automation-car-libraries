#ifndef _COMMON_INCLUDE_H
#define _COMMON_INCLUDE_H

#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <stdio.h>
#include <stdint.h>

#define TEST_PASSED() printf("[PASSED] %s\n", __FILE__)

#ifdef _DEBUG
#define DEBUG_PRINT(format, ...)            \
    printf("%s:%d - ", __FILE__, __LINE__); \
    printf(format, __VA_ARGS__)

void ResetMallocCount();
void IncreaseMallocCount();
void DecreaseMallocCount();
void AssertMallocCountIsZero();

#define DEBUG_RESET_MALLOC_COUNT() ResetMallocCount()
#define DEBUG_INCREASE_MALLOC_COUNT() IncreaseMallocCount()
#define DEBUG_DECREASE_MALLOC_COUNT() DecreaseMallocCount()
#define DEBUG_ASSERT_MALLOC_COUNT_ZERO() AssertMallocCountIsZero()

#define MALLOC(size) \
    malloc(size);    \
    DEBUG_INCREASE_MALLOC_COUNT()
#define FREE(ptr) \
    free(ptr);    \
    DEBUG_DECREASE_MALLOC_COUNT()
#else
#define MALLOC(size) malloc(size)
#define FREE(ptr) free(ptr)
#endif

#else
// MCU specific headers below

// MCU specific headers above

#define TEST_PASSED()

#ifdef _DEBUG
// Change the Debug print below to match the MCU
#define DEBUG_PRINT(format, ...)
// Change the Debug print above to match the MCU

#define DEBUG_RESET_MALLOC_COUNT()
#define DEBUG_INCREASE_MALLOC_COUNT()
#define DEBUG_DECREASE_MALLOC_COUNT()
#define DEBUG_ASSERT_MALLOC_COUNT_ZERO()
#define MALLOC(size) malloc(size)
#define FREE(ptr) free(ptr)
#endif

#endif

#ifdef _DEBUG
#include <assert.h>

#define DEBUG_STATEMENT(statement) statement
#define DEBUG_IF(condition) \
    if (condition)          \
    {
#define DEBUG_ELSE() \
    }                \
    else             \
    {
#define DEBUG_ENDIF() \
    }
#else
#define DEBUG_STATEMENT(statement)
#define DEBUG_IF(condition)
#define DEBUG_ELSE()
#define DEBUG_ENDIF()
#endif

#endif // _COMMON_INCLUDE_H