#include"list.h"
#include"data.h"

//������
int main()
{
	system("color 0b");
	//��ʾ�˵�
	menu();
	StuInfo* link;
	Initlink(link);
	//����ѡ�����
	int select = -1;
	//�����б�
	while (select != 0)
	{
		printf("\t\t\t��ѡ����Ҫ���еĲ�����");
		//����ѡ��
		scanf("%d", &select);
		printf("\n");
		switch (select)
		{
			//���ļ�������
		case 1:
			ReadStuInfo(link);
			break;
			//�ֶ���������
		case 2:
			InputInformation(link);
			break;
			//��ӡ��ǰPTA����
		case 3:
			PrintInfo(link);
			break;
			//ɾ��ĳ��ͬѧ��PTA����
		case 4:
			DeleteInfo(link);
			break;
			//����PTA����
		case 5:
			AddinFormation(link);
			break;
			//�����ݴ�������ɼ� 
		case 6:
		{
			//�������ֱ�׼��������
			Testscore Full={"#####","full"};
			float max[6];
			float min[6];
			//�ҳ�������������ĸ������ݵ����ֵ����Сֵ
			for (int i = 1; i < 5; i++)
			{
				max[i] = Max(link, i);
				min[i] = Min(link, i);
			}
			//�����ֱ�׼��������
			printf("�����뱾��Ŀ������Ŀ����");
			scanf("%f", &Full.NumofComplete);
			Full.RepetRate=min[4];
			Full.NumofMistake = min[3];
			Full.time = min[2];
			Insert(link, Full);
			//ͨ�����Ǽ�����ָ�꣬��ʱ����ʱ���Ͳ������Ǽ�С��ָ�꣬��Ҫ����ת���ɼ�����ָ��
			PostChange(link, max);
			//�����ݱ�׼��
			StandarDization(link);
			//����÷�
			//1.���������ҳ�ÿ�������е����ֵ����Сֵ
			for (int i = 1; i < 5; i++)
			{
				max[i] = Max(link, i);
				min[i] = Min(link, i);
			}
			//2.֮������ŷ�Ͼ���,���Ҹ���D-/(D-+D+)��������յ÷�
			LastScore(link, max, min);
			//���ɼ��ٷֻ�
			PercentScores(link);
			//�������չ�һ���ĳɼ���������
			sort(link);
			//��ӡ��������
			PrintScores(link);
			break;
		}
		default:
			break;
		}
	}
	//�ͷ�����
	//freeLink(link);
	return 0;
}