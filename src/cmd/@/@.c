/* UnSynk @ Compiler */
/* Build: 20260530XXXX */
/* Created by UnSynk, tsesuv notsel */

#include "Include/@.h"
#include "Include/token.h"

FILE *infile;
FILE *outfile;

int main(int ac, char **av)
{	if(ac == 1)
	{	return 0;
	}

	uint lenth = catlen((byte **)av, ac);
	byte *ag = (byte *)malloc((lenth + ac) * sizeof(byte));
	bytecat(ag, (byte **)av, ac);

	printf("Length: %d\n", lenth);
	for(uint i = 0; i < lenth; i++) printf("%c ($%02X)\n", ag[i], ag[i]);

	uint placeInName = 0;
	uint placeOutName = 0;
	bit flag[2];
	set(&flag[0], 0); // Detect & geted /i: option
	set(&flag[1], 0); // Detect & geted /o: option

	// 引数チェック部分
	for(uint i = 0; i < lenth; i++)
	{	if(get(cmpe(ag + i, "/i:", 3)) && !get(flag[0]))
		{	placeInName = i + 3;
			set(&flag[0], 1);
			printf("Detect /i: %d (p: %d, %s)\n", i, placeInName, &ag[placeInName]);
		}
		if(get(cmpe(ag + i, "/o:", 3)) && !get(flag[1]))
		{	placeOutName = i + 3;
			set(&flag[1], 1);
			printf("Detect /o: %d (p: %d, %s)\n", i, placeOutName, &ag[placeOutName]);
		}
	}

	// ファイル名獲得（in）
	if(get(flag[0]))
	{	uint letterInName = lenn(ag + placeInName);

		// 領域確保
		byte *inname = (byte *)malloc(letterInName * sizeof(byte));
		// 名前を引数からコピー
		bytesete(inname, ag, 0, placeInName, letterInName, '_', "/\\:;");
		printf("fname: %s, name size: %d\n", inname, letterInName);
		infile = fopen(inname, "rb"); // ファイルオープン

		if(!infile) // ファイルがなかった場合
		{	printf("[ E ] @: main: fopen: Can't open file: %s\n", inname);
		} else // ファイルが存在する場合
		{	printf("[ D ] @: main: Cat file: %s\n", inname);

			// ファイルサイズ獲得
			uint fsize = getfsize(infile) + 1;
			byte *text = (byte *)malloc(fsize * sizeof(byte));
			// ファイルの内容をコピー
			text[fread(text, 1, fsize - 1, infile)] = 0;
			fclose(infile);

			printf("READED TEXT (VALUE):\n%s\n", text);

			// Token関連のテスト
			Token t = tknnew();
			tknset(&t, TK_IDR, "MDL");
			printf("Token: %s(%s)\n", type2str(t.type), t.dat);
			tknset(&t, TK_STR, "Hola");
			printf("Token: %s(%s)\n", type2str(t.type), t.dat);

			tkList *list = tklnew(NULL);
			tklset(list, t);
			tknset(&t, TK_ENT, "");
			tklset(list, t);

			printf("Tokens: %s, %s\n", list->head, list->head->next);

			// tokenalizer(&list, text);

			tklfree(list);

			tknfree(&t);

			free(text);
		}

		free(inname);
	}
	// ファイル名獲得（out）
	if(get(flag[1]))
	{	uint letterOutName = lenn(ag + placeOutName);

		byte *outname = (byte *)malloc(letterOutName * sizeof(byte));
		bytesete(outname, ag, 0, placeOutName, letterOutName, '_', "/\\:;");
		printf("fname: %s, name size: %d\n", outname, letterOutName);
		outfile = fopen(outname, "wb");

		if(outfile)
		{	uint fsize = 1;
			byte *binary = (byte *)malloc(fsize * sizeof(byte));

			fwrite(binary, sizeof(byte), fsize, outfile);
			fclose(outfile);

			free(binary);

		}

		free(outname);
	}

	free(ag);

	return 0;
}
