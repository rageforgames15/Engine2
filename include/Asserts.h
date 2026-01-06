#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstdint>

// how i should work with fukcing windows API on fucking linux???
#ifdef WIN32
#include <Windows.h>
#define ASSERTATION_WIN_BUFFER_SIZE 1 << 9

#endif

#ifndef PRODUCT_BUILD

#ifndef WIN32
#define xengine_assert(exrp) \
                    if(!(exrp)) \
                    { \
                      printf("Assertion failed: %s, %d, %s \n", #exrp, __LINE__, __FILE__); \
                      std::abort(); \
                    }
#define xengine_assertmsg(exrp, msg) \
                    if(!(exrp)) \
                    { \
                      printf("Assertion failed: %s, %s, %d, %s \n", #exrp, msg, __LINE__, __FILE__); \
                      std::abort(); \
                    }
#else
// I hope this shit would be work
#define xengine_assert(expr) \
                    if(!(expr)) \
                    { \
                      char buff[ASSERTATION_WIN_BUFFER_SIZE]{}; \
                      snprintf(buff, sizeof(buff), "Assertion failed: %s, %d, %s\n", #expr, __LINE__, __FILE__); \
                      MessageBoxA(NULL, buff, "Assertion failed", MB_OK | MB_ICONERROR); \
                      printf("Assertion failed: %s, %d, %s \n", #expr, __LINE__, __FILE__); \
                      std::abort(); \
                    }

#define xengine_assertmsg(expr, msg) \
                    if(!(expr)) \
                    { \
                      char buff[ASSERTATION_WIN_BUFFER_SIZE]{}; \
                      snprintf(buff, sizeof(buff), "Assertion failed: %s, %s, %d, %s\n", #expr, msg, __LINE__, __FILE__); \
                      MessageBoxA(NULL, buff, "Assertion failed", MB_OK | MB_ICONERROR); \
                      printf("Assertion failed: %s, %d, %s \n", #expr, __LINE__, __FILE__); \
                      std::abort(); \
                    }
#endif
#else

#define xengine_assert(exrp)
#define xengine_assertmsg(exrp, msg)

#endif
