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


int register_fun_zon(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head)
{
	int connfd = *(int *)arg;
	int a;
	char buf[10];
		
//2.发送提示：输入你的名字 
	
	char bufi[50]= "you_name:\n" ;
	send(connfd,bufi,strlen(bufi),0);
	usleep(300000);
	
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		printf("%s\n",buf);
		if(strncmp(buf,"quit",4) == 0)
		{
			exit(-1);
		}
	
	
	if( check_registration(r_head,buf)  == NULL) //检查是否已经注册
	{
		
	 a = register_fun_chioce(&connfd,head1,r_head);//注册选择
	
		switch(a)
		{
			case 1 :
				{
					//管理员注册
					
					Ad_reg(r_head,&connfd);
					
				}break;
													
			case 2 :
				{
					user_reg(r_head,&connfd);

				}break;
													
			case 3 :
				{
					//printf("lisen\n");
					usleep(100000);	
				}break;
			default:
				{
					printf("enter error!\n");	
				}break;
		}
									
		printf("\n");	
									
	}
								
	else 
		{
			printf("You're already registered\n");

		}

}

