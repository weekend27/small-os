/**
*bootpack.c 其他处理，像是Controller
*/
#include "bootpack.h"
#include <stdio.h>

extern struct KEYBUF keybuf;

void HariMain(void){
	
	struct BOOTINFO *binfo = (struct BOOTINFO *)0x0ff0;
	char s[40], mcursor[256];
	int mx, my, i;
	
	init_gdtidt();
	init_pic();
	io_sti(); /* IDT/PICの初期化が終わったのでCPUの割り込み禁止を解除 */
	
	init_palette();
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
	mx = (binfo->scrnx - 16) / 2;	//先将鼠标位置放在窗口中央
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
	
	io_out8(PIC0_IMR, 0xf9); /* PIC1とキーボードを許可(11111001) */
	io_out8(PIC1_IMR, 0xef); /* マウスを許可(11101111) */
	
	for(;;){
		io_cli();				//先去屏蔽中断
		if(keybuf.flag == 0){	//flag是0说明键没有被按下
			io_stihlt();
		}else{
			i = keybuf.data;	//先将键码保存起来，后面有中断进来也不怕，哈哈哈
			keybuf.flag = 0;
			io_sti();			//重新开放中断
			sprintf(s, "%02X", i);
			boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
			putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
		}
	}
}





