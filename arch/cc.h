
#ifndef __LWIP_ARCH_CC_H__
#define __LWIP_ARCH_CC_H__

#include <stdint.h>
#include <assert.h>
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif

// Do NOT redefine ssize_t


/* Define platform endianness */
#define BYTE_ORDER LITTLE_ENDIAN

/* Define diagnostic output */
#define LWIP_PLATFORM_DIAG(x) do { } while(0)
#define LWIP_PLATFORM_ASSERT(x) do { assert(0); } while(0)

//#define SYS_LIGHTWEIGHT_PROT 1
typedef uint32_t sys_prot_t;

#endif /* __LWIP_ARCH_CC_H__ */
