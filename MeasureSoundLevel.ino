/*
 * Author: Shuvam Shah
 * Samples audio signals for 50 milliseconds (20Hz) and returns
 * maximum peak to peak voltage difference.
 * Note: `millis()` overflows after approx 50 days.
 */

#define INTERVAL 50
#define INPUTPIN A0
#define LEDPIN 13

int sensorValue, maxValue, minValue, peaktopeak;
float soundLevel;   // measured in decibels

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(INPUTPIN, INPUT); 
  pinMode(LEDPIN, OUTPUT);
  sensorValue = 0;
}

void loop() {
  maxValue = 0;
  minValue = 1024;
  peaktopeak = 0;
  soundLevel = 0.0f;
  long t0 = millis();
  while (millis() - t0 < INTERVAL) {
    if ((sensorValue = analogRead(INPUTPIN)) < 1024) {
      if (sensorValue > maxValue) maxValue = sensorValue;
      if (sensorValue < minValue) minValue = sensorValue;
    }
  }
  
  peaktopeak = abs(maxValue - minValue);
  soundLevel = map(peaktopeak, 20, 900, 49.5, 90);
  if (soundLevel > 75) {
    digitalWrite(LEDPIN, HIGH);
  }
  else {
    digitalWrite(LEDPIN, LOW);
  }
  
  Serial.println(soundLevel);
}
