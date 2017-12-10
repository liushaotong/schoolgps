#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <graphics.h>
#include <conio.h>

#define num 10
#define MAX 100
#define N 10

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
	fp1 = fopen("quanzhi.txt", "r");
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
			if (G->arcs[i][j] == 0) G->arcs[i][j] = max;
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
	int time = 420;//总时间
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
	case 1:
		line(480, 87, 400, 100);
		break;
	case 2:
		line(480, 87, 320, 87);
		break;
	case 3:
		line(480, 87, 465, 30);
		break;
	case 4:
		line(480, 87, 320, 257);
		break;
	case 5:
		line(480, 87, 430, 230);
		break;
	case 6:
		line(480, 87, 360, 350);
		break;
	case 7:
		line(480, 87, 420, 350);
		break;
	case 8:
		line(480, 87, 515, 390);
		break;
	case 9:
		line(480, 87, 620, 370);
		break;
	case 10:
		line(480, 87, 400, 100);
		break;
	case 12:
		line(400, 100, 320, 87);
		break;
	case 13:
		line(400, 100, 465, 30);
		break;
	case 14:
		line(400, 100, 320, 257);
		break;
	case 15:
		line(400, 100, 430, 230);
		break;
	case 16:
		line(400, 100, 410, 310);
		break;
	case 17:
		line(400, 100, 450, 310);
		break;
	case 18:
		line(400, 100, 515, 390);
		break;
	case 19:
		line(400, 100, 620, 370);
		break;
	case 20:
		line(480, 87, 320, 87);
		break;
	case 21:
		line(400, 100, 320, 87);
		break;
	case 23:
		line(320, 87, 465, 30);
		break;
	case 24:
		line(320, 87, 320, 257);
		break;
	case 25:
		line(320, 87, 430, 230);
		break;
	case 26:
		line(320, 87, 410, 310);
		break;
	case 27:
		line(320, 87, 450, 310);
		break;
	case 28:
		line(320, 87, 515, 390);
		break;
	case 29:
		line(320, 87, 620, 370);
		break;
	case 30:
		line(480, 87, 465, 30);
		break;
	case 31:
		line(465, 30, 400, 100);
		break;
	case 32:
		line(465, 30, 320, 87);
		break;
	case 34:
		line(465, 30, 320, 257);
		break;
	case 35:
		line(465, 30, 430, 230);
		break;
	case 36:
		line(465, 30, 410, 310);
		break;
	case 37:
		line(465, 30, 450, 310);
		break;
	case 38:
		line(465, 30, 515, 390);
		break;
	case 39:
		line(465, 30, 620, 370);
		break;
	case 40:
		line(480, 87, 320, 257);
		break;
	case 41:
		line(320, 257, 400, 100);
		break;
	case 42:
		line(320, 257, 320, 87);
		break;
	case 43:
		line(320, 257, 465, 30);
		break;
	case 45:
		line(320, 257, 430, 230);
		break;
	case 46:
		line(320, 257, 410, 310);
		break;
	case 47:
		line(320, 257, 450, 310);
		break;
	case 48:
		line(320, 257, 515, 390);
		break;
	case 49:
		line(320, 257, 620, 370);
		break;
	case 50:
		line(480, 87, 430, 230);
		break;
	case 51:
		line(430, 230, 400, 100);
		break;
	case 52:
		line(430, 230, 320, 87);
		break;
	case 53:
		line(430, 230, 465, 30);
		break;
	case 54:
		line(430, 230, 320, 257);
		break;
	case 56:
		line(430, 230, 410, 310);
		break;
	case 57:
		line(430, 230, 450, 310);
		break;
	case 58:
		line(430, 230, 515, 390);
		break;
	case 59:
		line(430, 230, 620, 370);
		break;
	case 60:
		line(480, 87, 410, 310);
		break;
	case 61:
		line(410, 310, 400, 100);
		break;
	case 62:
		line(410, 310, 320, 87);
		break;
	case 63:
		line(410, 310, 465, 30);
		break;
	case 64:
		line(410, 310, 320, 257);
		break;
	case 65:
		line(410, 310, 430, 230);
		break;
	case 67:
		line(410, 310, 450, 310);
		break;
	case 68:
		line(410, 310, 515, 390);
		break;
	case 69:
		line(410, 310, 620, 370);
		break;
	case 70:
		line(480, 87, 450, 310);
		break;
	case 71:
		line(450, 310, 400, 100);
		break;
	case 72:
		line(450, 310, 320, 87);
		break;
	case 73:
		line(450, 310, 465, 30);
		break;
	case 74:
		line(450, 310, 320, 257);
		break;
	case 75:
		line(450, 310, 430, 230);
		break;
	case 76:
		line(450, 310, 410, 310);
		break;
	case 78:
		line(450, 310, 515, 390);
		break;
	case 79:
		line(450, 310, 620, 370);
		break;
	case 80:
		line(480, 87, 515, 390);
		break;
	case 81:
		line(515, 390, 400, 100);
		break;
	case 82:
		line(515, 390, 320, 87);
		break;
	case 83:
		line(515, 390, 465, 30);
		break;
	case 84:
		line(515, 390, 320, 257);
		break;
	case 85:
		line(515, 390, 430, 230);
		break;
	case 86:
		line(515, 390, 410, 310);
		break;
	case 87:
		line(515, 390, 450, 310);
		break;
	case 89:
		line(515, 390, 620, 370);
		break;
	case 90:
		line(480, 87, 620, 370);
		break;
	case 91:
		line(620, 370, 400, 100);
		break;
	case 92:
		line(620, 370, 320, 87);
		break;
	case 93:
		line(620, 370, 465, 30);
		break;
	case 94:
		line(620, 370, 320, 257);
		break;
	case 95:
		line(620, 370, 430, 230);
		break;
	case 96:
		line(620, 370, 410, 310);
		break;
	case 97:
		line(620, 370, 450, 310);
		break;
	case 98:
		line(620, 370, 515, 390);
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
	fillcircle(480, 87, 7);//宿舍 0
	fillcircle(400, 100, 7);//图书馆 1
	fillcircle(320, 87, 7);//1教 2
	fillcircle(465, 30, 7);//校医院 3
	fillcircle(320, 257, 7);//信息楼 4
	fillcircle(430, 230, 7);//3教 5
	fillcircle(410, 310, 7);//餐厅 6
	fillcircle(450, 310, 7);//atm 7
	fillcircle(515, 390, 7);//体育馆 8
	fillcircle(620, 370, 7);//知行楼 9
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(515, 390, "5");
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

void main()
{
	int n=0, i=0,m=0;
	int bestpath[50];
	int a[10] = { 0 };
	MOUSEMSG m1, m2;
	IMAGE img_buxing, img_zixingche, img_qiche,testimg,img_duigou;
	IMAGE img_1jiao,img_3jiao,img_atm,img_canting,img_sushe,img_tiyuguan,img_tushuguan,img_zhixinglou,img_xiaoyiyuan,img_xinxilou;
	loadimage(&testimg, "test.jpg");
	loadimage(&img_buxing, "buxing.jpg");
	loadimage(&img_zixingche, "zixingche.jpg");
	loadimage(&img_qiche, "qiche.jpg");
	loadimage(&img_duigou, "1111.jpg");
	loadimage(&img_1jiao, "1jiao.jpg");
	loadimage(&img_3jiao, "3jiao.jpg");
	loadimage(&img_atm, "atm.jpg");
	loadimage(&img_canting, "canting.jpg");
	loadimage(&img_tiyuguan, "tiyuguan.jpg");
	loadimage(&img_sushe, "sushe.jpg");
	loadimage(&img_tushuguan, "tushuguan.jpg");
	loadimage(&img_zhixinglou, "zhixinglou.jpg");
	loadimage(&img_xiaoyiyuan, "xiaoyiyuan.jpg");
	loadimage(&img_xinxilou, "xinxilou.jpg");
	initgraph(640, 320);
	setbkcolor(WHITE);
	cleardevice();
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
					outtextxy(10, 80, "输入你想去几个地方(0-9)：");
					char ch = getc(stdin);
					char chtest[10];
					chtest[0] = ch;
					n = atoi(chtest) + 1;
					if(n==10)
						outtextxy(190, 80, "10");
					else
					{
						_itoa(n,chtest,10);
						ch = chtest[0];
						outtextxy(190, 80, ch);
					}
					
					
					outtextxy(10, 160, "选择要去的地点：");
					putimage(190, 160, &img_sushe);
					putimage(260, 160, &img_tushuguan);
					putimage(330, 160, &img_1jiao);
					putimage(400, 160, &img_xiaoyiyuan);
					putimage(470, 160, &img_xinxilou);
					putimage(190, 220, &img_3jiao);
					putimage(260, 220, &img_canting);
					putimage(330, 220, &img_atm);
					putimage(400, 220, &img_tiyuguan);
					putimage(470, 220, &img_zhixinglou);
					

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
								else if (m2.x >= 190 && m2.x <= 220 && m2.y >= 220 && m2.y <= 238) {
									putimage(200, 245, &img_duigou);
									a[i] = 6;
									i++;
								}
								else if (m2.x >= 260 && m2.x <= 290 && m2.y >= 220 && m2.y <= 238) {
									putimage(270, 245, &img_duigou);
									a[i] = 7;
									i++;
								}
								else if (m2.x >= 330 && m2.x <= 360 && m2.y >= 220 && m2.y <= 238) {
									putimage(340, 245, &img_duigou);
									a[i] = 8;
									i++;
								}
								else if (m2.x >= 400 && m2.x <= 430 && m2.y >= 220 && m2.y <= 238) {
									putimage(410, 245, &img_duigou);
									a[i] = 9;
									i++;
								}
								else if (m2.x >= 470 && m2.x <= 500 && m2.y >= 220 && m2.y <= 238) {
									putimage(480, 245, &img_duigou);
									a[i] = 10;
									i++;
								}
							}
						}
							
						
					}
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
					putimage(340, 35, &img_duigou);
					outtextxy(10, 80, "输入你想去几个地方(0-9)：");
					char ch = getc(stdin);
					char chtest[10];
					chtest[0] = ch;
					n = atoi(chtest) + 1;
					if (n == 10)
						outtextxy(190, 80, "10");
					else
					{
						_itoa(n, chtest, 10);
						ch = chtest[0];
						outtextxy(190, 80, ch);
					}


					outtextxy(10, 160, "选择要去的地点：");
					putimage(190, 160, &img_sushe);
					putimage(260, 160, &img_tushuguan);
					putimage(330, 160, &img_1jiao);
					putimage(400, 160, &img_xiaoyiyuan);
					putimage(470, 160, &img_xinxilou);
					putimage(190, 220, &img_3jiao);
					putimage(260, 220, &img_canting);
					putimage(330, 220, &img_atm);
					putimage(400, 220, &img_tiyuguan);
					putimage(470, 220, &img_zhixinglou);


					while (i<n) {
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
								else if (m2.x >= 190 && m2.x <= 220 && m2.y >= 220 && m2.y <= 238) {
									putimage(200, 245, &img_duigou);
									a[i] = 6;
									i++;
								}
								else if (m2.x >= 260 && m2.x <= 290 && m2.y >= 220 && m2.y <= 238) {
									putimage(270, 245, &img_duigou);
									a[i] = 7;
									i++;
								}
								else if (m2.x >= 330 && m2.x <= 360 && m2.y >= 220 && m2.y <= 238) {
									putimage(340, 245, &img_duigou);
									a[i] = 8;
									i++;
								}
								else if (m2.x >= 400 && m2.x <= 430 && m2.y >= 220 && m2.y <= 238) {
									putimage(410, 245, &img_duigou);
									a[i] = 9;
									i++;
								}
								else if (m2.x >= 470 && m2.x <= 500 && m2.y >= 220 && m2.y <= 238) {
									putimage(480, 245, &img_duigou);
									a[i] = 10;
									i++;
								}
							}
						}


					}
					closegraph();

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
					putimage(480, 35, &img_duigou);
					outtextxy(10, 80, "输入你想去几个地方(0-9)：");
					char ch = getc(stdin);
					char chtest[10];
					chtest[0] = ch;
					n = atoi(chtest) + 1;
					if (n == 10)
						outtextxy(190, 80, "10");
					else
					{
						_itoa(n, chtest, 10);
						ch = chtest[0];
						outtextxy(190, 80, ch);
					}


					outtextxy(10, 160, "选择要去的地点：");
					putimage(190, 160, &img_sushe);
					putimage(260, 160, &img_tushuguan);
					putimage(330, 160, &img_1jiao);
					putimage(400, 160, &img_xiaoyiyuan);
					putimage(470, 160, &img_xinxilou);
					putimage(190, 220, &img_3jiao);
					putimage(260, 220, &img_canting);
					putimage(330, 220, &img_atm);
					putimage(400, 220, &img_tiyuguan);
					putimage(470, 220, &img_zhixinglou);


					while (i<n) {
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
								else if (m2.x >= 190 && m2.x <= 220 && m2.y >= 220 && m2.y <= 238) {
									putimage(200, 245, &img_duigou);
									a[i] = 6;
									i++;
								}
								else if (m2.x >= 260 && m2.x <= 290 && m2.y >= 220 && m2.y <= 238) {
									putimage(270, 245, &img_duigou);
									a[i] = 7;
									i++;
								}
								else if (m2.x >= 330 && m2.x <= 360 && m2.y >= 220 && m2.y <= 238) {
									putimage(340, 245, &img_duigou);
									a[i] = 8;
									i++;
								}
								else if (m2.x >= 400 && m2.x <= 430 && m2.y >= 220 && m2.y <= 238) {
									putimage(410, 245, &img_duigou);
									a[i] = 9;
									i++;
								}
								else if (m2.x >= 470 && m2.x <= 500 && m2.y >= 220 && m2.y <= 238) {
									putimage(480, 245, &img_duigou);
									a[i] = 10;
									i++;
								}
							}
						}


					}
					closegraph();

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
