#ifndef __TBZ_SYS_H_
#define __TBZ_SYS_H_
#ifdef __cplusplus
extern "C" {
#include <cstdint>
using uint = unsigned int;
#else
#include <stdint.h>
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint8_t uchar;
// typedef uint32_t uint;
#ifdef __cplusplus
}
#endif
#endif
