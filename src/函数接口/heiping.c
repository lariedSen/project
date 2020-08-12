
#include "senge.h"
#include"kernel_list.h"
#include "head.h" 

int heiping()
{
	//1.打开lcd--open-----------------------------------------------------
	int lcd = open("/dev/fb0",O_RDWR);//1.打开lcd--open
		if(lcd<0)
			printf("Open failure \n");
		
//2.申请映射空间-------------------------------------------------
	int *p = (int *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd,0);
		if(p==(void*)-1) //$$$$$$$$$$$$$$$$$$
			printf("mmap failure\n");
	
//3.拷贝往内存空间中填充颜色 -------------------------------------	

	int color = 0x00000000;
	int	i					;

	for(i=0;i<800*480;i++)
	{
		memcpy(p+i,&color,4);//$$$$$$$$$  memcpy(目标地址（p指向的映射空间），需要拷贝的内容的地址，拷贝的字节数)	
	}
	
// 4.撤销映射--------------------------------------------------------

	munmap(p,800*480*4);

	close(lcd);
	return 0;
}
