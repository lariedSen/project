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