#include "senge.h"
#include"kernel_list.h"
int mian_interface();
int heiping();


/**===========================航班链表==================================================================*/
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
struct list_node_pic{
	char name[20];	//图片的名字		
	struct  list_head list;
};
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

	//----------------------图片内核链表尾插
int tail_add_pic_list(struct list_node_pic *head1,char *picname)
{
		struct list_node_pic *Node = NULL;
		Node = (struct list_node_pic *)malloc(sizeof(struct list_node_pic));
		if(Node == NULL)
			printf("malloc Node error!\n");
		strcpy(Node->name,picname);	
		list_add_tail(&(Node->list),&(head1->list));
		
		return 0;
}


//---------------函数功能：显示图片-------------------
int show_bmp(char*panme)
{
	char bmp_buf[800*480*3];
	char lcd_buf[800*480*4];
	char show_buf[800*480*4];
	
	int ret,lcd;
	int i,j,x,y;
	//1.访问bmp图片
	FILE *fp = fopen(panme,"r");
	if( fp == NULL)
	{
		printf("fopen error!\n");
		return 1;
	}
	//2.跳过bmp图片的54个头数据
	ret=fseek(fp,54,SEEK_SET);
	if( ret != 0)
		printf("fseek file!\n");
	//3.读取bmp图片的数据
	ret = fread(bmp_buf,sizeof(bmp_buf),1,fp);
	if(ret !=1)
		printf("fread error!\n");
	//4.访问LCD液晶
	lcd = open("/dev/fb0",O_WRONLY);
	if(lcd<0)
		printf("open error!\n");
	//5.像素点赋值
	for(i=0,j=0;i<800*480*4;i+=4,j+=3)
	{
		lcd_buf[i] = bmp_buf[j];
		lcd_buf[i+1] = bmp_buf[j+1];
		lcd_buf[i+2] = bmp_buf[j+2];
		lcd_buf[i+3] = 0;
		
	}
	
	//6.上下翻转
	for(y=0;y<480;y++)
	{
		for(x=0;x<800*4;x++)
		{	
			show_buf[(479-y)*800*4+x] = lcd_buf[y*800*4+x];
		}
	}
	//7.将图片数据写入到LCD液晶屏幕上
	ret = write(lcd,show_buf,sizeof(show_buf));
	if(ret != sizeof(show_buf))
			printf("write error!\n");
		
	//8.关闭设备与文件
	close(lcd);
	fclose(fp);
	return 0;
}

	
	//----------图片内核链表--搜索节点 -> 搜索到，显示图片-----
int sechor_show_list(struct list_node_pic*head1,char *picname)
{
	struct list_head *p = NULL;		//-----------小结构体指针域
	struct list_node_pic *tmp = NULL;
	int c,b,d=1;
	list_for_each(p,&(head1->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		
		tmp = list_entry(p,struct list_node_pic,list); 
		c = strcmp(tmp->name,picname);
		
		if(c !=0)
				continue;	
		if( c == 0 )
		{
			d = show_bmp(tmp->name);
			break;	
		}
		
	}
	return d;	
}

	//==========读取目录内容,把图片名字写进去，并尾插到图片链表下
int dir(struct list_node_pic*head1,char * picname)	
{
	chdir("/");
	//system("pwd");
	//1. 打开目录
	DIR *dp = opendir("xmbmp");
	system("pwd");
	if(dp == NULL)
		printf("opendir error!\n");
	
	//2. 切换目录
	chdir("xmbmp");
	
	//3. 读取目录中内容
	struct dirent *ep = NULL;
	
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;
		
		if(ep->d_name[0] == '.')
			continue;
		
		
		if( strcmp(picname,ep->d_name)==0 ) 
		{
			tail_add_pic_list(head1,ep->d_name);
			//printf("The name of the  picture is %s\n",ep->d_name);
				break;
		}
	}

	//system("pwd");
	closedir(dp);
	return 0;
}

	//显示LCD液晶屏欢迎界面 ---->同样这需要改一下图片名字
int LCD_Welcome_interface(struct list_node_pic*head1)
{
	
		int b;
		//读取目录内容并尾插该图片到图片链表下
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"LCDhuangying.bmp");
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");
		//else
		//printf("welcome\n");
	
	
}

int Welcome_chioce(struct list_node_pic*head1)
{
	
		int b;
		//读取目录内容并尾插该图片到图片链表下
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"mian_interface.bmp");//zhuce_jiem.bmp
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");
		//else
		//printf("welcome\n");
	
	
}
int reg_ch(struct list_node_pic*head1)
{
	
		int b;
		//读取目录内容并尾插该图片到图片链表下
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"zhuce_jiem.bmp");
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");
	
}

int login_ch(struct list_node_pic*head1)
{
	
		int b;
		//读取目录内容并尾插该图片到图片链表下
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"longin_jiem.bmp");
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");
	
}
	//管理员登陆图片主界面
int ad_login_ch(struct list_node_pic*head1)
{
	
		int b;
		//读取目录内容并尾插该图片到图片链表下
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"administrator_interface.bmp");
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");
	
}
	//普通用户登陆图片主界面
int user_login_ch(struct list_node_pic*head1)
{
	
		int b;
		//读取目录内容并尾插该图片到图片链表下
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"user_interface.bmp");
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");
	
}

	//买票图片
int buy_ticket_face(struct list_node_pic*head1)
{
		int b;
		//读取目录内容并尾插该图片到图片链表下
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"buy_ticket_interface.bmp");
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");
	
	
}

//该航班不存在，显示一张不存在的图片.bmp 5秒
int no1_pic(struct list_node_pic*head1)
{
		int b;
		char you_picname[30];
		char *p = you_picname;
		strcpy(p,"no_pic.bmp");
		dir(head1,p);
		b = sechor_show_list(head1,p);
		if(b != 0)
		printf("no this picture!\n");

}



/***
函数功能：
			选择 ----》可参考修改

*/
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


/**************************************/
/**=============    注册      ======**/
/*****************************8******/

	/**======register注册链表======================**/

struct list_node_reg{
	char name[10];
	int  age;
	char tel[15];
	char password_i[10];
	struct  list_head list;
};

struct list_node_reg * init_list_head2 (struct list_node_reg*r_head)
 {
	//1.为头节点申请空间	
		r_head=(struct list_node_reg*)malloc(sizeof(struct list_node_reg));
		if(r_head==NULL)
			printf("malloc file!\n");
		INIT_LIST_HEAD(&(r_head->list));
		return r_head;
		
 }
 int tail_add_reg_list(struct list_node_reg *head1,char *name)
{
		struct list_node_reg *Node = NULL;
		Node = (struct list_node_reg *)malloc(sizeof(struct list_node_reg));
		if(Node == NULL)
			printf("malloc Node error!\n");
		//struct list_node_reg *q=NULL;
		strcpy(Node->name,name);	
		list_add_tail(&(Node->list),&(head1->list));
		
		return 0;
}

	//显示某注册节点的信息
 void show_node(struct list_node_reg *p)
{
	printf("name:%s\n",p->name);
	printf("passwd:%s\n",p->password_i);
	printf("age = %d\n",p->age);
	printf("tel = %s\n",p->tel);
	
	return;
}

	//遍历注册节点的信息
int show_list(struct list_node_reg *r_head)
{
	struct list_node_reg *p = NULL;
	//for(p=r_head->next;p!=NULL;p=p->next)
	list_for_each_entry(p,&(r_head->list),list)
	{
		show_node(p);
	}
	
	return 0;
}


/************** 登陆链表  ********************/

		//=========登陆链表
struct list_node_login{
	char name[10];
	int  age;
	char tel[15];
	char password_i[10];
	struct  list_head list;
};
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
		

		//=========遍历某登陆节点的信息
void show_node_login(struct list_node_login *p)
{
	printf("name:%s\n",p->name);
	printf("passwd: ***********\n");
	printf("age = %d\n",p->age);
	printf("tel = %s\n",p->tel);
	
	return;
}
		//遍历全部登陆节点的信息
int show_list_login(struct list_node_login *l_head)
{
	struct list_node_login *p = NULL;
	//for(p=r_head->next;p!=NULL;p=p->next)
	list_for_each_entry(p,&(l_head->list),list)
	{
		show_node_login(p);
	}
	
	return 0;
}
	
	
	/**------------验证是否已经登陆-  ,登陆了；->name ,没有登陆:->NULL  --------------------------*/				

char *check_login(struct list_node_login *l_head,char *name_buf)
{
	struct list_node_login *tmp = NULL;
	struct  list_head *p = NULL;
	int c;
	list_for_each(p,&(l_head->list))//等价于for(p=&(head->list)->next;p!= &(head->list);p=p->next)
	{
		tmp = list_entry(p,struct list_node_login,list);		
		c = strcmp(tmp->name,name_buf );
		if( c == 0)
		{
			return name_buf;  
		}
		
	}
	
	return NULL; 
}
 
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



	//给他登陆，让他拥有登陆节点struct list_node_reg
int login_fun(struct list_node_reg * r_head, struct list_node_login *l_head, char *check_name)
{
	char passwd_buf[20] = {0};
	struct list_node_reg  *p = NULL;
	//for(p=r_head->next;p!=NULL;p=p->next)
	list_for_each_entry(p,&(r_head->list),list)
	{
		if(strcmp(p->name,check_name) == 0) //说明已经注册过
		{	
			tail_add_list_login(l_head,p);
			return 0;
			
		}
		
	}
	
	printf("you don`t register!\n!");
	return -1;
	
}
	






	//注册界面 
void zhuce_jiem()
{
	printf("welcome to \n");
	printf("----------------------------------------------------\n");
	printf("			   Welcome to the Desson Airlines 		\n");
	printf("			   Press 1 to Administrator registration\n");
	printf("			   Press 2 user registration   		\n");
	printf("			   Press 3 to exit registration 		\n");
	printf("----------------------------------------------------\n");
	printf("Please enter your choice:  ");
	
}


	//显示界面图片，并且返回选择1，2，3
int register_fun_chioce(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head)
{
	
	
	//1.显示界面
	int connfd = *(int *)arg;
	zhuce_jiem();   //SRT主界面
	reg_ch(head1); //LCD主界面
	
	int choice_hh = 0 ;
	int y=0;
	int A = 0;
	int c;
	
	
//2.发送输入提示
	
	
	char bufi[50]= "============================\n" ;
	send(connfd,bufi,strlen(bufi),0);

	char buf4[50]="1.Administrator\n" ;
	send(connfd,buf4,strlen(buf4),0);
	usleep(10000);
	char buf_5[50]="2.user_registration\n" ;
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


	/**-----------------------注册查询------------------*/				
char *check_registration(struct list_node_reg *r_head,char *name_buf)
{
	printf("%s\n",name_buf);
	struct list_node_reg *tmp = NULL;
	struct  list_head *p = NULL;
	int c;
	list_for_each(p,&(r_head->list))//等价于for(p=&(head->list)->next;p!= &(head->list);p=p->next)
	{
		tmp = list_entry(p,struct list_node_reg,list);		
		c = strcmp(tmp->name,name_buf );
		if( c == 0)
		{
			return name_buf;  //已经注册过，返回名字
		}
		
	}
	
	return NULL; //没有注册过
}


/***通用
	注册功能：
		获取信息，
		写入链表和文件**/
int register_fun(struct list_node_reg *r_head,void *arg)
{
	
	int connfd = *(int *)arg;
	int a;
	char name[10];
	char name_1[10];//.txt
	int age;
	char age_1[3];
	char tel[15];
	char password_i[10];
	
	char buf_1[50];
	char buf_2[50];
	char buf_3[50];
	char buf_4[50];
	char buf_5[50];

	struct list_node_reg *Node = NULL;
	Node = (struct list_node_reg *)malloc(sizeof(struct list_node_reg));
	
//--------------name
	

	char buf_name[50]= "you.name: \n" ;
	int b = send(connfd,buf_name,strlen(buf_name),0);
	
	if(b == -1)
		printf("send  name error !\n");
	
	bzero(buf_1,sizeof(buf_1));
	recv(connfd,buf_1,sizeof(buf_1),0);
	strtok(buf_1,"\n");
	strcpy(name,buf_1 );
	
	printf("name:%s\n",name);
	strcpy(Node->name,name);//写近链表
	
	strcpy(name_1,name);
	strcat(name_1,".txt");
	
	strcat(name,",");
	
	printf("%s\n",name);	//name -> li,
	printf("%s\n",name_1);//li.txt
	
//-------------age
	char buf_age[50]= "you.age: \n" ;
	b = send(connfd,buf_age,strlen(buf_age),0);
	if(b == -1)
		printf("send  age error !\n");
	
	//获取信息，
	usleep(300000);
	bzero(buf_2,sizeof(buf_2));
	recv(connfd,buf_2,sizeof(buf_2),0);
	
	age = atoi(buf_2);
	printf("age=%d\n",age);
	Node-> age = age;	//写近链表
	
	sprintf(age_1,"%d",age);
	strcat(age_1,",");
	
//---------------tel
	char buf_tel[50]= "you.tel: \n" ;
	b = send(connfd,buf_tel,strlen(buf_tel),0);
	if(b == -1)
		printf("send  tel error !\n");
	
	usleep(300000);
	//获取信息，
	
	bzero(buf_3,sizeof(buf_3));
	recv(connfd,buf_3,sizeof(buf_3),0);
	strtok(buf_3,"\n");
	strcpy(tel,buf_3);
	printf("tel:%s\n",tel);
	strcpy(Node->tel,tel);//写近链表
	strcat(tel,",");
	
		
//---------------password_i
	char buf_password[50]= "you.password_i: \n" ;
	b = send(connfd,buf_password,strlen(buf_password),0);
	if(b == -1)
		printf("send  pass error !\n");
	
	usleep(300000);
	
	//获取信息，
	bzero(buf_4,sizeof(buf_4));
	recv(connfd,buf_4,sizeof(buf_4),0);
	strtok(buf_4,"\n");
	strcpy(password_i,buf_4);
	
	printf("password:%s\n",password_i);
	strcpy(Node->password_i,password_i);//写近链表
	strcat(password_i,",");
	
	list_add_tail(&(Node->list),&(r_head->list));
	show_node(Node);


//--------是否进行遍历
	char buf_show[20]= "show_list? \n" ;
	send(connfd,buf_show,strlen(buf_show),0);
	bzero(buf_5,sizeof(buf_5));
	recv(connfd,buf_5,sizeof(buf_5),0);
	//strtok(buf_1,"\n");
	printf("show:%s\n",buf_5);
	
	a = atoi(buf_5);
	if(a == 1)
		show_list(r_head);
	

//--------写进文件
	int	ret,i	;
	struct dirent *ep = NULL;
	DIR * dp =NULL;
	chdir("/");
	system("pwd");
	
	//1. 访问目录文件
	dp = opendir("/zhucexx");
	if(dp == NULL)
		printf("opendir error!\n");
	
	//2. 切换到目录下
		ret = chdir("/zhucexx");
	if(ret == -1)
		printf("chdir error!\n");

	system("pwd");
	//3.打开文件
	FILE *fp = fopen(name_1,"w+");
	system("pwd");
	
	fputs(name,fp);
	fputs(age_1,fp);
	fputs(tel,fp);
	fputs(password_i,fp);
	
	
	fclose(fp);
	closedir(dp);
	return 0;
	
	
}

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

int user_reg(struct list_node_reg *r_head,void *arg)
{
	int connfd = *(int *)arg;
	char buf_name[50]= "Welcome: \n" ;
	send(connfd,buf_name,strlen(buf_name),0);
	register_fun(r_head,arg);
	
	return 0;
	
	
	
	
}

/**
函数功能：注册函数
			1.管理员注册
			2.普通用户注册
			3.退出
**/
int register_fun_zon(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head)
{
	int connfd = *(int *)arg;
	int a;
	char buf[10];
		
//2.发送提示：输入你的名字 
	
	char bufi[50]= "you_name:\n" ;
	send(connfd,bufi,strlen(bufi),0);
	usleep(300000);
	
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		printf("%s\n",buf);
		if(strncmp(buf,"quit",4) == 0)
		{
			exit(-1);
		}
	
	
	if( check_registration(r_head,buf)  == NULL) //检查是否已经注册
	{
		
	 a = register_fun_chioce(&connfd,head1,r_head);//注册选择
	
		switch(a)
		{
			case 1 :
				{
					//管理员注册
					
					Ad_reg(r_head,&connfd);
					
				}break;
													
			case 2 :
				{
					user_reg(r_head,&connfd);

				}break;
													
			case 3 :
				{
					//printf("lisen\n");
					usleep(100000);	
				}break;
			default:
				{
					printf("enter error!\n");	
				}break;
		}
									
		printf("\n");	
									
	}
								
	else 
		{
			printf("You're already registered\n");

		}

}


//以上是注册-------------------------------------


/***************************************登陆***********************************************************/
	//函数功能：成功----》pass_buf密码，失败----》NULL
 char *check_registration_pass(struct list_node_reg *r_head,char*pass_buf)
{
	
	struct list_node_reg *tmp = NULL;
	struct  list_head *p = NULL;
	int c;
	list_for_each(p,&(r_head->list))//等价于for(p=&(head->list)->next;p!= &(head->list);p=p->next)
	{
		tmp = list_entry(p,struct list_node_reg,list);		
		c = strcmp(tmp->password_i,pass_buf );
		if( c == 0)
		{
			return pass_buf ;  //已经注册过，返回密码
		}
	}
	
	return NULL; //没有登陆过
}



	//登陆主界面 ---管理员登陆，或者普通用户登陆 
int longin_jiem()
{
	
	printf("============================================================\n");
	printf("		Welcome to the Desson Airlines 						\n");
	printf("				Press 1 Administrator login					\n");
	printf("				Press 2 Common user login   							\n");
	printf("				Press 3 to exit  							\n");
	printf("============================================================\n");
	printf("Please enter your choice:  ");

}


	//显示主登陆界面图片，并且返回选择1，2，3
int login_fun_chioce(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head)
{
	
	
	//1.显示界面
	int connfd = *(int *)arg;
	longin_jiem();   //SRT登陆主界面
	login_ch(head1); //LCD登陆主界面
	
	int choice_hh = 0 ;
	int y=0;
	int A = 0;
	int c;
	
	
//2.发送输入提示
	
	
	char bufi[50]= "============================\n" ;
	send(connfd,bufi,strlen(bufi),0);

	char buf4[50]="1.Ad_login	\n" ;
	send(connfd,buf4,strlen(buf4),0);
	usleep(10000);
	char buf_5[50]="2.user_login\n" ;
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


/**===================== 管理员操作：进入管理员登陆界面---取消航班，录入航班，退出登陆===========**/
int  administrator_interface() //登陆界面
{
	printf("===============================================================\n");
	printf("	Welcome to the administrator login interface:              \n");
	printf("		To cancel the flight ,  please enter 1 				    \n");
	printf("		Entering the flight	 ,  please enter 2 				    \n");
	printf("		Exit login interface ,  please enter 3 				    \n");
	printf("login interface : 	");
}
	//显示管理员登陆界面图片，并且返回选择1，2，3
int Ad_login_fun_chioce(void *arg,struct list_node_pic*head1)
{
	
	
	//1.显示界面
	int connfd = *(int *)arg;
	administrator_interface();   //SRT登陆主界面
	ad_login_ch(head1); //LCD登陆主界面
	int choice_hh = 0 ;
	int y=0;
	int A = 0;
	int c;
	
	
//2.发送输入提示
	
	
	char bufi[50]= "============================\n" ;
	send(connfd,bufi,strlen(bufi),0);

	char buf4[50]="1.cancel_flight	\n" ;
	send(connfd,buf4,strlen(buf4),0);
	usleep(10000);
	char buf_5[50]="2.Enter_flight  \n" ;
	send(connfd,buf_5,strlen(buf_5),0);
	usleep(10000);
	char buf_2[50]="3.Exit.login    \n" ;
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


	//普通用户拥有登陆界面
int  user_interface()
{

	printf("===============================================================\n");
	printf("	Welcome to the user login interface:              \n");
	printf("		Display all flights ,     please enter 1 				    \n");
	printf("		Query flights	   ,      please enter 2 				    \n");
	printf("		Ticket purchase system ,  please enter 3 				    \n");
	printf("		Exit login , 			  please enter 4 				    \n");
	printf("user interface : 	");

}
	//显示普通登陆界面图片，并且返回选择1，2，3，4
int user_login_fun_chioce(void *arg,struct list_node_pic*head1)
{
	
	
	//1.显示界面
	int connfd = *(int *)arg;
	user_interface();   //SRT登陆主界面
	user_login_ch(head1); //LCD登陆主界面
	int choice_hh = 0 ;
	int y=0;
	int A = 0;
	int c;
	
	
//2.发送输入提示
	
	
	char bufi[50]= "============================\n" ;
	send(connfd,bufi,strlen(bufi),0);

	char buf4[50]="1.all_flights	\n" ;
	send(connfd,buf4,strlen(buf4),0);
	usleep(10000);
	char buf_5[50]="2.check_flights  \n" ;
	send(connfd,buf_5,strlen(buf_5),0);
	usleep(10000);
	
	char buf_2[50]="3.buy_Ticket_system    \n" ;
	send(connfd,buf_2,strlen(buf_2),0);
	usleep(10000);
	
	char buf_6[50]="4.Exit.login    \n" ;
	send(connfd,buf_6,strlen(buf_6),0);
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
			if(( 0<choice_hh ) &&( choice_hh<5 ) )
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
					
					if(y > 0 && y < 150 )
					{
						return 1;
					}

					if( y > 150 && y < 300 )
					{
						return 2;
					}
					if(y > 300 && y < 450 )
					{	
						return 3;
					}
					if(y > 450 && y < 600 )
					{	
						return 4;
					}
					
				}
			}
		}		
		if(FD_ISSET(STDIN_FILENO,&rset))//  测试下STDIN_FILENO 标准输入的文件描述符  是否在集合中
		{
			
			scanf("%d",&c);
			if(( 0<c) &&( c<5 ) )
			{
				return c;
			}
		}	
			
	
	
	}
	
	close(fd);
	return 0;
}



//搜索航班节点--有->0 ,没有-> -1
int sechor_show_list_hanban( struct list_node_hanban*head,char *name)
{
	struct list_head *p = NULL;		//-----------小结构体指针域
	struct list_node_hanban *tmp = NULL;
	int a;
	list_for_each(p,&(head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		tmp = list_entry(p,struct list_node_hanban,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(name,tmp->number);
		
		if(a == 0)
		{
			printf("The flight exists,lease continue do next \n");
			return 0;
		}
	}
	printf("The flight doesn't exist, You can enter the flight .\n");
	return -1;
}

	//删除该航班的链表节点
int delete_list_node(struct list_node_hanban *head,char *name)
{
	struct list_head *p = NULL;
	struct list_head *q = NULL;
	struct list_node_hanban *tmp = NULL;
	
	list_for_each_safe(p,q,&(head->list))//等同于for(q=head,p=head->next;p!=NULL;q=p,p=p->next)
	{
		tmp = list_entry(p,struct list_node_hanban,list);//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		if( strcmp( tmp->number,name ) == 0 )
		{
			list_del(p);//把节点脱离开链表，并且保证链表不断开，但是内存没有释放
			free(tmp);//释放内存
			return 0;
		}
	}
	return -1;
}

	//===========删除该航班的对应的文件，由下一个函数调用
int delete_file(char *file_name,char*delete_name)
{
	FILE *fp = NULL ;
	char str[50] = {0};
	
	char *q;
	char seps[] = ",";  //分隔的字符是","
	int j,m,n;
	
		//打开A001.TXT这个文件
		fp = fopen(file_name,"r");
		if(fp ==NULL)
		{
			printf(" delete_file_hangban -> fopen  error!\n");
			return 0;
		}
		fread(str,10,5,fp);
		
		q = strtok(str,seps);//一直读到“，”
		//printf("%s\n",q);
		if( strcmp(q,delete_name) == 0 )
		{
			m = remove(file_name);
			if(m == 0)
			{
				printf("remove success\n");
				return 0;
			}
			
		}
		
	return 1;
	
}
	//函数功能：删除该航班的对应文件
int delete_file_hangban(struct list_node_hanban*head,char*delete_name)
{

	
	
	int	ret,i,n,y,j;
	struct dirent *ep = NULL;
	struct dirent *ep1 = NULL;
	
	DIR * dp =NULL;
	chdir("/");
	system("pwd");
	
	//1. 访问目录文件
	dp = opendir("./data");
	if(dp == NULL)
		printf("opendir error!\n");
	
	//2. 切换到目录下
		ret = chdir("./data");
	if(ret == -1)
		printf("chdir error!\n");
	
	//3. 计算目录中总项数
	for(n=0; (ep=readdir(dp)) && (ep!= NULL); n++)
	{
		printf("ep->d_name = %s\n",ep->d_name);
	}//n=5
	
	//4. 定义数组的大小
	char *picname[n-2];
	
	//5. 重置指针
	rewinddir(dp);
	
	//6. 重新读取目录，将非隐藏文件文件名写入到数组中
	for(i=0;i<n-2;)
	{
		ep = readdir(dp);
		if(ep->d_name[0] == '.')
		{
			continue;
		}
		picname[i] = ep->d_name;//读到的时A001.TXT而不是A001
		y = delete_file(picname[i],delete_name);
		if(y == 0)
		{
			printf("delete_file success\n");
			rewinddir(dp);
			for(n=0; (ep=readdir(dp)) && (ep!= NULL); n++)
			{
				printf("ep->d_name = %s\n",ep->d_name);
			}
			/*
			char *pic[n-2];
			rewinddir(dp);
			for(j=0;j<n-2;)
			{
				ep = readdir(dp);
				if(ep->d_name[0] == '.')
				{
					continue;
				}
				pic[j] = ep->d_name;//读到的时A001.TXT而不是A001
				j++;
			}
			*/
			closedir(dp);
			return 0;
		}
		i++;
	}
	
	printf("delete_file fileure\n");
	closedir(dp);
	return 0;
}



	/**=遍历某节点航班链表======**/
void show_node_hangban(struct list_node_hanban *p)
{
	//printf("number	staddress	arraddress	data	type	stime	prine\n");
	
	printf("%s	",p-> number);
	printf("%s		",p->staddress);
	printf("%s		",p->arraddress);
	printf("%s	",p->data);
	printf("%c	",p->type);
	printf("%s		",p->stime);
	printf("%d	",p->prine);
	printf("\n");
	
}
	// 遍历全部航班信息			
int show_list_hangban(struct list_node_hanban *head)
{
	struct list_node_hanban *p = NULL;
	//for(p=r_head->next;p!=NULL;p=p->next)
	printf("number	staddress	arraddress	data		type	stime		prine\n");
	list_for_each_entry(p,&(head->list),list)
	{

		show_node_hangban(p);
	}
	
	return 0;
}

//void *arg,
//int connfd = *(int *)arg;
	//创建 以航班号来命名的文件，尾插到航班链表 ，并且写入到文件中
int xie_hangban_file(void *arg,struct list_node_hanban *head,char*cj_name)
{
	int connfd = *(int *)arg;
	struct list_head *p = NULL;		//-----------小结构体指针域
	struct list_node_hanban *tmp = NULL;
	int a;
	list_for_each(p,&(head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		tmp = list_entry(p,struct list_node_hanban,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(cj_name,tmp->number);
		
		if(a == 0)
		{
			printf("The flight exists！error\n");
			return 0;
		}
	}
	
	
	struct list_node_hanban*Node = NULL;
		Node = (struct list_node_hanban *)malloc(sizeof(struct list_node_hanban));
		if(Node == NULL)
			printf("malloc Node error!\n");
	
	int str[50];
	//----------------------------输入到数组作为缓冲区-----------
	char number[10];//A001
	char number_1[10];//A001.txt
	
	char staddress[10];//
	char arraddress[15];//
	char data[15];
	char type[3] ;
	char stime[10];
	int  prine;
	char prine_1[10];
	

//----------------number
	char buf_number[20]= "Enter:number\n" ;
	send(connfd,buf_number,strlen(buf_number),0);
	usleep(300000);
	
	char buf[20];
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);//A001
	strcpy(number,buf);
	strcpy(Node->number,number);//写到链表去
	
	strcpy(number_1,number);
	strcat(number_1,".txt");//A001.txt，作为文件名
	printf("%s\n",number_1);
	strcat(number,",");//写到文件去
	printf("%s\n",number);
	

//----------------staddress
	char buf_staddress[20]= "Enter:staddress\n" ;
	send(connfd,buf_staddress,strlen(buf_staddress),0);
	usleep(300000);
	
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(staddress,buf);
	strcpy(Node->staddress,staddress);//写到链表去
	
	strcat(staddress,",");
	printf("%s\n",staddress);
	
	
//----------------arraddress
	char buf_arraddress[20]= "Enter:arraddress\n" ;
	send(connfd,buf_arraddress,strlen(buf_arraddress),0);
	usleep(300000);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(arraddress,buf);
	
	strcpy(Node->arraddress,arraddress);//写到链表去
	strcat(arraddress,",");
	printf("%s\n",arraddress);
	
//----------------data
	char buf_data[20]= "Enter:data\n" ;
	send(connfd,buf_data,strlen(buf_data),0);
	usleep(300000);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(data,buf);
	
	strcpy(Node->data,data);//写到链表去
	strcat(data,",");
	printf("%s\n",data);	
	
//----------------type
	char buf_type[20]= "Enter:type\n" ;
	send(connfd,buf_type,strlen(buf_type),0);
	usleep(300000);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(type,buf);
	strcpy(&(Node-> type),type);//写到链表去
	
	strcat(type,",");
	printf("%s\n",type);	
		
//----------------stime
	char buf_stime[20]= "Enter:stime\n" ;
	send(connfd,buf_stime,strlen(buf_stime),0);
	usleep(300000);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(stime,buf);
	
	strcpy(Node->stime,stime);//写到链表去
	strcat(stime,",");
	printf("%s\n",stime);	
	
//----------------prine
	char buf_prine[20]= "Enter:prine\n" ;
	send(connfd,buf_prine,strlen(buf_prine),0);
	usleep(300000);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(prine_1,buf);
	
	prine = atoi(prine_1);
	Node->prine = prine;//写到链表去
	
	
	//strcat(prine_1,",");
	printf("%s\n",prine_1);		
	
	list_add_tail(&(Node->list),&(head->list));
	printf("number	staddress	arraddress	data	type	stime	prine\n");
	//printf("number	staddress	arraddress	data		type	stime		prine\n");
	show_node_hangban(Node);
	printf("lets yz yi xia \n");
	show_list_hangban(head);
	
	
	//---------------------------------------切换到该文件所在目录下--------------
	int	ret,i	;
	struct dirent *ep = NULL;
	DIR * dp =NULL;
	chdir("/");
	system("pwd");
	
	//1. 访问目录文件
	dp = opendir("/data");
	if(dp == NULL)
		printf("opendir error!\n");
	
	//2. 切换到目录下
		ret = chdir("/data");
	if(ret == -1)
		printf("chdir error!\n");


	//3.打开文件
	FILE *fp = fopen(number_1,"w+");
	//4.写如文件中
	fputs(number,fp);
	fputs( staddress,fp);
	fputs( arraddress,fp);
	fputs(data,fp);
	fputs( type,fp);
	fputs(stime,fp);
	fputs(prine_1,fp);
	
	//5.-------------验证一下写入的内容----------------------
	/**
	
	fseek(fp,0, SEEK_SET);
	printf("me write thing is : \n");
	fread(str,10,5,fp);
	printf("%s\n",str);
	//fseek(fp,0, SEEK_SET);
	hang_ban_xx(head,cj_name);
	
	fclose(fp);
	closedir(dp);
	return 0;
	**/
	
	fclose(fp);
	closedir(dp);
	return 0;
	
}



	//函数功能：显示所有航班，并且尾插到航班链表，由下一个函数调用 
int hang_ban_xx(struct list_node_hanban*head,const char *txt_name)
{	
	struct list_node_hanban*Node = NULL;
		Node = (struct list_node_hanban *)malloc(sizeof(struct list_node_hanban));
		if(Node == NULL)
			printf("malloc Node error!\n");
	char str[50] = {0};
	
	//打开改名字的文件
	FILE *fp = fopen(txt_name,"r+");
	if(fp ==NULL)
	{
		printf("error!\n");
		return 0;
	}
	
	fread(str,10,5,fp);
	printf("%s\n",str);
	//fseek(fp,0, SEEK_SET);
	
	char seps[] = ",";  //分隔的字符是什么
	char *q;
	q = strtok(str,seps);
	if(q == NULL)
		printf("strtok error \n");
	strcpy(Node->number,q);//A001
	
	q = strtok(NULL,seps); //第二次使用字符串时，就一定要置为NULL
	if(q == NULL)
		printf("strtok error \n");
	strcpy(Node->staddress,q);
	
	q = strtok(NULL,seps);
	if(q == NULL)
		printf("strtok error \n");
	strcpy(Node->arraddress,q);
	
	q = strtok(NULL,seps);
	if(q == NULL)
		printf("strtok error \n");
	strcpy(Node-> data,q);
	
	q = strtok(NULL,seps);
	if(q == NULL)
		printf("strtok error \n");
	strcpy(&(Node-> type),q);
	
	q = strtok(NULL,seps);
	strcpy( Node-> stime ,q);
	
	q = strtok(NULL,seps);
	if(q == NULL)
		printf("strtok error \n");
	Node-> prine =atoi(q);

	list_add_tail(&(Node->list),&(head->list));
	printf("number	staddress	arraddress	data		type	stime		prine\n");
	show_node_hangban(Node);
	fclose(fp);
	
	
	/**
	
	*/
	return 0;
}
	//函数功能：打开data目录，读出里面内容，显示所有航班信息
int login_hangban(struct list_node_hanban*head)
{
	int	ret,i,n;
	chdir("/");
	
	//1. 访问目录文件
	DIR * dp =NULL;
	//system("pwd");
	dp = opendir("/data/");
	if(dp == NULL)
		printf("opendir error!\n");
	
	//2. 切换到目录下
		ret = chdir("/data/");
	if(ret == -1)
		printf("chdir error!\n");
	//system("pwd");
	//3. 计算目录中总项数
	struct dirent *ep = NULL;
	for(n=0; (ep=readdir(dp)) && (ep!= NULL); n++)
	{
		printf("ep->d_name = %s\n",ep->d_name);
	}
	
	//4. 定义数组的大小
	char *picname[n-2];
	
	//5. 重置指针
	rewinddir(dp);
	
	//6. 重新读取目录，将非隐藏文件文件名写入到数组中
	for(i=0;i<n-2;)
	{
		ep = readdir(dp);
		if(ep->d_name[0] == '.')
		{
			continue;
		}
		//printf("li\n");
		//stpcpy(picname[i],ep->d_name);
		//printf("ep->d_name = %s\n",ep->d_name);
		hang_ban_xx(head,ep->d_name) ;
			i++;
	}
	
	

	closedir(dp);

	return 0;
}




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


int ad_login_fun(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head,struct list_node_login *l_head,struct list_node_hanban *head)
{
	int connfd = *(int *)arg;
	int a;
	char buf[10];
	char buf_1[20];
	
	int chioce ;
		
	while(1)
	{
		//显示管理员登陆界面图片，并且返回选择1，2，3
		chioce = Ad_login_fun_chioce(arg,head1);
		switch(chioce)
		{
			case 1 :
				{

					Cancel_the_flight(&connfd,head,head1);
				}break;
													
			case 2 :
				{
					enter_the_filght(&connfd,head) ;

				}break;
													
			default:
			{
				return 0;
			}break;//退出登陆
		}
	}
	
	return 0;
	

}	

	//1.显示某航班信息
int some_show_list_hangban(struct list_node_hanban *head,char *name)
{
	int a;
	struct list_head *p = NULL;
	struct list_node_hanban *tmp = NULL;
	list_for_each(p,&(head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		tmp = list_entry(p,struct list_node_hanban,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(name,tmp->number);
			if(a == 0)
			{
				printf("number	staddress	arraddress	data	type	stime	prine\n");
				show_node_hangban(tmp);
				return 0;
			}
	}
	printf("no this piane\n");
	return -1;
}


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



	//3.买票系统==================================================================
	/**====购票系统============================================================**/
	//购票结构体----》还可以找零钱----在购票链表中，假如购票人的名字，，在购票链表中假如登陆人的信息 ///（，，，登陆）
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
 

//===================遍历买票链表==================================================
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



//==========购票主界面----------
int buy_ticket_interface()
{

	printf("===============================================================\n");
	printf("	Welcome to Ticket purchase system:   			           \n");
	printf("	Buy_ticket ,           please enter 1 				    \n");
	printf("	check_tickets	,  please enter 2 				    \n");
	printf("	Return a ticket ,      please enter 3 				    \n");
	printf("	Alter tickets;endorse, please enter 4 				    \n");
	printf("	Exit    , 			   please enter other			     \n");
	printf("buy interface : 	");
	
}
	

//买票选择函数
int buy_Ticket_system_choice(void *arg,struct list_node_pic*head1)
{
	
	//1.显示界面
	int connfd = *(int *)arg;
	buy_ticket_interface();   //SRT登陆主界面
	buy_ticket_face(head1) ;//LCD登陆主界面
	int choice_hh = 0 ;
	int x=0;
	int A = 0;
	int c;
	
	
//2.发送输入提示
	
	
	char bufi[50]= "============================\n" ;
	send(connfd,bufi,strlen(bufi),0);

	char buf4[50]="1.Buy_ticket	\n" ;
	send(connfd,buf4,strlen(buf4),0);
	usleep(10000);
	char buf_5[50]="2.check_tickets \n" ;
	send(connfd,buf_5,strlen(buf_5),0);
	usleep(10000);
	
	char buf_2[50]="3.Return_ticket    \n" ;
	send(connfd,buf_2,strlen(buf_2),0);
	usleep(10000);
	
	char buf_6[50]="4.Alter_tickets  \n" ;
	send(connfd,buf_6,strlen(buf_6),0);
	usleep(10000);
	
	char buf_7[50]="5.exit  \n" ;
	send(connfd,buf_7,strlen(buf_7),0);
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
			if(( 0<choice_hh ) &&( choice_hh<6 ) )
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
				if(buf.type == EV_ABS && buf.code == ABS_X)
					x = buf.value;
				if(buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
				{
					
					if(x > 0 && x < 160 )
					{
						return 1;
					}

					if( x > 160 && x < 320 )
					{
						return 2;
					}
					if(x > 320 && x < 480 )
					{	
						return 3;
					}
					if(x > 480 && x < 640 )
					{	
						return 4;
					}
					if(x > 640 && x < 800 )
					{	
						return 5;
					}
					
				}
			}
		}		
		if(FD_ISSET(STDIN_FILENO,&rset))//  测试下STDIN_FILENO 标准输入的文件描述符  是否在集合中
		{
			
			scanf("%d",&c);
			if(( 0<c) &&( c<6 ) )
			{
				return c;
			}
		}	
			
	
	
	}
	
	close(fd);
	return 0;
}

//买票主函数：
//			买票，查票，退票，改签

//=====================买票函数============

int Buy_ticket_fun(void *arg,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_login *l_head,char*login_name,int ex_taxation)
{
	int connfd = *(int *)arg;
	float money ,f_money 	;
	int g_money  ;
	struct list_head *p = NULL;		
	struct list_node_hanban *tmp = NULL;
	
	//--------------购票节点空间--------------------------------------------
	struct list_node_buy_ticket *Node = NULL;
	Node = (struct list_node_buy_ticket*)malloc(sizeof(struct list_node_buy_ticket));
	if(Node == NULL)
		printf("malloc Node error!\n");
	
	
	char  f_name[10]; 
	int much_ticket ;
	
	char buf[30];
	
	char bufi[50]= "enter.your.flight.number:\n" ;
	send(connfd,bufi,strlen(bufi),0);
	usleep(300000);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strtok(buf,"\n");
	printf("%s\n",buf);
	strcpy(f_name,buf);
	

	int a;
	
	struct list_node_login *tmp1 = NULL;
	struct  list_head *q = NULL;
	
	int c;
	
	list_for_each(q,&(l_head->list))//等价于for(p=&(head->list)->next;p!= &(head->list);p=p->next)
	{
		tmp1 = list_entry(q,struct list_node_login,list);		
		c = strcmp(tmp1->name,login_name );
		if( c == 0)
		{
			strcpy(Node->name ,tmp1->name);
			Node->age = tmp1->age;
			strcpy(Node->tel , tmp1->tel);
			break;
		}
		
	}

	list_for_each(p,&(head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		tmp = list_entry(p,struct list_node_hanban,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(f_name,tmp->number);
		if(a == 0)//有该航班
		{
			printf("number	staddress	arraddress	data	type	stime	prine\n");
			show_node_hangban(tmp);//显示该航班的信息
					
			printf("The fare per ticket is %d\n",tmp->prine);//票价是
			printf("how mach ticket do you need:  "); 
	//输入你需要的票数		
			char buf_9[50]= "how.much.ticket:\n" ;
			send(connfd,buf_9,strlen(buf_9),0);
			usleep(300000);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			strtok(buf,"\n");
			printf("%s\n",buf);
			
			char much_ticket_1[10];
			strcpy(much_ticket_1,buf);
			much_ticket = atoi(much_ticket_1);
			
	//你需要支付的金额
			money = ( (tmp->prine)* much_ticket * ex_taxation );//ex_taxation-----税金
			
			printf("pls pay is %f\n",money);
			printf("please pay money :  ");
			
			char buf_8[50]= "please.pay.money:\n" ;
			send(connfd,buf_8,strlen(buf_8),0);
			usleep(100000);
			
			
			char buf_money[10];
			bzero(buf_money,sizeof(buf_money));
			
			sprintf(buf_money,"%f",money);//buf_money [] ="2000"
			strcat(buf_money,"\n");

			send(connfd,buf_money,strlen(buf_money),0);
			usleep(100000);

			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			strtok(buf,"\n");
			printf("%s\n",buf);
	
	
	//你实际支付的金额	
			char get_money[10];
			strcpy(get_money,buf);
			
			printf("The amount you actually paid is %s\n",get_money);
			
			g_money = atoi(get_money); 
			f_money = g_money - money ;//给你找的零钱
			if(f_money<0)
				printf("You don't have enough balance\n");
			else
			{
				//把内容写到航班链表中
				printf("Payment success\n");
				
				printf("give you money %f\n",f_money);
				
				strcpy(Node->number,tmp->number);
				strcpy(Node->staddress,tmp->staddress);
				strcpy(Node->arraddress,tmp->arraddress);
				strcpy(Node->data,tmp->data);
				Node->type = tmp->type;
				strcpy(Node->stime,tmp->stime);
				Node->prine = tmp->prine;
				Node->much = much_ticket;
				Node->money	= money;
				Node->get_money = g_money;
				Node->che_money =  f_money;
				show_node_buy_ticket(Node);
				list_add_tail(&(Node->list),&(g_head->list));
				//show_node_buy_ticket(Node);
				return 0;
			}
			
		
		}
		
	}
	return 0;
}
	//查询自己所购的票
int inquire_tickets(struct list_node_buy_ticket*g_head,char *logon_name)
{
	//int money ,g_money,f_money 	;
	struct list_head *p = NULL;		
	struct list_node_buy_ticket *tmp = NULL;
	
	int a;
	//查询自己的票，得看票链表上的节点->name,有没有自己的
	list_for_each(p,&(g_head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		tmp = list_entry(p,struct list_node_buy_ticket,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(logon_name,tmp->name);
		if(a == 0)
		{
			printf("Here is your ticket information\n");
			show_node_buy_ticket(tmp);
			return 0;
		}
	}	
	return -1;	
	
}

//========================================退票=========================================
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

	//退票函数----------------------------------------------------------
int Re_ticket(void *arg,struct list_node_buy_ticket*g_head,char *logon_name)
{
	int connfd = *(int *)arg;
	struct list_head *p = NULL;		
	struct list_node_buy_ticket *tmp = NULL;
	
	int a,b;
	//查询自己的票，得看票链表上的节点->name,有没有自己的
	list_for_each(p,&(g_head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{
		tmp = list_entry(p,struct list_node_buy_ticket,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(logon_name,tmp->name);
		if(a == 0)  //如果有你名字，你要退票，那就删除 该票节点
		{
			b = delete_list_node_re_ticket(g_head,logon_name);
			if(b != 0)
				printf("delete fail\n");

			int connfd = *(int *)arg;
			
			char bufi[50]= "Re_ticket.success\n" ;
			send(connfd,bufi,strlen(bufi),0);
			usleep(300000);
			return 0;
		}
	}
	return -1;
}

	//改签函数-------------------------------------------------------------	
int Alter_tickets(void *arg,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_login *l_head,char *login_name)
{	
	int connfd = *(int *)arg;
	struct list_head *p = NULL;		
	struct list_node_buy_ticket *tmp = NULL;
	
	int a,b;
	//查询自己的票，得看票链表上的节点->name,有没有自己的
	list_for_each(p,&(g_head->list))// 等价于for(p=(&(head->list))->next;p!= (&(head->list));p=p->next)
	{

		tmp = list_entry(p,struct list_node_buy_ticket,list); 		//根据小结构体(指针p)地址得到大结构体(tmp)的地址  
		a = strcmp(login_name,tmp->name);
		if(a == 0)  
		{	
			//如果有你名字，你要退票，那就删除 该票节点
			b = delete_list_node_re_ticket(g_head,login_name);
			if(b != 0)
				printf("delete fail\n");
			
			char bufi[50]= "Re_ticket.success\n" ;
			send(connfd,bufi,strlen(bufi),0);
			usleep(300000);
			char bufj[50]= "now.buy.ticekt\n" ;
			send(connfd,bufj,strlen(bufj),0);
			usleep(300000);
			
			//退了票，再购票,加到链表里，但是加收百分之十税金
			  Buy_ticket_fun(&connfd,head,g_head,l_head,login_name,1.1);
			return 0;
		}
	}
	return -1;
}





int buy_Ticket_system(void *arg,char *logon_name,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_login *l_head,struct list_node_pic*head1)
{
	int connfd = *(int *)arg;
	int buy_chioce ;
	int in_tic ;
	int re_tic ;
	int al_tic ;
	
	
	
while(1)
	{
		buy_chioce = buy_Ticket_system_choice(&connfd,head1);	
		if(buy_chioce == 1)//购票
		{
			printf("");
			Buy_ticket_fun(&connfd,head,g_head,l_head,logon_name,1);
			printf("The purchase of tickets was successful. You are welcome to buy tickets again.\n");
																	
		}																																				
		else if(buy_chioce == 2)//查询自己所购的票
		{
			in_tic = inquire_tickets(g_head,logon_name);//logon_name
			if(in_tic != 0)
			printf("inquire_tickets error\n");
		}
		else if(buy_chioce == 3)//退票
		{
			re_tic = Re_ticket(&connfd,g_head,logon_name);
			if(re_tic != 0)
			printf("re_ticket error\n");
		}
		else if (buy_chioce == 4)//改签
		{
			al_tic = Alter_tickets(&connfd,head,g_head,l_head,logon_name);
			if(al_tic != 0)
			printf("Alter_tickets error \n");
		}
		else//退出当前购票系统
		{
			printf("Please wait a minute , exit the current ticketing system \n");
			sleep(1);
			break;
		}	
	}
	
}

//logon_name,arg,g_head,head1,r_head,l_head,head

int user_login_fun(char *logon_name,void *arg,struct list_node_buy_ticket*g_head,struct list_node_pic*head1,struct list_node_reg *r_head,struct list_node_login *l_head,struct list_node_hanban *head)
{
	int connfd = *(int *)arg;
	int a;
	char buf[10];
	char buf_1[20];
	
	int chioce ;
		
	while(1)
	{
		//user_interface.bmp
		//显示管理员登陆界面图片，并且返回选择1，2，3
		chioce = user_login_fun_chioce(arg,head1);
		switch(chioce)
		{
			case 1 :
				{
					//2.1 显示所有航班，遍历航班链表
					show_list_hangban(head);
					
				}break;
													
			case 2 :
				{
					Query_flights(arg,head) ;

				}break;
			case 3 :
				{
					buy_Ticket_system(&connfd,logon_name,head,g_head,l_head,head1);

				}break;	
		
			default:
			{
				return 0;
			}break;//退出登陆
		}
	}
	
	return 0;
	

}	



//管理员登陆主函数
int Ad_login(void *arg,struct list_node_reg*r_head,struct list_node_login *l_head,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_pic*head1,char *delu_name,char*delu_pass)

{
	//给他登陆，让他拥有登陆节点struct list_node_reg
	login_fun(r_head,l_head,delu_name);
	//进入操作界面
	ad_login_fun(arg,head1,r_head,l_head,head);
	return 0;
}
//普通用户登陆主函数
int user_login(void *arg,struct list_node_reg*r_head,struct list_node_login *l_head,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_pic*head1,char *logon_name,char*delu_pass)
{
	//给他登陆，让他拥有登陆节点struct list_node_reg
	login_fun(r_head,l_head,logon_name);
	user_login_fun(logon_name,arg,g_head,head1,r_head,l_head,head);
	//logon_name,arg,g_head,head1,r_head,l_head,head
}

/**
函数功能：显示主登陆界面图片，并且返回选择1，2，3
		1.管理员登陆
		2。普通用户登陆
		3.退出登陆

**/
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


int heiping()
{
	//1.打开lcd--open-----------------------------------------------------
	int lcd = open("/dev/fb0",O_RDWR);//1.打开lcd--open
		if(lcd<0)
			printf("Open failure \n");
		
//2.申请映射空间-------------------------------------------------
	int *p = (int *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd,0);
		if(p==(void*)-1) //$$$$$$$$$$$$$$$$$$
			printf("mmap failure\n");
	
//3.拷贝往内存空间中填充颜色 -------------------------------------	

	int color = 0x00000000;
	int	i					;

	for(i=0;i<800*480;i++)
	{
		memcpy(p+i,&color,4);//$$$$$$$$$  memcpy(目标地址（p指向的映射空间），需要拷贝的内容的地址，拷贝的字节数)	
	}
	
// 4.撤销映射--------------------------------------------------------

	munmap(p,800*480*4);

	close(lcd);
	return 0;
}


int mian_interface()
{

	printf("============================================================\n");
	printf("		Welcome to the Desson Airlines 						\n");
	printf("				Press 1 to register							\n");
	printf("				Press 2 to login   							\n");
	printf("				Press 3 to exit  							\n");
	printf("============================================================\n");
	printf("Please enter your choice:  ");
	printf("\n");
	
}