#include <Arduino.h>

// Define the pins for RGB LED and buttons

// RGB LED pins
const int LED_RED_PIN = 5;
const int LED_GREEN_PIN = 6;
const int LED_BLUE_PIN = 7;

// Button pins
const int BUTTON_START_STOP_PIN = 11;
const int BUTTON_DIFFICULTY_PIN = 12;

bool roundActive = false;
int difficultyLevel = 0; // 0: Easy, 1: Medium, 2: Hard
unsigned long lastWordTime = 0;
unsigned long wordInterval = 3000; // Default interval (3 seconds for Easy)
unsigned long roundStartTime = 0;
int correctWordCount = 0;

String words[] = {"apple", "banana", "cherry", "date", "elderberry"};
int wordIndex = 0;

void setup() {
  // Set the RGB LED pins as outputs
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  // Set the button pins as inputs with pull-up resistors
  pinMode(BUTTON_START_STOP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DIFFICULTY_PIN, INPUT_PULLUP);

  // Initialize serial communication
  Serial.begin(9600);

  // Set the LED to white in idle state (all colors on)
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
}

void displayDifficulty() {
  // Display the current difficulty level in the serial monitor
  switch (difficultyLevel) {
    case 0:
      Serial.println("Easy mode on!");
      wordInterval = 3000; // 3 seconds
      break;
    case 1:
      Serial.println("Medium mode on!");
      wordInterval = 2000; // 2 seconds
      break;
    case 2:
      Serial.println("Hard mode on!");
      wordInterval = 1000; // 1 second
      break;
  }
}

void countdown() {
  // Countdown with blue LED blinking 3 times
  for (int i = 3; i > 0; i--) {
    Serial.println(i);
    digitalWrite(LED_BLUE_PIN, HIGH);
    delay(500);
    digitalWrite(LED_BLUE_PIN, LOW);
    delay(500);
  }
}

void startRound() {
  roundActive = true;
  correctWordCount = 0;
  wordIndex = random(0, 5);
  roundStartTime = millis();
  lastWordTime = millis();
  Serial.println("Type this word: " + words[wordIndex]);

  // Set LED to green to indicate round started
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_BLUE_PIN, LOW);
}

void endRound() {
  roundActive = false;
  // Set LED to white to indicate idle state
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
  Serial.print("Round ended. Correct words typed: ");
  Serial.println(correctWordCount);
}

void loop() {
  // Check if the difficulty button is pressed and round is not active
  if (digitalRead(BUTTON_DIFFICULTY_PIN) == LOW && !roundActive) {
    delay(300); // Debouncing delay to ensure the button press is registered only once
    difficultyLevel = (difficultyLevel + 1) % 3;
    displayDifficulty();
    while (digitalRead(BUTTON_DIFFICULTY_PIN) == LOW); // Wait until button is released
  }

  // Check if the start button is pressed to start a new round
  if (digitalRead(BUTTON_START_STOP_PIN) == LOW && !roundActive) {
    delay(300); // Debounce delay
    countdown(); // Blink blue LED 3 times
    startRound();
  }

  // During the round
  if (roundActive) {
    // Check if the time limit has passed for the current word
    if (millis() - lastWordTime >= wordInterval) {
      wordIndex = random(0, 5);
      Serial.println("Time's up! New word: " + words[wordIndex]);
      lastWordTime = millis();
      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, HIGH); // Reset to green for new word
    }

    // Check for input from serial
    if (Serial.available() > 0) {
      String userInput = Serial.readStringUntil('\n');
      Serial.flush(); // Flush buffer to ensure input is cleared
      userInput.trim();

      // Display the word typed by the user
      Serial.println("You typed: " + userInput);

      if (userInput.equals(words[wordIndex])) {
        // Correct word typed
        correctWordCount++;
        wordIndex = random(0, 5);
        lastWordTime = millis();
        Serial.println("Correct! Next word: " + words[wordIndex]);
        digitalWrite(LED_GREEN_PIN, HIGH); // Keep LED green
      } else {
        // Incorrect word typed
        digitalWrite(LED_GREEN_PIN, LOW);
        digitalWrite(LED_RED_PIN, HIGH);
        Serial.println("Incorrect! Try again or press BackSpace to clear.");
      }
    }

    // Check if the start button is pressed again to stop the round
    if (digitalRead(BUTTON_START_STOP_PIN) == LOW) {
      delay(300); // Debounce delay
      endRound();
    }

    // Check if 30 seconds have passed since the round started
    if (millis() - roundStartTime >= 30000) {
      endRound();
    }
  }
}
