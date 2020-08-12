# project
	（1）项目名称：基于 LINUX的机场航班自助购票系统
	（2）项目描述： 该系统是用来提供自助购票和查询平台，主要模块有：注册管理、登陆管理、航班管理、购票管理。
    用户能够了解航班信息，实现在线购票，及时退票、改签；因天气等因素，管理员也可以及时地取消航班、录入新的航班信息
			
	（3）功能实现：
	【1】注册：管理员和普通用户的注册，使用链表保存人员信息并保存到文件中
	【2】登陆：收集登陆信息，管理员对航班增删改查，用户对查询航班并进行购票、退票和改签等操作
	（4）技术描述：
		○ 项目使用内核链表、文件IO操作实现对注册人员信息、登陆人员信息、航班信息、购票信息的存储
		○ 使用网络编程io模型的多路复用模型和tcp协议 进行服务器和客户端的通信。
    编写Makefile文件、制作嵌入式Linux的动态库 进行编译和生成可执行文件
