;
;   part of this code is origined from
;
;       GOGO-no-coda
;       Copyright (c) 2001,2002,2003 gogo-developer
;

%include "nasm.cfg"

;	486������CPU�܂���FPU�𓋍ڂ��Ă��Ȃ����0
;	����ȊO�͎��̒l�̘_���a
;	PIII�ł͊ۂߌ덷���l�̌ܓ����[�h�ɂ���

;	gogo.h��CPU��`�Ƃ̐���������


MU_tFPU			equ	(1<<0)
MU_tMMX			equ	(1<<1)
MU_t3DN			equ	(1<<2)
MU_tSSE			equ	(1<<3)
MU_tCMOV		equ	(1<<4)
MU_tE3DN		equ	(1<<5)	;/* Athlon�p (extend 3D Now!)*/
MU_tEMMX		equ	(1<<6)  ;/* EMMX=E3DNow!_INT=SSE_INT */
MU_tSSE2		equ (1<<7)
MU_tINTEL		equ	(1<<8)
MU_tAMD			equ	(1<<9)
MU_tCYRIX		equ	(1<<10)
MU_tIDT			equ	(1<<11)
MU_tUNKNOWN		equ	(1<<15)	;�x���_�[��������Ȃ�
MU_tSPC1		equ	(1<<16)	;/* ���ʂȃX�C�b�` */
MU_tSPC2		equ	(1<<17)	;/* �p�r�͌��܂��ĂȂ� */
MU_tCLFLUSH		equ (1<<18)


MU_tFAMILY4		equ	(1<<20)	;/* 486 ���̎��x���_�[����͓��ĂɂȂ�Ȃ� */
MU_tFAMILY5		equ	(1<<21)	;/* 586 (P5, P5-MMX, K6, K6-2, K6-III) */
MU_tFAMILY6		equ	(1<<22)	;/* 686�ȍ~ P-Pro, P-II, P-III, Athlon */

	segment_data
	segment_text

ACflag equ (1<<18)
IDflag equ (1<<21)

proc haveUNITa
		push	ebx
		push	esi
		xor		esi,esi
;		call	near haveFPU		;�`�F�b�N��߂�
;		jnz		near .Lexit
		or		esi,MU_tFPU
		pushfd						;flag�ۑ�
		pushfd
		pop		eax					;eax=flag
		or		eax,ACflag			;eax=flag|ACflag
		push	eax
		popfd						;flag=eax
		pushfd
		pop		eax					;eax=flag
		popfd						;flag����
		test	eax,ACflag			;ACflag�͕ω��������H
		jz		near .Lexit
;486�ȍ~
		pushfd						;flag�ۑ�
		pushfd
		pop		eax					;eax=flag
		or		eax,IDflag			;eax=flag|IDflag
		push	eax
		popfd						;flag=eax
		pushfd
		pop		eax					;eax=flag
		popfd						;flag����
		test	eax,IDflag
;		jz		short .Lexit
		jnz		.L586

	;Cyrix 486CPU check Cyrix �� HP �ɂ�������� by Hash

        xor   ax, ax         ; clear ax
        sahf                 ; clear flags, bit 1 is always 1 in flags
        mov   ax, 5          
        mov   bx, 2
        div   bl             ; do an operation that does not change flags
        lahf                 ; get flags
        cmp   ah, 2          ; check for change in flags
        jne   .L486intel     ; flags changed not Cyrix        
        or    esi,MU_tCYRIX     ; TRUE Cyrix CPU 
        jmp   .L486

.L486intel:
		or		esi,MU_tINTEL
.L486:
		or		esi,MU_tFAMILY4
		jmp		.Lexit

.L586:

;cpuid �� eax,ebx,ecx,edx��j�󂷂�̂Œ��ӁI�I�I

		xor		eax,eax
		cpuid
		cmp		ecx,"ntel"
		jne		.F00
		or		esi,MU_tINTEL
		jmp		.F09
.F00:
		cmp		ecx,"cAMD"
		jne		.F01
		or		esi,MU_tAMD
		jmp		.F09
.F01:
		cmp		ecx,"tead"
		jne		.F02
		or		esi,MU_tCYRIX
		jmp		.F09
.F02:
		cmp		ecx,"auls"
		jne		.F03
		or		esi,MU_tIDT
		jmp		.F09
.F03:
		or		esi,MU_tUNKNOWN
		jmp		.F09
.F09:
		mov		eax,1
		cpuid
		cmp		ah,4
		jne		.F10
		or		esi,MU_tFAMILY4
		jmp		.Lexit
.F10:
		cmp		ah,5
		jne		.F11
		or		esi,MU_tFAMILY5
		jmp		.F19
.F11:
		cmp		ah,6
		jne		.F12
		or		esi,MU_tFAMILY6
		jmp		.F19
.F12:
		or		esi,MU_tFAMILY6	; 7�ȏ��6�ƌ��Ȃ�
.F19:

		;for AMD, IDT
		mov		eax,80000001h
		cpuid
		test	edx,(1 << 31)
		jz		.F20
		or		esi,MU_t3DN
.F20:
		test	edx,(1 << 15)	;CMOVcc
		jz		.F21
;		test	edx,(1 << 16)	;FCMOVcc ;K7����ύX by URURI
;		jz		.F21
		or		esi,MU_tCMOV
.F21:
		test	edx,(1 << 30)	;�g�� 3D Now!
		jz		.F22
		or		esi,MU_tE3DN
.F22:
		test	edx,(1 << 22)	;AMD MMX Ext
		jz		.F23
		or		esi,MU_tEMMX
.F23:
	;Intel�n
		mov		eax,1
		cpuid
		test	edx,(1 << 23)
		jz		.F30
		or		esi,MU_tMMX
.F30:
		test	edx,(1 << 15)		;CMOVcc and FCMOV if FPU=1
		jz		.F31
		or		esi,MU_tCMOV
.F31:
		test	edx,(1 << 25)
		jz		short .F32
		or		esi,MU_tEMMX
		or		esi,MU_tSSE
.F32:
		test	edx,(1 << 26)
		jz		short .F33
		or		esi, MU_tSSE2
.F33:
		test	edx,(1 << 19)
		jz		short .Lexit
		or		esi, MU_tCLFLUSH
.Lexit:
		mov		eax,esi
		pop		esi
		pop		ebx
		ret

;	  in:none
;	 out:ZF FPU����=1, �Ȃ�=0
;	dest:eax

proc haveFPU
		mov		al,1
		fninit
		fnstsw	ax
		cmp		al,0
		jne		short .exit
		sub		esp,4
		fnstcw	word [esp]
		mov		ax,[esp]
		add		esp,4
		and		ax,103Fh
		cmp		ax,3Fh
.exit:
		ret

proc setPIII_round
		;P-III��SSE���m���Ɏl�̌ܓ����[�h��
;		mov		eax,0x1f80	; default mode
		mov		eax,0x9f80	; flush to ZERO mode
		push	eax
		ldmxcsr	[esp]			; setup MXCSR
		pop		eax
		ret

proc setFpuState;(int);
		fldcw		word [esp+4]
		ret

proc getFpuState;(int*);
		mov			eax, [esp+4]
		fnstcw		word [eax]
		ret

proc exchangeFpuState;(int* oldState, int newState);
		mov			eax, [esp+4]
		fnstcw		word [eax]
		fldcw		word [esp+8]
		ret

		end
