#ifndef MY_STDINT_H_
#define MY_STDINT_H_

/*
** MS Visual C++ 2008 and below do not provide the header file <stdint.h>
** That is, we need to define the necessary types ourselves
*/

#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#else
#include <stdint.h>
#endif

#endif /* MY_STDINT_H_ */
