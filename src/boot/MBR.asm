; Dateiname: MBR

BITS 16														; 16Bit-Modus
ORG 0x7C00													; Adresse laden für Bootloader

start:
	; Initialisierung des Stapel
	cli														; Deaktivieren des Interrupt
	xor ax, ax												; Klar des AX-Register
	mov sp, 0x7C00											; Setzen des Stapel Zeiger
	mov ss, ax												; 0 Setzen für Stapel Segment
	sti														; Aktivieren des Interrupt

	; "Hello, World!" を画面に表示
	mov si, msg												; メッセージのアドレスをSIにロード

print_char:
	lodsb													; SIが指す文字をALにロード
	or al, al												; ALが0か確認
	jz hang													; 0なら終了
	mov ah, 0x0E											; BIOSのテキスト出力機能
	int 0x10												; BIOS割り込み
	jmp print_char											; 次の文字へ

hang:
	hlt														; CPUを停止
	jmp hang												; 無限ループ

msg db 'Willcommen bei Blusn Bootloader!', 0x0D, 0x0A, 0	; 表示するメッセージ (0で終了)

times 510-($-$$) db 0		; セクタサイズ(512バイト)にパディング
dw 0xAA55					; ブートセクタ署名
