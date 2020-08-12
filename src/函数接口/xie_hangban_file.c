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

