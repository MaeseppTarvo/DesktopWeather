#include "imports.h"
#include "defines.h"

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  pinMode(ONBOARD_LED_PIN, OUTPUT);
  WiFi.begin(ssid, password);
  debugln("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    debug(".");
    blinkEspBlueLed();
  }
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
  }
  debugln("")
  debug("Connected to WiFi successfully. The network IP Address is: ")
  debugln(WiFi.localIP())

  pinMode(buttonPin, INPUT_PULLUP);
  
  // WeatherServo Init
  weatherServo.attach(firstServoPin);
  weatherServo.write(weatherServoPosition);
  pinMode(firstServoPin, OUTPUT);
  // TimeRangeServo Init
  timeRangeServo.attach(secondServoPin);
  timeRangeServo.write(timeRangeServoPosition);
  pinMode(secondServoPin, OUTPUT);
  
}

void loop() {

  int buttonValue = digitalRead(buttonPin);
  
  if (buttonValue == 0 || firstSetup) {

    // Check WiFi connection status
    if(WiFi.status() == WL_CONNECTED){

      // Make OpenWeather request only if last time executed over timdeDelay(10seconds) ago. Also execute on first boot.
      if ( ((millis() - lastTime) > timerDelay) || firstSetup) {
        getWeatherForecast();
        lastTime = millis();
      }

      moveWeatherServoAccordingToTimeServoPosition();
      firstSetup = false;

    } else {
      debugln("WiFi Disconnected");
    }

    delay(1000);
  }
}

bool inRange(int val, int minimum, int maximum){
  return ((minimum <= val) && (val <= maximum));
}

void blinkEspBlueLed() {
  // Blink networkPin until connection is established.
  currentConnectionCheckMillis = millis();
  if (currentConnectionCheckMillis - previousConnectionCheckMillis > blueLedBlinkInterval ) {
    previousConnectionCheckMillis = currentConnectionCheckMillis;
    if (blueLedState == LOW) {
      blueLedState = HIGH;
    } else {
      blueLedState = LOW;
    }
    digitalWrite(ONBOARD_LED_PIN, blueLedState);
  }
}
