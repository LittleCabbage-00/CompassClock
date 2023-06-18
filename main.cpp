#include <graphics.h> 
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h> 

#define PI acos(-1)
#define Width 1000
#define Height 750

void DrawCircle(TCHAR str[25], int variable, int fors, int R, double Radian);
int monthdasy(int y, int m);

struct TimeCircle
{
	int loop;
	int R;
	double NextTime;
	double Radian;
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	initgraph(Width, Height, EW_SHOWCONSOLE);
	SYSTEMTIME ti;
	TimeCircle TC[7];
	TCHAR str[25];

	for (int i = 0; i < 7; i++)
	{
		TC[i].R = (i + 1) * 50;
		TC[i].Radian = 0;
		TC[i].NextTime = 0;

		switch (i)
		{
		case 0:
			TC[i].loop = 1;
			break;
		case 1:
			TC[i].loop = 12;
			break;
		case 2:
			TC[i].loop = 30;
			break;
		case 3:
			TC[i].loop = 7;
			break;
		case 4:
			TC[i].loop = 24;
			break;
		case 5:
			TC[i].loop = 60;
			break;
		case 6:
			TC[i].loop = 60;
			break;
		}
	}

	BeginBatchDraw();
	while (true)
	{
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		IMAGE background;
		loadimage(&background, L"win11.jpg", 1000, 1000);
		putimage(0, 0, &background);

		GetLocalTime(&ti);
		TC[2].loop = monthdasy(ti.wYear, ti.wMonth);
		for (int j = 0; j < 7; j++)
		{
			if (TC[5].NextTime != ti.wMinute)
			{
				TC[5].NextTime = ti.wMinute;
				TC[5].Radian = 0;
			}
			else
			{
				TC[5].Radian = TC[5].Radian +
					(2 * PI / TC[5].loop - TC[5].Radian) / 10;
			}

			if (TC[6].NextTime != ti.wSecond)
			{
				TC[6].NextTime = ti.wSecond;
				TC[6].Radian = 0;
			}
			else
			{
				TC[6].Radian = TC[6].Radian +
					(2 * PI / TC[6].loop - TC[6].Radian) / 10;
			}

			for (int i = 0; i < TC[j].loop; i++)
			{
				switch (j)
				{
				case 0: _stprintf_s(str, _T("%d年"), ti.wYear);
					break;
				case 1: _stprintf_s(str, _T("%d月"),
					(i + ti.wMonth) % TC[j].loop ?
					(i + ti.wMonth) % TC[j].loop : TC[j].loop);
					break;
				case 2: _stprintf_s(str, _T("%d号"),
					(i + ti.wDay) % TC[j].loop ?
					(i + ti.wDay) % TC[j].loop : i + ti.wDay);
					break;
				case 3: str[0] = L"周"[0];
					str[1] = L"日一二三四五六"[(i + ti.wDayOfWeek) % 7];
					str[2] = L""[0];
					break;
				case 4: _stprintf_s(str, _T("%d时"),
					(i + ti.wHour) % TC[j].loop);
					break;
				case 5: _stprintf_s(str, _T("%d分"),
					(i + ti.wMinute) % TC[j].loop);
					break;
				case 6: _stprintf_s(str, _T("%d秒"),
					(i + ti.wSecond) % TC[j].loop);
					break;
				}
				DrawCircle(str, i, TC[j].loop, TC[j].R, TC[j].Radian);;
			}
		}
		FlushBatchDraw();
		cleardevice();
	}
	EndBatchDraw();
	return 0;
}

int monthdasy(int y, int m)
{
	if (m == 2)
		return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) ? 29 : 28;
	else
		return 31 - (m - 3) % 5 % 2;
}

void DrawCircle(TCHAR str[25], int variable, int fors, int R, double Radian)
{
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	double a, x0, y0, w, h, x1, y1;
	int x, y;
	settextstyle(22, 0, L"微软雅黑", variable * 3600 / fors,
		variable * 3600 / fors, 0, false, false, false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		DEFAULT_PITCH);

	a = (fors == 60) ? ((variable + 1) * PI * 2 / fors - Radian) :
		(variable * PI * 2 / fors);

	w = textwidth(str);
	h = textheight(str);

	x0 = R;
	y0 = 0;

	x0 -= w / 2;
	y0 += h / 2;

	x = (int)(x0 * cos(a) - y0 * sin(a));
	y = (int)(y0 * cos(a) + x0 * sin(a));

	outtextxy(int(Width / 2 + x + 0.5), int(Height / 2 - y + 0.5), str);
}
