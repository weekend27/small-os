; naskfunc
; TAB = 4

[FORMAT "WCOFF"]					; ����Ŀ���ļ���ģʽ
[INSTRSET "i486p"]					; 486
[BITS 32]							; ����32λģʽ�õĻ�е����

; ����Ŀ���ļ�����Ϣ

[FILE "naskfunc.nas"]				; Դ�ļ�����Ϣ

		GLOBAL	_io_hlt				; �����а����ĺ�����		
		
; ������ʵ�ʵĺ���

[SECTION .text]						; Ŀ���ļ���д����Щ֮����д����

_io_hlt:							; void io_hlt(void);
		HLT
		RET
		
