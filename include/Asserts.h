#pragma once
#include <cstdio>
#include <cstdlib>

#ifndef PRODUCT_BUILD

#define xengine_assert(exrp) \
                    if(!(exrp)) \
                    { \
                      printf("Asseration failed: %s, %d, %s \n", #exrp, __LINE__, __FILE__); \
                      std::abort(); \
                    }
#define xengine_assertmsg(exrp, msg) \
                    if(!(exrp)) \
                    { \
                      printf("Asseration failed: %s, %s, %d, %s \n", #exrp, msg, __LINE__, __FILE__); \
                      std::abort(); \
                    }


#else

#define xengine_assert(exrp)
#define xengine_assertmsg(exrp, msg)

#endif

