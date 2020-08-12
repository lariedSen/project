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


	//1.管理员注册
int Ad_reg(struct list_node_reg *r_head,void *arg)
{
	int connfd = *(int *)arg;
	char pass[10]="senge777" ;
	char C_name[10]="lisen";
	
	char you_name[10];
	char you_pass[10];
	
	
//1.发送提示：密保名字 
	
	char buf_name[50]= "enter:lisen\n" ;
	send(connfd,buf_name,strlen(buf_name),0);
	//sleep(1);
	
	//对比密保名字
	bzero(you_name,sizeof(you_name));
	recv(connfd,you_name,sizeof(you_name),0);
	printf("%s\n",you_name);
	if(strncmp(you_name,"quit",4) == 0)
	{
			exit(-1);
	}
	int b = strncmp(you_name,C_name,5);//b=0 正确
	
	
	
//2.发送提示：密保密码 
	
	char buf_word[50]= "enter:senge777\n" ;
	send(connfd,buf_word,strlen(buf_word),0);
	sleep(1);

	//对比密保密码
	bzero(you_pass,sizeof(you_pass));
	recv(connfd,you_pass,sizeof(you_pass),0);
	printf("%s\n",you_pass);
	if(strncmp(you_pass,"quit",4) == 0)
	{
			exit(-1);
	}
	
	int a = strncmp(you_pass,pass,8);

	if( ( a == 0) &&(b == 0) )
	{
		
		register_fun(r_head,arg);
		
	}
	else
	{
		printf("Verification failure  \n");
	}
	return 0;
}
