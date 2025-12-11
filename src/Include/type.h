/* UnSynk Type Header */
/* Version: 1.0.0 Pre-alpha */
/* Created by UnSynk, tsesuv notsel */

#ifndef TYPE_H
#define TYPE_H

typedef enum {false, true} bool;

typedef enum {VTYPE_STR, VTYPE_SINT, VTYPE_USINT, VTYPE_MAP, VTYPE_NODE} signature;

typedef struct
{
	bool IsErr;
	signed int code;
} errno;

typedef struct
{
	signature vtype; // 変数の型を保持する変数
	char *dat; // data
	unsigned long int len; // 長さ
	unsigned long int cap; // キャパシティ
	int encode; // 文字エンコードも保持したいよなぁ。0でASCII、とか。やり方わからんがな。
} str;

typedef struct
{
	signature vtype;
	signed int dat;
	unsigned long int len; // 桁数
} sint;

typedef struct
{
	signature vtype;
	unsigned int dat;
	unsigned long int len;
} usint;

typedef struct
{
	signature vtype;
	node **kets;
} map;

typedef struct
{
	signature vtype;
	str *key;
	void *dat;
	struct map *left;
	struct map *right;
	unsigned long int height;
} node;

#endif
