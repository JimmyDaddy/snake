#include <iostream>
#include <windows.h>

#include <conio.h>
#include "point.h"
#include "snake.h"
#include "control.h"
#include "game.h"
using namespace std;

int main()
{
  system("mode con:cols=100 lines=40");

  control* ctrl1 = new control;
  ctrl1->setRange(0, 98, 5, 35);
  circlePointFactory cpf;
  simpleSnakeFactory ssf(cpf);
  ctrl1->createSnake(3, 22, 6, ssf);
  simpleGame sg(ctrl1);
  sg.play();

//  control* ctrl2 = new control;
//  ctrl2->setRange(20, 80, 5, 35);
//  colorfulPointFactory cpf;
//  simpleSnakeFactory ssf(cpf);
//  ctrl2->createSnake(3, 22, 6, ssf);
//  marqueeGame mq(ctrl2);
//  mq.play();

}
