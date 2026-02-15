; BIOS Binary
; BIOS ADDR: 0xE000:0x0000

; 0xE0000:
	; Call number 0:
	; Call number 1: Exit, Exit code: AL
	; Call number 2: Write char, char code: AL
	; Call number 3: Read char, regist register: AL
	; Call number 4: Write Disk, Sector count: AL, Cylinder: CH, Sector: CL, Head: DH, Drive number: DL, Buffer: ES:BX
	; Call number 5: Read Disk, Sector count: AL, Cylinder: CH, Sector: CL, Head: DH, Drive number: DL, Buffer: ES:BX
