#include"list.h"
#include"data.h"

//主函数
int main()
{
	system("color 0b");
	//显示菜单
	menu();
	StuInfo* link;
	Initlink(link);
	//定义选择变量
	int select = -1;
	//互动列表
	while (select != 0)
	{
		printf("\t\t\t请选择您要进行的操作：");
		//读入选择
		scanf("%d", &select);
		printf("\n");
		switch (select)
		{
			//从文件读数据
		case 1:
			ReadStuInfo(link);
			break;
			//手动输入数据
		case 2:
			InputInformation(link);
			break;
			//打印当前PTA数据
		case 3:
			PrintInfo(link);
			break;
			//删除某个同学的PTA数据
		case 4:
			DeleteInfo(link);
			break;
			//插入PTA数据
		case 5:
			AddinFormation(link);
			break;
			//对数据处理并输出成绩 
		case 6:
		{
			//定义满分标准的链表结点
			Testscore Full={"#####","full"};
			float max[6];
			float min[6];
			//找出链表中所储存的各类数据的最大值与最小值
			for (int i = 1; i < 5; i++)
			{
				max[i] = Max(link, i);
				min[i] = Min(link, i);
			}
			//对满分标准进行设置
			printf("请输入本题目集的题目数：");
			scanf("%f", &Full.NumofComplete);
			Full.RepetRate=min[4];
			Full.NumofMistake = min[3];
			Full.time = min[2];
			Insert(link, Full);
			//通过数是极大型指标，用时，罚时数和查重率是极小型指标，需要将其转化成极大型指标
			PostChange(link, max);
			//将数据标准化
			StandarDization(link);
			//计算得分
			//1.首先重新找出每类数据中的最大值与最小值
			for (int i = 1; i < 5; i++)
			{
				max[i] = Max(link, i);
				min[i] = Min(link, i);
			}
			//2.之后计算出欧氏距离,并且根据D-/(D-+D+)计算出最终得分
			LastScore(link, max, min);
			//将成绩百分化
			PercentScores(link);
			//根据最终归一化的成绩进行排序
			sort(link);
			//打印最后的排名
			PrintScores(link);
			break;
		}
		default:
			break;
		}
	}
	//释放链表
	//freeLink(link);
	return 0;
}