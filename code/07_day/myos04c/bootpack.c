/**
*bootpack.c ������������Controller
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
	io_sti(); /* IDT/PIC�γ��ڻ����K��ä��Τ�CPU�θ���z�߽�ֹ���� */
	
	init_palette();
	init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
	mx = (binfo->scrnx - 16) / 2;	//�Ƚ����λ�÷��ڴ�������
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
	
	io_out8(PIC0_IMR, 0xf9); /* PIC1�ȥ��`�ܩ`�ɤ��S��(11111001) */
	io_out8(PIC1_IMR, 0xef); /* �ޥ������S��(11101111) */
	
	for(;;){
		io_cli();				//��ȥ�����ж�
		if(keybuf.flag == 0){	//flag��0˵����û�б�����
			io_stihlt();
		}else{
			i = keybuf.data;	//�Ƚ����뱣���������������жϽ���Ҳ���£�������
			keybuf.flag = 0;
			io_sti();			//���¿����ж�
			sprintf(s, "%02X", i);
			boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
			putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
		}
	}
}





