#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int cpuTemp  = 0;
int cpuUsage = 0;
int gpuTemp  = 0;
int gpuUsage = 0;
String staticData = "";

int prevCpuTemp = -1;
int prevCpuUsage = -1;
int prevGpuTemp = -1;
int prevGpuUsage = -1;

void setup() {
  Serial.begin(112500);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello World");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CPU:");
  lcd.setCursor(0,1);
  lcd.print("GPU:");
}

void loop() {
  if (Serial.available() > 0){
    staticData = Serial.readString();
    cpuTemp = staticData.substring(1,4).toInt();
    cpuUsage = staticData.substring(5,8).toInt();
    gpuTemp = staticData.substring(9,12).toInt();
    gpuUsage = staticData.substring(13,16).toInt();
    if (cpuTemp >= 0 && cpuUsage >= 0 && gpuTemp >= 0 && gpuUsage >= 0){
      displayStatic();
    } else {
      displayError(1);
    }
  }
  delay(1);
}

void displayError(int code){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Error TwT");
  lcd.setCursor(0,1);
  switch (code){
    case 1:{
      lcd.print("No Data");
    }
  }
}

void displayStatic(){
  if (cpuTemp != prevCpuTemp) {
    if (prevCpuTemp == 100){
      lcd.setCursor(5,0);
      lcd.print(" ");
    }
    if (cpuTemp < 10){
      lcd.setCursor(5,0);
      lcd.print("  ");
    }
    lcd.setCursor(8-checkNumUnit(cpuTemp),0);
    lcd.print(cpuTemp);
    lcd.print("\xDF");
    lcd.print("C ");
    prevCpuTemp = cpuTemp;
  }
  if (cpuUsage != prevCpuUsage) {
    if (prevCpuUsage == 100){
      lcd.setCursor(11,0);
      lcd.print(" ");
    }
    if (cpuUsage < 10){
      lcd.setCursor(11,0);
      lcd.print("  ");
    }
    lcd.setCursor(14-checkNumUnit(cpuUsage),0);
    lcd.print(cpuUsage);
    lcd.print("%");
    prevCpuUsage = cpuUsage;
  }
  if (gpuTemp != prevGpuTemp) {
    if (prevGpuTemp == 100){
      lcd.setCursor(5,0);
      lcd.print(" ");
    }
    if (gpuTemp < 10){
      lcd.setCursor(5,0);
      lcd.print("  ");
    }
    lcd.setCursor(8-checkNumUnit(gpuTemp),1);
    lcd.print(gpuTemp);
    lcd.print("\xDF");
    lcd.print("C ");
    prevGpuTemp = gpuTemp;
  }
  if (gpuUsage != prevGpuUsage) {
    if (prevGpuUsage == 100){
      lcd.setCursor(11,1);
      lcd.print(" ");
    }
    if (gpuUsage < 10){
      lcd.setCursor(11,1);
      lcd.print("  ");
    }
    lcd.setCursor(14-checkNumUnit(gpuUsage),1);
    lcd.print(gpuUsage);
    lcd.print("%");
    prevGpuUsage = gpuUsage;
  }
}

int checkNumUnit(int num){
  int temp = num;
  int numUnit = 1;
  while(temp >= 10){
    temp /= 10;
    numUnit++;
  }
  return numUnit;
}
