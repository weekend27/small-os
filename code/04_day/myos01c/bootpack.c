//告诉C编译器，有一个函数在别的文件中
void io_hlt(void);
//void write_mem8(int addr, int data);

void HariMain(void){
	int i; //变量声明：i是一个32位整数
	char *p; //变量p，用于BYTE型地址
	
	for(i = 0xa0000; i <= 0xaffff; i++){
		//write_mem8(i,i&0xf0);		//搞搞条纹图案
		p = (char * )i;
		*p = i & 0x0f;
	}
	
	for(;;){
		io_hlt();
	}
}