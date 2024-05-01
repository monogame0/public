// Gamemain.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <Windows.h>
#include <graphics.h>
#include <math.h>
#include <iostream>
using namespace std;
#define   Window_Width  640
#define   Window_Higth  480

#define   MINE_PosX   200
#define   MINE_PosY   200
#define   MINE_Speed   5
#define   MINE_Angle  1
#define   MINE_IMAGE_Width  155
#define   MINE_IMAGE_Higth  180
#define   PI 3.14159265

struct Mouse {
	int x;
	int y;
};
void closewindow(void) {  //清平
	closegraph();
	return;
}
void CloseWindow(void) {  //关闭窗口
	closegraph();
}
void Begin(void) {
	BeginBatchDraw();
}
void End(void) {
	FlushBatchDraw();
}
bool GetKey(int nKey) {  //检测按键是否按下
	if (GetKeyState(nKey) < 0){
		return true;
	}
	else {
		return false;
	}
}
void rotateimage(const char * str, double angle) {
	IMAGE img, img2;
	loadimage(&img, str, 197, 134);
	rotateimage(&img2, &img, PI / (180 / angle));
	putimage(0, 0, &img2);
}
void GetMousePos(ExMessage * msg, struct Mouse * mouse) {  //获取鼠标坐标
	if (peekmessage(msg) == true) {
		mouse->x = msg->x;
		mouse->y = msg->y;
	}
	else {
		return;
	}
}
int abs(int a, int b) {  //绝对值
	if (a - b > 0)
		return a - b;
	else
		return b - a;
}
int TwoPointLength(int x1, int y1, int x2, int y2) {
	return (int)( sqrt( abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2)) );
}
void stop(void) {
	while (true) {
		while (true);
	}
	getchar();
}
void CleanWindow(void) {
	cleardevice();
}
class MINE {  //主角
public:
	int PosX;  //Y位置
	int PosY;    //X位置
	int Angle;  //角度
	int Speed;  //速度
	int SpeedX;  //Y速度
	int SpeedY;  //X速度
	IMAGE img;
	ExMessage point;  //鼠标位置
	struct Mouse mouse;

	MINE() {
		PosX = MINE_PosX;
		PosY = MINE_PosY;
		Speed = MINE_Speed;
		Angle = MINE_Angle;
		loadimage(&img, "IMAGE\\1.png", MINE_IMAGE_Width, MINE_IMAGE_Higth);
	}
	void TurnAround(void) {  //转向获取主角新方向
		GetMousePos(&point, &mouse);
		int HypLength;  //斜边长度
		int OppLength;  //对边长度
		HypLength = TwoPointLength(mouse.x, mouse.y, PosX, PosY);  //获取斜边
		OppLength = abs(mouse.y, PosY);  //获取对边
		Angle = asin(double((double)OppLength / (double)HypLength)) * 180.0 / PI;   //计算反sin
	}
	void Draw(void) {
		IMAGE imgtemp;
		if (Angle != 0) {
			rotateimage(&imgtemp, &img, (double)(PI / (180 / Angle)));
		}
		putimage(PosX, PosY, &imgtemp);
	}
};
int main()
{
	initgraph(Window_Width, Window_Higth);
	MINE my;
	while (true) {
		Begin();
		CleanWindow();
		//my.TurnAround();
		my.Draw();
		my.Angle++;
		End();
		if (GetKey(VK_SPACE)) {
			printf("Angle : %d\n", my.Angle);
			Sleep(50);
		}
		if (GetKey(VK_ESCAPE)) {
			break;
		}
		Sleep(10);
	}
	CloseWindow();
	stop();
    return 0;
}

