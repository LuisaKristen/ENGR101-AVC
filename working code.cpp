#include <stdio.h>
#include "E101.h"

double whiteThreshold;

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
        int white[320];
        take_picture();        
        for (int i = 0; i < 320; i++) {                                                                                                                                                                                                                                        
              white[i] = 0;                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                               
              int pixel = get_pixel(120, i, 3);                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                               
              if (pixel > whiteThreshold) {                                                                                                                                                                                                                                    
                      white[i] = 1;                                                                                                                                                                                                                                            
              }                                                                                                                                                                                                                                                                
      }                                                                                                                                                                                                                                                                        
      double error = 0;                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                               
      for (int i = 0; i < 320; i++) {                                                                                                                                                                                                                                          
              error += (i-160)*white[i];                                                                                                                                                                                                                                       
      }                                                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                               
      return error * kp;                                                                                                                                                                                                                                                       
}                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                               
int baseSpeed = 40;                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                               
int main() {                                                                                                                                                                                                                                                                   
        init();                                                                                                                                                                                                                                                                
        updateWhiteThreshold();                                                                                                                                                                                                                                                
       while(1) {
               double propSignal =  getPropSignal();
               double leftSpeed = baseSpeed + propSignal;
               double rightSpeed = baseSpeed - propSignal;

                printf("left=%f right=%f\n", leftSpeed, -rightSpeed);
               set_motor(2, -leftSpeed);
               set_motor(1, -rightSpeed); 
       }
}

