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
	FILE *fp1,*fp3;
	FILE *fp2 = NULL;
	int i, j;
	fp1 = fopen("test.txt", "r");
	fp3 = fopen("vextime.txt", "r");
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
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			fscanf(fp2, "%d", &G->min[i][j]);
	}

	for (i = 0; i < N; i++)
		fscanf(fp3, "%d", &G->t[i]);
	fclose(fp3);

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

int judge(MGraph *G, int time,int n,int a[]) {
	int i,j=0;
	for (i = 0; i < n; i++) {
		if (a[i] == 2) {
			if (time <= 480) {
				j = 1;
			}
			else
				continue;
		}
		else
			continue;
	}
	if (j == 1)
		return 1;
	else
		return 0;
	
}

int trans(int input) {
	int i, j,output;
	i = input / 60;
	j = input % 60;
	output = i * 100 + j;
	return output;
}

void path(MGraph *G, int a[], int n, int bestpath[]) {

	int min = max;
	int minf = max;
	int out=0;
	int f = 0, g = 0, h = 0;
	int ff[50];//每个城市的f值
	int gg[50];//城市的g值
	int i, j;
	bestpath[0] = 0;//起点为0
	int time = 470;//总时间
	int schedule[N];//每个点的时间
	for (int p = 0; p<n - 1; p++)
	{
		for (int kk = 0; kk<num; kk++)
			ff[kk] = max;
		for (i = 1; i<num; i++)//起点不算
		{
			if (isbest(i, bestpath, p, a, n))
				continue;
			else
				gg[i] = g + G->arcs[bestpath[p]][i];//i点的g值

			for (int m = 0; m<num; m++)
			{
				if (isbest(m, bestpath, p, a, n))
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
			ff[i] = gg[i] + h;//f值
			min = max;

		}
		//if (judge(G, time, n, a)) {
		//	bestpath[p + 1] = 1; 
		//	time = 420;
		//}
		//else
		//{
			for (i = 0; i < num; i++)//找寻最优点，即f值最小者
			{
				if (ff[i] < minf)
				{
					minf = ff[i];
					bestpath[p + 1] = i;
				}
			}
		//} 

		minf = max;
		g = g + G->arcs[bestpath[p]][bestpath[p + 1]];
		time = time + G->min[bestpath[p]][bestpath[p + 1]];
		schedule[p] = trans(time);
	    time = time + G->t[bestpath[p + 1]];
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
	schedule[n - 1] = trans(time);
	for (i = 0; i < n-1; i++) {
		printf("到达第%d个点的时间为%d，从第%d个点离开时间为%d\n", i + 1, schedule[i],i+1, schedule[i]+trans(G->t[bestpath[i+1]]));
	}
	printf("返回第0个点的时间为%d\n", schedule[n-1]);
}

void drawline(int input) {
	switch (input)
	{
	case 2:
		line(480, 87, 320, 87);
		break;
	case 4:
		line(480, 87, 320, 257);
		break;
	case 3:
		line(480, 87, 515, 390);
		break;
	case 1:
		line(480, 87, 360, 350);
		break;
	case 20:
		line(320, 87, 480, 87);
		break;
	case 21:
		line(320, 87, 360, 350);
		break;
	case 23:
		line(320, 87, 515, 390);
		break;
	case 24:
		line(320, 257, 320, 87);
		break;
	case 40:
		line(320, 257, 480, 87);
		break;
	case 41:
		line(320, 257, 360, 350);
		break;
	case 42:
		line(320, 257, 320, 87);
		break;
	case 43:
		line(320, 257, 515, 390);
		break;
	case 10:
		line(360, 350, 480, 87);
		break;
	case 12:
		line(360, 350, 320, 87);
		break;
	case 13:
		line(360, 350, 515, 390);
		break;
	case 14:
		line(360, 350, 320, 257);
		break;
	case 30:
		line(515, 390, 480, 87);
		break;
	case 31:
		line(515, 390, 360, 350);
		break;
	case 32:
		line(515, 390, 320, 87);
		break;
	case 34:
		line(515, 390, 320, 257);
		break;
	default:
		break;
	}
}

void graph(MGraph *G, int n, int bestpath[]) {
	int i,p,q;
	int j = 1;
	initgraph(884, 480);
	IMAGE ditu;
	loadimage(&ditu, "img_meitu_1.jpg");
	putimage(0, 0, &ditu);
	BeginBatchDraw();
	setlinecolor(RED);
	setfillcolor(RED);
	fillcircle(480, 87, 7);
	fillcircle(320, 257, 7);
	fillcircle(320, 87, 7);
	fillcircle(360, 350, 7);
	fillcircle(515, 390, 7);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(515, 390, "024130");
	outtextxy(480, 87, "1");
	outtextxy(320, 87, "3");
	outtextxy(320, 257, "2");
	outtextxy(360, 350, "4");
	FlushBatchDraw();
	i = 0;
	while (1) {
		getchar();
		p = bestpath[i];
		q = bestpath[i + 1];
		j = p * 10 + q;
		drawline(j);
		FlushBatchDraw();
		i++;
		if(i==n-1)
			break;
	}
	p = bestpath[n - 1];
	q = 0;
	j = p * 10 + q;
	getchar();
	drawline(j);
    FlushBatchDraw();
}

void chooseplace(MOUSEMSG m,int i,int a[],IMAGE duigou) {
	switch (m.uMsg)
	{
	case WM_LBUTTONDOWN:
		if (m.x >= 330 && m.x <= 360 && m.y >= 160 && m.y <= 168) {
			putimage(200, 200, &duigou);
		}
	}
}

void main()
{
	int n=0, i=0,m=0;
	int bestpath[50];
	int a[10] = { 0 };
	MOUSEMSG m1, m2;
	IMAGE img_buxing, img_zixingche, img_qiche,testimg,img_duigou;
	loadimage(&testimg, "test.jpg");
	loadimage(&img_buxing, "buxing.jpg");
	loadimage(&img_zixingche, "zixingche.jpg");
	loadimage(&img_qiche, "qiche.jpg");
	loadimage(&img_duigou, "1111.jpg");
	initgraph(640, 320);
	setbkcolor(WHITE);
	cleardevice();
	putimage(190, 160, &testimg);
	putimage(260, 160, &testimg);
	putimage(330, 160, &testimg);
	putimage(400, 160, &testimg);
	putimage(470, 160, &testimg);
	settextcolor(BLACK);
	outtextxy(10, 10, "选择你的出行方式：");
	putimage(190, 10, &img_buxing);
	putimage(330, 10, &img_zixingche);
	putimage(470, 10, &img_qiche);
	while (1) {
		if (MouseHit()) {
			m1 = GetMouseMsg();
			switch (m1.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (m1.x >= 190 && m1.x <= 220 && m1.y >= 10 && m1.y <= 28) {
					putimage(200, 35, &img_duigou);
					m = 1;
					outtextxy(10, 60, "输入你想去几个地方：");
					char ch = getc(stdin);
					outtextxy(170, 60, ch);
					outtextxy(10, 110, "选择要去的地点：");
					
					char chtest[10];
					chtest[0] = ch;
					n = atoi(chtest);

					while(i<n) {
						if (MouseHit()) {
							m2 = GetMouseMsg();
							switch (m2.uMsg) {
							case WM_LBUTTONDOWN:
								if (m2.x >= 190 && m2.x <= 220 && m2.y >= 160 && m2.y <= 178) {
									putimage(200, 185, &img_duigou);
									a[i] = 1;
									i++;
								}
								else if (m2.x >= 260 && m2.x <= 290 && m2.y >= 160 && m2.y <= 178) {
									putimage(270, 185, &img_duigou);
									a[i] = 2;
									i++;
								}
								else if (m2.x >= 330 && m2.x <= 360 && m2.y >= 160 && m2.y <= 178) {
									putimage(340, 185, &img_duigou);
									a[i] = 3;
									i++;
								}
								else if (m2.x >= 400 && m2.x <= 430 && m2.y >= 160 && m2.y <= 178) {
									putimage(410, 185, &img_duigou);
									a[i] = 4;
									i++;
								}
								else if (m2.x >= 470 && m2.x <= 500 && m2.y >= 160 && m2.y <= 178) {
									putimage(480, 185, &img_duigou);
									a[i] = 5;
									i++;
								}
							}
						}
							
						
					}
					//system("pause");
					closegraph();

					MGraph G;
					creat(&G, m);
					path(&G, a, n, bestpath);
					system("pause");
					getchar();
					graph(&G, n, bestpath);


					system("pause");
					//break;
				}
				else if (m1.x >= 330 && m1.x <= 360 && m1.y >= 10 && m1.y <= 28) {
					m = 2;
					outtextxy(10, 60, "输入你想去几个地方：");

					char ch = getc(stdin);
					outtextxy(170, 60, ch);
					outtextxy(10, 110, "选择要去的地点：");
					system("pause");
					closegraph();
					char chtest[10];
					chtest[0] = ch;
					n = atoi(chtest);
					
					printf("输入要去的地点:");
					for (i = 0; i < n; i++)
						scanf("%d", &a[i]);

					MGraph G;
					creat(&G, m);
					path(&G, a, n, bestpath);
					system("pause");
					getchar();
					graph(&G, n, bestpath);


					system("pause");
				}
				else if(m1.x >= 470 && m1.x <= 500 && m1.y >= 10 && m1.y <= 28) {
					m = 3;
					outtextxy(10, 60, "输入你想去几个地方：");

					char ch = getc(stdin);
					outtextxy(170, 60, ch);
					outtextxy(10, 110, "选择要去的地点：");
					system("pause");
					closegraph();
					char chtest[10];
					chtest[0] = ch;
					n = atoi(chtest);
					
					printf("输入要去的地点:");
					for (i = 0; i < n; i++)
						scanf("%d", &a[i]);

					MGraph G;
					creat(&G, m);
					path(&G, a, n, bestpath);
					system("pause");
					getchar();
					graph(&G, n, bestpath);


					system("pause");
				}
			}
			
		}
		
	}
			
	 closegraph();
	
}
