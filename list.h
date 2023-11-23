#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#pragma warning(disable : 4996)

//------------------------菜单部分----------------------
//互动菜单
void menu() {
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|-----------------PTA成绩处理系统---------------|\n");
	printf("\t\t|\t 0. 退出                                |\n");
	printf("\t\t|\t 1. 从文件录入学生PTA信息               |\n");
	printf("\t\t|\t 2. 手动录入学生PTA信息                 |\n");
	printf("\t\t|\t 3. 打印当前学生PTA信息                 |\n");
	printf("\t\t|\t 4. 删除学生PTA信息                     |\n");
	printf("\t\t|\t 5. 插入学生PTA信息                     |\n");
	printf("\t\t|\t 6. 对数据处理并输出成绩                |\n");
	printf("\t\t|-----------------------------------------------|\n\n");
	printf("\t\t\t\t选择(0-6)\n");
}

//-=---------------链表部分--------------
//学生成绩节点
typedef struct Testscore
{
	char ID[13];					//学号
	char name[20];					//姓名
	float NumofComplete;			//通过数
	float time;						//完成题目所用时间
	float NumofMistake;				//罚时数
	float RepetRate;				//查重率
	float score;					//最终成绩	
}Testscore;

//学生信息链表
typedef struct StuInfo
{
	Testscore data;			//头节点
	StuInfo* next;			//指向下一个节点	
	int length;				//链表的长度
}StuInfo;

//初始化链表
bool Initlink(StuInfo*& link)
{
	link = (StuInfo*)malloc(sizeof(StuInfo));
	if (link == NULL)	//分配空间失败
		return false;
	link->next = NULL;
	link->length = 0;
	return true;
}

//采用头插法插入数据
void Insert(StuInfo*& link, Testscore stu)
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p->data = stu;
	p->next = link->next;
	link->next = p;
	link->length++;					//链表长度++
}

//插入学生信息
void AddinFormation(StuInfo*& link)
{
	Testscore stu;
	printf("请输入学生的信息\n");
	printf("学号\n");
	scanf("%s", stu.ID);
	printf("姓名\n");
	scanf("%s", stu.name);
	printf("PTA题目通过数\n");
	scanf("%f", &stu.NumofComplete);
	float mistake;
	stu.NumofMistake = 0;
	printf("每道题的罚时数（用空格隔开）\n");
	//计算该学生的总罚时数
	for (int i = 0; i < stu.NumofComplete; i++)
	{
		scanf("%f", &mistake);
		stu.NumofMistake += mistake;
	}
	printf("查重率\n");
	scanf("%f", &stu.RepetRate);
	printf("PTA完成用时\n");
	scanf("%f", &stu.time);
	Insert(link, stu);
	printf("插入成功！\n");
}

//手动录入PTA成绩信息
void InputInformation(StuInfo*& link)
{
	StuInfo* p, * r; //p指向新结点，r指向当前链表的尾结点 
	int i, n; //n 为需要输入的学生人数
	r = link;
	printf("请输入学生的人数：");
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {		
		//通过循环依次插入学生数据
		AddinFormation(link);
		printf("---------------------------\n");
	}
	printf("************************\n");
}
//从文件中读取数据
void ReadStuInfo(StuInfo*& link)
{
	//从ScoreData.txt读取信息
	FILE* fp = fopen("ScoreData.txt", "r");
	if (fp == NULL)
	{
		printf("无法打开该文件\n");
		return;
	}
	char ID[13];
	char name[20];
	float NumofComplete;
	float time;
	float NumofMistake = 0;
	float RepetRate;
	float mistake;
	while (fscanf(fp, "%s %s %f %f", ID, name, &NumofComplete, &time) != EOF)
	{
		Testscore stu;
		for (int i = 0; i < NumofComplete; i++)
		{
			fscanf(fp, "%f", &mistake);
			NumofMistake += mistake;
		}
		fscanf(fp, "%f", &RepetRate);
		strcpy(stu.ID, ID);
		strcpy(stu.name, name);
		stu.NumofComplete = NumofComplete;
		stu.NumofMistake = NumofMistake;
		stu.RepetRate = RepetRate;
		stu.time = time;
		Insert(link, stu);
		NumofMistake = 0;
	}
	fclose(fp);
}

//删除学生PTA信息
void DeleteInfo(StuInfo*& link)
{
	StuInfo* p, * r;
	char s[15];
	r = link;
	//通过学号删除
	printf("请输入你要删除学生的学号：\n");
	scanf("%s", s);
	while ((r->next != NULL) && strcmp(s, r->next->data.ID))
	{
		r = r->next;
	}
	if (r == NULL)
	{
		printf("删除失败！\n");
	}
	p = r->next;
	r->next = p->next;
	free(p);
	printf("删除成功！\n");
}

//对成绩进行排序
void sort(StuInfo*& link)
{
	//冒泡排序思想
	Testscore temp;
	StuInfo* p = new StuInfo;
	p = link->next;
	StuInfo* q = new StuInfo;
	while (p != NULL)
	{
		q = p->next;
		while (q != NULL)
		{
			if (p->data.score < q->data.score)
			{
				//交换数据
				temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
}
//打印读入的数据
void PrintInfo(StuInfo*& link)
{
	StuInfo* cur = new StuInfo;
	cur = link->next;
	printf("当前共有%d位同学，各位同学的信息如下:\n", link->length);
	do
	{
		printf("学号：%s,姓名：%s\t,题目通过数：%d\t,罚时数：%d\t,查重率：%d\t,花费时间：%d\n", cur->data.ID, cur->data.name, int(cur->data.NumofComplete), int(cur->data.NumofMistake), int(cur->data.RepetRate), int(cur->data.time));
		cur = cur->next;
	} while (cur != NULL);
}

//打印成绩
void PrintScores(StuInfo*& link)
{
	StuInfo* cur = new StuInfo;
	cur = link->next;
	printf("当前共有%d位同学，各位同学的信息如下:\n", link->length);
	do
	{
		printf("学号：%s, 姓名：%s，最终成绩：%f\n", cur->data.ID, cur->data.name, cur->data.score);
		cur = cur->next;
	} while (cur != NULL);
}

//释放链表
void FreeLink(StuInfo*& link)
{
	if (link->length == 0)
		return;
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link;
	while (p)
	{
		free(p);
		p = p->next;
	}
	link->length = 0;
}