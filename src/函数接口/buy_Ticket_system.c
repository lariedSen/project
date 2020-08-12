
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

int buy_Ticket_system(void *arg,char *logon_name,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_login *l_head,struct list_node_pic*head1)
{
	int connfd = *(int *)arg;
	int buy_chioce ;
	int in_tic ;
	int re_tic ;
	int al_tic ;
	
	
	
while(1)
	{
		buy_chioce = buy_Ticket_system_choice(&connfd,head1);	
		if(buy_chioce == 1)//购票
		{
			printf("");
			Buy_ticket_fun(&connfd,head,g_head,l_head,logon_name,1);
			printf("The purchase of tickets was successful. You are welcome to buy tickets again.\n");
																	
		}																																				
		else if(buy_chioce == 2)//查询自己所购的票
		{
			in_tic = inquire_tickets(g_head,logon_name);//logon_name
			if(in_tic != 0)
			printf("inquire_tickets error\n");
		}
		else if(buy_chioce == 3)//退票
		{
			re_tic = Re_ticket(&connfd,g_head,logon_name);
			if(re_tic != 0)
			printf("re_ticket error\n");
		}
		else if (buy_chioce == 4)//改签
		{
			al_tic = Alter_tickets(&connfd,head,g_head,l_head,logon_name);
			if(al_tic != 0)
			printf("Alter_tickets error \n");
		}
		else//退出当前购票系统
		{
			printf("Please wait a minute , exit the current ticketing system \n");
			sleep(1);
			break;
		}	
	}
	
}
