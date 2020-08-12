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

void show_node_buy_ticket(struct list_node_buy_ticket *p)
{
	//printf("\n");
	printf("----------  Your ticket information  ------------------------\n");
	printf("name:%s\n",p-> name);
	printf("age = %d\n",p->age);
	printf("tel:%s\n",p-> tel);
	printf("number:%s\n",p-> number);
	printf("staddress:%s\n",p->staddress);
	printf("arraddress:%s\n",p->arraddress);
	printf("data:%s\n",p->data);
	printf("type:%c\n",p->type);
	printf("stime = %s\n",p->stime);
	printf("prine = %d\n",p->prine);
	printf("much = %d\n",p->much);
	printf("money = %f\n",p->money);
	printf("get_money = %f\n",p->get_money);
	printf("che_money= %f\n\n",p->che_money);

	printf("\n");
	
}
