#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include"list.h"
#include"fun.h" 
//打开文件 
FILE* openFile(char *filename,char *type)
{
	FILE*file=fopen(filename,type);
	if(file==NULL)
	{
		printf("打开%s文件失败！\n",filename);
		return NULL; 
	}
	return file;
}
//文件数据添加到链表中 
void fileToList(struct List *list,char *filename)
{
	int count=0;
	struct Student student;
	struct Node *node=NULL; 
	FILE*file=openFile(filename,"r");
	if(file==NULL)return;
	while(1)
	{
		count=fscanf(file,"%d%s%s%f%f%f%f\n",&student.class_num,student.id,student.name,\
		&student.score[0],&student.score[1],&student.score[2],&student.sum);
		student.sum=student.score[0]+student.score[1]+student.score[2]; 
		if(count<=0)break;
		node=createNode(student);//创建节点 
	 	addList(list,node);//添加到链表 
	}
	fclose(file); 	
}
//将链表数据存储到文件中 
void listToFile(struct List *list,char *filename)
{
	struct Node *temp=list->head;
	FILE*file=openFile(filename,"w");
	if(file==NULL)return;
	while(temp)
	{
		fprintf(file,"%d\t%s\t%s\t%.0f\t%.0f\t%.0f\t%.0f\n",temp->student.class_num,temp->student.id,temp->student.name,\
		temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum);
		temp=temp->next;
	}
	fclose(file);
}
//添加学生信息 
void input(struct List *list)
{
	struct Student student; 
	struct Node *node=NULL;
	struct Node *temp;
	int x,i,flag;
	while(1)
	{
		flag=1;
		printf("请输入该学生信息的班级、学号、姓名\n-->");
	 	scanf("%d %s %s",&student.class_num,student.id,student.name);
		temp=list->head;
		while(temp)
		{
			if(strcmp(temp->student.id,student.id)==0)
			{
				printf("您输入的学号已存在！\n");
				flag=0;
			}					
			temp=temp->next;			//当前链表的下一个节点
		}
		if(flag)
		{
			printf("请输入该学生的每门成绩\n数学：");
			scanf("%f",&student.score[0]);
			printf("英语：");
			scanf("%f",&student.score[1]);
			printf("计算机：");
			scanf("%f",&student.score[2]);
			student.sum=0;
			for(i=0;i<3;i++)
			{
				student.sum+=student.score[i];
			}
	 		node=createNode(student);	//创建节点 
	 		addList(list,node);			//添加到链表 
		}
	 	printf("退出请按数字0，其他数字键继续添加：");
	 	scanf("%d",&x);
	 	if(x==0)break; 
	} 
}
//按总成绩排序 
void sort(struct List *list)
{
	int i,j; 
	struct Student s;
	struct Node *temp=NULL,*temp1=NULL,*temp2=NULL;
	for(i=0;i<list->size-1;i++)
	{
		temp=list->head;
		for(j=0;j<list->size-i-1;j++)
		{
			temp1=temp;
			temp2=temp->next;
			if(temp1->student.sum<temp2->student.sum)
			{
				s=temp1->student;
				temp1->student=temp2->student;
				temp2->student=s;
			}
			temp=temp->next;			//当前链表的下一个节点
		}
	}
}
//输出学生信息 
void output(struct List *list)
{
	int cnt=0,num=0,class_num=0,i;
	float av_math=0,av_eng=0,av_se=0;
	float pass[3],min[3],max[3];
	struct Node *temp=list->head;
	if(list->size==0)
	{
		printf("抱歉，暂无学生信息！\n");
		return;
	}
	sort(list);						//排序 
	system("cls");
	while(1)
	{	
		system("cls");
		printf("*******1.本专业学生成绩分析******\n");
		printf("*******2.按班级显示成绩分析******\n");
		printf("*******3.退出********************\n");
		printf("请选择：");
		scanf("%d",&num);
		cnt=0;
		system("cls");
		temp=list->head;
		av_math=av_eng=av_se=0;
		pass[0]=pass[1]=pass[2]=0; 
		switch(num)
		{
			case 1:
				for(i=0;i<35;i++)
					printf("*");
				printf("本专业学生成绩分析");
				for(i=0;i<35;i++)
					printf("*"); 
				printf("\n\n%s\t%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","序号","班级","学号","姓名","数学","英语","计算机","总成绩","平均分");
				while(temp)
				{
					cnt++;
					printf(" %d\t %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\t %.2f\n",cnt,temp->student.class_num,temp->student.id,temp->student.name,\
					temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum,temp->student.sum/3);
					av_math+=temp->student.score[0];
					av_eng+=temp->student.score[1];
					av_se+=temp->student.score[2];
					if(cnt==1)
					{
						for(i=0;i<3;i++)
						{
							max[i]=min[i]=temp->student.score[i];
						}
					}
					for(i=0;i<3;i++)
					{
						if(temp->student.score[i]>=60)
						{
							pass[i]+=100;
						}
						if(temp->student.score[i]>max[i])
						{
							max[i]=temp->student.score[i];
						}
						if(temp->student.score[i]<min[i])
						{
							min[i]=temp->student.score[i];
						}
					}
					temp=temp->next;	//当前链表的下一个节点
				} 
				printf("\n数学-->最高分：%.0f\t最低分：%.0f\t平均分：%.2f\t及格率：%.2f%%\n",\
				max[0],min[0],av_math/cnt,pass[0]/cnt);
				printf("英语-->最高分：%.0f\t最低分：%.0f\t平均分：%.2f\t及格率：%.2f%%\n",\
				max[1],min[1],av_eng/cnt,pass[1]/cnt);
				printf("计算机-->最高分：%.0f\t最低分：%.0f\t平均分：%.2f\t及格率：%.2f%%\n",\
				max[2],min[2],av_se/cnt,pass[2]/cnt);
				system("pause");
				break;
			case 2:
				printf("请输入班级：");
				scanf("%d",&class_num);
				for(i=0;i<37;i++)
					printf("*");
				printf("%d班学生成绩表",class_num);
				for(i=0;i<37;i++)
					printf("*");  
				printf("\n\n%s\t%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","序号","班级","学号","姓名","数学","英语","计算机","总成绩","平均分");
				while(temp)
				{
					if(temp->student.class_num==class_num)
					{
						cnt++;
						printf(" %d\t %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\t %.2f\n",cnt,temp->student.class_num,temp->student.id,temp->student.name,\
						temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum,temp->student.sum/3);	
						av_math+=temp->student.score[0];
						av_eng+=temp->student.score[1];
						av_se+=temp->student.score[2];
						if(cnt==1)
						{
							for(i=0;i<3;i++)
							{
								max[i]=min[i]=temp->student.score[i];
							}
						}
						for(i=0;i<3;i++)
						{
							if(temp->student.score[i]>=60)
							{
								pass[i]+=100;
							}
							if(temp->student.score[i]>max[i])
							{
								max[i]=temp->student.score[i];
							}
							if(temp->student.score[i]<min[i])
							{
								min[i]=temp->student.score[i];
							}
						}
					}
					temp=temp->next;		//当前链表的下一个节点 
				} 
				if(cnt==0)
				{
					printf("%d班级，暂无学生信息！\n",class_num);
					break;
				}
				printf("\n数学-->最高分：%.0f\t最低分：%.0f\t平均分：%.2f\t及格率：%.2f%%\n",\
				max[0],min[0],av_math/cnt,pass[0]/cnt);
				printf("英语-->最高分：%.0f\t最低分：%.0f\t平均分：%.2f\t及格率：%.2f%%\n",\
				max[1],min[1],av_eng/cnt,pass[1]/cnt);
				printf("计算机-->最高分：%.0f\t最低分：%.0f\t平均分：%.2f\t及格率：%.2f%%\n",\
				max[2],min[2],av_se/cnt,pass[2]/cnt);
				system("pause");
				break;
			case 3:
				return; 
			default:
				printf("输入有误，请重新输入！\n");
				system("pause");
				break; 
		}	
	}	
}
//查找学生信息 
void find(struct List *list)
{
	int num,class_num; 
	char id[10],name[10];	//学号、姓名 
	struct Node *temp;	
	if(list->size==0)
	{
		printf("抱歉，暂无学生信息！\n");
		return;
	}
	while(1)
	{
		system("cls");		//清屏 
		printf("*******1.按学号查询******\n");
		printf("*******2.按姓名查询******\n");
		printf("*******3.退出************\n");
		printf("请选择：");
		scanf("%d",&num);
		system("cls");
		temp=list->head;	//每循环一次该节点重新作为头节点 
		switch(num)
		{
		   case 1:
			   	printf("请输入要查找学生信息的学号："); 
				scanf("%s",id);
				while(temp)
				{
					if(strcmp(temp->student.id,id)==0)break;	//查找学号 
					temp=temp->next;
				}
				if(temp)
				{
					printf("查找到该学生信息为：\n");
					printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","班级","学号","姓名","数学","英语","计算机","总成绩","平均分");
					printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\t %.2f\n",temp->student.class_num,temp->student.id,temp->student.name,\
					temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum,temp->student.sum/3);
				} 
				else
				{
					printf("抱歉，不存在该学生信息！\n");
				}
				system("pause");
				break;
		   case 2:
			   printf("请输入要查找学生信息的班级、姓名：");
			   scanf("%d %s",&class_num,name);
			   	while(temp)
				{
					/* 查找班级、学号*/ 
					if(temp->student.class_num==class_num && strcmp(temp->student.name,name)==0) 
					{ 
						break;
					} 
					temp=temp->next;	//当前链表的下一个节点 
				}
				//输出该学生信息 
				if(temp)
				{
					printf("查找到该学生信息为：\n");
					printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","班级","学号","姓名","数学","英语","计算机","总成绩","平均分");
					printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\t %.2f\n",temp->student.class_num,temp->student.id,temp->student.name,\
					temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum,temp->student.sum/3);
				} 
				else
				{
					printf("抱歉，不存在该学生信息！\n");
				}
				system("pause");
				break;
		   case 3:
				return; 
			default:
				printf("输入有误，请重新输入！\n");
				system("pause");
				break; 
		}
	}

}
//修改具体细节 
void detail(struct Node *temp)
{
	char id[10];	//学号 
	int num=0,x;
	printf("\n******信息修改********");
	printf("\n******1.班级修改******");
	printf("\n******2.学号修改******");
	printf("\n******3.姓名修改******");
	printf("\n******4.成绩修改******");
	printf("\n******5.退出**********\n");
	while(1)
	{
		printf("请选择：");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
					printf("请您输入修改后的班级号为：");
					scanf("%d",&temp->student.class_num);
					break;
			case 2:
					printf("请您输入修改后的学号为：");
					scanf("%s",temp->student.id);
					break;
			case 3:
					printf("请您输入修改后的姓名为：");
					scanf("%s",temp->student.name);
					break;
			case 4:
					printf("请您修改该同学的成绩为：\n");
					printf("数学--英语--计算机\n-->");
					scanf("%f %f %f",&temp->student.score[0],&temp->student.score[1],&temp->student.score[2]);
					temp->student.sum=temp->student.score[0]+temp->student.score[1]+temp->student.score[2];
					system("pause");
					break;
			case 5:
				return;
			default:
				printf("您输入有误,请重新输入!");
				break; 
		} 
		printf("退出请按数字0，其他数字键继续修改：");
		scanf("%d",&x);
		if(x==0)break;
	}
}
//修改学生信息 
void change(struct List *list)
{
	char id[10],flag=1;
	struct Student student;
	struct Node *temp=list->head;	//把新节点作为头节点 
	if(list->size==0)				//若链表空间大小为0，则返回上级 
	{
		printf("抱歉，暂无学生信息！\n");
		return;
	}
	printf("请输入要修改学生信息的学号："); 
	scanf("%s",id);
	while(temp)
	{
		if(strcmp(temp->student.id,id)==0)	//查找学号 
		{
			printf("当前该学生信息为：\n"); 
			printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\n","班级","学号","姓名","数学","英语","计算机","总成绩");
			printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\n",temp->student.class_num,temp->student.id,temp->student.name,\
			temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum);
			detail(temp);
			printf("修改成功！\n");
			flag=0; 
			break;
		}
		temp=temp->next;		//当前链表的下一个节点
	}
	if(flag)
	{
		printf("抱歉，不存在该学生信息，无法修改！\n");
	}
}
//删除 
void Delete(struct List *list)
{
	char id[10];
	int flag,x;
	struct Node *temp,*prevNode=NULL;	//建立新头节点prevNode 
	while(1)
	{	
		temp=list->head;				//每循环一次该节点重新作为头节点
		if(list->size==0)				//若链表空间大小为0，则结束循环 
		{
			printf("\n抱歉，暂无学生信息！\n");
			break;
		}
		flag=1;
		printf("请输入要删除学生信息的学号："); 
		scanf("%s",id);		
		while(temp)
		{
			if(strcmp(temp->student.id,id)==0)
			{
				printf("删除的该学生信息为：\n");
				printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\n","班级","学号","姓名","数学","英语","计算机","总成绩");
				printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\n",temp->student.class_num,temp->student.id,temp->student.name,\
			temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum);
				/*找到前一个节点，再与后一个节点连接 */
				prevNode=getBeforeNode(list,temp->student);  
				
				if(prevNode==NULL)				//删除的是头节点 
				{				
					list->head=temp->next; 
				}
				else
				{
					prevNode->next=temp->next;	//删除的是普通节点 
				}
				flag=0;							
				free(temp);						//释放temp所指的空间内存 
				temp=NULL;						//将该节点为空 
				list->size--;					//该 
				printf("\n该学生信息删除成功！\n");
				break;
			}
			temp=temp->next;					//当前链表的下一个节点
		}
		if(flag)
		{
			printf("\n抱歉，不存在该学生信息，无法删除！\n\n");
		} 
		printf("\n退出请按数字0，其他数字键继续删除操作：");
	 	scanf("%d",&x);
	 	if(x==0)break; 
	}
	system("pause");
} 
//退出画面 
void quit()
{
	int i,j,k;
	for(k=0;k<5;k++)
		printf("\n");
	for(i=0;i<21;i++)
	{
		for(k=0;k<i;k++)
		{
			printf(" ");
		}
		for(j=0;j<80;j++)
		{
			if(i==10)
			{
				for(k=0;k<29;k++)
				{
					printf("*");
				}
				printf("—> 感谢您的使用！ <—");
				for(k=0;k<29;k++)
				{
					printf("*");
				}
				break;
			}
			printf("*");
		}
		printf("\n");
	}
	for(k=0;k<5;k++)
		printf("\n");
}
