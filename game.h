#ifndef GAME_H
#define GAME_H
#include "control.h"
#include <omp.h>

class game
{
public:
  game(control* c):ctrl(c){}
  virtual void play() = 0;
protected:
  control* ctrl;
};

class simpleGame : public game
{
public:
  simpleGame(control* c):game(c){}
  virtual void play(){
    circlePointFactory cpf;
    ctrl->createFrame(cpf);
    ctrl->drawFrame();
    ctrl->createFood(cpf);

    char key;
    bool isOver = false;
    omp_lock_t mylock;
    omp_init_lock(&mylock);
    #pragma omp parallel sections num_threads(2)
    {
      #pragma omp section
      {
        while(true){
          omp_set_lock(&mylock);
          if(ctrl->tryToEat()){
            ctrl->createFood(cpf);
          }
          ctrl->move();
          ctrl->draw();
          if(ctrl->outOfRange()){
            isOver = true;
            break;
          }
          omp_unset_lock(&mylock);
          Sleep(ctrl->getSpeed()*1000);
          }
      }
      #pragma omp section
      {
        while(true){
         key = getch();
         if(key == 'w'){
           omp_set_lock(&mylock);
           ctrl->turnTo(snake::North);
           omp_unset_lock(&mylock);
         }else if(key == 'a'){
           omp_set_lock(&mylock);
           ctrl->turnTo(snake::West);
           omp_unset_lock(&mylock);
         }else if(key == 'd'){
           omp_set_lock(&mylock);
           ctrl->turnTo(snake::East);
           omp_unset_lock(&mylock);
         }else if(key == 's'){
           omp_set_lock(&mylock);
           ctrl->turnTo(snake::South);
         omp_unset_lock(&mylock);
         }else if(ctrl->outOfRange()){
           break;
         }
        }
      }
    }
  }
};

class marqueeGame : public game
{
public:
  marqueeGame(control* c):game(c){}
  virtual void play(){
    colorfulPointFactory cpf;
    ctrl->createFrame(cpf);
    ctrl->drawFrame();
    ctrl->createFood(cpf);
    bool isOver = false;
    char key;
    omp_lock_t mylock;
    omp_init_lock(&mylock);
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        while(true){
          omp_set_lock(&mylock);
          if(ctrl->tryToEat()){
            ctrl->createFood(cpf);
          }
        ctrl->move();
        ctrl->draw();
        ctrl->drawFrame();
        if(ctrl->outOfRange()){
            isOver = true;
            break;
        }
        omp_unset_lock(&mylock);
        Sleep(ctrl->getSpeed()*1000);
        }
      }
      #pragma omp section
      {
        while(true){
         if(isOver){cout << "aaaaa" ;break;}
         key = getch();
         if(key == 'w'){
         omp_set_lock(&mylock);
         ctrl->turnTo(snake::North);
         omp_unset_lock(&mylock);
         }else if(key == 'a'){
         omp_set_lock(&mylock);
         ctrl->turnTo(snake::West);
         omp_unset_lock(&mylock);
         }else if(key == 'd'){
         omp_set_lock(&mylock);
         ctrl->turnTo(snake::East);
         omp_unset_lock(&mylock);
         }else if(key == 's'){
         omp_set_lock(&mylock);
         ctrl->turnTo(snake::South);
         omp_unset_lock(&mylock);
         }else if(ctrl->outOfRange()){
         break;
         }
        }
      }
    }
  }
};
#endif // GAME_H
