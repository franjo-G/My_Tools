#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <U8g2lib.h>
#include <ArduinoOTA.h>
#include <TZ.h>
#include "TCA9548.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled_time(U8G2_R0, U8X8_PIN_NONE);//OLED 0,96 Zoll
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled_date(U8G2_R0, U8X8_PIN_NONE);//OLED 0,96 Zoll
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled_temp(U8G2_R0, U8X8_PIN_NONE);//OLED 0,96 Zoll
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled_temp1(U8G2_R0, U8X8_PIN_NONE);//OLED 0,96 Zoll

#define TZ TZ_Europe_Berlin
#define TCAADDR 0x70
const int ONE_WIRE_BUS = 2;
const char* ssid = "xxxxxxx";
const char* password = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


char weekdays[7][4] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
char months[12][6] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};

void setup(void) {

  Wire.begin();

  tcaselect(0);
  oled_date.begin();

  tcaselect(1);
  oled_time.begin();

  tcaselect(2);
  oled_temp.begin();

  tcaselect(3);
  oled_temp1.begin();

  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.setHostname("Aquarium");
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    }
    else { // U_FS
      type = "filesystem";
    }
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  ArduinoOTA.handle();

  sensors.requestTemperatures();

  tcaselect(0);
  oled_date.setFont(u8g2_font_ncenB18_tf);
  draw_date(oled_date);

  tcaselect(1);
  oled_time.setFont(u8g2_font_logisoso34_tf);
  draw_time(oled_time);

  tcaselect(2);
  draw_temp(oled_temp,1);

  tcaselect(3);
  draw_temp(oled_temp1,0);

  delay(5000);
}

void draw_temp(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &oled, int Index) {
  oled.clearBuffer();
  oled.setFont(u8g2_font_logisoso30_tf);
  oled.setCursor(10, 47);

  float temp = sensors.getTempCByIndex(Index);
  oled.print(temp);
  oled.drawUTF8(90, 44, " °");
  oled.sendBuffer();
}

void draw_date(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &oled) {
  oled.clearBuffer();
  configTime(TZ, "pool.ntp.org");
  time_t now;
  struct tm * s_time;
  char line_buffer[20];
  now = time(nullptr);
  s_time = localtime(&now);
  sprintf(line_buffer, "%s %i.%s   ", weekdays[s_time->tm_wday], s_time->tm_mday, months[s_time->tm_mon]);
  oled.setCursor (7, 25);
  oled.print(line_buffer);
  
  sprintf(line_buffer, "%i", s_time->tm_year + 1900);
  oled.setCursor(45, 50);
  oled.print(line_buffer);
  oled.sendBuffer();
}

void draw_time(U8G2_SSD1306_128X64_NONAME_F_HW_I2C &oled) {
  oled.clearBuffer();
  configTime(TZ, "pool.ntp.org");
  time_t now;
  struct tm * s_time;
  char line_buffer[20];
  now = time(nullptr);
  s_time = localtime(&now);
  strftime(line_buffer, 16, "%H:%M", s_time);
  oled.setCursor (12, 50);
  oled.print(line_buffer);
  oled.sendBuffer();
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}
