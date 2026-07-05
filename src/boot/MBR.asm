BITS 16
ORG 0x7C00

jmp START

LSEG equ 0x0900
LOFS equ 0x0000

START:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00

	mov ah, 0x02
	mov al, 1
	mov ch, 0
	mov cl, 1
	mov dh, 0

	mov bx, LSEG
	mov es, bx
	mov bx, LOFS
	; es:bx = LSEG:LOFS

	push bx ; save LOFS
	push dx
	xor dx, dx
	xor si, si

	diskRead:
		inc cl ; secter 2+

		int 0x13 ; read to es:bx = LSEG:LOFS
		jc errorDisk ; if err

		mov bx, LOFS ; reset bx to LOFS

		test dx, dx ; if first char
		jz cmp_b_0 ; compare first char
		inc bx ; see next char
		cmp dx, 1 ; else if second char
		jz cmp_b_1 ; compare second char
		inc bx ; see next char
		cmp dx, 2 ; else if third char
		jz cmp_b_2 ; compare third char
		inc bx ; see next char
		cmp dx, 3 ; else if forth char
		jz cmp_b_3 ; compare forth char
		inc bx ; see next char
		cmp dx, 4 ; else if fifth char
		jz cmp_b_4 ; compare fifth char
		inc bx ; see next char
		cmp dx, 5 ; else if sixth char
		jz cmp_b_4 ; compare sixth char
		jmp cmp_b_f ; else

		cmp_b_0:
			cmp bx, 0x51 ; if char = 0x51
			jnz cmp_b_f
			jmp cmp_b_t
		cmp_b_1:
			cmp bx, 0x6B
			jnz cmp_b_f
			jmp cmp_b_t
		cmp_b_2:
			cmp bx, 0x4D
			jnz cmp_b_f
			jmp cmp_b_t
		cmp_b_3:
			cmp bx, 0x48
			jnz cmp_b_f
			jmp cmp_b_t
		cmp_b_4:
			test bl, bl
			jnz cmp_b_f

		cmp_b_t:
			inc dx
			jmp cmp_b_endBlock

		cmp_b_f:
			xor dl, dl
			inc si
			cmp si, 20
			jge errorDisk2
			jmp diskRead

		cmp_b_endBlock:
		cmp dx, 7
		jnz diskRead

		mov si, bx
		add si, 10

	pop dx
	pop bx

	call print

	cli
	hlt

	jmp LSEG:LOFS

errorDisk:
	mov si, err
	call print

	hlt

errorDisk2:
	mov si, err2
	call print

	hlt

print: ; str: si, str is terminated $0
	lodsb

	test al, al
	jz return

	mov ah, 0x0E
	int 0x10

	jmp print

return:
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

err db "MBR: START: int $13: Disk I/O Error", 0x0D, 0x0A, 0x0
err2 db "MBR: START: diskRead: cmp_b_f: Error", 0x0D, 0x0A, 0x0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

times 510 - ($ - $$) db 0

db 0x55
db 0xAA
; ブートセクタ署名
