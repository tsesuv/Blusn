/* Type header */
/* Version:1.1.0 Pre-Alpha */

#ifndef TYPE_H
#define TYPE_H

#ifndef bool
#define bool bool_t
#endif

typedef enum {FALSE, TRUE} bool_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct
{
	int8_t a;
	uint8_t b;
} word_t;

typedef struct
{
	uint8_t a;
	uint8_t b;
} uword_t;

typedef struct
{
	int8_t a;
	uint8_t b;
	uint8_t c;
} int24_t;

typedef struct
{
	uint8_t a;
	uint8_t b;
	uint8_t c;
} uint24_t;

typedef struct
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	uint32_t e;
	uint32_t f;
	uint32_t g;
	uint32_t h;
} uint256_t;

#endif
