#include <Arduino.h>
#include <ArduinoSTL.h>

#include <map>

int const keyA = 2;
int const keyB = 3;
int const keyC = 4;
int const keyD = 5;
int const keyE = 6;  // Erase
int const keyF = 7;  // Enter
int const greenLed = 12;
int const redLed = 13;

bool codeSubmitted = false;
String code = "ACDB";
String userInput = "";
int sensorValue;

void turnOn(int led) {
    digitalWrite(led, HIGH);
}

void turnOff(int led) {
    digitalWrite(led, LOW);
}

bool isPressed(int key) {
    return digitalRead(key) == LOW;
}

void processUserInput() {
    // TODO: a hashmap can be used here probably
    if (isPressed(keyA)) {
        userInput += "A";
    } else if (isPressed(keyB)) {
        userInput += "B";
    } else if (isPressed(keyC)) {
        userInput += "C";
    } else if (isPressed(keyD)) {
        userInput += "D";
    } else if (isPressed(keyE)) {
        userInput = userInput.substring(0, userInput.length() - 1);
    } else if (isPressed(keyF)) {
        codeSubmitted = true;
    }
}

void handleGuessedCode() {
    turnOn(greenLed);
    Serial.println("Right code: " + userInput);
    delay(3000);
}

void handleWrongCode() {
    Serial.println("Wrong code: " + userInput);
    Serial.println("Try again..");
    turnOn(redLed);
    delay(3000);
    codeSubmitted = false;
    turnOff(redLed);
}

void checkIfUserGuessedCode() {
    bool userGuessedCode = userInput == code;
    bool areaIsDark = sensorValue <= 80;
    if (userGuessedCode & areaIsDark) {
        handleGuessedCode();
    } else {
        handleWrongCode();
    }
}

void readLightSensorValue() {
    sensorValue = analogRead(A5);
}

void setup() {
    for (int i = 2; i <= 7; i++) {
        pinMode(i, INPUT_PULLUP);
    }
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (codeSubmitted) {
        checkIfUserGuessedCode();
    } else {
        processUserInput();
        readLightSensorValue();
        Serial.println("User input: " + userInput);
        delay(1000);
    }
}
