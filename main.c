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
	list=createList();	//�������� 
	fileToList(list,"studentFile.txt");//��������ӵ������� 
	SetConsoleTitle("ѧ���ɼ�����ϵͳ");
	void Menu()
	{
		printf("******ѧ���ɼ�����ϵͳ****\n"); 
		printf("******1.���ѧ����Ϣ******\n"); 
		printf("******2.���ѧ����Ϣ******\n");
		printf("******3.��ѯѧ����Ϣ******\n");
		printf("******4.�޸�ѧ����Ϣ******\n");
		printf("******5.ɾ��ѧ����Ϣ******\n");
		printf("******6.������˳�********\n");
		printf("��ѡ��");
	}
	while(1)
	{
		system("cls");	//���� 
		Menu();			//�˵��� 
		scanf("%d",&num);
		switch(num){
			case 1:
				system("cls");
				input(list); //��� 
			 	printf("�������������ּ�\n�����ϼ��˵���");
			 	scanf("%d",&num);
				break;
			case 2:
				system("cls");
				output(list); //���
				break; 
			case 3:
				system("cls");
				find(list);	//��ѯ
				break; 
			case 4:
				system("cls");
				change(list); //�޸� 
				break;
			case 5:
				system("cls");
				Delete(list); //ɾ�� 
				break;
			case 6: 
				system("cls");
				listToFile(list,"studentFile.txt");//���ݱ��浽�ļ��� 
				destoryList(list); // ��������
				quit();		 //�˳����� 
				exit(0);
			default:
				printf("��������������ѡ��\n");
				printf("�������������ּ�\n�����ϼ��˵���");
			 	scanf("%d",&num);
				break;
		} 
	}
	return 0;
}
