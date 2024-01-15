#include<WinBGIm/graphics.hpp>
#include<iostream>
#define ROUND(a) (int)(a+0.5)
using namespace std;

void plot(int xc, int yc, int x, int y, int color)
{
    putpixel(xc + x, yc + y, color);// trên phải
    putpixel(xc - x, yc + y, color);// trên trái
    putpixel(xc + x, yc - y, color);// dưới phải
    putpixel(xc - x, yc - y, color);// dưới trái
}
void elipMidpoint(int xc, int yc, int a, int b, int color)
{
    int x, y, fx, fy, a2, b2, p;
    x = 0;
    y = b;
    a2 = a * a;
    b2 = b * b;
    //x=0,y=b
    //f(x)=2b^2x
    //f(y)=2a^2y
    fx = 0;
    fy = 2 * a2 * y;

    plot(xc, yc, x, y, color);
    p = ROUND(b2 - (a2 * b) + (0.25 * a2));//p1=b2 - a2*b +a2/4
    while (fx < fy)
    {
        x++;// đồng biến theo x => f(x) tăng
        fx += 2 * b2;
        delay(50);
        if (p < 0)
        {
            p += b2 * (2 * x + 3);//p=p + b2*(2x +3)
            cout << "p1" << p << "\n";
        }
        else
        {
            y--;
            p += b2 * (2 * x + 3) + a2 * (2 - 2 * y);//p=p +b2(2x +3) +a2(2-2y)
            cout <<"p1" << p << "\n";
            fy -= 2 * a2;
        }
        plot(xc, yc, x, y, color);
    }
    p = ROUND(b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2);
    //
    while (y > 0)
    {
        y--;
        fy -= 2 * a2;
        delay(50);
        if (p >= 0)
        {
            p += a2 * (3 - 2 * y); //p=p +a2(3-2y)
            cout << "p2" << p << "\n";
        }
        else
        {
            x++;
            fx += 2 * b2;
            p += b2 * (2 * x + 2) + a2 * (3 - 2 * y);//p=p+ b2(2x +2) + a2(3-2y)
            cout << "p2" << p << "\n";
        }
        plot(xc, yc, x, y, 150);
    }
}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    int a,b;
    int delay = 50;
    cout << "Nhập a:";
    cin >> a;
    cout << "Nhập b:";
    cin >> b;
    int maxX = getmaxx();
    int maxY = getmaxy();

    // Tọa độ của điểm chính giữa màn hình
    int centerX = maxX / 2;
    int centerY = maxY / 2;
    setcolor(GREEN);
    line(0, centerY, getmaxx(), centerY);

    // Thiết lập màu xanh cho trục y
    setcolor(GREEN);
    line(centerX, 0, centerX, getmaxy());
    //line(0, centerY, maxX, centerY);  // Trục x
    //line(centerX, 0, centerX, maxY);  // Trục y
    elipMidpoint(centerX, centerY, a, b, 15);
    getch();
    closegraph();
    cin.get();
    return 0;
}