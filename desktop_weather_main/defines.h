#define DEBUG true

#if DEBUG == true
  #define debug(x) Serial.print(x);
  #define debugln(x) Serial.println(x);
#else
  #define debug(x);
  #define debugln(x);
#endif

#define buttonPin 14
#define firstServoPin 13
#define secondServoPin 15

#define ONBOARD_LED_PIN 2

boolean firstSetup = true;

Servo weatherServo;
Servo timeRangeServo;

int weatherServoPosition = 180;
int timeRangeServoPosition = 180;

boolean blueLedState = true;

long previousConnectionCheckMillis = 0;
unsigned long currentConnectionCheckMillis;
int blueLedBlinkInterval = 100;

const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";
String openWeatherMapApiKey = "OPEN_WEATHER_MAP_API_KEY";

String city = "Saue";
String countryCode = "EE";
String locationLatitude = "59.31978752102142";
String locationLongitude = "24.55390007650135";

// THE DEFAULT TIMER IS SET TO 60 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
// unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

int weatherArray[6];

JSONVar weatherForecast;
