/* hash algorithm header */
/* Version:1.0.0 */

#ifndef HASH_H
#define HASH_H

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

static uint16_t fnvla16(const char *p)
{
	#define FNV16_OFFSET_BASIS 0x9DC5
	#define FNV_16_PRIME 0x0193
	uint16_t result = FNV16_OFFSET_BASIS;
	int i = 0;
	while(*(p + i))
	{
		result ^= (uint8_t)*(p + i);
		result *= FNV_16_PRIME;
		i++;
	}
	return result;

}

static uint32_t fnvla(const char *p)
{
	#define FNV_OFFSET_BASIS 0x811C9DC5
	#define FNV_32_PRIME 0x01000193
	uint32_t result = FNV_OFFSET_BASIS;
	int i = 0;
	while(*(p + i))
	{
		result ^= (uint8_t)*(p + i);
		result *= FNV_32_PRIME;
		i++;
	}
	return result;
}

static uint256_t sha256(const char *p)
{

	size_t len = strlen(p);

	/* パディング後の長さ計算 */
	size_t new_len = len + 1;  /* 0x80を追加 */
	while ((new_len + 8) % 64 != 0)
	{
		new_len++;
	}

	/* メッセージバッファの確保（パディング＋8バイト長分） */
	unsigned char *msg = (unsigned char *)malloc(new_len + 8);
	if (msg == NULL)
	{
		/* メモリ確保に失敗した場合は、全メンバ0のハッシュを返す */
		uint256_t zero = { 0, 0, 0, 0, 0, 0, 0, 0 };
		return zero;
	}

	/* 元メッセージのコピー */
	memcpy(msg, p, len);
	/* 0x80の付加 */
	msg[len] = 0x80;
	/* 残りを0でパディング */
	memset(msg + len + 1, 0, new_len - len - 1);

	/* 元メッセージ長をビット単位で表現（ここでは最大4GBまで対応） */
	unsigned int bit_len = (unsigned int)len * 8;
	/* 上位32ビットは0として格納 */
	msg[new_len + 0] = 0;
	msg[new_len + 1] = 0;
	msg[new_len + 2] = 0;
	msg[new_len + 3] = 0;
	/* 下位32ビットをビッグエンディアンで格納 */
	msg[new_len + 4] = (unsigned char)((bit_len >> 24) & 0xff);
	msg[new_len + 5] = (unsigned char)((bit_len >> 16) & 0xff);
	msg[new_len + 6] = (unsigned char)((bit_len >> 8) & 0xff);
	msg[new_len + 7] = (unsigned char)(bit_len & 0xff);

	/* 初期ハッシュ値（SHA256規定） */
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

	/* SHA256定数 */
	static const uint32_t k[64] =
	{
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	size_t total_len = new_len + 8;
	size_t i, j;
	for (i = 0; i < total_len; i += 64)
	{
		uint32_t w[64];
		/* 最初の16ワードを設定（ビッグエンディアン変換） */
		for (j = 0; j < 16; j++)
		{
			w[j] = ((uint32_t)msg[i + j * 4 + 0] << 24) |
				   ((uint32_t)msg[i + j * 4 + 1] << 16) |
				   ((uint32_t)msg[i + j * 4 + 2] << 8)  |
				   ((uint32_t)msg[i + j * 4 + 3]);
		}
		/* 16以降のワードを拡張計算 */
		for (j = 16; j < 64; j++)
		{
			uint32_t s0 = RRT(w[j - 15], 7) ^ RRT(w[j - 15], 18) ^ (w[j - 15] >> 3);
			uint32_t s1 = RRT(w[j - 2], 17) ^ RRT(w[j - 2], 19) ^ (w[j - 2] >> 10);
			w[j] = w[j - 16] + s0 + w[j - 7] + s1;
		}

		/* 作業用変数の初期化 */
		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;
		uint32_t e = h4;
		uint32_t f = h5;
		uint32_t g = h6;
		uint32_t h = h7;

		/* 圧縮処理メインループ */
		for (j = 0; j < 64; j++)
		{
			uint32_t S1 = RRT(e, 6) ^ RRT(e, 11) ^ RRT(e, 25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = h + S1 + ch + k[j] + w[j];
			uint32_t S0 = RRT(a, 2) ^ RRT(a, 13) ^ RRT(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = S0 + maj;

			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}

		/* ハッシュ値の更新 */
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		h4 += e;
		h5 += f;
		h6 += g;
		h7 += h;
	}

	free(msg);

	/* 結果をuint256_tに格納して返却 */
	uint256_t result;
	result.a = h0;
	result.b = h1;
	result.c = h2;
	result.d = h3;
	result.e = h4;
	result.f = h5;
	result.g = h6;
	result.h = h7;
	return result;
}

#endif
