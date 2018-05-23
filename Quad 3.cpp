
#include <stdio.h>
#include "E101.h"

void gate1() {
        char password[24];
        char IP_addr [15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'}; //Gate's  IP
        char send [24] = {'P','l','e','a','s','e'};
        connect_to_server(IP_addr, 1024);
        send_to_server(send);
        receive_from_server(password);
        send_to_server(password);
        sleep1(0,2000000);
}

double whiteThreshold;
int count;
int  rightCorner=0;
int  leftCorner=0;
int TIntersect=0;
int uTurn=0;
int baseSpeed = 40;
int reversing=0;


double updateWhiteThreshold() {
      take_picture();
      int min = 255;
      int max = 0;    
      for (int i = 0; i < 320; i++) {
              int currentPixel = get_pixel(120, i, 3);

              if (currentPixel > max) {
                      max = currentPixel;
              }
              else if (currentPixel < min) {
                      min = currentPixel;
              }
      }

      whiteThreshold = (max + min) / 2;
return whiteThreshold;
}

double kp = 0.005;
double getPropSignal() {
        count=0;
        int white[320];
        take_picture();
        for (int i = 0; i < 320; i++) {
              white[i] = 0;
              int pixel = get_pixel(120, i, 3);
              if (pixel > whiteThreshold) {
                      white[i] = 1;
                      count++;
              }
              if (i==160 && count>140){
               rightCorner=1;
              }
              if (i==319 && count>140 && rightCorner==false){
              leftCorner=1;
              }
              else if (i==319 && count>300 && rightCorner==true){
              rightCorner=0;
              TIntersect=1;
              }
              else if (i==219 && count<5){
                uTurn=1;
}
      }
      double error = 0;
       for (int i = 0; i < 320; i++) {
              error += (i-160)*white[i];
      }
        printf("Count: %d \n",count);
      return error * kp;
}

 void turn_left(int turn){
	 while (count<90){
		 getPropSignal();
         set_motor(1,0);
         set_motor(2,-30);
}
}
void turn_right(int turn){
	 while (count<90){
		getPropSignal();
         set_motor(1,-30);
         set_motor(2,30);
         sleep1(1,0);
 }
}

void reverse(){
	while(count>10){
		double propSignal =  getPropSignal();
      double leftSpeed = (baseSpeed + propSignal);
      double rightSpeed = (baseSpeed - propSignal);
       set_motor(2, -leftSpeed);
       set_motor(1, -rightSpeed);
	}
	while (count<=10){
         set_motor(2,30 );
         set_motor(1,30 ); //reverses
		reversing=1;
}
	
	}
void quad3 (){
  while (1){
reverse();
 if (TIntersect==1){
    if (reversing==1){
        printf("T Intersection");
        turn_left(100000); //write turn left
        TIntersect=0;
        reversing=0;
}
  }
  
       
  else if (leftCorner==1){
          printf("Left Corner");
          turn_left(100000); //write turn left
          leftCorner=0;
                reversing=0;

        }
  else if (uTurn==1){
        printf("U Turn");
        turn_left(100000);
        turn_left(100000);
        uTurn=0;

        reversing=0;
        }
}
}


int main() {
        init();
        gate1();
        updateWhiteThreshold();
        while(1) {
               double propSignal =  getPropSignal();
               double leftSpeed = baseSpeed + propSignal;
               double rightSpeed = baseSpeed - propSignal;

              // printf("left=%f right=%f\n", leftSpeed, -rightSpeed);
               set_motor(2, -leftSpeed);
               set_motor(1, -rightSpeed);

               if (TIntersect==1){
                   printf("Start of Quadrant 3 \n");
                   quad3();
                   TIntersect=0;
                   }
              }
		  }
	  
       
   



