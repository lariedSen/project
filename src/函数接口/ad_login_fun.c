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


int ad_login_fun(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head,struct list_node_login *l_head,struct list_node_hanban *head)
{
	int connfd = *(int *)arg;
	int a;
	char buf[10];
	char buf_1[20];
	
	int chioce ;
		
	while(1)
	{
		//显示管理员登陆界面图片，并且返回选择1，2，3
		chioce = Ad_login_fun_chioce(arg,head1);
		switch(chioce)
		{
			case 1 :
				{

					Cancel_the_flight(&connfd,head,head1);
				}break;
													
			case 2 :
				{
					enter_the_filght(&connfd,head) ;

				}break;
													
			default:
			{
				return 0;
			}break;//退出登陆
		}
	}
	
	return 0;
	

}	
