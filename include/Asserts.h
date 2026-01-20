#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <source_location>

// how i should work with fukcing windows API on fucking linux???
#ifdef WIN32
#include <Windows.h>
#define ASSERTATION_WIN_BUFFER_SIZE 1 << 9

#endif

#ifndef PRODUCT_BUILD

#ifndef WIN32
#define xengine_assert(expr) \
                    if(!(expr)) \
                    { \
                      printf( \
                        "Assertion failed: %s, %d, %s \n", \
                        #expr, \
                        __LINE__, \
                        std::source_location::current().file_name() \
                      ); \
                      std::abort(); \
                    }
#define xengine_assertmsg(expr, msg) \
                    if(!(expr)) \
                    { \
                      printf( \
                        "Assertion failed: %s, %s, %d, %s \n", \
                        #expr, \
                        msg, \
                        __LINE__, \
                        std::source_location::current().file_name() \
                      ); \
                      std::abort(); \
                    }
#else
// I hope this shit would be work
// Yes it is
#define xengine_assert(expr) \
                    if(!(expr)) \
                    { \
                      char buff[ASSERTATION_WIN_BUFFER_SIZE]{}; \
                      snprintf( \
                        buff, \
                        sizeof(buff), \
                        "Assertion failed: %s, %d, %s\n", \
                        #expr, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      MessageBoxA(NULL, buff, "Assertion failed", MB_OK | MB_ICONERROR); \
                      printf( \
                        "Assertion failed: %s, %d, %s \n", \
                        #expr, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      std::abort(); \
                    }

#define xengine_assertmsg(expr, msg) \
                    if(!(expr)) \
                    { \
                      char buff[ASSERTATION_WIN_BUFFER_SIZE]{}; \
                      snprintf( \
                        buff, \
                        sizeof(buff), \
                        "Assertion failed: %s, %s, %d, %s\n", \
                        #expr, \
                        msg, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      MessageBoxA(NULL, buff, "Assertion failed", MB_OK | MB_ICONERROR); \
                      printf( \
                        "Assertion failed: %s, %d, %s \n",\
                        #expr, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      std::abort(); \
                    }
#endif
#else

#define xengine_assert(expr)
#define xengine_assertmsg(expr, msg)

#endif

#ifdef WIN32
#define xengine_prod_assert(expr) \
                    if(!(expr)) \
                    { \
                      char buff[ASSERTATION_WIN_BUFFER_SIZE]{}; \
                      snprintf( \
                        buff, \
                        sizeof(buff), \
                        "Assertion failed: %s, %d, %s\n", \
                        #expr, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      MessageBoxA(NULL, buff, "Assertion failed", MB_OK | MB_ICONERROR); \
                      printf( \
                        "Assertion failed: %s, %d, %s \n", \
                        #expr, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      std::abort(); \
                    }
#define xengine_prod_assertmsg(expr, msg) \
                    if(!(expr)) \
                    { \
                      char buff[ASSERTATION_WIN_BUFFER_SIZE]{}; \
                      snprintf( \
                        buff, \
                        sizeof(buff), \
                        "Assertion failed: %s, %s, %d, %s\n", \
                        #expr, \
                        msg, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      MessageBoxA(NULL, buff, "Assertion failed", MB_OK | MB_ICONERROR); \
                      printf( \
                        "Assertion failed: %s, %d, %s \n",\
                        #expr, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      std::abort(); \
                    }
#else
#define xengine_prod_assert(expr) \
                    if(!(expr)) \
                    { \
                      printf( \
                        "Assertion failed: %s, %d, %s \n", \
                        #expr, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      std::abort(); \
                    }

#define xengine_prod_assertmsg(expr, msg) \
                    if(!(expr)) \
                    { \
                      printf( \
                        "Assertion failed: %s, %s, %d, %s \n", \
                        #expr, \
                        msg, \
                        __LINE__, \
                        std::source_location::file_name() \
                      ); \
                      std::abort(); \
                    }
#endif
