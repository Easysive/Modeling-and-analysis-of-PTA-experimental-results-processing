#pragma once
#include"list.h"
//设置一个满分标准
// 通过数=题目数
// 完成时间是所有数据中最小值
// 罚时数为数据中最小值
// 查重率为所有数据中最小
// 算出他当作满分标准

//通过数学建模算出来的权重
// 通过数=0.5972
//完成题目所用时间=0.0924
//罚时数=0.0513
//查重率=0.2691

//将链表中的某些数据正向化
void PostChange(StuInfo*& link, float a[])
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	//对于不是正向标准的数据，用这类数据的最大值减去各个数据，即可将其正向化
	for (p; p != NULL; p = p->next)
	{
		p->data.time = a[2] - p->data.time;
		p->data.NumofMistake = a[3] - p->data.NumofMistake;
		p->data.RepetRate = a[4] - p->data.RepetRate;
	}
}

//将参考的指标数据标准化,消去量纲
void StandarDization(StuInfo*& link)
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	float sum[5] = { 0.00 };
	//使用特定的公式消去量纲
	for (p; p != NULL; p = p->next)
	{
		sum[1] += p->data.NumofComplete * p->data.NumofComplete;
		sum[2] += p->data.time * p->data.time;
		sum[3] += p->data.NumofMistake * p->data.NumofMistake;
		sum[4] += p->data.RepetRate * p->data.RepetRate;
	}
	//求出各类数据的平方根数据
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

//计算最终得分，并进行归一化
void LastScore(StuInfo*& link, float max[], float min[])
{
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	float Z1 = 0.0, Z2 = 0.0;
	float lastscore;
	//计算学生成绩
	for (p; p != NULL; p = p->next)
	{
		Z1 = sqrt(0.5972 * (max[1] - p->data.NumofComplete) * (max[1] - p->data.NumofComplete) + 0.0824 * (max[2] - p->data.time) * (max[2] - p->data.time) + 0.0513 * (max[3] - p->data.NumofMistake) * (max[3] - p->data.NumofMistake) + 0.2691 * (max[4] - p->data.RepetRate) * (max[4] - p->data.RepetRate));
		Z2 = sqrt(0.5972 * (min[1] - p->data.NumofComplete) * (min[1] - p->data.NumofComplete) + 0.0824 * (min[2] - p->data.time) * (min[2] - p->data.time) + 0.0513 * (min[3] - p->data.NumofMistake) * (min[3] - p->data.NumofMistake) + 0.2691 * (min[4] - p->data.RepetRate) * (min[4] - p->data.RepetRate));
		lastscore = Z2 / (Z1 + Z2);
		p->data.score = lastscore;
	}
	p = link->next;
	//计算出所有学生成绩之和
	float sumscore = 0.0;
	for (p; p != NULL; p = p->next)
	{
		sumscore += p->data.score;
	}
	p = link->next;
	//将学生成绩归一化
	for (p; p != NULL; p = p->next)
	{
		p->data.score = p->data.score / sumscore;
	}
}
//找到各类数据中的最大值
float Max(StuInfo* link, int choice)
{
	StuInfo* p = new StuInfo;
	p = link->next;
	float max = 0;
	switch (choice)
	{
	case 1:									
		//找寻完成数的最大值
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
		//查找链表中完成所花费时间的最大值
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
		//查找链表中罚时数的最大值
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
		//查找链表中查重率的最大值
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
		//找出最终成绩的最大值
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
//找到各类数据中的最小值
float Min(StuInfo* link, int choice)
{
	StuInfo* p = new StuInfo;
	p = link->next;
	float min = 0;
	switch (choice)
	{
	case 1:									
		//找寻完成数的最小值
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
		//查找链表中完成所花费时间的最小值
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
		//查找链表中罚时数的最小值
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
		//查找链表中查重率的最小值
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
//将成绩百分化
void PercentScores(StuInfo*& link)
{
	float maxscore;
	//找到链表中的最高成绩
	maxscore = Max(link, 5);
	StuInfo* p = (StuInfo*)malloc(sizeof(StuInfo));
	p = link->next;
	//此时maxscore一定是定义的full标准
	for (int i = 0; i < link->length; i++)
	{
		p->data.score = (p->data.score / maxscore) * 100;
		p = p->next;
	}
}