BITS 16
ORG 0x7C00

start:
	cli
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00

	mov si, PartTable
	mov cx, 4
	FindEnt:
		mov al, [si]
		cmp al, 0x80
		je FoundEnt
		
		add si, 16
		loop FindEnt

		jmp NoActPart

	FoundEnt:
		mov ch, [si + 3]
		mov cl, [si + 2]
		mov dh, [si + 1]
		mov dl, [Bootable]

		mov ah, 2
		mov al, 1
		mov bx, 0x7C00
		int 0x13
		jc ReadErr

		msg db 'I try jmp to 7C00!', 0x0D, 0x0A, 0
		mov si, msg
		call print

		jmp 0x0000:0x7C00

		nop

		msg2 db 'End MBR program but not Jumping...', 0
		mov si, msg2
		call print

	NoActPart:
		error1 db 'E1 - No Active Partition', 0
		mov si, error1
		call print
		hlt
		jmp $

	ReadErr:
		error2 db 'E2 - Read Error', 0
		mov si, error2
		call putchar
		hlt
		jmp $

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

Bootable:
	db 0

times 0x1BE - ($ - $$) db 0

PartTable:
	times 64 db 0

times 510 - ($ - $$) db 0

db 0x55
db 0xAA
; ブートセクタ署名
