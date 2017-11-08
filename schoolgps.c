#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <graphics.h>
#include <conio.h>

#define num 5
#define MAX 100
#define N 5

typedef int AdjMatrix[MAX][MAX];
typedef int Time[MAX];
typedef struct
{
	AdjMatrix arcs;
	AdjMatrix min;
	Time t;

}MGraph;

typedef struct
{
	int cost[N];
	char info[MAX];
}Vertex;

const int max = 9999;
const int ax = 50;

void creat(MGraph *G, int m) {
	FILE *fp1;
	FILE *fp2 = NULL;
	int i, j;
	fp1 = fopen("test.txt", "r");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			fscanf(fp1, "%d", &G->arcs[i][j]);
	}
	fclose(fp1);

	switch (m)
	{
	case 1:
		fp2 = fopen("time1.txt", "r");
		break;
	case 2:
		fp2 = fopen("time2.txt", "r");
		break;
	case 3:
		fp2 = fopen("time3.txt", "r");
		break;
	default:
		printf("你输入了错误的数字");
		break;
	}
	//for (i = 0; i < N; i++)
	//	fscanf(fp2, "%d", &G->t[i]);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			fscanf(fp2, "%d", &G->min[i][j]);
	}
	fclose(fp2);

	for (i = 0; i <= N; i++)
		for (j = 0; j <= N; j++)
			if (G->arcs[i][j] == 0) G->arcs[i][j] = MAX;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf("%d ", G->arcs[i][j]);
		printf("\n");
	}
}


int isbest(int i, int bestpath[], int p, int a[], int n)//检测改节点是否已经加入bestpath[]中
{
	int k, q;
	int m = 0;
	for (q = 0; q < n; q++)
	{
		if (i == a[q] - 1)
			break;
		else
			m++;
	}

	for (k = 1; k <= p; k++)
	{
		if (i == bestpath[k])
			break;

	}
	if ((k != p + 1) || (m == n))//新测试节点在a[]中
		return 1;
	else
		return 0;

}

int judge(MGraph *G, int time) {
	if (time == 3)
		return 1;
	else
		return 0;
}


void path(MGraph *G, int a[], int n, int bestpath[]) {

	int min = max;
	int minf = max;
	//int bestpath[50];//最佳路径
	int f = 0, g = 0, h = 0;
	int ff[50];//依次求每个城市的f值
	int gg[50];//城市的g值
	int i, j;
	bestpath[0] = 0;//起点为0，即城市A
	int time = 420;//总时间
	int schedule[N];//每个点的时间
	for (int p = 0; p<n - 1; p++)//依次求每个最优节点，每次循环得到一个新的最优城市放到bestpath[]中
	{
		for (int kk = 0; kk<num; kk++)
			ff[kk] = max;//便于后面求最小值
		for (i = 1; i<num; i++)//起点A不算，从非起点开始找寻最优城市
		{
			if (isbest(i, bestpath, p, a, n))//该点已经在bestpath[]中的话，忽略
				continue;
			else//计算该点的g值
				gg[i] = g + G->arcs[bestpath[p]][i];//i点的g值

			for (int m = 0; m<num; m++)//开始计算h值
			{
				if (isbest(m, bestpath, p, a, n))//该点已经在bestpath[]中的话，忽略
					continue;
				for (int t = m + 1; t<num; t++)

				{
					if (isbest(t, bestpath, p, a, n))
						continue;
					if (m != 0 || t != i || p == n - 2)//不是最后一个点的话，不算A点到这个点长度
						if (G->arcs[m][t]<min)
							min = G->arcs[m][t];
				}
			}
			h = min*(n - p - 1);//h值
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
		g = g + G->arcs[bestpath[p]][bestpath[p + 1]];//更新g值
		time = time + G->min[bestpath[p]][bestpath[p + 1]];
		schedule[p] = time;
	}

	printf("最优路径为:");
	for (i = 0; i<n; i++)
		printf("%d->", bestpath[i] + 1);
	printf("1\n");

	printf("总路程为:");
	int sum = 0;
	for (i = 0; i<n - 1; i++)
		sum = sum + G->arcs[bestpath[i]][bestpath[i + 1]];
	sum = sum + G->arcs[bestpath[n - 1]][0];//总路程最后一个城市要回到A，所以加上其距离
	printf("%d\n", sum);
	time = time + G->min[bestpath[n - 1]][0];
	schedule[n - 1] = time;
	for (i = 0; i < n; i++)
		printf("第%d个点的时间为%d\n",i+1,schedule[i]);

}

void time(MGraph *G, int n, int bestpath[]) {

}


void main()
{
	int n, i, m;
	int bestpath[50];
	int a[10] = { 0 };
	printf("选择你的出行方式：（1为步行，2位自行车，3为汽车）");
	scanf("%d", &m);
	printf("输入你想去几个地点：");
	scanf("%d", &n);
	printf("输入要去的地点:");
	for (i = 0; i<n; i++)
		scanf("%d", &a[i]);
	printf("你要去：");
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	MGraph G;
	creat(&G, m);
	path(&G, a, n, bestpath);
	system("pause");
	getchar();

	initgraph(884, 480);
	IMAGE img;
	loadimage(&img, "img_meitu_1.jpg");
	putimage(0, 0, &img);
	BeginBatchDraw();
	setlinecolor(RED);
	setfillcolor(RED);
	fillcircle(480, 87, 7);
	fillcircle(320, 257, 7);
	fillcircle(320, 87, 7);
	fillcircle(360, 350, 7);
	fillcircle(515, 390, 7);
	line(480, 87, 320, 87);
	line(320, 257, 320, 87);
	line(320, 257, 360, 350);
	line(360, 350, 515, 390);
	line(515, 390, 480, 87);
	FlushBatchDraw();

	system("pause");
}
