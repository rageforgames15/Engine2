#pragma once
#define ZEROBIT(x) 0 << x
#define TOBIT(x) 1 << x
#define GETBIT(x, bit) x & bit
#define TOBITFROMEXISTING(x, bit) x | bit