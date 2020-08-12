#include "senge.h"
#include"kernel_list.h"
#include "head.h"

struct list_node_reg{
	char name[10];
	int  age;
	char tel[15];
	char password_i[10];
	struct  list_head list;
};
	//显示某注册节点的信息
 void show_node(struct list_node_reg *p)
{
	printf("name:%s\n",p->name);
	printf("passwd:%s\n",p->password_i);
	printf("age = %d\n",p->age);
	printf("tel = %s\n",p->tel);
	
	return;
}