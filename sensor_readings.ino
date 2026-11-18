#include "Adafruit_LiquidCrystal.h"
#include "Adafruit_SHT4x.h"
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);
Adafruit_SHT4x sht4 = Adafruit_SHT4x();

const uint32_t interval = 300000; // ms between reads: 5 min = 300 sec
sensors_event_t humidity, temp; 
uint32_t lastReadMs = 0;

String supabaseUrl = "https://url.supabase.co";
String supabaseKey = "anonkey";
const char *ssid = "wifi";
const char *password = "password";
const String device_id = "device_id";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  
  Serial.print("ESP32 Board MAC Address: "); // print MAC address
  Serial.println(WiFi.macAddress());
  
  Wire.begin();

  Serial.println("Starting LCD...");
  
  if (!lcd.begin(16, 2)) {
    Serial.println("Could not init backpack. Check wiring.");
    while (1) delay(1);
  }

  Serial.println("Backpack init'd.");
  lcd.setBacklight(HIGH);

  delay(1500);

  Serial.println("Starting SHT4x...");

  if (!sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    lcd.clear();
    lcd.print("Sensor not found");
    while (1) delay(1);
  }

  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);

  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  takeReading();
}

void takeReading() {
  sht4.getEvent(&humidity, &temp);
  lastReadMs = millis();
  float tempF = (temp.temperature * 1.8) + 32.0;
  float rhPercent = humidity.relative_humidity;

  // Display readings on the character LCD
  lcd.setCursor(0, 0);
  lcd.print(tempF); lcd.print((char)223); lcd.print("F ");
  lcd.print(rhPercent); lcd.print("%rH ");

  // Print to serial monitor
  Serial.print(tempF); Serial.print("F ");
  Serial.print(humidity.relative_humidity); Serial.print("%rH ");

  // Insert into database
  if (WiFi.status() == WL_CONNECTED) {
    insertData(tempF, rhPercent);
  } else {
    Serial.println("WiFi disconnected, reconnecting...");
    WiFi.reconnect();
  }
}

void insertData(float tempF, float rhPercent) {
  String url = supabaseUrl + "/rest/v1/readings";

  String json = "{\"devices_device_id\":\"" + device_id + "\","
                "\"temp_f\":" + String(tempF, 2) + ","
                "\"humidity_percent\":" + String(rhPercent, 2) + "}";

  WiFiClientSecure client;
  client.setInsecure();   // skips certificate checking

  HTTPClient http;
  if (!http.begin(client, url)) {
    Serial.println("- http.begin failed");
    return;
  }
  http.addHeader("apikey", supabaseKey);
  http.addHeader("Authorization", "Bearer " + supabaseKey);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Prefer", "return=minimal");

  int code = http.POST(json);
  Serial.printf("- Supabase response: %d (%s)\n", code, HTTPClient::errorToString(code).c_str());
  if (code != 201) Serial.println(http.getString());   // shows Supabase's error message
  http.end();
}

void loop() {
  if (millis() - lastReadMs >= interval) {
    takeReading();
  }

  uint32_t elapsed = (millis() - lastReadMs) / 1000;

  lcd.setCursor(0, 1);
  lcd.print("Since read: "); lcd.print(elapsed); lcd.print("s ");
}