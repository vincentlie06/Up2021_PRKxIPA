#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,8,9,10,11);
const int redled[2] = {2,13}, greenled = 3, pinDc[2] = {7,12};
const int buzzer = 4, sensor[2] = {A0,A1}, thresh = 150;

void setup(){
  for (const int pin : redled)pinMode(pin, OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(buzzer,OUTPUT);
  for (const int pin : sensor)pinMode(pin,INPUT);
  for (const int pin : pinDc)pinMode(pin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop()
{
  int read[2] = {analogRead(sensor[0]),analogRead(sensor[1])};
  bool conds[2] = {read[0] > thresh, read[1] > thresh};
  bool var = max(conds[0],conds[1]);
  Serial.print("Baca dari sensor 1: ");
  Serial.print(read[0]);
  Serial.print(" Baca dari sensor 2: ");
  Serial.println(read[1]);
  bool bakar = conds[0]+conds[1] == 2;
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.println(bakar);
  if (bakar){
    tone(buzzer,750);
    lcd.print("KEBAKARAN BESAR");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("EVACUATE");
    for(const int pin : pinDc) digitalWrite(pin,1);
    for(const int pin : redled)digitalWrite(pin, 1);
    digitalWrite(greenled, 0);
  }
  else if(var){
    tone(buzzer,440);
    lcd.print("ALERT");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("API KECIL");
    for(int i=0; i<2; i++){
      digitalWrite(pinDc[i],i);
      digitalWrite(redled[i],i);
    }
    digitalWrite(greenled, 0);
  }
  else{
    noTone(buzzer);
    lcd.print("SAFE");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("ALL CLEAR");
    for(const int pin : pinDc) digitalWrite(pin,0);
    for(const int pin : redled)digitalWrite(pin, 0);
    digitalWrite(greenled, 1);
  }
  delay(500);
}
