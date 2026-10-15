#include <Arduino.h>

#define BOOT_PIN 0
#define LED1_PIN 5
#define LED2_PIN 6
#define BUTTON_PIN 7

#define MODE1_MS 200
#define MODE2_MS 1000
#define POLL_MS 10

enum class LedMode {
  MODE1,
  MODE2
};

LedMode currentMode = LedMode::MODE1;

void readButtons() {
  LedMode newMode = currentMode;

  if (digitalRead(BUTTON_PIN) == LOW) {
    newMode = LedMode::MODE1;
  } else if (digitalRead(BOOT_PIN) == LOW) {
    newMode = LedMode::MODE2;
  }

  if (newMode != currentMode) {
    currentMode = newMode;
    Serial.println(currentMode == LedMode::MODE1 ? "Mode 1" : "Mode 2");
  }
}

void wait(unsigned long ms) {
  for (unsigned long t = 0; t < ms; t += POLL_MS) {
    readButtons();
    delay(POLL_MS);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BOOT_PIN, INPUT_PULLUP);
}

void loop() {
  switch (currentMode) {
    case LedMode::MODE1:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      wait(MODE1_MS);
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      wait(MODE1_MS);
      break;

    case LedMode::MODE2:
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, LOW);
      wait(MODE2_MS);
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, HIGH);
      wait(MODE2_MS);
      break;
  }
}
