#include "E101.h"
#include <stdio.h>

int forward(int speed){
  if(speed>255){
    speed=255;
  }
  if(speed<-255){
    speed=-255; //127/-127?
  }
  set_motor(1,speed);
  set_motor(2,speed);
}
int stop(){
  set_motor(1,0);
  set_motor(2,0);
}

int main(){
  init();
  forward(50);
  sleep1(3,0);
  stop();

  return 0;
}
