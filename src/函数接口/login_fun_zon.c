
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



int login_fun_zon(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head,struct list_node_login *l_head,struct list_node_hanban *head,struct list_node_buy_ticket*g_head)
{
	int connfd = *(int *)arg;
	int a;
	char buf[10];
	char buf_1[20];
	char login_name[10] ; 
	char login_pass[10]; 
	int user_name_yz 	,user_pass_yz ;
	int chioce ;
	

while(1)
{	
//2.发送提示：输入你的名字 
	
	char bufi[50]= "you_name:\n" ;
	send(connfd,bufi,strlen(bufi),0);
	usleep(300000);
	
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(login_name,buf);

//2.发送提示：输入你的密码 
	char bufj[50]= "you_password :\n" ;
	send(connfd,bufj,strlen(bufj),0);
	usleep(300000);
	
		bzero(buf_1,sizeof(buf_1));
		recv(connfd,buf_1,sizeof(buf_1),0);

	strtok(buf_1,"\n");
	printf("%s\n",buf_1);
	strcpy(login_pass,buf_1);
	
	
	
		if( (check_registration(r_head,login_name) !=NULL )&& (check_registration_pass(r_head,login_pass) != NULL)  )
		{	
	

			//显示主登陆界面图片，并且返回选择1，2，3
			 chioce = login_fun_chioce(arg,head1,r_head);
			
			switch(chioce)
			{
				case 1 :
					{
						//管理员登陆
						 Ad_login(arg,r_head,l_head,head,g_head,head1,login_name,login_pass);
						printf("nihao\n");
						
					}break;
														
				case 2 :
					{
						printf("666\n");
						//普通用户登陆
						user_login(arg,r_head,l_head,head,g_head,head1,login_name,login_pass);

					}break;
														
				default:return 0;
			}
 
		}
		else
		{
			break;
		}
	
}	

}	

