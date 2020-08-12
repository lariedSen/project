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
