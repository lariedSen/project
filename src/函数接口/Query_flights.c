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

	//2.查询某个航班
int Query_flights(void *arg,struct list_node_hanban *head)
{
	int connfd = *(int *)arg;
	printf("What flights do you want to find out,pls enter A001..  ");
	//2.发送提示：输入你的名字 
	char buf[20];
	char flight_name[20];
	int filght_xx ;
	
	char bufi[50]= "you.check_flights:\n" ;
	send(connfd,bufi,strlen(bufi),0);
	usleep(300000);
	
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(flight_name,buf);	
	filght_xx = sechor_show_list_hanban( head,flight_name);
	if(filght_xx == 0)//该航班存在，显示该航班信息
	some_show_list_hangban(head,flight_name);//
	else	//该航班不存在
	printf("no this plane or you enter error \n");
						
	return 0;				
	
	
}
