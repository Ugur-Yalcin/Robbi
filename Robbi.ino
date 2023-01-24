#include <Servo.h>
#include "Laufe.h"

#define RightHipPin 2
#define RightKneePin 3
#define RightAnklePin 8

#define LeftHipPin 5
#define LeftKneePin 6
#define LeftAnklePin 9

//int Offsets[6] = {0, 0, 0, 0, 0, 0};
Servo ServoTable[6];


void setup()
{
  ServoTable[0].attach(RightHipPin);    //sag kalca
  ServoTable[1].attach(RightKneePin);   //sag diz
  ServoTable[2].attach(RightAnklePin);  //sag ayak

  ServoTable[3].attach(LeftHipPin);     //sol kalca
  ServoTable[4].attach(LeftKneePin);    //sol diz
  ServoTable[5].attach(LeftAnklePin);   //sol ayak
  Serial.begin(9600);

}

void loop()
{

if (Serial.available() > 0) {             // Serialden gelen veri geliyorsa
     byte Gelenveri = Serial.read();      // Bu veriyi Gelenveri degiskenine aktar
     switch(Gelenveri)
     {
       case 'x':
       Serial.println("Robot yürüyor!");
       Walk1(20);
       break;
       
       case 'y':
       Serial.println("Robot durdu");// Favorim
       Walk2(30);
       break;

       case 'z':
       Serial.println("Robot durdu");
       Saga_Sola(); 
       break;
       
       default:
       Serial.println("Led 1 kere sinyal veriyor");
       Stop();
       
  Walk1(20);
  //Walk2(20);// Favorim
  //Stop();
  //Saga_Sola();  
  //Turn_Left();
     }
                          }     
}
