/* UnSynk Hash Header */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef HASH_H
#define HASH_H

////////////////////////////////////////////////////////

#include "type.h"

////////////////////////////////////////////////////////

const unsigned short int fnv1a16(const str s);
const unsigned int fnv1a(const str s);

////////////////////////////////////////////////////////

const unsigned short int fnv1a16(const str s)
{	unsigned short int result = 0x9DC5;
	int i = 0;

	while(strget(s)[i])
	{	result ^= (unsigned char)strget(s)[i];
		result *= 0x0193;
		i++;
	}

	return result;

}

const unsigned int fnv1a(const str s)
{	unsigned int result = 0x811C9DC5;
	int i = 0;

	while(strget(s)[i])
	{	result ^= (unsigned char)strget(s)[i];
		result *= 0x01000193;
		i++;
	}

	return result;
}

////////////////////////////////////////////////////////

#endif /* hash.h */
