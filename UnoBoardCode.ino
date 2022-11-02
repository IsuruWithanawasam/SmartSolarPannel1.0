
#include <Servo.h>
//defining Servos
Servo servoH;
int h = 90;
int hLimHigh = 165;
int hLimLow = 15;

Servo servoV; 
int v = 90; 
int vLimHigh = 180;
int vLimLow = 0;

int minD=50;
int tbD;
int lrD;

int avgtop;
int avgbot;
int avgleft;
int avgright;

int axis_delay;



 void setup () 
 {
  Serial.begin(9600);
  servoH.attach(9);
  servoH.write(90);
  servoV.attach(10);
  servoV.write(90);
  delay(1000);
 }

void loop()
{
  h = servoH.read();
  v = servoV.read();
  
  int topl = analogRead(A0);
  int topr = analogRead(A2);
  int botl = analogRead(A1);
  int botr = analogRead(A3);

  int vr1= analogRead(A4);
  int vr2= analogRead(A5);

//  Serial.print(topl);
//  Serial.print(',');
//  Serial.print(topr);
//  Serial.print(',');
//  Serial.print(botl);
//  Serial.print(',');
//  Serial.print(botr);
//  Serial.println(' ');
  

  axis_delay=map(vr1,0,1023,50,5);//speed 20
  minD=map(vr2,0,1023,200,1);//sensitivity 50
 
  avgtop = (topl + topr) / 2; //average of top LDRs
  avgbot = (botl + botr) / 2; //average of bottom LDRs
  avgleft = (topl + botl) / 2; //average of left LDRs
  avgright = (topr + botr) / 2; //average of right LDRs
  tbD=abs(avgtop-avgbot);
  lrD=abs(avgleft-avgright);
  
  horiax();
  /////////////////////////////
  if(h>90){
    vertiax1();
  }
  else{
    vertiax2();
  }
  

}
void horiax(){
 if(tbD>minD){
  if (avgtop < avgbot)
  {
    servoH.write(h+1);
    if (h > hLimHigh){
     h = hLimHigh;
    }
    delay(axis_delay);
  }
  else if (avgbot < avgtop)
  {
   servoH.write(h-1);
    if (h < hLimLow){
      h = hLimLow;
     }
    delay(axis_delay);
  }
  else 
  {
    servoH.write(h);
  }
  } 
}

void vertiax1(){
  if(lrD>minD){
  if (avgleft > avgright)
  {
    servoV.write(v-1);
    if (v < vLimLow)
  {
    v = vLimLow;
  }
    delay(axis_delay);
  }
  else if (avgright > avgleft)
  {
     servoV.write(v+1);
    if (v > vLimHigh) 
     { 
      v = vLimHigh;
     }
    delay(axis_delay);
  }
  else 
  {
    servoV.write(v);
  }
 }
}

void vertiax2(){
  if(lrD>minD){
  if (avgleft > avgright)
  {
    servoV.write(v+1);
    if (v > vLimHigh) 
     { 
      v = vLimHigh;
     }
    delay(axis_delay);
  }
  else if (avgright > avgleft)
  {
    servoV.write(v-1);
    if (v < vLimLow)
  {
    v = vLimLow;
  }
     
    delay(axis_delay);
  }
  else 
  {
    servoV.write(v);
  }
 }
}
