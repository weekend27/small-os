; weekend-os
; TAB=4

CYLS	EQU		10				; cylinders,定义读取柱面的个数
		ORG		0x7c00			; 程序的装载地址，ORG是来自于origin

; 以下的记述用于标准FAT12格式的软盘

		JMP		entry			; 类似于C里面的goto语句
		DB		0x90
		DB		"HELLOIPL"		; 启动区的名称可以是任意字符串（8字节就OK）
		DW		512				; 每个扇区sector的大小，必须为512个字节
		DB		1				; 每个簇cluster的大小，必须为1个扇区
		DW		1				; FAT的起始位置，一般从第一个扇区开始
		DB		2				; FAT的个数，必须为2个
		DW		224				; 根目录的大小，一般设为224项
		DW		2880			; 该磁盘的大小，必须是2880个扇区
		DB		0xf0			; 磁盘的种类，必须是0xf0
		DW		9				; FAT的长度，必须是9个扇区
		DW		18				; 1个磁道track包含的扇区，必须是18个扇区
		DW		2				; 磁头数，必须是2个
		DD		0				; 不使用分区，所以是0咯
		DD		2880			; 重写一次磁盘的大小
		DB		0,0,0x29		; 意义不明，固定。（表示不懂）
		DD		0xffffffff		; 可能是卷标号码，不确定
		DB		"WEEKEND-OS "	; 磁盘的名称（11个字节），后面不够的补上空格了
		DB		"FAT12   "		; 磁盘格式名称（8个字节），不够的补上空格
		RESB	18				; 先空出18个空格

; 程序核心

entry:
		MOV		AX,0			; 初始化寄存器
		MOV		SS,AX
		MOV		SP,0x7c00
		MOV		DS,AX

; 读磁盘

		MOV 	AX,0x0820
		MOV		ES,AX
		MOV		CH,0			; 柱面0
		MOV		DH,0			; 磁头0
		MOV		CL,2			; 扇区2

readloop:
		MOV		SI,0			; 记录失败次数的寄存器
retry:
		MOV		AH,0x02			; 读盘
		MOV		AL,1			; 1个扇区
		MOV		BX,0
		MOV		DL,0x00			; A驱动器
		INT		0x13			; 调用磁盘BIOS
		JNC		next			; 没出错的话跳到fin
		ADD		SI,1			; SI加1
		CMP		SI,5
		JAE 	error			; SI>=5时，跳转到error
		MOV 	AH,0x00
		MOV		DL,0x00			; A驱动器
		INT		0x13			; 重置驱动器
		JMP		retry

next:
		MOV		AX,ES			; 把内存地址后移0x200
		ADD		AX,0x0020		; 0x20是十六进制下512/16
		MOV		ES,AX
		ADD		CL,1
		CMP		CL,18			; 读取18个扇区
		JBE		readloop		; 如果CL小于等于18，跳转到readloop
		MOV		CL,1
		ADD		DH,1
		CMP		DH,2
		JB      readloop
		MOV		DH,0
		ADD		CH,1
		CMP		CH,CYLS    		; 这里读取10个柱面
		JB      readloop

; 跳到程序装载的地方
		JMP		0xC200			

fin:
		HLT						; 让CPU停止，等待指令
		JMP		fin				; 无限循环

error:
		MOV     SI,msg

putloop:
		MOV		AL,[SI]
		ADD		SI,1			; 给SI加1
		CMP		AL,0
		JE		fin
		MOV		AH,0x0e			; 显示一个文字
		MOV		BX,15			; 指定字符颜色
		INT		0x10			; 调用显卡BIOS
		JMP		putloop

msg:
		DB		0x0a, 0x0a		; 换行2次
		DB		"load error"
		DB		0x0a			; 再次换行
		DB		0

		RESB	0x7dfe-$		; 填写0x00，直到0x001fe

		DB		0x55, 0xaa


