/* UnSynk MKUBF Header */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef MKUBF_H
#define MKUBF_H

#ifndef uchar
#define uchar unsigned char
#endif

////////////////////////////////////////////////////////

#include "str.h"

#include <stdlib.h>

////////////////////////////////////////////////////////

#pragma pack(push, 1)

typedef struct
{	/* Header */
	uchar	Signature[4];		//	"UBF\0"
	uchar	MajorV;			//	Major Version
	uchar	MinorV;			//	Minor Version
	uchar	Patch;			//	Patch Version

	uchar	Width;			//	Font width
	uchar	Height;			//	Font height

	uchar	Entries[4];		//	Entries, Little Endian, SbS

	uchar	Mode;			//	Font mode
							//	(e.g., 0: 1Bit Mono, 1: 2Bit Mono, 2: 4Bit Mono, 3: 8Bit Mono...)

	uchar	Reserved[2];	//	Padding: \0\0
	/* Header */



	/* Data */
	uchar	dat[];			//	Font data
} ubf;

#pragma pack(pop)

////////////////////////////////////////////////////////

bool sethead(ubf *out, uchar Signature[4], uchar MajorV, uchar MinorV, uchar Patch, uchar Width, uchar Height, uchar Entries[4], uchar Mode);

////////////////////////////////////////////////////////

bool sethead(ubf *out, uchar Signature[4], uchar MajorV, uchar MinorV, uchar Patch, uchar Width, uchar Height, uchar Entries[4], uchar Mode)
{	if(!out || !Signature || !Entries) return false;

	for(int i = 0; i < 4; i++) out->Signature[i] = Signature[i];
	out->MajorV = MajorV;
	out->MinorV = MinorV;
	out->Patch = Patch;

	out->Width = Width;
	out->Height = Height;

	for(int i = 0; i < 4; i++) out->Entries[i] = Entries[i];

	out->Mode = Mode;

	out->Reserved[0] = 0;
	out->Reserved[1] = 0;

	return true;
}

////////////////////////////////////////////////////////

#endif /* mkubf.h */
