#include "E101.h"
#include <stdio.h>

int forward(int left, int right){  //left and right to be decided by error size
  if(left>255){left=255;}
  if(right>255){right=255;}
  if(left<-255){left=-255;}
  if(right<-255){right=-255;}
  set_motor(1,left);
  set_motor(2,right);
}
int stop(){
  set_motor(1,0);
  set_motor(2,0);
}

int hard_turn_left(int turn){ //hard turning for Q2 part where it is all sharp turns
  set_motor(1,0);
  set_motor(2,127);
  sleep1(0,turn);
  forward();
}

int hard_turn_right(int turn){ //hard turning for Q2 part where it is all sharp turns
  set_motor(2,0);             //turn to be decided by error size
  set_motor(1,127);
  sleep1(0,turn);
  forward();
}

void gate1() {
	char password[24];
	char IP_addr [15] = {};
	char send [24] = {'p','l','e','a','s','e'};
	connect_to_server(IP_addr, 1024);
	send_to_server(send);
	receive_from_server(password);
	send_to_server(password);
}

int main(){
  init();
  forward(50);
  sleep1(3,0);
  hard_turn_right(100000);
  hard_turn_left(100000);
  stop();

  return 0;
}
