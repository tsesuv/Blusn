BITS 16
ORG 0x7C00

start:
	mov ah, 0x0E
	mov al, 'B'
	mov bx, 0x0007
	int 0x10

	hlt
	jmp $

times 510 - ($ - $$) db 0

db 0x55
db 0xAA
