#include<iostream>
#include<graphics.h>

using namespace std;

#define WINDOW_X 800
#define WINDOW_Y 600

#define COLOR_NUM 8

/********************************************************************/

enum Shapes
{
	Square = 1,
	Circle = 2,
};

enum color
{
	White  = 0,
	Black  = 1,
	Red    = 2,
    Green  = 3,
	Blue   = 4,
	Yellow = 5,
	Purple = 6,
	Cyan   = 7,
};

COLORREF  base_color[COLOR_NUM] = {
	0xffffff,
	0x000000,
	0xff0000,
	0x00ff00,
	0x0000ff,
	0xffff00,
	0xff00ff,
	0x00ffff
};

MOUSEMSG mouse_now;

/********************************************************************/

bool MouseInsideImg(IMAGE& img);
bool MouseInside(int x1, int y1, int x2, int y2);
bool MouseInsideClick(int x1, int y1, int x2, int y2);

void Welcome(IMAGE& img);

/********************************************************************/

class Pen
{
private:
	int size;
	Shapes shape;
	COLORREF color;

public:
	Pen(int size = 10, Shapes shape = Square, COLORREF color = 0)
	{
		SetSize(size);
		Setshape(shape);
		SetColor(color);
	}
	void SetSize(int size);
	void Setshape(Shapes shape);
	void SetColor(COLORREF color);
	void Draw(void);
};

void Pen::SetSize(int size)
{
	this->size = size;
}

void Pen::Setshape(Shapes shape)
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

/********************************************************************/

class Patette
{
private:
	COLORREF color;

public:
	Patette(COLORREF color = 0);
	void SelectColor();
	void Update(Pen& pen);
	void DrawPattleBox();
};

Patette::Patette(COLORREF color)
{
	this->color = color;
	DrawPattleBox();
}

void Patette::SelectColor()
{
	const int w = 20;		//width
	const int h = 20;		//heigth
	const int s = 20;		//space
	const int x = 20;
	const int y = 20;

	for (int i = 0; i < COLOR_NUM; i++)
	{
		if (MouseInside(x + i * s, y, x + i * s + w, y + h))
		{
			this->color = base_color[i];
			break;
		}
		else
		{
			;
		}
	}
}

void Patette::DrawPattleBox()
{
	const int w = 20;		//width
	const int h = 20;		//heigth
	const int s = 20;		//space
	const int x = 20;
	const int y = 20;

	setfillstyle(BS_SOLID);

	for (int i = 0; i < COLOR_NUM; i++)
	{
		setfillcolor(0x000000);
		bar(x + i * s - 1, y - 1, x + i * s + w + 1, y + h + 1);
		setfillcolor(base_color[i]);
		bar(x + i * s, y, x + i * s + w, y + h);
	}

	setfillcolor(0xffffff);
}

void Patette::Update(Pen& pen)
{
	pen.SetColor(this->color);
}

/********************************************************************/

class Size
{
private:
	int size;
public:
	Size(int size = 10);
	void SelectSize();
	void Update(Pen& pen);
	void DrawSizeBox();
};

Size::Size(int size)
{
	this->size = size;
	DrawSizeBox();
}

void Size::SelectSize()
{
	const int x1 = 400;
	const int y1 = 20;
	const int w = 20;
	const int h = 20;
	const int space = 22;

	if (MouseInside(x1, y1, x1 + w, y1 + h))
	{
		if (this->size < 20)
		{
			this->size++;
		}
	}
	else if (MouseInside(x1 + space, y1, x1 + w + space, y1 + h))
	{
		if (this->size > 0)
		{
			this->size--;
		}
	}
}

void Size::DrawSizeBox()
{
	const int x1 = 400;
	const int y1 = 20;
	const int w = 20;
	const int h = 20;
	const int space = 22;

	setfillcolor(0x000000);
	bar(x1 - 1, y1 - 1, x1 + w + 1, y1 + h + 1);
	bar(x1 + space - 1, y1 - 1, x1 + w + space + 1, y1 + h + 1);

	setfillcolor(0x808080);
	bar(x1, y1, x1 + w, y1 + h);
	bar(x1 + space, y1, x1 + w + space, y1 + h);

	settextstyle(16, 16, "ËÎÌå");
	setfillstyle(BS_NULL);
	outtextxy(x1 + 2, y1 + 2, '+');
	outtextxy(x1 + space + 2, y1 + 2, '-');
	setfillstyle(BS_SOLID);
}

void Size::Update(Pen& pen)
{
	pen.SetSize(this->size);
	
	char size_string[4];
	sprintf_s(size_string, "%-2d", this->size);

	setfillstyle(BS_NULL);
	outtextxy(450, 20, size_string);
	setfillstyle(BS_SOLID);
}

/********************************************************************/

class Shape
{
private:
	Shapes shape;
public:
	Shape(Shapes shape = Square);
	void SelectSpape();
	void Update(Pen& pen);
	void DrawShapeBox();

};

Shape::Shape(Shapes shape)
{
	this->shape = shape;
	DrawShapeBox();
}

void Shape::SelectSpape()
{
	const int x1 = 600;
	const int y1 = 20;
	const int w = 20;
	const int h = 20;
	const int space = 22;

	if (MouseInside(x1, y1, x1 + w, y1 + h))
	{
		this->shape = Square;
	}
	else if (MouseInside(x1 + space, y1, x1 + w + space, y1 + h))
	{
		this->shape = Circle;
	}
}

void Shape::DrawShapeBox()
{
	const int x1 = 600;
	const int y1 = 20;
	const int w = 20;
	const int h = 20;
	const int space = 22;


	setfillcolor(0x404040);
	bar(x1, y1, x1 + w, y1 + h);
	bar(x1 + space, y1, x1 + w + space, y1 + h);

	setcolor(0xffffff);
	rectangle(x1 + 2, y1 + 2, x1 + w - 2, y1 + h - 2);
	circle(x1 + space + w / 2, y1 + h / 2, sqrt(h * h + w * w) / 4);

	setfillcolor(0xffffff);
}

void Shape::Update(Pen& pen)
{
	pen.Setshape(this->shape);
}

/********************************************************************/

int main()
{
	IMAGE img;

	Welcome(img);

	Pen pen;
	Size size;
	Shape shape;
	Patette pat;

	while (true)
	{
		mouse_now = GetMouseMsg();
		if (MouseInsideClick(20, 20, 180, 40))
		{
			pat.SelectColor();
			pat.Update(pen);
		}
		else if (MouseInsideClick(400, 20, 450, 40))
		{
			size.SelectSize();
			size.Update(pen);
		}
		else if (MouseInsideClick(600, 20, 650, 40))
		{
			shape.SelectSpape();
			shape.Update(pen);
		}
		else if (MouseInsideImg(img))
		{
			pen.Draw();
		}
		else
		{
			;
		}
		Sleep(2);
	}

	closegraph();

	return 1;
}

bool MouseInsideClick(int x1, int y1, int x2, int y2)
{
	if (mouse_now.x >= x1 &&
		mouse_now.x <= x2 &&
		mouse_now.y >= y1 &&
		mouse_now.y <= y2 &&
		mouse_now.mkLButton == 1)
		return 1;
	else
		return 0;
}

bool MouseInside(int x1, int y1, int x2, int y2)
{
	if (mouse_now.x >= x1 &&
		mouse_now.x <= x2 &&
		mouse_now.y >= y1 &&
		mouse_now.y <= y2)
		return 1;
	else
		return 0;
}

bool MouseInsideImg(IMAGE& img)
{
	static int x1 = (WINDOW_X - img.getwidth()) / 2;
	static int x2 = (WINDOW_X + img.getwidth()) / 2;
	static int y1 = (WINDOW_Y - img.getheight()) / 2;
	static int y2 = (WINDOW_Y + img.getheight()) / 2;

	if (mouse_now.x >= x1 &&
		mouse_now.x <= x2 &&
		mouse_now.y >= y1 &&
		mouse_now.y <= y2 &&
		mouse_now.mkLButton == 1)
		return 1;
	else
		return 0;
}

void Welcome(IMAGE& img)
{
	initgraph(WINDOW_X, WINDOW_Y, NOMINIMIZE);

	setfillcolor(0xffffff);
	bar(0, 0, 800, 600);

	outtextxy(20, 20, _T("ÇëÊäÈë:"));

	char file_path[64];
	cin >> file_path;

	setfillcolor(0xffffff);
	bar(0, 0, 800, 600);

	loadimage(&img, _T(file_path));

	int center_x = (WINDOW_X - img.getwidth()) / 2;
	int center_y = (WINDOW_Y - img.getheight()) / 2;
	putimage(center_x, center_y, &img);
}