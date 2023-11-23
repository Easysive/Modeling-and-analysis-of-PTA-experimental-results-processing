#pragma once
#include"list.h"
//����һ�����ֱ�׼
// ͨ����=��Ŀ��
// ���ʱ����������������Сֵ
// ��ʱ��Ϊ��������Сֵ
// ������Ϊ������������С
// ������������ֱ�׼

//ͨ����ѧ��ģ�������Ȩ��
// ͨ����=0.5972
//�����Ŀ����ʱ��=0.0924
//��ʱ��=0.0513
//������=0.2691

//�������е�ĳЩ��������
void PostChange(StuInfo*& link, float a[])
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	//���ڲ��������׼�����ݣ����������ݵ����ֵ��ȥ�������ݣ����ɽ�������
	for (p; p != NULL; p = p->next)
	{
		p->data.time = a[2] - p->data.time;
		p->data.NumofMistake = a[3] - p->data.NumofMistake;
		p->data.RepetRate = a[4] - p->data.RepetRate;
	}
}

//���ο���ָ�����ݱ�׼��,��ȥ����
void StandarDization(StuInfo*& link)
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	float sum[5] = { 0.00 };
	//ʹ���ض��Ĺ�ʽ��ȥ����
	for (p; p != NULL; p = p->next)
	{
		sum[1] += p->data.NumofComplete * p->data.NumofComplete;
		sum[2] += p->data.time * p->data.time;
		sum[3] += p->data.NumofMistake * p->data.NumofMistake;
		sum[4] += p->data.RepetRate * p->data.RepetRate;
	}
	//����������ݵ�ƽ��������
	for (int i = 1; i < 5; i++) {
		sum[i] = sqrt(sum[i]);
	}
	p = link->next;
	for (p; p != NULL; p = p->next) {
		p->data.NumofComplete = p->data.NumofComplete / sum[1];
		p->data.time = p->data.time / sum[2];
		p->data.NumofMistake = p->data.NumofMistake / sum[3];
		p->data.RepetRate = p->data.RepetRate / sum[4];
	}
}

//�������յ÷֣������й�һ��
void LastScore(StuInfo*& link, float max[], float min[])
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	float Z1 = 0.0, Z2 = 0.0;
	float lastscore;
	//����ѧ���ɼ�
	for (p; p != NULL; p = p->next)
	{
		Z1 = sqrt(0.5972 * (max[1] - p->data.NumofComplete) * (max[1] - p->data.NumofComplete) + 0.0824 * (max[2] - p->data.time) * (max[2] - p->data.time) + 0.0513 * (max[3] - p->data.NumofMistake) * (max[3] - p->data.NumofMistake) + 0.2691 * (max[4] - p->data.RepetRate) * (max[4] - p->data.RepetRate));
		Z2 = sqrt(0.5972 * (min[1] - p->data.NumofComplete) * (min[1] - p->data.NumofComplete) + 0.0824 * (min[2] - p->data.time) * (min[2] - p->data.time) + 0.0513 * (min[3] - p->data.NumofMistake) * (min[3] - p->data.NumofMistake) + 0.2691 * (min[4] - p->data.RepetRate) * (min[4] - p->data.RepetRate));
		lastscore = Z2 / (Z1 + Z2);
		p->data.score = lastscore;
	}
	p = link->next;
	//���������ѧ���ɼ�֮��
	float sumscore = 0.0;
	for (p; p != NULL; p = p->next)
	{
		sumscore += p->data.score;
	}
	p = link->next;
	//��ѧ���ɼ���һ��
	for (p; p != NULL; p = p->next)
	{
		p->data.score = p->data.score / sumscore;
	}
}
//�ҵ����������е����ֵ
float Max(StuInfo* link, int choice)
{
	StuInfo* p = new StuInfo;
	p = link->next;
	float max = 0;
	switch (choice)
	{
	case 1:									
		//��Ѱ����������ֵ
		max = p->data.NumofComplete;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (max < p->data.NumofComplete)
			{
				max = p->data.NumofComplete;
			}
		}
		break;
	case 2:									
		//�������������������ʱ������ֵ
		max = p->data.time;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (max < p->data.time)
			{
				max = p->data.time;
			}
		}
		break;
	case 3:									
		//���������з�ʱ�������ֵ
		max = p->data.NumofMistake;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (max < p->data.NumofMistake)
			{
				max = p->data.NumofMistake;
			}
		}
		break;
	case 4:									
		//���������в����ʵ����ֵ
		max = p->data.RepetRate;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (max < p->data.RepetRate)
			{
				max = p->data.RepetRate;
			}
		}
		break;
	case 5:				
		//�ҳ����ճɼ������ֵ
		max = p->data.score;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (max < p->data.score)
			{
				max = p->data.score;
			}
		}
		break;
	default:
		break;
	}
	return max;
}
//�ҵ����������е���Сֵ
float Min(StuInfo* link, int choice)
{
	StuInfo* p = new StuInfo;
	p = link->next;
	float min = 0;
	switch (choice)
	{
	case 1:									
		//��Ѱ���������Сֵ
		min = p->data.NumofComplete;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (min > p->data.NumofComplete)
			{
				min = p->data.NumofComplete;
			}
		}
		break;

	case 2:									
		//�������������������ʱ�����Сֵ
		min = p->data.time;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (min > p->data.time)
			{
				min = p->data.time;
			}
		}
		break;

	case 3:									
		//���������з�ʱ������Сֵ
		min = p->data.NumofMistake;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (min > p->data.NumofMistake)
			{
				min = p->data.NumofMistake;
			}
		}
		break;

	case 4:									
		//���������в����ʵ���Сֵ
		min = p->data.RepetRate;
		p = p->next;
		for (p; p != NULL; p = p->next)
		{
			if (min > p->data.RepetRate)
			{
				min = p->data.RepetRate;
			}
		}
		break;

	default:
		break;
	}
	return min;
}
//���ɼ��ٷֻ�
void PercentScores(StuInfo*& link)
{
	float maxscore;
	//�ҵ������е���߳ɼ�
	maxscore = Max(link, 5);
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	//��ʱmaxscoreһ���Ƕ����full��׼
	for (int i = 0; i < link->length; i++)
	{
		p->data.score = (p->data.score / maxscore) * 100;
		p = p->next;
	}
}