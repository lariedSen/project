
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


	//==========读取目录内容,把图片名字写进去，并尾插到图片链表下
int dir(struct list_node_pic*head1,char * picname)	
{
	chdir("/");
	//system("pwd");
	//1. 打开目录
	DIR *dp = opendir("xmbmp");
	system("pwd");
	if(dp == NULL)
		printf("opendir error!\n");
	
	//2. 切换目录
	chdir("xmbmp");
	
	//3. 读取目录中内容
	struct dirent *ep = NULL;
	
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		
		if(ep->d_name[0] == '.')
			continue;
		
		
		if( strcmp(picname,ep->d_name)==0 ) 
		{
			tail_add_pic_list(head1,ep->d_name);
			//printf("The name of the  picture is %s\n",ep->d_name);
				break;
		}
	}

	//system("pwd");
	closedir(dp);
	return 0;
}