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


int chioce_fun(void *arg,struct list_node_pic*head1)
{
//1.显示界面
	
	mian_interface();   //SRT主界面
	Welcome_chioce(head1); //LCD主界面
	
	int choice_hh = 0 ;
	int y=0;
	int A = 0;
	int c;
	
	
//2.发送输入提示
	
	int connfd = *(int *)arg;
	
	char bufi[50]= "============================\n" ;
	send(connfd,bufi,strlen(bufi),0);

	char buf8[50]="1.registration \n" ;
	send(connfd,buf8,strlen(buf8),0);
	usleep(10000);
	char buf_5[50]="2.logon\n" ;
	send(connfd,buf_5,strlen(buf_5),0);
	usleep(10000);
	char buf_2[50]="3.exit\n" ;
	send(connfd,buf_2,strlen(buf_2),0);
	usleep(10000);
	send(connfd,bufi,strlen(bufi),0);
	char buf_3[50]="enter....\n" ;
	send(connfd,buf_3,strlen(buf_3),0);

//3.打开触摸屏	
	int fd;
	fd = open("/dev/input/event0",O_RDONLY);
	struct input_event buf;

//4. 设置一个集合，并将文件描述符加入到集合中
	fd_set rset;
	struct timeval v;
	int ret ;
	
	int maxfd1 = connfd > STDIN_FILENO ? connfd : STDIN_FILENO;
	int maxfd =   maxfd1 > fd ?  maxfd1 : fd ;
	printf("%d\n",maxfd);
	char buf_1[50];
	
	
	//4. 不断监听集合
	while(1)
	{
		FD_ZERO(&rset);//清空集合中所有的文件描述符
		FD_SET(connfd,&rset);//添加一个文件描述符到集合中
		FD_SET(STDIN_FILENO,&rset);
		FD_SET(fd,&rset);//添加fd描述符到集合中
		
		
		bzero(&v,sizeof(v));
		v.tv_sec = 5;
		v.tv_usec = 0;
		ret = select(maxfd+1,&rset,NULL,NULL,&v); //只要有数据到达，就会返回！
		
		
		if(FD_ISSET(connfd,&rset))    // 测试下 connfd文件描述符是否在集合中
		{
			bzero(buf_1,sizeof(buf_1));
			recv(connfd,buf_1,sizeof(buf_1),0);
			printf("from client:%s",buf_1);  //在就接收读取
			choice_hh = atoi(buf_1);
			printf("from client chioce is %d\n",choice_hh);
			if(( 0<choice_hh ) &&( choice_hh<4 ) )
			{
				return choice_hh ;
			}
		}
		
		if(FD_ISSET(fd,&rset))//  测试下STDIN_FILENO 标准输入的文件描述符  是否在集合中
		{
			
			
			while(1)
			{
				
				bzero(&buf,sizeof(buf));
				read(fd,&buf,sizeof(buf));
				if(buf.type == EV_ABS && buf.code == ABS_Y)
					y = buf.value;
				if(buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
				{
					
					if(y > 0 && y < 200 )
					{
						return 1;
					}

					if( y > 200 && y < 400 )
					{
						return 2;
					}
					if(y > 400 && y < 600 )
					{	
						return 3;
					}
				}
			}
		}	
		if(FD_ISSET(STDIN_FILENO,&rset))//  测试下STDIN_FILENO 标准输入的文件描述符  是否在集合中
		{
			
			scanf("%d",&c);
			if(( 0<c) &&( c<4 ) )
			{
				return c;
			}
		}	
		
	}


	close(fd);
	return 0;
	
}

