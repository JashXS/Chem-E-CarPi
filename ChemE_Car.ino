int LDR_Cont = A0; //analog pin 0
int LDR_Test = A1; //anadlog pin 1
unsigned long time;

int switchstate = 0;
int startswitch = 0;
int runSwitch = 0;
int testSwitch = 0;
int modeSwitch = 0;
int sensorValue = 0;
const int ledPin = 13;
const int relay = 7;
int sensorLow = 1023;
int sensorHigh = 0;
int calibration = 0;
bool done = false;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(relay, OUTPUT); //relay
  pinMode(2, INPUT); //Switch
  pinMode(ledPin, OUTPUT);

}
int Average() {

  int sensorAvg = 1023;
  for (int i = 0; i <= 1000; i++)
  {
    sensorValue = analogRead(A0);
    sensorAvg = (sensorValue + sensorAvg) / 2;
  }
  return sensorAvg;
}

// the loop routine runs over and over again forever:
void loop() {
  while (done==true)
  {
    delay(5);
    if(digitalRead(2) == LOW)
    {
      done = false;
    }
  }
  while (done==false && digitalRead(2) == LOW) {
    digitalWrite(relay, LOW);
    digitalWrite(ledPin, HIGH);
    Serial.println("claibrating");
    calibration = Average();
    Serial.println(calibration);

  }
  while (done==false&&digitalRead(2) == HIGH)
  {
    digitalWrite(relay, HIGH);
    digitalWrite(ledPin, LOW);
    sensorValue = Average();
    Serial.println(sensorValue);
    if ( calibration - 200 > sensorValue)
    {
      digitalWrite(relay, LOW);
      digitalWrite(ledPin, HIGH);
      done = true;
      continue;
    }
  }
  delay(1);        // delay in between reads for stability
}
