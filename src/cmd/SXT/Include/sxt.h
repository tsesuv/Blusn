/* UnSynk SXT Header */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef SXT_H
#define SXT_H

#ifndef uchar
	#define uchar unsigned char
#endif

////////////////////////////////////////////////////////

#include "str.h"

////////////////////////////////////////////////////////

typedef struct
{	uchar Signature[2];	//	"MZ"

	uchar blp[2];		//	Bytes on Last Page
	uchar page[2];		//	number of PAGEs

	uchar rlcE[2];		//	ReLoCation table Entries

	uchar pgrH[2];		//	Number of ParaGRaphs Header size
	uchar mAlc[2];		//	minimum extra ALloCation paragraphs
	uchar MAlc[2];		//	Maximum extra ALloCation paragraphs

	uchar ssR[2];		//	initial SS Register
	uchar sp[2];		//	initial SP register

	uchar csum[2];		//	CheckSUM

	uchar pc[2];		//	initial PC
	uchar csR[2];		//	initial CS Register

	uchar lfaRlc[2];	//	Long File Address of ReLoCation table

	uchar ov[2];		//	OVerlay number

	uchar rev[8];		//	REserVed

	uchar oem[2];		//	OEM number
	uchar oemI[2];		//	OEM Information

	uchar rv2[2];		//	ReserVed

	uchar lfaNew[4];	//	Long File Address of NEW exe header
} dosMZ;

////////////////////////////////////////////////////////

#endif /* sxt.h */
