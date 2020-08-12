#include "senge.h"
#include"kernel_list.h"
#include "head.h" 

/**===========================航班链表==================================================================*/

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



 struct list_node_hanban* init_list_head(struct list_node_hanban*head)
 {
	//1.为头节点申请空间	
		head=(struct list_node_hanban*)malloc(sizeof(struct list_node_hanban));
		if(head==NULL)
			printf("malloc file!\n");
		INIT_LIST_HEAD(&(head->list));
		return head;
		
 }
 


/**=====================================图片内核链表================================================================*/

	//----------------------图片链表头节点
struct list_node_pic *init_list_head1(struct list_node_pic *head1)
	{
		//1）为头节点申请堆空间。
		head1 = (struct list_node_pic *)malloc(sizeof(struct list_node_pic));
		if(head1 == NULL)
			printf("malloc head error!\n");
			
		//2）为头节点成员赋值
		INIT_LIST_HEAD(&(head1->list));
		
		return head1;
}





struct list_node_reg * init_list_head2 (struct list_node_reg*r_head)
 {
	//1.为头节点申请空间	
		r_head=(struct list_node_reg*)malloc(sizeof(struct list_node_reg));
		if(r_head==NULL)
			printf("malloc file!\n");
		INIT_LIST_HEAD(&(r_head->list));
		return r_head;
		
 }


/************** 登陆链表  ********************/


		//登陆链表初始化
struct list_node_login * init_list_head3 (struct list_node_login*l_head)
 {
	//1.为头节点申请空间	
		l_head=(struct list_node_login*)malloc(sizeof(struct list_node_login));
		if(l_head==NULL)
			printf("malloc file!\n");
		INIT_LIST_HEAD(&(l_head->list));
		return l_head;
		
 } 
		



	//购票头节点
struct list_node_buy_ticket* init_list_head4(struct list_node_buy_ticket*g_head)
 {
	//1.为头节点申请空间	
		g_head=(struct list_node_buy_ticket*)malloc(sizeof(struct list_node_buy_ticket));
		if(g_head==NULL)
			printf("malloc file!\n");
		INIT_LIST_HEAD(&(g_head->list));
		return g_head;
	
 }
 


int main(int argc,char*argv[])
{
/***2.网络通信========================***/
	//1. 创建未连接套接字
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("sockfd = %d\n",sockfd); //3
	
	//2. 绑定IP地址，端口号等到未连接套接字中
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr,len);
	
	srvaddr.sin_family = AF_INET; //协议
	srvaddr.sin_port = htons(atoi(argv[1])); //端口号
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY); //服务器的IP
	
	bind(sockfd,(struct sockaddr *)&srvaddr,len);
	
	//3. 设置监听套接字
	listen(sockfd,5);
	
	//4. 等待连接
	struct sockaddr_in cliaddr;
	int connfd;
	connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len); //阻塞！
	if(connfd > 0)
	{
		printf("new connection:%s\n",(char *)inet_ntoa(cliaddr.sin_addr));
	}
	
		
	//------------航班链表初始化
	struct list_node_hanban*head = NULL;
	head = init_list_head(head);
	//----------图片链表初始化
	struct list_node_pic*head1 = NULL;
	head1 = init_list_head1(head1);
	//-----------注册链表初始化
	struct list_node_reg *r_head = NULL;
	r_head = init_list_head2(r_head);
	
	 //-----------登陆链表初始化
	struct list_node_login *l_head = NULL;
	l_head = init_list_head3(l_head);
	
	//------------购票链表初始化
	struct list_node_buy_ticket*g_head = NULL;
	g_head = init_list_head4(g_head);
	
	
	
	
	int A;
/***1.显示LCD液晶屏欢迎界面========================***/
	LCD_Welcome_interface(head1);
	
	
/*****===    主界面进行选择       ==*********/
	while(1)
	{
		A = chioce_fun(&connfd,head1);
			switch(A)
			{
				case 1 ://=================注册
				{
					//显示注册图片
					register_fun_zon(&connfd,head1,r_head);
					
				}break;
				
				case 2://===================登陆
				{
					//显示所有航班信息
					//显示所有航班，并且尾插到航班链表，由下一个函数调用 
					login_hangban(head);
					
					//主登陆函数
					login_fun_zon(&connfd,head1,r_head,l_head,head,g_head);
					
				}break;
				
				case 3 :
				{
					char bufj[50]= "quit \n" ;
					send(connfd,bufj,strlen(bufj),0);
					usleep(300000);
					heiping();
					exit(0);
				}break;
				
			
			}
	}
	sleep(15);
	
	//6. 挂断
	close(connfd);
	close(sockfd);
	return 0;
}


