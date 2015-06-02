//告诉C编译器，有一个函数在别的文件中
void io_hlt(void);

void HariMain(void){
	int i; //变量声明：i是一个32位整数
	char *p; //变量p，用于BYTE型地址
	
	p = (char *)0xa0000;  //给地址变量赋值
	
	for(i = 0; i <= 0xffff; i++){
		//搞搞条纹图案
		*(p + i) = i & 0x0f;
	}
	
	for(;;){
		io_hlt();
	}
}