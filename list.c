#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"list.h"
#include"fun.h"
//创建链表 
struct List* createList()
{
	struct List *list;
	list=(struct List*)malloc(sizeof(struct List));
	list->head=NULL;
	list->size=0;
	return list;
}
//销毁链表 
void destoryList(struct List *list)
{
	struct Node *temp=list->head,*del=NULL;
	while(temp)
	{
		del=temp;
		temp=temp->next;
		free(del);//释放节点空间 
		list->size--; 
	}
	free(list);//释放链表空间 
}
//创建节点 
struct Node* createNode(struct Student student)
{
	struct Node *node=NULL;
	node=(struct Node*)malloc(sizeof(struct Node));
	node->student=student;
	node->next=NULL;
	return node;
}
//获取链表最后一个节点 
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
//获取当前节点的上一个节点 
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
//将节点添加到链表中 
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
