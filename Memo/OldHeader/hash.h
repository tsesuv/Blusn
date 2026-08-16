/* UnSynk hash algorithm header */
/* Version:1.0.0 */

#ifndef HASH_H
#define HASH_H

#define FNV16_OFFSET_BASIS 0x9DC5
#define FNV_16_PRIME 0x0193

#define FNV_OFFSET_BASIS 0x811C9DC5
#define FNV_32_PRIME 0x01000193

#define RRT(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define RSH(x, n) ((x) >> (n))

/* SHA256の論理関数 */
#define CH(x,y,z) (((x) & (y)) ^ ((~(x)) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define BSIG0(x) (RRT((x), 2) ^ RRT((x), 13) ^ RRT((x), 22))
#define BSIG1(x) (RRT((x), 6) ^ RRT((x), 11) ^ RRT((x), 25))
#define SSIG0(x) (RRT((x), 7) ^ RRT((x), 18) ^ RSH((x), 3))
#define SSIG1(x) (RRT((x), 17) ^ RRT((x), 19) ^ RSH((x), 10))

#include <stdlib.h>
#include <string.h>
#include "type.h"

static uint16_t fnvla16(const char *p);
static uint32_t fnvla(const char *p);
static uint256_t sha256(const char *p);

#endif
