
// C++ code
//

#include <LiquidCrystal_I2C.h>

const int tmpPin = A0;
float temperature = 9;

int warningLedPin = 7;
int motorPin1 = 9;
int motorPin2 = 8;
int enablePin = 10;


LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup()
{
  pinMode(warningLedPin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
}

void loop()
{
  
	int sensorValue = analogRead(tmpPin);  
	
  	// formula for conversion of analogue reading to celsius from AutoDESK documentation 
  	int celsius = map(((sensorValue - 20) * 3.04), 0, 1023, -40, 125);

  	lcd.setCursor(0,1);
  	lcd.print("Tmp: ");
  	lcd.print(celsius);
  	lcd.print("C");
  	
  if(celsius > 23 && celsius < 30){
  	analogWrite(enablePin, 128); // Half speed
  	digitalWrite(motorPin1, HIGH);
  	digitalWrite(motorPin2, LOW);
    digitalWrite(warningLedPin, LOW);
  	delay(2000);

  }else if (celsius >= 30){
    analogWrite(enablePin, 255); // Full speed	 
  	digitalWrite(motorPin1, HIGH);
  	digitalWrite(motorPin2, LOW);
    digitalWrite(warningLedPin, HIGH);
  	delay(2000);


  }
  
  delay(1000);
}