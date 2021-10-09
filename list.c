#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"list.h"
#include"fun.h"
//�������� 
struct List* createList()
{
	struct List *list;
	list=(struct List*)malloc(sizeof(struct List));
	list->head=NULL;
	list->size=0;
	return list;
}
//�������� 
void destoryList(struct List *list)
{
	struct Node *temp=list->head,*del=NULL;
	while(temp)
	{
		del=temp;
		temp=temp->next;
		free(del);//�ͷŽڵ�ռ� 
		list->size--; 
	}
	free(list);//�ͷ�����ռ� 
}
//�����ڵ� 
struct Node* createNode(struct Student student)
{
	struct Node *node=NULL;
	node=(struct Node*)malloc(sizeof(struct Node));
	node->student=student;
	node->next=NULL;
	return node;
}
//��ȡ�������һ���ڵ� 
struct Node* getLastNode(struct List *list)
{
	struct Node *temp=list->head,*last=NULL;
	while(temp)
	{
		last=temp;
		temp=temp->next;
	}
	return last;
}
//��ȡ��ǰ�ڵ����һ���ڵ� 
struct Node* getBeforeNode(struct List *list,struct Student student)
{
	struct Node *temp=list->head,*prevNode=NULL;
	while(temp)
	{
		if(strcmp(temp->student.id,student.id)==0)
		{
			break;
		}
		prevNode=temp;
		temp=temp->next;
	}
	return prevNode;
}
//���ڵ���ӵ������� 
void addList(struct List *list, struct Node *node)
{
	struct Node *last;
 	if(list->head==NULL)
 	{
 		list->head=node;
 	}
 	else
 	{
	 	last=getLastNode(list);
		last->next=node;	
 	}
 	list->size++;
}
