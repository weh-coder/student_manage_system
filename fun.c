#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include"list.h"
#include"fun.h" 
//���ļ� 
FILE* openFile(char *filename,char *type)
{
	FILE*file=fopen(filename,type);
	if(file==NULL)
	{
		printf("��%s�ļ�ʧ�ܣ�\n",filename);
		return NULL; 
	}
	return file;
}
//�ļ�������ӵ������� 
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
		node=createNode(student);//�����ڵ� 
	 	addList(list,node);//��ӵ����� 
	}
	fclose(file); 	
}
//���������ݴ洢���ļ��� 
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
//���ѧ����Ϣ 
void input(struct List *list)
{
	struct Student student; 
	struct Node *node=NULL;
	struct Node *temp;
	int x,i,flag;
	while(1)
	{
		flag=1;
		printf("�������ѧ����Ϣ�İ༶��ѧ�š�����\n-->");
	 	scanf("%d %s %s",&student.class_num,student.id,student.name);
		temp=list->head;
		while(temp)
		{
			if(strcmp(temp->student.id,student.id)==0)
			{
				printf("�������ѧ���Ѵ��ڣ�\n");
				flag=0;
			}					
			temp=temp->next;			//��ǰ�������һ���ڵ�
		}
		if(flag)
		{
			printf("�������ѧ����ÿ�ųɼ�\n��ѧ��");
			scanf("%f",&student.score[0]);
			printf("Ӣ�");
			scanf("%f",&student.score[1]);
			printf("�������");
			scanf("%f",&student.score[2]);
			student.sum=0;
			for(i=0;i<3;i++)
			{
				student.sum+=student.score[i];
			}
	 		node=createNode(student);	//�����ڵ� 
	 		addList(list,node);			//��ӵ����� 
		}
	 	printf("�˳��밴����0���������ּ�������ӣ�");
	 	scanf("%d",&x);
	 	if(x==0)break; 
	} 
}
//���ܳɼ����� 
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
			temp=temp->next;			//��ǰ�������һ���ڵ�
		}
	}
}
//���ѧ����Ϣ 
void output(struct List *list)
{
	int cnt=0,num=0,class_num=0,i;
	float av_math=0,av_eng=0,av_se=0;
	float pass[3],min[3],max[3];
	struct Node *temp=list->head;
	if(list->size==0)
	{
		printf("��Ǹ������ѧ����Ϣ��\n");
		return;
	}
	sort(list);						//���� 
	system("cls");
	while(1)
	{	
		system("cls");
		printf("*******1.��רҵѧ���ɼ�����******\n");
		printf("*******2.���༶��ʾ�ɼ�����******\n");
		printf("*******3.�˳�********************\n");
		printf("��ѡ��");
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
				printf("��רҵѧ���ɼ�����");
				for(i=0;i<35;i++)
					printf("*"); 
				printf("\n\n%s\t%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","���","�༶","ѧ��","����","��ѧ","Ӣ��","�����","�ܳɼ�","ƽ����");
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
					temp=temp->next;	//��ǰ�������һ���ڵ�
				} 
				printf("\n��ѧ-->��߷֣�%.0f\t��ͷ֣�%.0f\tƽ���֣�%.2f\t�����ʣ�%.2f%%\n",\
				max[0],min[0],av_math/cnt,pass[0]/cnt);
				printf("Ӣ��-->��߷֣�%.0f\t��ͷ֣�%.0f\tƽ���֣�%.2f\t�����ʣ�%.2f%%\n",\
				max[1],min[1],av_eng/cnt,pass[1]/cnt);
				printf("�����-->��߷֣�%.0f\t��ͷ֣�%.0f\tƽ���֣�%.2f\t�����ʣ�%.2f%%\n",\
				max[2],min[2],av_se/cnt,pass[2]/cnt);
				system("pause");
				break;
			case 2:
				printf("������༶��");
				scanf("%d",&class_num);
				for(i=0;i<37;i++)
					printf("*");
				printf("%d��ѧ���ɼ���",class_num);
				for(i=0;i<37;i++)
					printf("*");  
				printf("\n\n%s\t%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","���","�༶","ѧ��","����","��ѧ","Ӣ��","�����","�ܳɼ�","ƽ����");
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
					temp=temp->next;		//��ǰ�������һ���ڵ� 
				} 
				if(cnt==0)
				{
					printf("%d�༶������ѧ����Ϣ��\n",class_num);
					break;
				}
				printf("\n��ѧ-->��߷֣�%.0f\t��ͷ֣�%.0f\tƽ���֣�%.2f\t�����ʣ�%.2f%%\n",\
				max[0],min[0],av_math/cnt,pass[0]/cnt);
				printf("Ӣ��-->��߷֣�%.0f\t��ͷ֣�%.0f\tƽ���֣�%.2f\t�����ʣ�%.2f%%\n",\
				max[1],min[1],av_eng/cnt,pass[1]/cnt);
				printf("�����-->��߷֣�%.0f\t��ͷ֣�%.0f\tƽ���֣�%.2f\t�����ʣ�%.2f%%\n",\
				max[2],min[2],av_se/cnt,pass[2]/cnt);
				system("pause");
				break;
			case 3:
				return; 
			default:
				printf("�����������������룡\n");
				system("pause");
				break; 
		}	
	}	
}
//����ѧ����Ϣ 
void find(struct List *list)
{
	int num,class_num; 
	char id[10],name[10];	//ѧ�š����� 
	struct Node *temp;	
	if(list->size==0)
	{
		printf("��Ǹ������ѧ����Ϣ��\n");
		return;
	}
	while(1)
	{
		system("cls");		//���� 
		printf("*******1.��ѧ�Ų�ѯ******\n");
		printf("*******2.��������ѯ******\n");
		printf("*******3.�˳�************\n");
		printf("��ѡ��");
		scanf("%d",&num);
		system("cls");
		temp=list->head;	//ÿѭ��һ�θýڵ�������Ϊͷ�ڵ� 
		switch(num)
		{
		   case 1:
			   	printf("������Ҫ����ѧ����Ϣ��ѧ�ţ�"); 
				scanf("%s",id);
				while(temp)
				{
					if(strcmp(temp->student.id,id)==0)break;	//����ѧ�� 
					temp=temp->next;
				}
				if(temp)
				{
					printf("���ҵ���ѧ����ϢΪ��\n");
					printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","�༶","ѧ��","����","��ѧ","Ӣ��","�����","�ܳɼ�","ƽ����");
					printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\t %.2f\n",temp->student.class_num,temp->student.id,temp->student.name,\
					temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum,temp->student.sum/3);
				} 
				else
				{
					printf("��Ǹ�������ڸ�ѧ����Ϣ��\n");
				}
				system("pause");
				break;
		   case 2:
			   printf("������Ҫ����ѧ����Ϣ�İ༶��������");
			   scanf("%d %s",&class_num,name);
			   	while(temp)
				{
					/* ���Ұ༶��ѧ��*/ 
					if(temp->student.class_num==class_num && strcmp(temp->student.name,name)==0) 
					{ 
						break;
					} 
					temp=temp->next;	//��ǰ�������һ���ڵ� 
				}
				//�����ѧ����Ϣ 
				if(temp)
				{
					printf("���ҵ���ѧ����ϢΪ��\n");
					printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\t%s\n","�༶","ѧ��","����","��ѧ","Ӣ��","�����","�ܳɼ�","ƽ����");
					printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\t %.2f\n",temp->student.class_num,temp->student.id,temp->student.name,\
					temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum,temp->student.sum/3);
				} 
				else
				{
					printf("��Ǹ�������ڸ�ѧ����Ϣ��\n");
				}
				system("pause");
				break;
		   case 3:
				return; 
			default:
				printf("�����������������룡\n");
				system("pause");
				break; 
		}
	}

}
//�޸ľ���ϸ�� 
void detail(struct Node *temp)
{
	char id[10];	//ѧ�� 
	int num=0,x;
	printf("\n******��Ϣ�޸�********");
	printf("\n******1.�༶�޸�******");
	printf("\n******2.ѧ���޸�******");
	printf("\n******3.�����޸�******");
	printf("\n******4.�ɼ��޸�******");
	printf("\n******5.�˳�**********\n");
	while(1)
	{
		printf("��ѡ��");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
					printf("���������޸ĺ�İ༶��Ϊ��");
					scanf("%d",&temp->student.class_num);
					break;
			case 2:
					printf("���������޸ĺ��ѧ��Ϊ��");
					scanf("%s",temp->student.id);
					break;
			case 3:
					printf("���������޸ĺ������Ϊ��");
					scanf("%s",temp->student.name);
					break;
			case 4:
					printf("�����޸ĸ�ͬѧ�ĳɼ�Ϊ��\n");
					printf("��ѧ--Ӣ��--�����\n-->");
					scanf("%f %f %f",&temp->student.score[0],&temp->student.score[1],&temp->student.score[2]);
					temp->student.sum=temp->student.score[0]+temp->student.score[1]+temp->student.score[2];
					system("pause");
					break;
			case 5:
				return;
			default:
				printf("����������,����������!");
				break; 
		} 
		printf("�˳��밴����0���������ּ������޸ģ�");
		scanf("%d",&x);
		if(x==0)break;
	}
}
//�޸�ѧ����Ϣ 
void change(struct List *list)
{
	char id[10],flag=1;
	struct Student student;
	struct Node *temp=list->head;	//���½ڵ���Ϊͷ�ڵ� 
	if(list->size==0)				//������ռ��СΪ0���򷵻��ϼ� 
	{
		printf("��Ǹ������ѧ����Ϣ��\n");
		return;
	}
	printf("������Ҫ�޸�ѧ����Ϣ��ѧ�ţ�"); 
	scanf("%s",id);
	while(temp)
	{
		if(strcmp(temp->student.id,id)==0)	//����ѧ�� 
		{
			printf("��ǰ��ѧ����ϢΪ��\n"); 
			printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\n","�༶","ѧ��","����","��ѧ","Ӣ��","�����","�ܳɼ�");
			printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\n",temp->student.class_num,temp->student.id,temp->student.name,\
			temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum);
			detail(temp);
			printf("�޸ĳɹ���\n");
			flag=0; 
			break;
		}
		temp=temp->next;		//��ǰ�������һ���ڵ�
	}
	if(flag)
	{
		printf("��Ǹ�������ڸ�ѧ����Ϣ���޷��޸ģ�\n");
	}
}
//ɾ�� 
void Delete(struct List *list)
{
	char id[10];
	int flag,x;
	struct Node *temp,*prevNode=NULL;	//������ͷ�ڵ�prevNode 
	while(1)
	{	
		temp=list->head;				//ÿѭ��һ�θýڵ�������Ϊͷ�ڵ�
		if(list->size==0)				//������ռ��СΪ0�������ѭ�� 
		{
			printf("\n��Ǹ������ѧ����Ϣ��\n");
			break;
		}
		flag=1;
		printf("������Ҫɾ��ѧ����Ϣ��ѧ�ţ�"); 
		scanf("%s",id);		
		while(temp)
		{
			if(strcmp(temp->student.id,id)==0)
			{
				printf("ɾ���ĸ�ѧ����ϢΪ��\n");
				printf("\n%s\t%-15s\t%-10s\t%s\t%s\t%s\t%s\n","�༶","ѧ��","����","��ѧ","Ӣ��","�����","�ܳɼ�");
				printf(" %d\t%-15s\t%-10s\t%.0f\t%.0f\t %.0f\t %.0f\n",temp->student.class_num,temp->student.id,temp->student.name,\
			temp->student.score[0],temp->student.score[1],temp->student.score[2],temp->student.sum);
				/*�ҵ�ǰһ���ڵ㣬�����һ���ڵ����� */
				prevNode=getBeforeNode(list,temp->student);  
				
				if(prevNode==NULL)				//ɾ������ͷ�ڵ� 
				{				
					list->head=temp->next; 
				}
				else
				{
					prevNode->next=temp->next;	//ɾ��������ͨ�ڵ� 
				}
				flag=0;							
				free(temp);						//�ͷ�temp��ָ�Ŀռ��ڴ� 
				temp=NULL;						//���ýڵ�Ϊ�� 
				list->size--;					//�� 
				printf("\n��ѧ����Ϣɾ���ɹ���\n");
				break;
			}
			temp=temp->next;					//��ǰ�������һ���ڵ�
		}
		if(flag)
		{
			printf("\n��Ǹ�������ڸ�ѧ����Ϣ���޷�ɾ����\n\n");
		} 
		printf("\n�˳��밴����0���������ּ�����ɾ��������");
	 	scanf("%d",&x);
	 	if(x==0)break; 
	}
	system("pause");
} 
//�˳����� 
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
				printf("��> ��л����ʹ�ã� <��");
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
