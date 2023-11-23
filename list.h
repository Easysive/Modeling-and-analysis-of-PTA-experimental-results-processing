#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#pragma warning(disable : 4996)

//------------------------�˵�����----------------------
//�����˵�
void menu() {
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|-----------------PTA�ɼ�����ϵͳ---------------|\n");
	printf("\t\t|\t 0. �˳�                                |\n");
	printf("\t\t|\t 1. ���ļ�¼��ѧ��PTA��Ϣ               |\n");
	printf("\t\t|\t 2. �ֶ�¼��ѧ��PTA��Ϣ                 |\n");
	printf("\t\t|\t 3. ��ӡ��ǰѧ��PTA��Ϣ                 |\n");
	printf("\t\t|\t 4. ɾ��ѧ��PTA��Ϣ                     |\n");
	printf("\t\t|\t 5. ����ѧ��PTA��Ϣ                     |\n");
	printf("\t\t|\t 6. �����ݴ�������ɼ�                |\n");
	printf("\t\t|-----------------------------------------------|\n\n");
	printf("\t\t\t\tѡ��(0-6)\n");
}

//-=---------------������--------------
//ѧ���ɼ��ڵ�
typedef struct Testscore
{
	char ID[13];					//ѧ��
	char name[20];					//����
	float NumofComplete;			//ͨ����
	float time;						//�����Ŀ����ʱ��
	float NumofMistake;				//��ʱ��
	float RepetRate;				//������
	float score;					//���ճɼ�	
}Testscore;

//ѧ����Ϣ����
typedef struct StuInfo
{
	Testscore data;			//ͷ�ڵ�
	StuInfo* next;			//ָ����һ���ڵ�	
	int length;				//����ĳ���
}StuInfo;

//��ʼ������
bool Initlink(StuInfo*& link)
{
	link = (StuInfo*)malloc(sizeof(StuInfo));
	if (link == NULL)	//����ռ�ʧ��
		return false;
	link->next = NULL;
	link->length = 0;
	return true;
}

//����ͷ�巨��������
void Insert(StuInfo*& link, Testscore stu)
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p->data = stu;
	p->next = link->next;
	link->next = p;
	link->length++;					//������++
}

//����ѧ����Ϣ
void AddinFormation(StuInfo*& link)
{
	Testscore stu;
	printf("������ѧ������Ϣ\n");
	printf("ѧ��\n");
	scanf("%s", stu.ID);
	printf("����\n");
	scanf("%s", stu.name);
	printf("PTA��Ŀͨ����\n");
	scanf("%f", &stu.NumofComplete);
	float mistake;
	stu.NumofMistake = 0;
	printf("ÿ����ķ�ʱ�����ÿո������\n");
	//�����ѧ�����ܷ�ʱ��
	for (int i = 0; i < stu.NumofComplete; i++)
	{
		scanf("%f", &mistake);
		stu.NumofMistake += mistake;
	}
	printf("������\n");
	scanf("%f", &stu.RepetRate);
	printf("PTA�����ʱ\n");
	scanf("%f", &stu.time);
	Insert(link, stu);
	printf("����ɹ���\n");
}

//�ֶ�¼��PTA�ɼ���Ϣ
void InputInformation(StuInfo*& link)
{
	StuInfo* p, * r; //pָ���½�㣬rָ��ǰ�����β��� 
	int i, n; //n Ϊ��Ҫ�����ѧ������
	r = link;
	printf("������ѧ����������");
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {		
		//ͨ��ѭ�����β���ѧ������
		AddinFormation(link);
		printf("---------------------------\n");
	}
	printf("************************\n");
}
//���ļ��ж�ȡ����
void ReadStuInfo(StuInfo*& link)
{
	//��ScoreData.txt��ȡ��Ϣ
	FILE* fp = fopen("ScoreData.txt", "r");
	if (fp == NULL)
	{
		printf("�޷��򿪸��ļ�\n");
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

//ɾ��ѧ��PTA��Ϣ
void DeleteInfo(StuInfo*& link)
{
	StuInfo* p, * r;
	char s[15];
	r = link;
	//ͨ��ѧ��ɾ��
	printf("��������Ҫɾ��ѧ����ѧ�ţ�\n");
	scanf("%s", s);
	while ((r->next != NULL) && strcmp(s, r->next->data.ID))
	{
		r = r->next;
	}
	if (r == NULL)
	{
		printf("ɾ��ʧ�ܣ�\n");
	}
	p = r->next;
	r->next = p->next;
	free(p);
	printf("ɾ���ɹ���\n");
}

//�Գɼ���������
void sort(StuInfo*& link)
{
	//ð������˼��
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
				//��������
				temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
			q = q->next;
		}
		p = p->next;
	}
}
//��ӡ���������
void PrintInfo(StuInfo*& link)
{
	StuInfo* cur = new StuInfo;
	cur = link->next;
	printf("��ǰ����%dλͬѧ����λͬѧ����Ϣ����:\n", link->length);
	do
	{
		printf("ѧ�ţ�%s,������%s\t,��Ŀͨ������%d\t,��ʱ����%d\t,�����ʣ�%d\t,����ʱ�䣺%d\n", cur->data.ID, cur->data.name, int(cur->data.NumofComplete), int(cur->data.NumofMistake), int(cur->data.RepetRate), int(cur->data.time));
		cur = cur->next;
	} while (cur != NULL);
}

//��ӡ�ɼ�
void PrintScores(StuInfo*& link)
{
	StuInfo* cur = new StuInfo;
	cur = link->next;
	printf("��ǰ����%dλͬѧ����λͬѧ����Ϣ����:\n", link->length);
	do
	{
		printf("ѧ�ţ�%s, ������%s�����ճɼ���%f\n", cur->data.ID, cur->data.name, cur->data.score);
		cur = cur->next;
	} while (cur != NULL);
}

//�ͷ�����
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