/* UnSynk Type Header */
/* Version: 1.0.4 Pre-Alpha */
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
	VTYPE_MAP,
	VTYPE_NODE
} signature;

typedef struct
{	signature vtype;

	bool IsErr;
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

typedef struct node
{	signature vtype;

	struct node *head;

	str key;
	void *dat;
	unsigned long int dsze; // データサイズ

	struct node *prev;
	struct node *next;
} node; // ある文字列とそれに対応するデータへのポインタ、リストとして使う場合はヘッドと直前・直後のノードへのポインタを持つ
		// nodeという型。あくまで汎用的なノードの型でしかない

typedef struct map // 木構造のmap型
{	signature vtype;

	node *tree;

	struct map *chld; // 子のポインタ

	unsigned long int cap;
	unsigned long int len;
} map; // C++のmapって便利よね

////////////////////////////////////////////////////////

#endif /* type.h */
