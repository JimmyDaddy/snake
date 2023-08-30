#ifndef CONTROL_H
#define CONTROL_H
#include <omp.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include "point.h"
#include "snake.h"
using namespace std;
class control
{
public:
  control():_snake(0),speed(1.0){
    setRange(0,2*30,0,30);
  }
  virtual ~control(){
    delete _snake;
    destroyFrame();
  }
  virtual void setRange(int minx, int maxx, int miny, int maxy){
    minX = minx;
    maxX = maxx;
    minY = miny;
    maxY = maxy;
  }
  virtual void createSnake(int numOfPoint, int x0, int y0,snakeFactory& ssf){
    _snake = ssf.makeSnake(numOfPoint, x0, y0);
  }
  virtual void createFood(pointFactory& cpf){
    srand((unsigned)time(NULL));
    int x =(rand()%(maxX - minX - 3) + minX + 2)/2*2;
    int y = rand()%(maxY - minY - 1) + minY + 1;
    food = cpf.makePoint(x, y);
    food->draw();
  }
  virtual bool tryToEat(){
    if(_snake->canEat(food) ){
      _snake->eat(food);
      speedUp();
      return true;
    }
    else return false;
  }
  virtual double getSpeed(){
    return speed;
  }
  virtual void speedUp(){
    speed /= 1.3;
  }
  virtual void turnTo(snake::direction dir){
    _snake->setDirection(dir);
  }
  virtual void move(){
    _snake->move();
  }
  virtual void draw(){
    _snake->draw();
  }
  virtual bool outOfRange(){
    if(_snake->theHead()->theX() >= maxX ||
       _snake->theHead()->theX() <= minX ||
       _snake->theHead()->theY() >= maxY ||
       _snake->theHead()->theY() <= minY   )return true;
    else return false;
  }
  virtual void drawFrame(){
    vector<point*>::iterator index;
    for(index = Frame.begin(); index != Frame.end(); ++index){
      (*index)->draw();
    }
  }
  virtual void createFrame(pointFactory& cpf){
    for(int x = minX; x <= maxX; x += 2){
      Frame.push_back(cpf.makePoint(x, minY));
    }
    for(int y = minY+1; y < maxY; y += 1){
      Frame.push_back(cpf.makePoint(maxX, y));
    }
    for(int x = maxX; x >= minX; x -= 2){
      Frame.push_back(cpf.makePoint(x, maxY));
    }
    for(int y = maxY-1; y > minY; y -= 1){
      Frame.push_back(cpf.makePoint(minX, y));
    }
  }
  virtual void destroyFrame(){
    vector<point*>::iterator index;
    for(index = Frame.begin(); index != Frame.end(); ++index){
      delete (*index);
    }
  }
protected:
  vector<point*> Frame;
  snake* _snake;
  point* food;
  double speed;
  int minX;
  int maxX;
  int minY;
  int maxY;
};
#endif // CONTROL_H
