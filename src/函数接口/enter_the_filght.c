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


	//录入航班
int enter_the_filght(void *arg,struct list_node_hanban *head)
{
	int hh ;
	int connfd = *(int *)arg;
	printf(" Please enter the name of the flight you are looking for,  ");
	printf(" for example A001 ,,,:    ");
	
	char sousuo_name[10];
	
	char bufi[50]= "enter_the_filght:\n" ;
	send(connfd,bufi,strlen(bufi),0);
	usleep(300000);
	
	char bufj[50]= "enter_example:A009\n" ;
	send(connfd,bufj,strlen(bufj),0);
	usleep(300000);
	
	char buf[20];
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);//A009
	
	strcpy(sousuo_name,buf);
	printf("%s\n",sousuo_name);
	hh = sechor_show_list_hanban( head,sousuo_name) ;
		
	if(hh ==0)//判断该航班是否存在，用搜索节点
	{
		printf("The flight is present, please enter a different flight \n");
	}
	else//该航班不存在,录入航班
	{
		//创建 以航班号来命名的文件，并且写入到文件中
		//尾插航班链表节点login_hangban
		//xie_hangban_file(void *arg,struct list_node_hanban *head,char*cj_name)
		xie_hangban_file(&connfd,head,sousuo_name);
	}	
	bzero(sousuo_name,sizeof(sousuo_name));		
	
	
}
