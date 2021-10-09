#ifndef _FUN_H_
#define _FUN_H_
void Menu(); 
FILE* openFile(char *filename,char *type);	 
void fileToList(struct List *list,char *filename);
void listToFile(struct List *list,char *filename);
void input(struct List *list);
void sort(struct List *list);
void output(struct List *list);
void find(struct List *list);
void detail(struct Node *temp);
void change(struct List *list);
void Delete(struct List *list);
void quit();
#endif
