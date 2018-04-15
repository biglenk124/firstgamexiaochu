#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

//定义结构体变量类型，可以用posType变量定义光标中心点位置，
typedef struct postion 
{
	int x;
	int y;
}posType;

//定义按键  KEY_DOWN 宏
#define KEY_DOWN(vk_c) (GetAsyncKeyState(vk_c)&0x8000)



void init1 (void);
void init (void);//初始化界面
void gamebegin(void);//游戏开始画面
void gameplay(void);//游戏具体过程
void close(void);//释放资源
void drawcursor(posType,COLORREF);//重绘光标
void drawtime(int);//重绘时间
void drawscore(int);//重绘分数
void getsamecolorballs(posType,COLORREF);//获取同色小球
int isvalid(posType,COLORREF);//判断是否合法
void ballsfall();//小球下落

COLORREF colorArr[6]={RGB(180,0,0),RGB(0,180,0),RGB(0,0,180),RGB(180,180,0),RGB(0,180,180),RGB(180,0,180),};//随机颜色数组
posType cur;//当前光标位置
posType ballsArr[180];//同色小球坐标
int index;//同色小球个数


void main()
{
	init();

	init1();
	gamebegin();
	gameplay();
	system("pause");
	close();
}






void init()
{
	initgraph(1000,700);
	settextcolor(RGB(255,255,255));
	settextstyle(25,0,_T("黑体"));
	outtextxy(740,650,"游戏制作人员：韩丰");
	outtextxy(50,650,"游戏版本：1.0.0.1");
	settextcolor(RGB(25,182,192));
	settextstyle(100,0,_T("黑体"));
	outtextxy(241,130,"夜夜爱消除");
	settextcolor(RGB(255,0,0));
	settextstyle(65,0,_T("黑体"));


	outtextxy(320,400,"游戏开始");
	getch();
}

void init1()
{
	float wya,wyb,wyc,wyd,wye,wyf,wyg,wyh;			
	wya=242;wyb=130;wyc=320;wyd=400;wye=50;wyf=650;wyg=740;wyh=650;
	float dxa,dxb,dxc;
	cleardevice();	
	dxa=100;dxb=65;dxc=25;
	for(int i=1;i<50;i++)
	{
		
		settextcolor(RGB(255,255,255));
		settextstyle(dxc-i*0.5,0,_T("黑体"));
		outtextxy(wyg-i*4.6,wyh-i*5.98,"游戏制作人员：韩丰");
		outtextxy(wye+i*8.4,wyf-i*5.8,"游戏版本：1.0.0.1");
		settextcolor(RGB(25,182,192));
		settextstyle(dxa-i*1.95,0,_T("黑体"));
		outtextxy(wya+i*5.16,wyb+i*4.34,"夜夜爱消除");
		settextcolor(RGB(255,0,0));
		settextstyle(dxb-i*1.28,0,_T("黑体"));
		outtextxy(wyc+i*3.56,wyd-i*0.96,"游戏开始");
	

		
		/*settextcolor(RGB(255,255,255));
		settextstyle(dxc-i*0.25,0,_T("黑体"));
		outtextxy(wyg-i*2.3,wyh-i*2.9,"游戏制作人员：韩丰");
		outtextxy(wye+i*4.47,wyf-i*2.89,"游戏版本：1.0.0.1");
		settextcolor(RGB(25,182,192));
		settextstyle(dxa-i*0.92,0,_T("黑体"));
		outtextxy(wya+i*2.58,wyb+i*2.17,"夜夜爱消除");
		settextcolor(RGB(255,0,0));
		settextstyle(dxb-i*0.64,0,_T("黑体"));
		outtextxy(wyc+i*1.78,wyd-i*0.48,"GAME BEGIN");	
		Sleep(1);*/


		

	}	
	

}




void gamebegin()
{

	cleardevice();
	
	//绘制边框
	setlinecolor(RGB(50,50,50));
	setlinestyle(PS_SOLID,10);
	rectangle(255,45,745,655);
	//绘制小球
	
	setlinestyle(PS_SOLID);
	srand((unsigned)time(NULL));//提供随机数种子 相当于随机数初始化
	for(int x=280;x<740;x+=40)
	{
		for(int y=70;y<650;y+=40)
		{
			COLORREF cl=colorArr[rand()%6];//rand()%6 生成随机数，%6是随机数的6的余数，所以取值范围是0到5
			setlinecolor(cl); 
			setfillcolor(cl);
			fillcircle(x,y,18);
			

		}
			

	}
	//绘制光标
	cur.x=480;
	cur.y=390;
	drawcursor(cur,RGB(255,255,255));
	//绘制时间
	drawtime(30);
	//绘制分数
	drawscore(0);
}



void gameplay()
{
	int score=0;
	getch();
	for(int i=299;i>-1;i--)
	{
		if(i%10==0)
		{
			drawtime(i/10);
		}

		
		if(KEY_DOWN(VK_UP)&&cur.y>70)
		{
			drawcursor(cur,RGB(0,0,0,));
			cur.y-=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_DOWN)&&cur.y<630)
		{
			drawcursor(cur,RGB(0,0,0,));
			cur.y+=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_LEFT)&&cur.x>280)
		{
			drawcursor(cur,RGB(0,0,0,));
			cur.x-=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_RIGHT)&&cur.x<720)
		{
			drawcursor(cur,RGB(0,0,0,));
			cur.x+=40;
			drawcursor(cur,RGB(255,255,255));
		}
		else if(KEY_DOWN(VK_RETURN)||KEY_DOWN(VK_SPACE))
		{
			//获得光标所在位置周围的同色小球坐标，存入数组，并记录个数
			getsamecolorballs(cur,getpixel(cur.x,cur.y));
			
			//将数组中元素依次置黑
			if(index>1)
			{
				for(int k=0;k<index;k++)
				{
					setlinecolor(RGB(0,0,0,)); 
					setfillcolor(RGB(0,0,0,));
					fillcircle(ballsArr[k].x,ballsArr[k].y,18);
				}
				Sleep(500);
				//上方小球下落
				ballsfall();
				//刷新分数
				score=score+(index*index);
				drawscore(score);



			}

			
			index=0;

		}
		Sleep(80);	
	}
	//游戏结束擦掉屏幕
	Sleep(500);
	
	cleardevice();
	//定义画笔字体
	settextcolor(RGB(255,0,0));
	settextstyle(80,0,_T("黑体"));
	outtextxy(320,300,"GAME OVER");
	drawscore(score);
	

}

void close()
{
	getch();
	closegraph();
}

//画光标代码需要重复多次，所以进行封装处理
void drawcursor(posType pos,COLORREF cl)
{
	setlinecolor(cl);
	rectangle(pos.x-20,pos.y-20,pos.x+20,pos.y+20);
}

//封装绘制时间
void drawtime(int sec)
{
	char str[30];//定义字符串
	settextcolor(RGB(255,255,0));
	settextstyle(25, 0, _T("黑体"));
	sprintf(str,"剩余时间：%2d s",sec);//格式化字符串组
	outtextxy(20, 50, str);

}

//封装绘制分数
void drawscore(int score)
{
	char str[30];//定义字符串
	settextcolor(RGB(255,0,0));
	settextstyle(25, 0, _T("黑体"));
	sprintf(str,"分数：%d",score);//格式化字符串组
	outtextxy(20, 630, str);

}


//获取相同颜色小球
void getsamecolorballs(posType cur,COLORREF cl)
{
	
	ballsArr[index].x=cur.x;
	ballsArr[index].y=cur.y;
	index++;
	
	posType tempos;
	for(int k=0;k<4;k++)
	{
		switch(k)
		{
		case 0:tempos.x=cur.x;tempos.y=cur.y-40;break;//上
		case 1:tempos.x=cur.x;tempos.y=cur.y+40;break;//下
		case 2:tempos.x=cur.x-40;tempos.y=cur.y;break;//左
		case 3:tempos.x=cur.x+40;tempos.y=cur.y;break;//右
		}


		if(isvalid(tempos,cl))
		{
		
			getsamecolorballs(tempos,cl);//递归
			
		}
	}
	
}


//返回值0和1判断
int isvalid(posType cur,COLORREF cl)
{
	if(getpixel(cur.x,cur.y)!=cl)
	{
		return 0;
	}
	else
	{
		for(int i=0;i<index;i++)//判断数组中之前是否已经存在
		{
			if(cur.x==ballsArr[i].x&&cur.y==ballsArr[i].y)
			{
				return 0;
			}
		}
		return 1;
	}
}






void turn()
{
	int i,j;posType temp;
	for(j=0;j<index-1;j++)
	for(i=0;i<index-1-j;i++)
	{
		if(ballsArr[i].x>ballsArr[i+1].x)
		{
			temp=ballsArr[i];
			ballsArr[i]=ballsArr[i+1];
			ballsArr[i+1]=temp;
		}
		if(ballsArr[i].y>ballsArr[i+1].y)
		{
			temp=ballsArr[i];
			ballsArr[i]=ballsArr[i+1];
			ballsArr[i+1]=temp;
		}
	}
}

void ballsfall()
{
	turn();
	for(int i=0;i<index;i++)
	{
		for(int k=ballsArr[i].y;k>70;k-=40)
		{
			COLORREF cl=getpixel(ballsArr[i].x,k-40);
			setlinecolor(cl);
			setfillcolor(cl);
			fillcircle(ballsArr[i].x,k,18);
		}
		COLORREF cl=colorArr[rand()%6];
		setlinecolor(cl);
		setfillcolor(cl);
		fillcircle(ballsArr[i].x,70,18);
	}
}






































/*posType upball;
	upball.x=cur.x;
	upball.y=cur.y-40;
	if(getpixel(upball.x,upball.y)==cl)
	{
		ballsArr[index].x=upball.x;
		ballsArr[index].y=upball.y;
		index++;
	}

	posType downball;
	downball.x=cur.y+40;
	if(getpixel(downball.x,downball.y)==cl)
	{
		ballsArr[index].x=downball.x;
		ballsArr[index].y=downball.y;
		index++;
	}*/
