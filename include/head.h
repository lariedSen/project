#ifndef _HEAD_H_
#define _HEAD_H_
#include "senge.h"
#include"kernel_list.h"

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


struct list_node_hanban* init_list_head(struct list_node_hanban*head) ;
struct list_node_pic *init_list_head1(struct list_node_pic *head1) ;
struct list_node_reg * init_list_head2 (struct list_node_reg*r_head) ;
struct list_node_login * init_list_head3 (struct list_node_login*l_head) ;
struct list_node_buy_ticket* init_list_head4(struct list_node_buy_ticket*g_head) ; 


int mian_interface();
int heiping();
int tail_add_pic_list(struct list_node_pic *head1,char *picname);
int show_bmp(char*panme);
int sechor_show_list(struct list_node_pic*head1,char *picname);
int dir(struct list_node_pic*head1,char * picname)	;
int LCD_Welcome_interface(struct list_node_pic*head1);
int Welcome_chioce(struct list_node_pic*head1);
int reg_ch(struct list_node_pic*head1);
int login_ch(struct list_node_pic*head1);
int ad_login_ch(struct list_node_pic*head1);
int user_login_ch(struct list_node_pic*head1);
int buy_ticket_face(struct list_node_pic*head1);
int no1_pic(struct list_node_pic*head1) ;
int chioce_fun(void *arg,struct list_node_pic*head1);
 int tail_add_reg_list(struct list_node_reg *head1,char *name) ;
 void show_node(struct list_node_reg *p) ;
 int show_list(struct list_node_reg *r_head) ;
 void show_node_login(struct list_node_login *p) ;
 int show_list_login(struct list_node_login *l_head) ;
 char *check_login(struct list_node_login *l_head,char *name_buf) ;
 int tail_add_list_login(struct list_node_login *l_head,struct list_node_reg *tmp);
 int login_fun(struct list_node_reg * r_head, struct list_node_login *l_head, char *check_name);
 void zhuce_jiem();
 int register_fun_chioce(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head);
 char *check_registration(struct list_node_reg *r_head,char *name_buf);
 int register_fun(struct list_node_reg *r_head,void *arg);
 int Ad_reg(struct list_node_reg *r_head,void *arg);
 int user_reg(struct list_node_reg *r_head,void *arg) ;
 int register_fun_zon(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head) ;
 char *check_registration_pass(struct list_node_reg *r_head,char*pass_buf) ;
 int longin_jiem() ;
 int login_fun_chioce(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head);
 int  administrator_interface() ;
 
 int Ad_login_fun_chioce(void *arg,struct list_node_pic*head1) ;
 int  user_interface() ;
 int user_login_fun_chioce(void *arg,struct list_node_pic*head1) ;
 int sechor_show_list_hanban( struct list_node_hanban*head,char *name) ;
 int delete_list_node(struct list_node_hanban *head,char *name) ;
 int delete_file(char *file_name,char*delete_name);
 void show_node_hangban(struct list_node_hanban *p) ;
 int show_list_hangban(struct list_node_hanban *head) ;
 int xie_hangban_file(void *arg,struct list_node_hanban *head,char*cj_name) ;
 int hang_ban_xx(struct list_node_hanban*head,const char *txt_name) ;
 int login_hangban(struct list_node_hanban*head) ;
 int Cancel_the_flight(void *arg,struct list_node_hanban *head,struct list_node_pic*head1) ;
 int enter_the_filght(void *arg,struct list_node_hanban *head) ;
 int ad_login_fun(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head,struct list_node_login *l_head,struct list_node_hanban *head);
 int some_show_list_hangban(struct list_node_hanban *head,char *name) ;
 int Query_flights(void *arg,struct list_node_hanban *head) ;
 void show_node_buy_ticket(struct list_node_buy_ticket *p) ;
 int buy_ticket_interface() ;
 int buy_Ticket_system_choice(void *arg,struct list_node_pic*head1);
 int Buy_ticket_fun(void *arg,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_login *l_head,char*login_name,int ex_taxation) ;
 int inquire_tickets(struct list_node_buy_ticket*g_head,char *logon_name) ;
 int delete_list_node_re_ticket(struct list_node_buy_ticket *g_head,char *name);
 int Re_ticket(void *arg,struct list_node_buy_ticket*g_head,char *logon_name) ;
 int Alter_tickets(void *arg,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_login *l_head,char *login_name) ;
 int buy_Ticket_system(void *arg,char *logon_name,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_login *l_head,struct list_node_pic*head1) ;
 int user_login_fun(char *logon_name,void *arg,struct list_node_buy_ticket*g_head,struct list_node_pic*head1,struct list_node_reg *r_head,struct list_node_login *l_head,struct list_node_hanban *head) ;
 int Ad_login(void *arg,struct list_node_reg*r_head,struct list_node_login *l_head,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_pic*head1,char *delu_name,char*delu_pass) ;
 int user_login(void *arg,struct list_node_reg*r_head,struct list_node_login *l_head,struct list_node_hanban *head,struct list_node_buy_ticket*g_head,struct list_node_pic*head1,char *logon_name,char*delu_pass) ;
 int login_fun_zon(void *arg,struct list_node_pic*head1,struct list_node_reg *r_head,struct list_node_login *l_head,struct list_node_hanban *head,struct list_node_buy_ticket*g_head) ;
 
 
 
 
#endif