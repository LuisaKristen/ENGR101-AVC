#include <stdio.h>
#include "E101.h"

void openGate() {
	char[] ipAddr;
	strcopy(ipAddr, "192.168.1.1".c_str()); 	//Convert string to character array (easier than declaring a character array with the IP address).
	
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
	whiteThreshold = (max + min) / 2;
}

int getErrorSignal() {
     updateWhiteThreshold();
	take_picture();
	
	int error = 0;
	int whitePixelCount = 0;
	
	for (int i = 0; i < 320; i++) {
		int pixel = get_pixel(120, i, 3);
		
		if (pixel > whiteThreshold) {
			pixel = 1;
			whitePixelCount++;
		}
		else {
			pixel = 0;
		}
		
		error += (i - 160) * pixel;
		
	}
	
	return error / whitePixelCount;
}

double previousError = 0; //Stores the value of the previous error signal
double kp = 0.005; 
double kd = 0.2;
int time =  500000;
int currentStep = 0; //Stores the current step (increments every loop)

void go() {
	int currentError = getErrorSignal();
	double dv = currentError * kp + ((currentError - previousError) / ((time * currentStep) - (time * (currentStep - 1)))) * kd;
	//dv = error ∗ Kp + de/dt ∗ Kd
	
	double vRight = v_go + dv; //Final speed of right motor
	double vLeft = v_go - dv; //Final speed of left motor
	
	previousError = currentError;
	currentStep++;
	
	set_motor(1, vLeft);
	set_motor(2, vRight);
`	updateWhiteThreshold();
	sleep1(0,time);
}


int quad = 1;

int main() {
	while (1) {
		if (quad == 1) {
			
			/*if (isAtGate()) {
				openGate();
				quad++;
			}*/
			
			go();
			
		}
		else if (quad == 2) {
			
		}
		else if (quad == 3) {
			
		}
		else if (quad == 4) {
			
		}
	}
	
	return 0;
}
