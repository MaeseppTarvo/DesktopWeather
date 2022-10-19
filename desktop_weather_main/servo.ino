void moveWeatherServoAccordingToTimeServoPosition() {

  if (timeRangeServoPosition <= 180 && timeRangeServoPosition != 0 && !firstSetup) {
    timeRangeServoPosition = timeRangeServoPosition - 30;
  }

  if (timeRangeServoPosition == 0) {
    timeRangeServoPosition = 180;
  }
  timeRangeServo.write(timeRangeServoPosition);

  if (timeRangeServoPosition == 180) {

    debugln("NOW");
    
    String weatherValueAsString = JSON.stringify(weatherForecast[0]["weather"]);
    int weatherId = weatherForecast[0]["id"];
    moveWeatherServo(weatherValueAsString, weatherId);
  } else if (timeRangeServoPosition == 150) {
    debugln("3h");
    String weatherValueAsString = JSON.stringify(weatherForecast[1]["weather"]);
    int weatherId = weatherForecast[1]["id"];
    moveWeatherServo(weatherValueAsString, weatherId);
  } else if (timeRangeServoPosition == 120) {
    debugln("6h");
    String weatherValueAsString = JSON.stringify(weatherForecast[2]["weather"]);
    int weatherId = weatherForecast[2]["id"];
    moveWeatherServo(weatherValueAsString, weatherId);
  } else if (timeRangeServoPosition == 90) {
    debugln("12h");
    String weatherValueAsString = JSON.stringify(weatherForecast[3]["weather"]);
    int weatherId = weatherForecast[3]["id"];
    moveWeatherServo(weatherValueAsString, weatherId);
  } else if (timeRangeServoPosition == 60) {
    debugln("24h");
    String weatherValueAsString = JSON.stringify(weatherForecast[4]["weather"]);
    int weatherId = weatherForecast[4]["id"];
    moveWeatherServo(weatherValueAsString, weatherId);
  } else if (timeRangeServoPosition ==   30) {
    debugln("48h");
    String weatherValueAsString = JSON.stringify(weatherForecast[5]["weather"]);
    int weatherId = weatherForecast[5]["id"];
    moveWeatherServo(weatherValueAsString, weatherId);
  }

}

int previousWeatherServoPosition;
void moveWeatherServo(String weatherString, int weatherId) {

  if (weatherString == "\"Clear\"") {
   weatherServoPosition = 180;
  } else if (weatherString == "\"Clouds\"") {
   weatherServoPosition = 154;
  } else if (weatherString == "\"Rain\"") {
   weatherServoPosition = 108;
  } else if (weatherString == "\"Thunderstorm\"") {
   weatherServoPosition = 72;
  } else if (weatherString == "\"Snow\"") {
   weatherServoPosition = 36;
  } else if (weatherString == "\"Mist\"") {
   weatherServoPosition = 0;
  }

  // if (inRange(weatherId, 800, 803)) {
  //   weatherServoPosition = 180;
  // } else if (inRange(weatherId, 803, 805)) {
  //  weatherServoPosition = 154;
  // } else if (inRange(weatherId, 500, 600)) {
  //  weatherServoPosition = 108;
  // } else if (inRange(weatherId, 200, 300)) {
  //  weatherServoPosition = 72;
  // } else if (inRange(weatherId, 600, 700)) {
  //  weatherServoPosition = 36;
  // } else if (inRange(weatherId, 300, 400)) {
  //  weatherServoPosition = 36;
  // } else {
  //  weatherServoPosition = 0;
  // }

  previousWeatherServoPosition = weatherServoPosition;

  if (previousWeatherServoPosition == weatherServoPosition) {
    wobbleServo();
  } else {
    weatherServo.write(weatherServoPosition);
  }
  
}

void wobbleServo() {
  weatherServo.write(weatherServoPosition - 15);
  delay(50);
  weatherServo.write(weatherServoPosition + 15);
  delay(50);
  weatherServo.write(weatherServoPosition - 15);
  delay(50);
  weatherServo.write(weatherServoPosition + 15);
}
