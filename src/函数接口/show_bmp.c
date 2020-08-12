
#include "senge.h"
#include"kernel_list.h"
#include "head.h"


struct list_node_buy_ticket {
	
	char name[10];
	int age;
	char tel[15];
	
	char number[10];	//航班的名字
	char staddress[10];	//起始点
	char arraddress[15];//终点
	char data[15];		//日期
	char type ;			//类型
	char stime[10];		//出发时间	
	int prine;		//票价
	
	int much	;		//几张票
	float money		;	//总票钱
	float get_money	;	//拿到的钱
	float che_money	;	//找回给顾客的钱
	
	struct list_head list;//内核链表指针域
};


struct list_node_hanban{
	char number[10];//
	char staddress[10];//
	char arraddress[15];//
	char data[15];
	char type ;
	char stime[10];
	int prine;//数据域
	struct list_head list;//内核链表指针域
};


struct list_node_pic{
	char name[20];	//图片的名字		
	struct  list_head list;
};

//list_node_reg
struct list_node_reg{
	char name[10];
	int  age;
	char tel[15];
	char password_i[10];
	struct  list_head list;
};

		//=========登陆链表
struct list_node_login{
	char name[10];
	int  age;
	char tel[15];
	char password_i[10];
	struct  list_head list;
};


int show_bmp(char*panme)
{
	char bmp_buf[800*480*3];
	char lcd_buf[800*480*4];
	char show_buf[800*480*4];
	
	int ret,lcd;
	int i,j,x,y;
	//1.访问bmp图片
	FILE *fp = fopen(panme,"r");
	if( fp == NULL)
	{
		printf("fopen error!\n");
		return 1;
	}
	//2.跳过bmp图片的54个头数据
	ret=fseek(fp,54,SEEK_SET);
	if( ret != 0)
		printf("fseek file!\n");
	//3.读取bmp图片的数据
	ret = fread(bmp_buf,sizeof(bmp_buf),1,fp);
	if(ret !=1)
		printf("fread error!\n");
	//4.访问LCD液晶
	lcd = open("/dev/fb0",O_WRONLY);
	if(lcd<0)
		printf("open error!\n");
	//5.像素点赋值
	for(i=0,j=0;i<800*480*4;i+=4,j+=3)
	{
		lcd_buf[i] = bmp_buf[j];
		lcd_buf[i+1] = bmp_buf[j+1];
		lcd_buf[i+2] = bmp_buf[j+2];
		lcd_buf[i+3] = 0;
		
	}
	
	//6.上下翻转
	for(y=0;y<480;y++)
	{
		for(x=0;x<800*4;x++)
		{	
			show_buf[(479-y)*800*4+x] = lcd_buf[y*800*4+x];
		}
	}
	//7.将图片数据写入到LCD液晶屏幕上
	ret = write(lcd,show_buf,sizeof(show_buf));
	if(ret != sizeof(show_buf))
			printf("write error!\n");
		
	//8.关闭设备与文件
	close(lcd);
	fclose(fp);
	return 0;
}