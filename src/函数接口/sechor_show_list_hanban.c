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


int sechor_show_list_hanban( struct list_node_hanban*head,char *name)
{
	struct list_head *p = NULL;		//-----------小结构体指针域
	struct list_node_hanban *tmp = NULL;
	int a;
	list_for_each(p,&(head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		tmp = list_entry(p,struct list_node_hanban,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(name,tmp->number);
		
		if(a == 0)
		{
			printf("The flight exists,lease continue do next \n");
			return 0;
		}
	}
	printf("The flight doesn't exist, You can enter the flight .\n");
	return -1;
}
