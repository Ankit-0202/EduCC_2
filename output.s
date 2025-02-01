	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0
	.globl	_factorial                      ; -- Begin function factorial
	.p2align	2
_factorial:                             ; @factorial
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #48
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 48
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	cmp	w0, #1
	str	w0, [sp, #12]
	b.gt	LBB0_2
; %bb.1:
	mov	w0, #1                          ; =0x1
	b	LBB0_3
LBB0_2:                                 ; %else
	ldr	w19, [sp, #12]
	sub	w0, w19, #1
	bl	_factorial
	mul	w0, w19, w0
LBB0_3:                                 ; %common.ret
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_add                            ; -- Begin function add
	.p2align	2
_add:                                   ; @add
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	stp	w1, w0, [sp, #8]
	add	w0, w0, w1
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:                                ; %entry
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	.cfi_def_cfa_offset 32
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w8, #5                          ; =0x5
	mov	w0, #5                          ; =0x5
	str	w8, [sp, #12]
	bl	_factorial
	mov	w1, w0
	ldr	w0, [sp, #12]
	str	w1, [sp, #8]
	bl	_add
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	mov	w8, w0
	cmp	w0, #100
	str	w8, [sp, #4]
	csel	w0, w0, wzr, gt
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
