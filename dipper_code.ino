#include <elapsedMillis.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "utility/Adafruit_MS_PWMServoDriver.h"


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *xStepper = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *yStepper = AFMS.getStepper(200, 2);
//Settingsdefault



//////////////////////////

//elapsedMillis timeElapsed;

int i = 0;
int SX = 7;
int SY = 6;
int xCount = 0;
int yCount = 0;
int l ; // number of layers in the film
int xval = digitalRead(SX);
int yval = 1;
int p = 900;  // time delay for dipping in polymers in milliseconds
int w = 900;
int calCount = 0;
char ch = '0' ;
char a = '0';
char cat = '0';
char washcat = '0';
char wwashcat = '0';
char an = '0';
char washan = '0';
char wwashan = '0';
int catpos = 0;
int washcatpos = 0;
int wwashcatpos = 0;
int anpos = 0;
int washanpos = 0;
int wwashanpos = 0;

int A = 2651;  //column A
int B = 3406;  //column B
int C = 4161;  //column C
int D = 4916;  //column D
int E = 5671;  //column E
int F = 6426;  //column F
int ydip = 400;  // lowest dip point
int ytrans = 3100; // must be above the plate
int xorig = 400; //set the origin pount for the x motor
int yorig = 3100; // set the origin point for the y motor
int yagit = ydip + 50;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMS.begin();

  xStepper->setSpeed(150);  // 100 rpm   
  yStepper->setSpeed(150);  // 100 rpm
  
  pinMode(SX,INPUT);
  pinMode(SY, INPUT);
  
}

void loop() {

if (Serial.available() > 0) {
    ch = Serial.read();
    Serial.println("start loop");

    if(ch == 'x') {                          // X motor calibration
     Serial.println("x");
      xval = digitalRead(SX);
      
      while(xval == 1){
        xStepper->step(10, FORWARD, DOUBLE);
        xval = digitalRead(SX);
        Serial.println(xval);
      }
      
        xStepper->step(1, BACKWARD, DOUBLE);
        Serial.println("x=0");
        xCount = 1;
        ch== '0';
      }
    

    if (ch == 'y') {                          // Y motor calibration
      Serial.println("y");
      yval = digitalRead(SY);
     while(yval == 1){
      yStepper->step(10, FORWARD, DOUBLE);
      yval = digitalRead(SY);
      Serial.println(yval);
     } 


     yStepper->step(50, BACKWARD, DOUBLE);
       Serial.println("y=0");
       yCount = 50;
       Serial.println(yCount);
       ch =='0';
     }
    
    
      if (ch == 'h'){                  //bring motors to origin point
      Serial.println("...");
      
      while(yCount < yorig) {
        yStepper->step(10, BACKWARD, DOUBLE);
        yCount = yCount + 10;
        
      }
      while(yCount > yorig){
        yStepper->step(1, FORWARD, DOUBLE);
        yCount = yCount - 1;
      }
      
        while(xCount > xorig){
           xStepper->step(1, FORWARD, DOUBLE);
           xCount = xCount - 1;
           Serial.println("y origin found");
         }
        while(xCount< xorig){
           xStepper->step(10, BACKWARD, DOUBLE);
           xCount = xCount + 10;
         }
        if (xCount == xorig && yCount == yorig) {
      //  yStepper->step(10, BACKWARD, DOUBLE);
       // yCount = yCount + 10;
        Serial.println("Origin"); 
        ch = '0' ;
      }
    }

    if(ch == 'q'){
      Serial.println(xCount);
     
    }
    if (ch == 'e'){
      Serial.println(yCount);
     // ch = Serial.readString();
    }
    if (ch == 'w') {
      yStepper->step(200, BACKWARD, DOUBLE);
        yCount = yCount + 200;
        Serial.print("Y Position = ");
        Serial.println(yCount);
    }
    if(ch == 'z') {
      yStepper->step(50, FORWARD, DOUBLE);
        yCount = yCount - 50;
        Serial.print("Y Position = ");
        Serial.println(yCount);
      } 
    if(ch == 'a') {
      xStepper->step(50, FORWARD, DOUBLE);
        xCount = xCount - 50;
        Serial.print("X Position = ");
        Serial.println(xCount);
      }
    if(ch == 's') {
      xStepper->step(100, BACKWARD, DOUBLE);
        xCount = xCount + 150;
        Serial.print("X Position = ");
        Serial.println(xCount);
      }  

    if(ch == 'r'){                         // Set the recipe for dipping
      Serial.println("Layers?");
        l = Serial.parseInt();
         while(l == 0){
             l = Serial.parseInt();
           }
             Serial.print("#L: ");
             Serial.println(l);
             
//      Serial.println("PDip?");
//         p = Serial.parseInt();
//          while(p == 0){
//          p =  Serial.parseInt();
//          } 
//          Serial.print("T: ");
//          Serial.println(p);
//        // p == (Serial.read()*60000);  // sets delay for polymer dip and converts minutes to milliseconds
//      
//      Serial.println("PWash?");
//          w = Serial.parseInt();
//          while(w == 0){
//           w = Serial.parseInt();
//          } 
//          Serial.print("T: ");
//          Serial.println(w);
//        //  w == (Serial.read()*60000);  // sets delay for wash dipping steps
//     
//      Serial.println("Ag?");
//         a = Serial.read();
//          while(a != 'Y' && a!= 'N'){
//           a = Serial.read();
//          } 
//          Serial.println(a);
         // Yes or No output of agitation
         Serial.print("Positions");
      Serial.println("P1");
         cat = Serial.read();
          while(cat != 'A' && cat != 'B'){
           cat = Serial.read();
          } 
          Serial.println(cat);
  
      Serial.println("W1");
          washcat = Serial.read();
          while(washcat != 'B' && washcat != 'C'){
             washcat = Serial.read();
          } 
          Serial.println(washcat);
      Serial.println("W2");
          wwashcat = Serial.read();
          while(wwashcat != 'C' && wwashcat != 'D'){
             wwashcat = Serial.read();
          } 
          Serial.println(wwashcat);
       
      Serial.println("P2");
          an = Serial.read();
          while(an != 'D' && an != 'E'){
            an = Serial.read();
          } 
          Serial.println(an);
        //  an == Serial.read();
      Serial.println("W3");
          washan = Serial.read();
          while(washan != 'E' && washan != 'F'){
             washan = Serial.read();
          } 
          Serial.println(washan);
       Serial.println("W4");
          wwashan = Serial.read();
          while(wwashan != 'E' && wwashan != 'F'){
             wwashan = Serial.read();
          } 
          Serial.println(wwashan);
         // washan = Serial.read();  
         Serial.print("set");   
    }
    // POSITIONS ////////////////////////////
if(cat == 'A'){
      catpos = A;
    }
if(cat == 'B'){
      catpos = B;
    }
if(washcat == 'B'){
      washcatpos = B;
    }
if(washcat == 'C'){
      washcatpos = C;
    }
if(wwashcat == 'C'){
      wwashcatpos = C;
    }
if(wwashcat == 'D'){
      wwashcatpos = D;
    }
if(an == 'D'){
      anpos = D;
    }
if(an == 'E'){
      anpos = E;  
    }
if(an == 'D'){
      anpos = D;
    }   
if(washan == 'E'){
      washanpos = E;
    }   
if(washan == 'F'){
      washanpos = F;
    }   
if(wwashan == 'E'){
      wwashanpos = E;
    }   
if(wwashan == 'F'){
      wwashanpos = F;

    if(ch == 'g'){                           //Running the recipe
         for(i = 0; i < l; i++){

          // POLYMER DIP 1
          Serial.print("DIP: ");
          Serial.println(i);
          
           
           while(yCount != ytrans){           // bring dipper above plate
           if(yCount < ytrans){
              yStepper->step(10, BACKWARD, DOUBLE);
              yCount = yCount + 10;
          }
           if(yCount >ytrans){
              yStepper->step(1, FORWARD, DOUBLE);
              yCount = yCount - 1;   
          }
         }
           
           while(xCount != catpos){ // move to position for polymer 1
         
            if(xCount < catpos){                           // moves x first then y
              xStepper->step(10, BACKWARD, DOUBLE);
              xCount = xCount + 10;
            }
            if(xCount > catpos){
              xStepper->step(1, FORWARD, DOUBLE);
              xCount = xCount - 1;
            }
           }
           
           yval = digitalRead(SY);
           while(yval == 1){
             yStepper->step(10, FORWARD, DOUBLE);
             yval = digitalRead(SY);
           }
           yStepper->step(5, BACKWARD, DOUBLE);
           Serial.println("y=0");
           yCount = 5;
              
           /*while(yCount != ydip){
              if(yCount > ydip){
                  yStepper->step(10, FORWARD, DOUBLE);
                  yCount = yCount - 10;
              }
              if(yCount < ydip){
                  yStepper->step(1, BACKWARD, DOUBLE);
                 yCount = yCount + 1;   
              }
           */
           
      
         delay(900000);            //polymer dip time
       
         while(yCount != ytrans){           // removal from polymer solution 1 in the y direction
           if(yCount < ytrans){
              yStepper->step(10, BACKWARD, DOUBLE);
              yCount = yCount + 10;
          }
           if(yCount >ytrans){
              yStepper->step(1, FORWARD, DOUBLE);
              yCount = yCount - 1;   
          }
         }
     
         //WASH DIP 1
         
         while(xCount != washcatpos){  // move to position for polymer 1
            if(xCount < washcatpos){                           // moves x first then y
              xStepper->step(10, BACKWARD, DOUBLE);
              xCount = xCount + 10;
            }
            if(xCount > washcatpos){
              xStepper->step(1, FORWARD, DOUBLE);
              xCount = xCount - 1;
            }     
         }  
         yval = digitalRead(SY);                        //down until y button pushed
           while(yval == 1){
             yStepper->step(10, FORWARD, DOUBLE);
             yval = digitalRead(SY);
           }
           yStepper->step(5, BACKWARD, DOUBLE);
           Serial.println("y=0");
           yCount = 5;
           
          /* while(yCount != ydip){
              if(yCount > ydip){
                  yStepper->step(10, FORWARD, DOUBLE);
                  yCount = yCount - 10;
              }
              if(yCount < ydip){
                  yStepper->step(1, BACKWARD, DOUBLE);
                 yCount = yCount + 1;   
              }
            
           }*/
           
//         if(a == 'Y'){      // wash dip agitation
//         // timeElapsed == 0;
//          while(timeElapsed < w){
//                  yStepper->step(yagit, FORWARD, DOUBLE);
//                  yCount = yCount + yagit;
//                  delay(500);
//                  
//                  yStepper->step(yagit, BACKWARD, DOUBLE);
//                  yCount = yCount - yagit; 
//                  delay(500);
//              }
//          }
//         else{
          delay(120000); // wash dip time
         //}
          while(yCount != ytrans){           // removal from polymer solution 1 in the y direction
          if(yCount < ytrans){
              yStepper->step(10, BACKWARD, DOUBLE);
              yCount = yCount + 10;
          }
           if(yCount >ytrans){
              yStepper->step(1, FORWARD, DOUBLE);
              yCount = yCount - 1;   
          }
         }

         //WASH DIP 2
         
         while(xCount != wwashcatpos){  // move to position for polymer 1
            if(xCount < wwashcatpos){                           // moves x first then y
              xStepper->step(10, BACKWARD, DOUBLE);
              xCount = xCount + 10;
            }
            if(xCount > wwashcatpos){
              xStepper->step(1, FORWARD, DOUBLE);
              xCount = xCount - 1;
            }     
         }  
         yval = digitalRead(SY);                       //down until y button pushed
           while(yval == 1){
             yStepper->step(10, FORWARD, DOUBLE);
             yval = digitalRead(SY);
           }
           yStepper->step(5, BACKWARD, DOUBLE);
           Serial.println("y=0");
           yCount = 5;
           
          /* while(yCount != ydip){
              if(yCount > ydip){
                  yStepper->step(10, FORWARD, DOUBLE);
                  yCount = yCount - 10;
              }
              if(yCount < ydip){
                  yStepper->step(1, BACKWARD, DOUBLE);
                 yCount = yCount + 1;   
              }
            
           }*/
           
//         if(a == 'Y'){      // wash dip agitation
//         // timeElapsed == 0;
//          while(timeElapsed < w){
//                  yStepper->step(yagit, FORWARD, DOUBLE);
//                  yCount = yCount + yagit;
//                  delay(500);
//                  
//                  yStepper->step(yagit, BACKWARD, DOUBLE);
//                  yCount = yCount - yagit; 
//                  delay(500);
//              }
//          }
//         else{
          delay(120000); // wash dip time
         //}
          while(yCount != ytrans){           // removal from polymer solution 1 in the y direction
          if(yCount < ytrans){
              yStepper->step(10, BACKWARD, DOUBLE);
              yCount = yCount + 10;
          }
           if(yCount >ytrans){
              yStepper->step(1, FORWARD, DOUBLE);
              yCount = yCount - 1;   
          }
         }
         
         // POLYMER DIP 2

        while(xCount != anpos ){  // move to position for polymer 1
            if(xCount < anpos){                           // moves x first then y
              xStepper->step(10, BACKWARD, DOUBLE);
              xCount = xCount + 10;
            }
            if(xCount > anpos){
              xStepper->step(1, FORWARD, DOUBLE);
              xCount = xCount - 1;
            }
        }
          yval = digitalRead(SY);                       //down until y button pushed
           while(yval == 1){
             yStepper->step(10, FORWARD, DOUBLE);
             yval = digitalRead(SY);
           }
           yStepper->step(5, BACKWARD, DOUBLE);
           Serial.println("y=0");
           yCount = 5;
           
           /*while(yCount != ydip){
              if(yCount > ydip){
                  yStepper->step(10, FORWARD, DOUBLE);
                  yCount = yCount - 10;
              }
              
              if(yCount < ydip){
                  yStepper->step(1, BACKWARD, DOUBLE);
                 yCount = yCount + 1;   
              }
            }*/
           
         delay(900000);                              //polymer dip time
         while(yCount != ytrans){           // removal from polymer solution 1 in the y direction
          if(yCount < ytrans){
              yStepper->step(10, BACKWARD, DOUBLE);
              yCount = yCount + 10;
          }
           if(yCount >ytrans){
              yStepper->step(1, FORWARD, DOUBLE);
              yCount = yCount - 1;   
          }
         }
     
         //WASH DIP 3
         
         while(xCount != washanpos){  // move to position for polymer 1
            if(xCount < washanpos){                           // moves x first then y
              xStepper->step(10, BACKWARD, DOUBLE);
              xCount = xCount + 10;
            }
            if(xCount > washanpos){
              xStepper->step(1, FORWARD, DOUBLE);
              xCount = xCount - 1;
            }
         }

         yval = digitalRead(SY);                       //down until y button pushed
           while(yval == 1){
             yStepper->step(10, FORWARD, DOUBLE);
             yval = digitalRead(SY);
           }
           yStepper->step(5, BACKWARD, DOUBLE);
           Serial.println("y=0");
           yCount = 5;
           
        /* while(yCount != ydip){
              if(yCount > ydip){
                  yStepper->step(10, FORWARD, DOUBLE);
                  yCount = yCount - 10;
              }
             
              if(yCount < ydip){
                  yStepper->step(1, BACKWARD, DOUBLE);
                 yCount = yCount + 1;   
              }
           }*/
           
//         if(agit == "Y"){      // wash dip agitation
//          timeElapsed == 0;
//          while(timeElapsed < w){
//                  yStepper->step(yagit, FORWARD, DOUBLE);
//                  yCount = yCount + yagit;
//                  delay(500);
//                  
//                  yStepper->step(yagit, BACKWARD, DOUBLE);
//                  yCount = yCount - yagit; 
//                  delay(500);
//              }
//          }
//         else{
          delay(120000); // wash dip time
        // }
          while(yCount != ytrans){           // removal from polymer solution 1 in the y direction
          if(yCount < ytrans){
              yStepper->step(10, BACKWARD, DOUBLE);
              yCount = yCount + 10;
          }
           if(yCount >ytrans){
              yStepper->step(1, FORWARD, DOUBLE);
              yCount = yCount - 1;   
          }
         }

         // WASHDIP 4

         
 while(xCount != wwashanpos){  // move to position for polymer 1
            if(xCount < wwashanpos){                           // moves x first then y
              xStepper->step(10, BACKWARD, DOUBLE);
              xCount = xCount + 10;
            }
            if(xCount > wwashanpos){
              xStepper->step(1, FORWARD, DOUBLE);
              xCount = xCount - 1;
            }
         }
         yval = digitalRead(SY);                       //down until y button pushed
           while(yval == 1){
             yStepper->step(10, FORWARD, DOUBLE);
             yval = digitalRead(SY);
           }
           yStepper->step(5, BACKWARD, DOUBLE);
           Serial.println("y=0");
           yCount = 5;
           
         /*while(yCount != ydip){
              if(yCount > ydip){
                  yStepper->step(10, FORWARD, DOUBLE);
                  yCount = yCount - 10;
              }
             
              if(yCount < ydip){
                  yStepper->step(1, BACKWARD, DOUBLE);
                 yCount = yCount + 1;   
              }
           }*/
           
//         if(agit == "Y"){      // wash dip agitation
//          timeElapsed == 0;
//          while(timeElapsed < w){
//                  yStepper->step(yagit, FORWARD, DOUBLE);
//                  yCount = yCount + yagit;
//                  delay(500);
//                  
//                  yStepper->step(yagit, BACKWARD, DOUBLE);
//                  yCount = yCount - yagit; 
//                  delay(500);
//              }
//          }
//         else{
          delay(120000); // wash dip time
        // }
          while(yCount != ytrans){            // removal from polymer solution 1 in the y direction
          if(yCount < ytrans){
              yStepper->step(10, BACKWARD, DOUBLE);
              yCount = yCount + 10;
          }
           if(yCount >ytrans){
              yStepper->step(1, FORWARD, DOUBLE);
              yCount = yCount - 1;   
          }
         }



  xval = digitalRead(SX);
      while(xval== 1){
        xStepper->step(10, FORWARD, DOUBLE);
        xval = digitalRead(SX);
      }
     
        xStepper->step(1, BACKWARD, DOUBLE);
        Serial.println("Found X Zero Point");
        xCount = 1;
     
     
         yval = digitalRead(SY);
        while(yval == 1){
          yStepper->step(10, FORWARD, DOUBLE);
          yval = digitalRead(SY);
        }
       
       yStepper->step(50, BACKWARD, DOUBLE);
       yCount = 50;
       Serial.println("calibrated");
      
    
 
 Serial.print("Layers Completed: ");
 Serial.println(i+1);
        
  } 
}     
}
}}

  
