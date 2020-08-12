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


	//给他登陆，让他拥有登陆节点struct list_node_reg
int login_fun(struct list_node_reg * r_head, struct list_node_login *l_head, char *check_name)
{
	char passwd_buf[20] = {0};
	struct list_node_reg  *p = NULL;
	//for(p=r_head->next;p!=NULL;p=p->next)
	list_for_each_entry(p,&(r_head->list),list)
	{
		if(strcmp(p->name,check_name) == 0) //说明已经注册过
		{	
			tail_add_list_login(l_head,p);
			return 0;
			
		}
		
	}
	
	printf("you don`t register!\n!");
	return -1;
	
}
