#ifndef _LIST_H_
#define _LIST_H_
struct Student{
	int class_num; 		//�༶
	char id[15];		//ѧ��
	char name[10];		//����
	float score[3];		//���Ʒ���
	float sum; 			//�ܳɼ�
	float course_av[3];	//����ƽ����
	float course_pass[3];//���Ƽ�����
	float course_max[3];//������ͷ�
	float course_min[3];//������߷�
};
struct Node{
	struct Student student;
	struct Node *next;
};
struct List{
	struct Node *head;
	int size;
};
struct List* createList();
void destoryList(struct List *list);
struct Node* createNode(struct Student student);
struct Node* getLastNode(struct List *list);
struct Node* getBeforeNode(struct List *list,struct Student student);
void addList(struct List *list, struct Node *node);
#endif
