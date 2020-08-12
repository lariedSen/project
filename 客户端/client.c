#include "senge.h"

//���� ���������Ϣ��
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
//1. ����һ��δ�����׽���
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("sockfd = %d\n",sockfd); //3
	
//2. ֱ�ӷ�������
	struct sockaddr_in srvaddr;

	socklen_t len = sizeof(srvaddr);  //len -> �ṹ��Ĵ�С
	bzero(&srvaddr,len);
	
	srvaddr.sin_family = AF_INET;// ��ַ�� = ����Э��
	srvaddr.sin_port = htons(atoi(argv[2])); //�˿ں�16λ 2���ֽ� = htons -> ����ת����
	
	//2.3 ���ı���ַת��Ϊ�����Ƶ�ַ
	inet_pton(AF_INET,argv[1],&srvaddr.sin_addr);
	
	//2.4 connect ���ӶԶ˼����׽���
	int ret = connect(sockfd,(struct sockaddr *)&srvaddr,len);
	if(ret == -1)
		printf("connect error!\n");
	
	//2.5 �����߳�
	pthread_t tid;
	pthread_create(&tid,NULL,routine,(void *)&sockfd);
	
	//3. ���Ϸ������ݸ�������
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
	
	//4. �Ҷϵ绰
	close(sockfd);
	
	return 0;
}