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

	mov [Drive], dl

	mov bx, LSEG
	mov es, bx
	mov bx, LOFS
	; es:bx = LSEG:LOFS

	push bx ; save LOFS
	push dx
	xor dx, dx
	xor si, si

	mov di, Magic

	diskRead:
		cmp si, 20
		jg errorDisk2

		mov ah, 0x02
		mov al, 1
		mov dh, 0
		mov cx, 2
		add cx, si
		mov ch, 0
		mov dl, [Drive]

		mov bx, 0x7E00
		int 0x13 ; read to es:bx = LSEG:0x7E00
		jc errorDisk ; if err

		push si

		mov si, bx
		mov di, Magic
		mov cx, 6
		call scmp

		pop si

		cmp ax, 6
		je diskReadEnd

		inc si
		jmp diskRead

	diskReadEnd:

	mov si, bx
	add si, 16 ; volumeLabel offset in the HtFS header

	pop dx
	pop bx

	push ds
	push es
	pop ds
	call print
	pop ds

	cli
	hlt

	jmp LSEG:LOFS

errorDisk:
	mov si, err
	call print

	jmp $

errorDisk2:
	mov si, err2
	call print

	jmp $

print: ; str: si, str is terminated $0
	push si
	push ax

	printBlock:
		lodsb

		test al, al
		jz printBlockEnd

		mov ah, 0x0E
		int 0x10

		jmp printBlock

	printBlockEnd:

	pop ax
	pop si

	ret

scmp: ; src: es:si, cmp: ds:di, cnt: cx, result: ax = matched byte count
	push si
	push di
	push bx
	push dx
	push cx

	xor ax, ax

	scmpBlock:
		jcxz scmpBlockEnd

		mov bl, [es:si]
		mov dl, [di]

		inc si
		inc di
		dec cx

		cmp bl, dl
		jne scmpBlock

		inc ax

		jmp scmpBlock

	scmpBlockEnd:

	pop cx
	pop dx
	pop bx
	pop di
	pop si

	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

err db "MBR: START: int $13: Disk I/O Error", 0x0D, 0x0A, 0x0
err2 db "MBR: START: diskRead: Error: Over 20", 0x0D, 0x0A, 0x0
Magic db "HtFS", 0x0, 0x0
Drive db 0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

times 510 - ($ - $$) db 0

db 0x55
db 0xAA
; ブートセクタ署名
