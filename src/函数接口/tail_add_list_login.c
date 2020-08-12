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


	//===============登陆尾插----->由下一个函数调用
int tail_add_list_login(struct list_node_login *l_head,struct list_node_reg *tmp) //------------------tmp就是指向需要登陆的用户
{
	
	char name[10];
	int  age;
	char tel[15];
	//新建一个节点
	 struct list_node_login *Node = NULL;
	Node = (struct list_node_login*)malloc(sizeof(struct list_node_login));
	if(Node == NULL)
		printf("malloc Node error!\n");

	strcpy(Node->name,tmp->name);
	Node->age = tmp->age;
	strcpy(Node->tel,tmp->tel);
	//strcpy(Node->password_i,password_i);不打印密码

	list_add_tail(&(Node->list),&(l_head->list));
	show_node_login(Node);
	return 0;
}
