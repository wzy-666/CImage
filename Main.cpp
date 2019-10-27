#include<iostream>
#include<graphics.h>

using namespace std;

#define WINDOW_X 800
#define WINDOW_Y 600

enum Shape
{
	Square = 1,
	Circle = 2,
};

class Pen
{
private:
	int size;
	Shape shape;
	COLORREF color;

public:
	Pen(int size = 10, Shape shape = Square, COLORREF color = 0)
	{
		SetSize(size);
		Setshape(shape);
		SetColor(color);
	}
	void SetSize(int size);
	void Setshape(Shape shape);
	void SetColor(COLORREF color);
	void Draw(void);
};

void Pen::SetSize(int size)
{
	this->size = size;
}

void Pen::Setshape(Shape shape)
{
	this->shape = shape;
}

void Pen::SetColor(COLORREF color)
{
	this->color = color;
	setfillcolor(this->color);
}

void Pen::Draw(void)
{
	MOUSEMSG mouse = GetMouseMsg();
	if (this->size==1)
	{
		putpixel(mouse.x, mouse.y, this->color);
	}
	else
	{
		switch (this->shape)
		{
		case Square:
			bar(mouse.x - size, mouse.y - size, mouse.x, mouse.y);
			break;
		case Circle:
			fillcircle(mouse.x, mouse.y, this->size);
			break;
		default:
			break;
		}
	}
}

bool MouseInside(int x1, int y1, int x2, int y2)
{
	MOUSEMSG mouse_now = GetMouseMsg();
	if (mouse_now.x >= x1 &&
		mouse_now.x <= x2 &&
		mouse_now.y >= y1 &&
		mouse_now.y <= y2)
		return 1;
	else
		return 0;
}

HDC imgHDC;

void Welcome(IMAGE &img)
{
	cout << "Welcome, Please input your image path." << endl;

	char file_path[64];
	cin >> file_path;

	loadimage(&img, _T(file_path));
	imgHDC = GetImageHDC(&img);
}

void DrawMenu(IMAGE& img)
{
	initgraph(WINDOW_X, WINDOW_Y, NOMINIMIZE);

	/* »æÍ¼ */
	setfillcolor(0xffffff);
	bar(0, 0, WINDOW_X, WINDOW_Y);
	/* »æÍ¼ */

	int center_x = (WINDOW_X - img.getwidth()) / 2;
	int center_y = (WINDOW_Y - img.getheight()) / 2;
	putimage(center_x, center_y, &img);
}

void Palette(Pen &pen)
{
	MOUSEMSG mouse = GetMouseMsg();
}

int main()
{
	IMAGE img;
	Welcome(img);
	DrawMenu(img);

	Pen pen;

	while (true)
	{
		if (MouseHit())
		{
			if (MouseInside(20,20,400,100))
			{
				//µ÷É«°å
			}
			else if (MouseInside(0,0,500,500))
			{
				pen.Draw();
			}
			else
			{
				;
			}
		}
	}

	closegraph();

	return 1;
}

