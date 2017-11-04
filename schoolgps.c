#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define num 5
#define MAX 100
#define N 5

typedef int AdjMatrix[MAX][MAX];
typedef struct
{
	AdjMatrix arcs;
}MGraph;

const int max = 9999;
const int ax = 50;

void creat(MGraph *G) {
	FILE *fp;
	int i, j;
	fp = fopen("test.txt", "r");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			fscanf(fp, "%d", &G->arcs[i][j]);
	}
	fclose(fp);

	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
	    	if (G->arcs[i][j] == 0) G->arcs[i][j] = MAX;
}


int isbest(int i, int bestpath[], int p)//检测改节点是否已经加入bestpath[]中
{
	int k;
	for (k = 1; k <= p; k++)
	{
		if (i == bestpath[k])
			break;

	}
	if (k != p + 1)//新测试节点在a[]中
		return 1;
	else
		return 0;

}

void main()
{
	int min = max;
	int minf = max;
	//int mat[50][50];//城市间距离
	int bestpath[50];//最佳路径
	int f = 0, g = 0, h = 0;
	int ff[50];//依次求每个城市的f值
	int gg[50];//城市的g值
	int i, j;
	MGraph G;
	creat(&G);
	
	//printf("城市间的距离为：\n");//输入各城市间距离的矩阵
	//for ( i = 0; i<num; i++)
	//	for (j = 0; j<num; j++)
	//		scanf_s("%d", &mat[i][j]);

	bestpath[0] = 0;//起点为0，即城市A
	for (int p = 0; p<num - 1; p++)//依次求每个最优节点，每次循环得到一个新的最优城市放到bestpath[]中
	{
		for (int kk = 0; kk<num; kk++)
			ff[kk] = max;//便于后面求最小值
		for (i = 1; i<num; i++)//起点A不算，从非起点开始找寻最优城市
		{
			if (isbest(i, bestpath, p))//该点已经在bestpath[]中的话，忽略
				continue;
			else//计算该点的g值
				gg[i] = g + G.arcs[bestpath[p]][i];//i点的g值

			for (int m = 0; m<num; m++)//开始计算h值
			{
				if (isbest(m, bestpath, p))//该点已经在bestpath[]中的话，忽略
					continue;
				for (int t = m + 1; t<num; t++)

				{
					if (isbest(t, bestpath, p))
						continue;
					if (m != 0 || t != i || p == num - 2)//不是最后一个点的话，不算A点到这个点长度
						if (G.arcs[m][t]<min)
							min = G.arcs[m][t];
				}
			}
			h = min*(num - p - 1);//h值
			ff[i] = gg[i] + h;//第i个节点的f值
			min = max;//重新赋值最大，以便下次循环

		}
		for (i = 0; i<num; i++)//找寻最优点，即f值最小者
		{
			if (ff[i]<minf)
			{
				minf = ff[i];
				bestpath[p + 1] = i;
			}
		}
		minf = max;//重新赋值最大，以便下次循环	
		g = g + G.arcs[bestpath[p]][bestpath[p + 1]];//更新g值
	}

	printf("最优路径为:");
	for (i = 0; i<num; i++)
		printf("%d->", bestpath[i] + 1);
	printf("1\n");

	printf("总路程为:");
	int sum = 0;
	for (i = 0; i<num - 1; i++)
		sum = sum + G.arcs[bestpath[i]][bestpath[i + 1]];
	sum = sum + G.arcs[bestpath[num - 1]][0];//总路程最后一个城市要回到A，所以加上其距离
	printf("%d\n", sum);
	system("pause");
}
