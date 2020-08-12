#include "senge.h"
#include"kernel_list.h"
#include "head.h" 

//=====================买票函数============


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