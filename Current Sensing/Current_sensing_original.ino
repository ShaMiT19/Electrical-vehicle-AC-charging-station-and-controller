#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

const int currentPin = A0;
const int temp_sensor = A1;
const int residual_sensor = A2;


int sensitivity = 66;
int adcValue = 0;
int offsetVoltage = 2500;
double adcVoltage = 0;
double currentValue = 0;


byte degree[8] = {0b00011, 0b00011, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000};


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16, 2);
lcd.print(" Current Sensor ");
lcd.setCursor(0,1);
lcd.print("  with Arduino  ");

//temperature
lcd.createChar(1, degree);
delay(2000);

// residual current


}

void loop() {
  // put your main code here, to run repeatedly:
  
  adcValue = analogRead(currentPin);
  adcVoltage = (adcValue / 1024.0) * 5000;
  currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
  
  lcd.clear();
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("V in mV =       ");
  lcd.setCursor(10,0);
  lcd.print(adcVoltage,1);

  delay(2000);

//Current Value
if (currentValue <= 2)
  {
    lcd.setCursor(0,0);
    lcd.print("Current =       ");
    lcd.setCursor(10,0);
    lcd.print(currentValue,2);
    lcd.setCursor(14,0);
    lcd.print("A");
    delay(2500);
  }
else
{
  lcd.setCursor(0,0);
  lcd.print("    Fault    ");
  //lcd.setCursor(10,0);
  delay(1000);
  }


// temperature
lcd.setCursor(0,1);
float reading = analogRead(temp_sensor);
float temperature = reading *(5.0/1023.0)*100;
delay(10);

if (temperature <= 75.0)
{
lcd.clear();
lcd.setCursor(2,0);
lcd.print("Temperature");
//Serial.println(temperature);
lcd.setCursor(4,1);
lcd.print(temperature);
lcd.write(1);
delay(1000);  
}
else 
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(" Temp Fault  ");
  lcd.write(1);
  delay(500);
  }

// Residual Current

lcd.setCursor(0,1);
float resi_reading = analogRead(residual_sensor);
float resi_current = (resi_reading / 1024.0) * 500 ;
delay(10);
lcd.setCursor(0,0);
lcd.print("resi_current =     ");
lcd.setCursor(12,0);
lcd.print(resi_current,1);
delay(500);

if (resi_current <= 30.0)
{
lcd.clear();
lcd.setCursor(2,0);
lcd.print("Residual Current");
//Serial.println(resi_current);
lcd.setCursor(4,1);
//lcd.print(resi_current,2);
delay(1000);  
}

else 
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("  Fault  ");
  
  delay(1000);
  
  }

}
