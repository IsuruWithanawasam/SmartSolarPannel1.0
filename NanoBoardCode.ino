#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <MapFloat.h>
LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


float inVolt;
float volt_val;
float I;

void setup()
{
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();

  lcd.setCursor(4, 0);         
  lcd.print("WELCOME");       
  lcd.setCursor(1, 1);         
  lcd.print("SmartSolar 1.0");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);         
  lcd.print("M.W.I. CHANILKA");       
  lcd.setCursor(0, 1);         
  lcd.print("S14312");
  delay(2000);
  lcd.clear(); 
}

void loop()
{
  lcd.clear();
  inVolt=analogRead(A0);
  volt_val=2*mapFloat(inVolt, 0.0, 1023.0, 0.0, 5.0);
  I=volt_val/(2000);
  Serial.println(volt_val);

  lcd.setCursor(0, 0); 
  lcd.print("Voltage: ");

  if(volt_val>=1){
    V_out();
  }
  else{
    mV_out();
  }

  lcd.setCursor(0, 1); 
  lcd.print("Current: ");

  if(I>=1){
    A_out();
  }
  else{
    mA_out();
  }
  
  delay(1000);
} 

void V_out(){

  lcd.setCursor(9, 0);
  lcd.print(volt_val);
  lcd.setCursor(14, 0);
  lcd.print("V");
}
void mV_out(){
  volt_val=1000*volt_val;
  lcd.setCursor(9, 0);
  lcd.print(volt_val);
  lcd.setCursor(14, 0);
  lcd.print("mV");
}
void A_out(){
  lcd.setCursor(9, 1);
  lcd.print(I);
  lcd.setCursor(14, 1);
  lcd.print("A");
}
void mA_out(){
  I=I*1000;
  lcd.setCursor(9, 1);
  lcd.print(I);
  lcd.setCursor(14, 1);
  lcd.print("mA");
}
