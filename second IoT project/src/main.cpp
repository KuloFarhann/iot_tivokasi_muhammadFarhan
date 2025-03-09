#include <Arduino.h>

// Definisikan pin untuk tombol dan LED
const int button1Pin = 32;  // Tombol 1
const int button2Pin = 35;  // Tombol 2
const int button3Pin = 34;  // Tombol 3

const int led1Pin = 21;     // LED merah
const int led2Pin = 22;     // LED kuning
const int led3Pin = 23;     // LED hijau

// Variabel untuk debouncing
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
}

void loop() {
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);

  if (millis()-lastDebounceTime > debounceDelay) {
    if (button1State == LOW) {
      lastDebounceTime = millis();
      for (int i=0;i<5;i++) {
        digitalWrite(led1Pin, HIGH);
        delay(500);
        digitalWrite(led1Pin, LOW);
        delay(500);
      }
    }

    if (button2State == LOW) {
      lastDebounceTime = millis();
      for (int i=0;i<3;i++) {
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led3Pin, LOW);
        delay(500);
      }

      digitalWrite(led1Pin, LOW);
      digitalWrite(led3Pin, LOW);
    }

    if (button3State==LOW) {
      lastDebounceTime=millis();
      for (int i=0;i<5;i++) {
        lastDebounceTime=millis();
        for(int i=0;i<5;i++) {
          digitalWrite(led1Pin, HIGH);
          digitalWrite(led2Pin, LOW);
          digitalWrite(led3Pin, LOW);

          delay(500);

          digitalWrite(led1Pin, LOW);
          digitalWrite(led2Pin, HIGH);
          delay(500);

          digitalWrite(led2Pin, LOW);   
          digitalWrite(led3Pin, HIGH);  
          delay(500);                   

          digitalWrite(led3Pin, LOW);

        }
      }
    }
  }
}