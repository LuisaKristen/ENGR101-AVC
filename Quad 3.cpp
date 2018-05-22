#include <stdio.h>
#include "E101.h"

void gate1() {
        char password[24];
        char IP_addr [15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'}; //Nathan's IP
        char send [24] = {'P','l','e','a','s','e'};
        connect_to_server(IP_addr, 1024);
        send_to_server(send);
        receive_from_server(password);
        send_to_server(password);
        sleep1(0,2000000);
}

double whiteThreshold;
int count;
boolean rightCorner=false;
boolean leftCorner=false;
boolean TIntersect=false;

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
              if (i==160 && count>100){
               rightCorner=true;
              }
              if (i==319 && count>100 && rightCorner==false){
              leftCorner=true;
              }
              else if (i==319 && count>100 && rightCorner==true){
              rightCorner=false;
              TIntersect=true;
              }
      }                                                                                                                                                                                                                                                                        
      double error = 0;                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                               
      for (int i = 0; i < 320; i++) {                                                                                                                                                                                                                                          
              error += (i-160)*white[i];                                                                                                                                                                                                                                       
      }                                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                               
      return error * kp;                                                                                                                                                                                                                                                       
}  

int numOfTurns=0;                                                                                                                                                                                                                                                                               

void quad3 (){
  while (count>5){
      double propSignal =  getPropSignal();
      double leftSpeed = (baseSpeed + propSignal)/2;
      double rightSpeed = (baseSpeed - propSignal)/2;

       set_motor(2, -leftSpeed);
       set_motor(1, -rightSpeed); 
  if (TIntersect==true){
        printf("T Intersection");
        numOfTurns++;
        turn_left(); //write turn left
        TIntersect=false;

  }
  else if (rightCorner==true){
          printf("Right Corner");
          turn_right(100000); //write turn left
          rightCorner=false;
          
  }
  else if (leftCorner==true){
          printf("Left Corner");
          turn_left(100000); //write turn left
          leftCorner=false;
  }
}
}
 
 void turn_left(int turn){
	 set_motor(1,30);
  	 set_motor(2,30);
	  sleep1(0,turn/2);}

	 set_motor(1,0);
  	 set_motor(2,-30);	
  	 sleep1(0,turn);
}

 void turn_right(int turn){
 	set_motor(1,30);
  	 set_motor(2,30);
	  sleep1(0,turn/2);}

	 set_motor(1,-30);
  	 set_motor(2,30);	
  	 sleep1(0,turn);
 }
 
int baseSpeed = 40;                                                                                                                                                                                                                                                            
int main() {                                                                                                                                                                                                                                                                   
        init();   
        gate1();
        updateWhiteThreshold();                                                                                                                                                                                                                                                
       	while(1) {
               double propSignal =  getPropSignal();
               double leftSpeed = baseSpeed + propSignal;
               double rightSpeed = baseSpeed - propSignal;

               printf("left=%f right=%f\n", leftSpeed, -rightSpeed);
               set_motor(2, -leftSpeed);
               set_motor(1, -rightSpeed); 
               
               if (TIntersect==true){
                   printf("Start of Quadrant 3");
                   quad3();
                   set_motor(2, -leftSpeed/2);
                   set_motor(1, -rightSpeed/2); 
                   
                   TIntersect=false;
                   rightCorner=false;
                   leftCorner=false;
                   }
                   
              }
               
       }
	
}


