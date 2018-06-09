#include "E101.h"
#include <stdio.h>

int forward(int left, int right){  //left and right to be decided by error size
  if(left>255){left=255;}
  if(right>255){right=255;}
  if(left<-255){left=-255;}
  if(right<-255){right=-255;}
  right=right*-1 //wheels need to turn in opposite directions otherwise we have a burnout
  set_motor(1,left);
  set_motor(2,right);
}

int stop(){
  set_motor(1,0);
  set_motor(2,0);
}

int hard_turn_left(int turn){ //hard turning for Q2 part where it is all sharp turns
  set_motor(1,0);
  set_motor(2,127);	//not 127 holy shit it's fast
  sleep1(0,turn);
  forward();
}

int hard_turn_right(int turn){ //hard turning for Q2 part where it is all sharp turns
  set_motor(2,0);             //turn to be decided by error size
  set_motor(1,127);	//not 127 holy shit it's fast
  sleep1(0,turn);
  forward();
}

//figure out which gate code we're using
void gate1() {
	char password[24];
	char IP_addr [15] = {'1','0','.','1','4','0','.3','0','.,'1','5',',6'}; //Nathan's IP
	char send [24] = {'p','l','e','a','s','e'};
	connect_to_server(IP_addr, 1024);
	send_to_server(send);
	receive_from_server(password);
	send_to_server(password);
}

void openGate() {
	char[] ipAddr;
	strcopy(ipAddr, "10.140.30.156".c_str()); 	//Convert string to character array (easier than declaring a character array with the IP address).
	
	char[] message;
	strcopy(message, "please".c_string());
	
	connect_to_server(ipAddr, 1000); 	//Establish a connection to the server
	send_to_server(message); 	//Request the password from the server
	
	char[24] response;
	recieve_from_server(response);	 //Store the server response
	
	send_to_server(response); 	//Transmit the response back to the server
	
	//Gate is now open.
  
}

int whiteThreshold;

void updateWhiteThreshold() {
	int min = 255;
	int max = 0;
	
	take_picture();
	
	for (int r = 0; r < 240; r++) { //#of rows
		for (int c = 0; c < 320; c++) { //# of columns
			int pixel = get_pixel(r, c, 3);
			
			if (pixel > max) {
				max = pixel;
			}
			else if (pixel < min) {
				min = pixel;
			}
		}
	}
	
	//whiteThreshold is a global variable.
	whiteThreshold = (max - min) / 2;
}

int getErrorSignal() {
     updateWhiteThreshold();
	take_picture();
	
	int error = 0;
	int whitePixelCount = 0;
	
	for (int i = 0; i < 320; i++) {
		int pixel = get_pixel(120, i, 3);
		
		error += (i - 160) * pixel;
		
		if (pixel > whiteThreshold) {
			whitePixelCount++;
		}
	}
	
	return error / whitePixelCount;
}

int main(){
  init();
  forward(50,50);	//not 127 holy shit it's fast
  sleep1(3,0);
  hard_turn_right(100000);
  hard_turn_left(100000);
  stop();

  return 0;
}
