#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
int pos = 0; // LCD Connections
const byte rows = 4;
const byte cols = 4;

char key[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[rows] = {9, 8, 7, 6};
byte colPins[cols] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(key), rowPins, colPins, rows, cols);
const char* password = "4567";
int currentposition = 0;
int redled = 10;
int greenled = 11;
int invalidcount = 12;

void setup()
{
  //  keypad
  Serial.begin(9600);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  myservo.attach(12); //SERVO ATTACHED//
}
void loop()
{
  mykeypad();
}

void mykeypad() {
  char code = keypad.getKey();
  if (code)
    Serial.print(code);
  if (code != NO_KEY) {
    if (code == password[currentposition]) {
      ++currentposition;
      if (currentposition == 4) {
        digitalWrite(greenled, HIGH);
        unlockdoor();
        currentposition = 0;
        digitalWrite(greenled, LOW);
      }
    }
    else {
      ++invalidcount;
      incorrect();
      currentposition = 0;
    }
  }
}

//Door Open
void unlockdoor()
{
  delay(900);

  for (pos = 90; pos >= 0; pos -= 5) {
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(5); // waits 15ms for the servo to reach the position
  }
  delay(3000);

  for (pos = 0; pos <= 90; pos += 5) { // in steps of 1 degree
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15);
    currentposition = 0;
  }
}

//Wrong Code
void incorrect()
{
  delay(500);
  digitalWrite(redled, HIGH);
  delay(3000);
  digitalWrite(redled, LOW);
}
