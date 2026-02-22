/* UnSynk SXT Header */
/* Version: 1.0.0 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef SXT_H
#define SXT_H

#ifndef uchar
	#define uchar unsigned char
#endif

////////////////////////////////////////////////////////

////////////////////////////////////////////////////////

#pragma pack(push, 1)

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

#pragma pack(pop)

#pragma pack(push, 1)

	typedef struct
	{	uchar Signature[4];	//	"BXO\0"
		uchar Sections[2];	//	number of Section
	} bxo;

#pragma pack(pop)

////////////////////////////////////////////////////////

bool wrMzH(dosMZ *mz, uchar blp[2], uchar page[2], uchar rlcE[2], uchar pgrH[2], uchar mAlc[2], uchar MAlc[2], uchar ssR[2], uchar sp[2], uchar csum[2], uchar pc[2], uchar csR[2], uchar lfaRlc[2], uchar ov[2], uchar oem[2], uchar oemI[2], uchar lfaNew[4]);

////////////////////////////////////////////////////////

bool wrMzH(dosMZ *mz, uchar blp[2], uchar page[2], uchar rlcE[2], uchar pgrH[2], uchar mAlc[2], uchar MAlc[2], uchar ssR[2], uchar sp[2], uchar csum[2], uchar pc[2], uchar csR[2], uchar lfaRlc[2], uchar ov[2], uchar oem[2], uchar oemI[2], uchar lfaNew[4])
{	mz->Signature[0] = 'M';
	mz->Signature[1] = 'Z';

	for(int i = 0; i < 2; i++)
	{	mz->blp[i] = blp[i];
		mz->page[i] = page[i];
		mz->rlcE[i] = rlcE[i];
		mz->pgrH[i] = pgrH[i];
		mz->mAlc[i] = mAlc[i];
		mz->MAlc[i] = MAlc[i];
		mz->ssR[i] = ssR[i];
		mz->sp[i] = sp[i];
		mz->csum[i] = csum[i];
		mz->pc[i] = pc[i];
		mz->csR[i] = csR[i];
		mz->lfaRlc[i] = lfaRlc[i];
		mz->ov[i] = ov[i];
		mz->oem[i] = oem[i];
		mz->oemI[i] = oemI[i];
		mz->rv2[i] = 0;
	}

	for(int i = 0; i < 8; i++) mz->rev[i] = 0;

	for(int i = 0; i < 4; i++) mz->lfaNew[i] = lfaNew[i];

	return true;
}

////////////////////////////////////////////////////////

#endif /* sxt.h */
