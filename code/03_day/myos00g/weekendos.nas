; weekend-os
; TAB=4

		ORG		0xC200			; 这就是程序要被装载的地方

		MOV		AL,0x13			; VGA显卡，320*200*8位彩色
		MOV		AH,0x00
		INT		0x10
fin:
		HLT
		JMP 	fin