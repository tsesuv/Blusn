; Debug routines extracted from MBR.asm.
; This is a source fragment: it expects Magic and print to be defined by the
; file that includes or copies it.

debug:
	mov si, Magic
	call print
	jmp $

debugF:
	mov si, Magic
	call print
	call print
	jmp $
