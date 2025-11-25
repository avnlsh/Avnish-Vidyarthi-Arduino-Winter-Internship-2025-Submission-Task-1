#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 2         // Data pin
#define DHTTYPE DHT11    // Your HT sensor
DHT dht(DHTPIN, DHTTYPE);

int LDR_pin = A0;
int Flex_pin = A1;

int LED_LDR = 10;
int LED_TEMP = 11;

int servoPin = 3;
int buzzerPin = 9;

Servo myservo;

int LDR_THRESHOLD = 60;
int FLEX_THRESHOLD = 250;
int TEMP_THRESHOLD = 30;   

void setup() {
  Serial.begin(115200);

  pinMode(LED_LDR, OUTPUT);
  pinMode(LED_TEMP, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  myservo.attach(servoPin);
  myservo.write(0);

  // Start sensors
  dht.begin();

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // halt if OLED missing
  }
  display.clearDisplay();
}

void loop() {

  int ldrValue = analogRead(LDR_pin);
  int flexValue = analogRead(Flex_pin);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  bool ldrDark = (ldrValue < LDR_THRESHOLD);
  digitalWrite(LED_LDR, ldrDark ? HIGH : LOW);

  bool flexBent = (flexValue > FLEX_THRESHOLD);
  myservo.write(flexBent ? 120 : 0);

  bool tempOK = !isnan(temperature);
  bool tempHigh = tempOK && temperature > TEMP_THRESHOLD;

  digitalWrite(LED_TEMP, tempHigh ? HIGH : LOW);
  digitalWrite(buzzerPin, tempHigh ? HIGH : LOW);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("LDR:  ");
  display.println(ldrValue);

  display.setCursor(0, 10);
  display.print("Flex: ");
  display.println(flexValue);

  display.setCursor(0, 20);
  display.print("Temp: ");
  if (tempOK) display.print(temperature);
  else display.print("Err");
  display.println(" C");

  display.setCursor(0, 30);
  display.print("Hum:  ");
  if (tempOK) display.println(humidity);
  else display.println("Err");

  display.setCursor(0, 40);
  display.print("Servo: ");
  display.println(flexBent ? "ACTIVE" : "REST");

  display.setCursor(0, 50);
  display.print("Buzz: ");
  display.println(tempHigh ? "ON" : "OFF");

  display.display();

  Serial.println("------ SENSOR STATUS ------");
  Serial.print("LDR Value      : "); Serial.println(ldrValue);
  Serial.print("Flex Value     : "); Serial.println(flexValue);

  Serial.print("Temperature(C) : ");
  if (tempOK) Serial.println(temperature);
  else Serial.println("Error");

  Serial.print("Humidity(%)    : ");
  if (tempOK) Serial.println(humidity);
  else Serial.println("Error");

  Serial.print("Servo State    : ");
  Serial.println(flexBent ? "ACTIVE" : "REST");

  Serial.print("Buzzer State   : ");
  Serial.println(tempHigh ? "ON" : "OFF");

  Serial.println("---------------------------\n");

  delay(300);
}
