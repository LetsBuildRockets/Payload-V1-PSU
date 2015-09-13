#define statusPin 13

long beepMillis = 0;
long blinkMillis = 0;
long serialMillis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(statusPin, OUTPUT);
  pinMode(9, OUTPUT);
  
  tone(9, 880, 100);
  delay(100);
  tone(9, 1109, 100);
  delay(100);
  tone(9, 1319, 100);
  delay(100);
  tone(9, 1760, 100);
  delay(100);
  
}

void loop() {
  float vbat = getBatteryVoltage();
  if(vbat < 10) {
    digitalWrite(statusPin, HIGH);
    beep();
  } else {
    bip();
  }
  if(millis() - serialMillis > 1000) {
    Serial.println(vbat);
    serialMillis = millis();
  }
  delay(1);
}


float getBatteryVoltage() {
  int z1 = 2200;
  int z2 = 1000;
  float vout = analogRead(0) * (5.0 / 1023.0);
  float vin = vout*((z1+z2)/z2);
  return vin;
}

void bip() {
  if(digitalRead(statusPin) && millis() - blinkMillis > 100) {
      digitalWrite(statusPin, LOW);
      blinkMillis = millis();
  } else if (!digitalRead(statusPin) && millis() - blinkMillis > 3000) {
      digitalWrite(statusPin, HIGH);
      blinkMillis = millis();
  }
}

void beep() {
  if(millis() - beepMillis > 150) {
    tone(9, 4000, 100);
    beepMillis = millis();
  }
}
