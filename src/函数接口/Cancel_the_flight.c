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


	//取消航班
int Cancel_the_flight(void *arg,struct list_node_hanban *head,struct list_node_pic*head1)
{
	int connfd = *(int *)arg;
	char sousuo_name[10];
	int hh ,whe_show;
	int delete_yz;
	
	char bufi[50]= "Cancel_the_flight:\n" ;
	send(connfd,bufi,strlen(bufi),0);
	usleep(300000);
	
	char bufj[50]= "enter_example:A001\n" ;
	send(connfd,bufj,strlen(bufj),0);
	usleep(300000);
	
	char buf[20];
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);//A001
	strcpy(sousuo_name,buf);
	
	
	//sechor_show_list_hanban( head,sousuo_name) 
	hh = sechor_show_list_hanban( head,sousuo_name) ;
	if( hh  == 0)//判断该航班存在--删除该航班节点，删除该航班对应文件
	{
		//-删除该航班的链表节点
		delete_yz = delete_list_node(head,sousuo_name);
		if( delete_yz == -1 ) 
		printf("delete file!\n");

		char bufi[50]= "show_list_hangban:enter.1\n" ;
		send(connfd,bufi,strlen(bufi),0);
		usleep(300000);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		whe_show = atoi(buf);
		if( whe_show ==1)
		{
			show_list_hangban(head);
			printf("		Delete flight node complete  \n");
			printf("		Next, delete the flight file\n");
			
		}
		//删除该航班的对应文件
		delete_file_hangban(head,sousuo_name);
	}
	else//该航班不存在，显示一张不存在的图片.bmp 5秒
	{
		printf("no this hangban\n");
		no1_pic(head1);
									
	}
	bzero(sousuo_name,sizeof(sousuo_name));
	return 0;
}

