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
void openGate() {
	char pass[24];
	char addr [15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	char toSend [24] = {'p','l','e','a','s','e'};
	connect_to_server(addr, 1024);
	send_to_server(toSend);
	receive_from_server(pass);
	send_to_server(pass);
}


// white threshold to account for variations in lighting
void updateWhiteThreshold() {
	take_picture();
	int totalWhite = 0;
	//Loop through whole image
	for (int r = 0; r < 240; r++) {
		for (int c = 0; c < 320; c++) {
			totalWhite += get_pixel(r, c, 3);
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





