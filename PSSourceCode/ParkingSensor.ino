#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 5;
const int echoPin = 18;
const int ledGreen = 13;
const int ledYellow = 12;
const int ledRed = 14;
const int buzzer = 27;
const int buttonPin = 4;

#define SOUND_SPEED 0.034
#define MAX_DIST 50.0

float smoothDistance = 50.0;
float filterCoeff = 0.15;  

bool isMuted = false;
bool lastButtonState = HIGH;

void setup() {
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledRed, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for (;;);
     
  }
    display.clearDisplay();
    display.setTextColor(WHITE);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
    if (currentButtonState == LOW && lastButtonState == HIGH) {
        isMuted = !isMuted;
        delay(50);
     
  }
    lastButtonState = currentButtonState;

  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
  long duration = pulseIn(echoPin, HIGH, 30000);
    float currentDist = duration * SOUND_SPEED / 2.0;

  if (currentDist > 0 && currentDist < 200) {
    if (abs(currentDist - smoothDistance) > 15) {
            smoothDistance = currentDist;
         
    }
    else {
      smoothDistance = smoothDistance + (currentDist - smoothDistance) * filterCoeff;
         
    }
     
  }

    int displayDist = (int)(smoothDistance + 0.5);

  digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);

    if (displayDist > 30) {
        digitalWrite(ledGreen, HIGH);
        noTone(buzzer);
     
  }
    else if (displayDist <= 30 && displayDist > 19) {
        digitalWrite(ledYellow, HIGH);
        if (!isMuted) {
            tone(buzzer, 800);
            delay(40); 
            noTone(buzzer);
         
    }
        int gap = map(displayDist, 19, 30, 80, 250);
        delay(gap);
     
  }
    else if (displayDist <= 19 && displayDist > 6) {
        digitalWrite(ledRed, HIGH);
        if (!isMuted) {
            tone(buzzer, 1300);
            delay(30);
            noTone(buzzer);
         
    }
        int gap = map(displayDist, 6, 19, 10, 80);
        delay(gap);
     
  }
    else if (displayDist <= 6 && displayDist > 0) {
        digitalWrite(ledRed, HIGH);
        if (!isMuted) tone(buzzer, 2500);
        else noTone(buzzer);
     
  }


  display.clearDisplay();
    
  float barWidth = map(constrain(smoothDistance, 0, MAX_DIST), 0, MAX_DIST, 128, 0);
    display.drawRect(0, 0, 128, 12, WHITE);
       
  display.fillRect(0, 0, (int)barWidth, 12, WHITE);

    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print("Dystans:");
    display.setCursor(20, 42);
    display.print(displayDist);
    display.print(" cm");

    display.setTextSize(1);
    display.setCursor(0, 56);
    if (isMuted) display.print("MUTE: ON");
    else display.print("MUTE: OFF");

    if (displayDist < 10) {
        display.setTextSize(2);
        display.setCursor(85, 42);
        display.print("!!!");
     
  }

    display.display();
}
