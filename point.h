#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <windows.h>
using namespace std;

class point
{
public:
  point(int px, int py):x(px),y(py),left(0),right(0){}
  virtual void setLeft(point* l){ left = l;}
  virtual void setRight(point* r){ right = r;}
  virtual void setPosition(point* p){
    if(!p)return;
    x = p->x; y = p->y;
  }
  virtual void setPosition(int px, int py){
    x = px; y = py;
  }
  virtual point* theLeft(){ return left;}
  virtual point* theRight(){ return right;}
  virtual int theX(){ return x;}
  virtual int theY(){ return y;}
  virtual void draw() = 0;
  virtual void draw(string str) = 0;
  virtual ~point(){}
protected:
  int x;
  int y;
  point* left;
  point* right;
};

class circlePoint : public point
{
public:
  circlePoint(int px, int py):point(px, py){}
  virtual ~circlePoint(){}
  virtual void draw(string str){
    COORD pos;
    pos.X = x;
    pos.Y = y;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
    SetConsoleTextAttribute(handle,FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << str;
  }
  virtual void draw(){
    draw("¡ñ");
  }
};

class colorfulPoint : public point
{
public:
  colorfulPoint(int px, int py, int c):point(px, py),colorIndex(c){
    colors[0] = FOREGROUND_BLUE;
    colors[1] = FOREGROUND_GREEN;
    colors[2] = FOREGROUND_RED;
    colors[3] = FOREGROUND_BLUE | FOREGROUND_GREEN;
    colors[4] = FOREGROUND_BLUE | FOREGROUND_RED;
    colors[5] = FOREGROUND_GREEN | FOREGROUND_RED;
    colors[6] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    colors[7] = FOREGROUND_INTENSITY;
  }
  virtual ~colorfulPoint(){}
  virtual void draw(string str){
    COORD pos;
    pos.X = x;
    pos.Y = y;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle,pos);
    colorIndex %= 8;
    SetConsoleTextAttribute(handle,colors[colorIndex]);
    ++colorIndex;
    cout << str;
  }
  virtual void draw(){
    draw("¡ö");
  }
private:
  int colors[8];
  int colorIndex;
};
class pointFactory
{
public:
  virtual point* makePoint(int x, int y) = 0;
};

class circlePointFactory : public pointFactory
{
public:
  virtual point* makePoint(int x, int y){
    return new circlePoint(x,y);
  }
};

class colorfulPointFactory : public pointFactory
{
public:
  colorfulPointFactory():index(0){}
  virtual point* makePoint(int x, int y){
    return new colorfulPoint(x, y, index++);
  }
private:
  int index;
};
#endif // POINT_H

