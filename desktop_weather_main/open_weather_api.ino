String httpGETRequest(const char *serverName) {
  WiFiClient client;
  HTTPClient http;
 
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload;

  if (httpResponseCode > 0) {
    debug("HTTP Response code: ")
    debugln(httpResponseCode);
    payload = http.getString();
  } else {
    debug("Error code: ")
    debugln(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void getWeatherForecast() {
  String weatherApiUrl = "http://api.openweathermap.org/data/2.5/onecall?lat=" + locationLatitude +"&lon=" + locationLongitude + "&exclude=minutely&appid=" + openWeatherMapApiKey + "&units=metric";

  String jsonBuffer = httpGETRequest(weatherApiUrl.c_str());
  JSONVar openWeatherResponseObject = JSON.parse(jsonBuffer);

  JSONVar weatherObject;

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(openWeatherResponseObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  debug("Current Weather: ");
  debugln(openWeatherResponseObject["current"]["weather"][0]["main"]);
  debugln(openWeatherResponseObject["current"]["weather"][0]["id"]);
  JSONVar zeroHWeatherString = openWeatherResponseObject["current"]["weather"][0]["main"];
  weatherObject[0]["time"] = "ZERO_H";
  weatherObject[0]["weather"] = zeroHWeatherString;

  debug("3h From Now: ");
  debugln(openWeatherResponseObject["hourly"][2]["weather"][0]["main"]);
  debugln(openWeatherResponseObject["hourly"][2]["weather"][0]["id"]);
  JSONVar threeHWeatherString = openWeatherResponseObject["hourly"][2]["weather"][0]["main"];
  weatherObject[1]["time"] = "THREE_H";
  weatherObject[1]["weather"] = threeHWeatherString;
  

  debug("6h From Now: ");
  debugln(openWeatherResponseObject["hourly"][5]["weather"][0]["main"]);
  debugln(openWeatherResponseObject["hourly"][5]["weather"][0]["id"]);
  JSONVar sixHWeatherString = openWeatherResponseObject["hourly"][5]["weather"][0]["main"];
  weatherObject[2]["time"] = "SIX_H";
  weatherObject[2]["weather"] = sixHWeatherString;


  debug("12h From Now: ");
  debugln(openWeatherResponseObject["hourly"][11]["weather"][0]["main"]);
  debugln(openWeatherResponseObject["hourly"][11]["weather"][0]["id"]);
  JSONVar twelveHWeatherString = openWeatherResponseObject["hourly"][11]["weather"][0]["main"];
  weatherObject[3]["time"] = "TWELVE_H";
  weatherObject[3]["weather"] = twelveHWeatherString;


  debug("Tomorraw at midday: ");
  debugln(openWeatherResponseObject["daily"][1]["weather"][0]["main"]);
  debugln(openWeatherResponseObject["daily"][1]["weather"][0]["id"]);
  JSONVar twentyFourHWeatherString = openWeatherResponseObject["daily"][1]["weather"][0]["main"];
  weatherObject[4]["time"] = "TWENTY_FOUR_H";
  weatherObject[4]["weather"] = twentyFourHWeatherString;


  debug("The day after tomorrow: ");
  debugln(openWeatherResponseObject["daily"][2]["weather"][0]["main"]);
  debugln(openWeatherResponseObject["daily"][2]["weather"][0]["id"]);
  JSONVar fortyEightHWeatherString = openWeatherResponseObject["daily"][2]["weather"][0]["main"];
  weatherObject[5]["time"] = "FORTY_EIGHT_H";
  weatherObject[5]["weather"] = fortyEightHWeatherString;

  weatherForecast = weatherObject;
}
