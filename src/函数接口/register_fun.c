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


		//写入链表和文件**/
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