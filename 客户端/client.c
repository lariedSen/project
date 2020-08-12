#include "senge.h"

//任务： 负责接收消息。
void *routine(void *arg) //arg = &connfd
{
	int sockfd = *(int *)arg;
	
	char buf[50];
	while(1)
	{
		bzero(buf,sizeof(buf));
		recv(sockfd,buf,sizeof(buf),0);
		printf("%s",buf);
		
		if(strncmp(buf,"quit",4) == 0)
		{
			exit(0);
		}
	}
}

int main(int argc,char *argv[]) //./client 192.168.90.2 50001
{
//1. 创建一个未连接套接字
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("sockfd = %d\n",sockfd); //3
	
//2. 直接发起连接
	struct sockaddr_in srvaddr;

	socklen_t len = sizeof(srvaddr);  //len -> 结构体的大小
	bzero(&srvaddr,len);
	
	srvaddr.sin_family = AF_INET;// 地址族 = 网际协议
	srvaddr.sin_port = htons(atoi(argv[2])); //端口号16位 2个字节 = htons -> 本地转网络
	
	//2.3 将文本地址转化为二进制地址
	inet_pton(AF_INET,argv[1],&srvaddr.sin_addr);
	
	//2.4 connect 连接对端监听套接字
	int ret = connect(sockfd,(struct sockaddr *)&srvaddr,len);
	if(ret == -1)
		printf("connect error!\n");
	
	//2.5 创建线程
	pthread_t tid;
	pthread_create(&tid,NULL,routine,(void *)&sockfd);
	
	//3. 不断发送数据给服务器
	char buf[50];
	while(1)
	{
		bzero(buf,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		send(sockfd,buf,strlen(buf),0);

		if(strncmp(buf,"quit",4) == 0)
		{
			break;
		}
	}
	
	//4. 挂断电话
	close(sockfd);
	
	return 0;
}