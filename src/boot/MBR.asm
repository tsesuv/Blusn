BITS 16
ORG 0x7C00


start:
	cli
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00

	msg db 'I try jmp to 7C00!', 0x0D, 0x0A, 0
	mov si, msg
	call print

	jmp 0x0000:0x7C00

	nop

	msg2 db 'End MBR program but not Jumping...', 0x0D, 0x0A, 0
	mov si, msg2
	call print

ReadErr:
	err1 db 'E1 - Read Error', 0x0D, 0x0A, 0
	ReadErrMarker:
		mov si, err1
		call print
		jmp ReadErrMarker

putchar:
	mov ah, 0x0E
	mov bx, 7
	int 0x10
	ret

print:
	mov ah, 0x0E
	mov bx, 7
	print_loop:
		mov al, [si]
		int 0x10
		inc si
		cmp al, 0
		jne print_loop
	ret

times 510 - ($ - $$) db 0

db 0x55
db 0xAA
; ブートセクタ署名
