#pragma once
#include <cstdio>
#include <cstdlib>

#ifndef PRODUCT_BUILD

#define xengine_assert(exrp) \
                    if(exrp) \
                    { \
                      printf("Asseration failed: %s \n", #exrp); \
                      std::abort(); \
                    }
#else

#define xengine_assert(exrp)

#endif

