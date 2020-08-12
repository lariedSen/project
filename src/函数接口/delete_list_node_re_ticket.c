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
	//删除该购票的链表节点
int delete_list_node_re_ticket(struct list_node_buy_ticket *g_head,char *name)
{
	struct list_head *p = NULL;
	struct list_head *q = NULL;
	struct list_node_buy_ticket *tmp = NULL;
	
	list_for_each_safe(p,q,&(g_head->list))//等同于for(q=head,p=head->next;p!=NULL;q=p,p=p->next)
	{
		tmp = list_entry(p,struct list_node_buy_ticket,list);//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		if( strcmp( tmp->name,name ) == 0 )
		{
			list_del(p);//把节点脱离开链表，并且保证链表不断开，但是内存没有释放
			free(tmp);//释放内存
			return 0;
		}
	}
	return -1;
}