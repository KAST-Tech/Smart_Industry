// Library Files
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// LCD Display
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(6, 5, 4, 3, 2, 1); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

//Temperature
#define DHTPIN 11     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

//Motion Sensor
int ledpin1 = 8;// Digital pin n D6
int pir1;
int sensor1 = 10 ;//motion senson1 on D7

//Gas Sensor
const int smoke = A0;
const int exFan = 7; //exFan
const int threshold = 400;//gas sensor

//Vibration sensor
int vibration = A8; //vibration sensor D0
int LedPin3 = 9; //vibration in led D1

//dust sensor
int measurePin = A15;
int ledPower = 52;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup() {

  //Motion
  pinMode(sensor1, INPUT);   // declare sensor as input
  pinMode(ledpin1, OUTPUT);  // declare LED as output

  //gas sensor
  pinMode(smoke, INPUT);
  pinMode(exFan, OUTPUT); //Buzzpin for fire alarm

  //temperature
  dht.begin();

  //Vibration
  pinMode (vibration, INPUT);
  pinMode(LedPin3, OUTPUT);

  //Display
  lcd.begin(16, 2);
  lcd.print("Smart Industry");
//  Serial.begin(9600);/
}

void loop() {
  gasSensor();
  temperature();
  vibration_sensor();
  motionDetected1();
  lcd.clear();
  lcd.println(temp);
}

//Vibration
void vibration_sensor() {
  int vibrationvalue = analogRead(vibration);
//  Serial.println(vibrationvalue);/

  if (vibrationvalue == 0) {
    digitalWrite(LedPin3, HIGH);
//    Serial.println("\n Vibration");/
    delay(1000);
  }

  else {
    digitalWrite(LedPin3, LOW);
    Serial.println("\n No Vibration");
    delay(1000);
  }
  //  delay(500);
}


//temperature
void temperature() {
  delay(1000);
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
//  Serial.print("Humidity: ");
//  Serial.print(hum);
//  Serial.print(" %, Temp: ");
//  Serial.print(temp);
//  Serial.println(" Celsius");
  delay(1000);
}

//Motion Sensor Detection
void motionDetected1() {
  pir1 = digitalRead (sensor1);
  //  Serial.println(pir1);

  if (pir1 == HIGH) {
    digitalWrite(ledpin1, HIGH);
//    Serial.println("\n Motion Detected");/
    // Serial.println(pir1);
    delay(50);
    digitalWrite(ledpin1, LOW);

  }
  else {
    digitalWrite(ledpin1, LOW);
//    Serial.println(" Motion Not Detected");/
    //Serial.println(pir1);
    delay(50);
  }
}

//gas sensor
void gasSensor() {
  int analogValue = analogRead(smoke);

//  Serial.println("\n Gas value = ");/
//  Serial.println(analogValue);/

  if (analogValue > threshold) {
    digitalWrite(exFan, HIGH);
  }
  else if (analogValue == threshold) {
    digitalWrite(exFan, LOW);
    delay(400);
    //digitalWrite(Buzzerpin, LOW);
  }
  else {
    digitalWrite(exFan, LOW);
  }

  //  Serial.println(analogRead(A0));
  delay(500);
}
