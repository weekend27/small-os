//����C����������һ�������ڱ���ļ���
void io_hlt(void);

void HariMain(void){
	int i; //����������i��һ��32λ����
	char *p; //����p������BYTE�͵�ַ
	
	p = (char *)0xa0000;  //����ַ������ֵ
	
	for(i = 0; i <= 0xffff; i++){
		//�������ͼ��
		*(p + i) = i & 0x0f;
	}
	
	for(;;){
		io_hlt();
	}
}