#ifndef _LIST_H_
#define _LIST_H_
struct Student{
	int class_num; 		//班级
	char id[15];		//学号
	char name[10];		//姓名
	float score[3];		//各科分数
	float sum; 			//总成绩
	float course_av[3];	//各科平均分
	float course_pass[3];//各科及格率
	float course_max[3];//各科最低分
	float course_min[3];//各科最高分
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
