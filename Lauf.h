#include <Arduino.h>

#define period 10 //time between each servo adjustment in Microseconds


extern Servo ServoTable[6];
int Offsets[6] = {0, 0, 0, 0, 0, 0};
//extern int Offsets[6];

float RHP = 90;
float RKP = 90;
float RAP = 90;

float LHP = 90;
float LKP = 90;
float LAP = 90;

boolean stepN;
int last_angle = 90;
int Speed = 400;

void GroupMove(int p1, int p2, int p3, int p4, int p5, int p6, int Speed)
{
                            Serial.print("Sag_Kalca: ");
              Serial.println(p1);
                            Serial.print("Sag_Diz: ");
              Serial.println(p2);
                            Serial.print("Sag_Ayak: ");
              Serial.println(p3);
                            Serial.print("Sol_Kalca: ");
              Serial.println(p4);
                            Serial.print("Sol_Diz: ");
              Serial.println(p5);
                            Serial.print("Sol_Ayak: ");
              Serial.println(p6);
                            Serial.print("Hiz: ");
              Serial.println(Speed);
              Serial.println("----------");
              
  float ticks = Speed / period;
  float RHS = (p1 - RHP) / ticks;
  float RKS = (p2 - RKP) / ticks;
  float RAS = (p3 - RAP) / ticks;
  
  float LHS = (p4 - LHP) / ticks;
  float LKS = (p5 - LKP) / ticks;
  float LAS = (p6 - LAP) / ticks;
  for(int x = 0; x < ticks; x++)
  {
    RHP = RHP + RHS;
    RKP = RKP + RKS;
    RAP = RAP + RAS;
    
    LHP = LHP + RHS;
    LKP = LKP + LKS;
    LAP = LAP + LAS;
    ServoTable[0].write(RHP + Offsets[0]);
    ServoTable[1].write(RKP + Offsets[1]);
    ServoTable[2].write(RAP + Offsets[2]);//+5
   
    
    ServoTable[3].write(LHP + Offsets[3]);
    ServoTable[4].write(LKP + Offsets[4]);
    ServoTable[5].write(LAP + Offsets[5]);//+10
    delay(period);

  }
}

void Walk1(byte angle)
{
  if(stepN)
  {
    angle = 90 + angle ;//SOLA
    GroupMove(last_angle, last_angle, 55, last_angle, last_angle, 75, Speed);
    GroupMove(angle, angle, 70, angle, angle, 75, Speed);
    GroupMove(angle, angle, 90, angle, angle, 90, Speed);
    stepN = !stepN;
  }
  else
  {
    angle = 90 - angle  ;//SAGA
    GroupMove(last_angle, last_angle, 108, last_angle, last_angle, 125, Speed);
    GroupMove(angle, angle, 105, angle, angle, 115, Speed);
    GroupMove(angle, angle, 90, angle, angle, 90, Speed);
    stepN = !stepN;
  }
  last_angle = angle;
}


void Walk2(byte angle)
{
  if(stepN)
  {
  
    angle = 90 + angle;//SOLA
    GroupMove(last_angle, last_angle, 70, last_angle, last_angle, 65, Speed);
    GroupMove(angle, angle, 80, angle, angle, 80, Speed);
    GroupMove(angle, angle, 90, angle, angle, 90, Speed/3);
    stepN = !stepN;
  }
  else
  {
    
    angle = 90 - angle;//SAGA

    GroupMove(last_angle, last_angle, 110, last_angle, last_angle, 110, Speed);
    GroupMove(angle, angle, 100, angle, angle, 100, Speed);   
    GroupMove(angle, angle, 90, angle, angle, 90, Speed/3);
    stepN = !stepN;
  }
  last_angle = angle;
}



void Saga_Sola()
{
      delay(1000);
         GroupMove(last_angle, last_angle, 90, last_angle, last_angle, 90, Speed);//sag
      delay(1000);
         GroupMove(last_angle, last_angle, 70, last_angle, last_angle, 65, Speed);//sola egim
      delay(1000);
         GroupMove(last_angle, last_angle, 90, last_angle, last_angle, 90, Speed);//sag
      delay(1000);
         GroupMove(last_angle, last_angle, 110, last_angle, last_angle, 110, Speed);//saga egim

         
  }


void Turn_Left()
{
  GroupMove(55, 55, 75, 55, 55, 75, 500);
  GroupMove(55, 55, 90, 55, 55, 90, 250);
  GroupMove(90, 90, 90, 90, 90, 90, 500);
  GroupMove(90, 90, 75, 90, 90, 55, 450);
  GroupMove(90, 90, 75, 90, 90, 75, 50);

}

void Stop()
{
    GroupMove(90, 90, 90, 90, 90, 90, 500);
}
