#ifndef SNAKE_H
#define SNAKE_H
#include "point.h"
class snake
{
public:
  enum direction { East = 0, South, West, North};
public:
  snake():dir(East),head(0),tail(0){}
  virtual ~snake(){
    point* tmp = 0;
    while(head){
      tmp = head->theLeft();
      delete head;
      head = tmp;
    }
  }
  virtual void draw() = 0;
  virtual void move() = 0;
  virtual void eat(point* p){
    if(!head){tail = head = p; return;}
    head->setRight(p);
    p->setLeft(head);
    head = p;
  }
  virtual bool canEat(point* p){
    if(dir == East){
      if(p->theX()-2 == head->theX() && p->theY() == head->theY())
        return true;
    }else if(dir == South){
      if(p->theX() == head->theX() && p->theY()-1 == head->theY())
        return true;
    }else if(dir == West){
      if(p->theX()+2 == head->theX() && p->theY() == head->theY())
        return true;
    }else if(dir == North){
      if(p->theX() == head->theX() && p->theY()+1 == head->theY())
        return true;
    }
    return false;
  }
  virtual point* theHead(){ return head;}
  virtual void setDirection(direction d){ dir = d;}
protected:
  direction dir;
  point* head;
  point* tail;
};

class simpleSnake : public snake
{
public:
  simpleSnake():snake(){}
  virtual ~simpleSnake(){}
  virtual void draw(){
    head->draw("¡ô");
    point* tmp = head->theLeft();
    while(tmp){
      tmp->draw();
      tmp = tmp->theLeft();
    }
  }
  virtual void move(){
    tail->draw("  ");
    point* tmp = tail;
    while(tmp){
      tmp->setPosition(tmp->theRight());
      tmp = tmp->theRight();
    }
    int newX = head->theX();
    int newY = head->theY();
    if(dir == East)  newX += 2;
    if(dir == South) newY += 1;
    if(dir == West)  newX -= 2;
    if(dir == North) newY -= 1;
    head->setPosition(newX, newY);
  }
};

class snakeFactory
{
public:
  virtual snake* makeSnake(int numOfPoint, int x0, int y0) = 0;
};

class simpleSnakeFactory : public snakeFactory
{
public:
  simpleSnakeFactory(pointFactory& pf):Pf(pf){}
  virtual snake* makeSnake(int numOfPoint, int x0, int y0){
    if(_snake)return _snake;
    _snake = new simpleSnake();
    for(int i = 0; i < numOfPoint; ++i){
      _snake->eat(Pf.makePoint(2*i + x0, y0));
    }
    return _snake;
  }
private:
  pointFactory& Pf;
  static simpleSnake* _snake;
};
simpleSnake* simpleSnakeFactory::_snake = 0;

class colorfulSnakeFactroy : public snakeFactory
{
public:
  virtual snake* makeSnake(int numOfPoint, int x0, int y0){
    if(_snake)return _snake;
  }
private:
  static simpleSnake* _snake;
};

#endif // SNAKE_H
