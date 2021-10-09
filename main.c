#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include"list.h"
#include"fun.h"
int main()
{
	int num=0;
	FILE*file=NULL;
	struct List *list=NULL;
	list=createList();	//创建链表 
	fileToList(list,"studentFile.txt");//把数据添加到链表中 
	SetConsoleTitle("学生成绩管理系统");
	void Menu()
	{
		printf("******学生成绩管理系统****\n"); 
		printf("******1.添加学生信息******\n"); 
		printf("******2.输出学生信息******\n");
		printf("******3.查询学生信息******\n");
		printf("******4.修改学生信息******\n");
		printf("******5.删除学生信息******\n");
		printf("******6.保存后退出********\n");
		printf("请选择：");
	}
	while(1)
	{
		system("cls");	//清屏 
		Menu();			//菜单栏 
		scanf("%d",&num);
		switch(num){
			case 1:
				system("cls");
				input(list); //添加 
			 	printf("请输入任意数字键\n返回上级菜单：");
			 	scanf("%d",&num);
				break;
			case 2:
				system("cls");
				output(list); //输出
				break; 
			case 3:
				system("cls");
				find(list);	//查询
				break; 
			case 4:
				system("cls");
				change(list); //修改 
				break;
			case 5:
				system("cls");
				Delete(list); //删除 
				break;
			case 6: 
				system("cls");
				listToFile(list,"studentFile.txt");//数据保存到文件中 
				destoryList(list); // 销毁链表
				quit();		 //退出画面 
				exit(0);
			default:
				printf("输入有误，请重新选择！\n");
				printf("请输入任意数字键\n返回上级菜单：");
			 	scanf("%d",&num);
				break;
		} 
	}
	return 0;
}
