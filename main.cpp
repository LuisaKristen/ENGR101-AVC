#include "E101.h"
#include <stdio.h>

int forward(int speed){
  set_motor(1,speed);
  set_motor(2,speed);
}
int stop(){
  set_motor(1,0);
  set_motor(2,0);
}

int main(){
  init();
  foward(50);
  sleep1(3,0);
  stop();

  return 0;
}
