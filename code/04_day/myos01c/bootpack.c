//����C����������һ�������ڱ���ļ���
void io_hlt(void);
//void write_mem8(int addr, int data);

void HariMain(void){
	int i; //����������i��һ��32λ����
	char *p; //����p������BYTE�͵�ַ
	
	for(i = 0xa0000; i <= 0xaffff; i++){
		//write_mem8(i,i&0xf0);		//�������ͼ��
		p = (char * )i;
		*p = i & 0x0f;
	}
	
	for(;;){
		io_hlt();
	}
}