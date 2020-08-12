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