#include <stdio.h>
#include <math.h>
#include "E101.h"

int lineWhiteThreshold = 127;
int minWhiteToSeeLine = 10000000;
float kp = 0.00005;   //Will need to be adjusted, depends on the weight of the robot
int loopDelay = 100000;
int baseSpeed = 50;
int minWhiteForQ3 = 10005000;

//speed of robot:
void setSpeed(int left, int right) {
	if (left > 254) left = 254;
	if (left < -254) left = -254;
	if (right > 254) right = 254;
	if (right < -254) right = -254;
	right *= -1;
	set_motor(2, right);
	set_motor(1, left);
}

//First gate:
void gate1() {
	char password[24];
	char IP_addr [15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	char send [24] = {'p','l','e','a','s','e'};
	connect_to_server(IP_addr, 1024);
	send_to_server(send);
	receive_from_server(password);
	send_to_server(password);
}


// white threshold to account for variations in lighting
void whiteMinUpdate() {
	take_picture();
	int totalWhite = 0;
	//Loop through whole image
	for (int row = 0; row < 240; row++) {
		for (int col = 0; col < 320; col++) {
			totalWhite += get_pixel(row, col, 3);
		}
	}

	//Set to average of all pixels
	lineWhiteThreshold = totalWhite / 76800;
}


//rowStart and rowEnd are inclusive. Remember to take picture before using.
double getLineErrorSignal(int rowStart, int rowEnd) {
	int error = 0; //If negative, go left, if positive, go right
	int currWhite;
	for (int r = rowStart; r <= rowEnd; r++) {
		//Loop through the rows we are looking at
		for (int c = 0; c < 320; c++) {
			//Loop through the columns in the row
			currWhite = get_pixel(r, c, 3);
			error += currWhite*(c - 160);
		}
	}


	//Return the Average error of the rows
	return (double) error / (rowEnd - rowStart + 1);


}
void quadOne() {
	openGate();
	quad Two Loop();
}
int image_analysis() {
	take_picture();
	int sum = 0;
	int w;
	int s;
	for( int =0; i<320; i++){
		w = get_pixel( i, 120, 3);
		if( W >127){
			s=1;
		}
		else{
			s=0;
	}
		sum = sum + (i-160)*s
	}
	return 0;
}
int get_ir(int pin){
	int ir = 0;
for( int i =0; i<5; i++){
	ir = ir + read_analog( pin);
}
	return(ir/5);
}
int main(){
	init();
	sleep(15,0);
	quadOne();}
	





