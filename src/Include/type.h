/* UnSynk Type Header */
/* Version: 1.0.2 Pre-Alpha */
/* Created by UnSynk, tsesuv notsel */

#ifdef errno
#undef errno

#endif

#ifndef TYPE_H
#define TYPE_H

////////////////////////////////////////////////////////

typedef enum
{	false,
	true
} bool;

typedef enum
{	VTYPE_ERR,
	VTYPE_STR,
	VTYPE_SINT,
	VTYPE_USINT,
	VTYPE_FRAC,
	VTYPE_ANY,
	VTYPE_MAP
} signature;

typedef struct
{	bool IsErr;
	signed int code;
} errno;

typedef struct
{	signature vtype; // 変数の型を保持する変数
	char *dat; // data
	unsigned long int len; // 長さ
	unsigned long int cap; // キャパシティ
	int encode; // 文字エンコードも保持したいよなぁ。0でASCII、とか。やり方わからんがな。
} str;

typedef struct
{	signature vtype;
	signed int sign;
	unsigned int dat;
	unsigned long int len; // 桁数
} sint;

typedef struct
{	signature vtype;
	unsigned int dat;
	unsigned long int len;
} usint;

typedef struct
{	signature vtype;
	signed int sign;
	usint denom;
	usint numer;
} frac; // 分母、分子をそれぞれ持つ「有理数型」。但し一切の実装が進んでない・・・

typedef struct
{	signature vtype;
	void *dat;
	unsigned int dsize;
} any; // 一応作ってある安全版void型・・・用途が一切思いつかないがな

typedef struct
{	signature vtype;
	str key;
	any dat;
	unsigned long int cap;
	unsigned long int len;
} map; // C++のmapって便利よね

////////////////////////////////////////////////////////

#endif /* type.h */
