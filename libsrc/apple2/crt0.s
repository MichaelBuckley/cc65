;
; Startup code for cc65 (Apple2 version)
;
; This must be the *first* file on the linker command line
;

	.export		_exit
	.import	   	initlib, donelib
	.import	   	zerobss, push0
	.import		__CODE_LOAD__, __BSS_LOAD__	; Linker generated
	.import		_main

        .include        "zeropage.inc"
	.include	"apple2.inc"

; ------------------------------------------------------------------------
; The executable header

.segment	"EXEHDR"

	.word	__CODE_LOAD__			; Start address
	.word	__BSS_LOAD__ - __CODE_LOAD__	; Size

; ------------------------------------------------------------------------
; Actual code

.code

       	ldx	#zpspace-1
L1:	lda	sp,x
   	sta	zpsave,x	; Save the zero page locations we need
	dex
       	bpl	L1

; Clear the BSS data

	jsr	zerobss

; Save system stuff and setup the stack

       	tsx
       	stx    	spsave 		; Save the system stack ptr

	lda    	#<TOPMEM
	sta	sp
	lda	#>TOPMEM
       	sta	sp+1   		; Set argument stack ptr

; Call module constructors

	jsr	initlib

; Initialize conio stuff

	lda	#$ff
	sta	TEXTTYP

; Set up to use Apple ROM $C000-$CFFF

	;; 	sta    	USEROM

; Pass an empty command line

	jsr	push0  	 	; argc
	jsr	push0  	 	; argv

	ldy	#4     	 	; Argument size
       	jsr    	_main  	 	; call the users code

; Call module destructors. This is also the _exit entry.

_exit:	jsr	donelib

; Restore system stuff

	lda	#$ff  		; Reset text mode
	sta	TEXTTYP

	ldx	spsave
	txs	       		; Restore stack pointer

; Copy back the zero page stuff

	ldx	#zpspace-1
L2:	lda	zpsave,x
	sta	sp,x
	dex
       	bpl	L2

; Reset changed vectors, back to basic

	jmp	RESTOR


.data

zpsave:	.res	zpspace

.bss

spsave:	.res	1
