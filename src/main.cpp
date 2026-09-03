#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ==========================
// ESP32
// ==========================
#define TFT_CS    15
#define TFT_RST    4
#define TFT_DC     2

#define TFT_MOSI  23
#define TFT_MISO  19
#define TFT_SCK   18

Adafruit_ILI9341 tft(
  TFT_CS,
  TFT_DC,
  TFT_RST
);

void setup()
{
  Serial.begin(115200);

  // ESP32 VSPI
  SPI.begin(
    TFT_SCK,
    TFT_MISO,
    TFT_MOSI,
    TFT_CS
  );

  // เริ่ม TFT
  tft.begin();

  // แนวนอน
  tft.setRotation(3);

  // พื้นหลัง
  tft.fillScreen(ILI9341_BLACK);

  // --------------------------
  // TEST 1
  // --------------------------

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);

  tft.setCursor(20, 20);
  tft.println("ESP32 + ILI9341");

  tft.setCursor(20, 50);
  tft.println("3.2 TFT SPI");

  tft.drawLine(
    10, 80,
    310, 80,
    ILI9341_RED
  );

  // --------------------------
  // TEST COLORS
  // --------------------------

  tft.fillRect(
    20, 100,
    80, 60,
    ILI9341_RED
  );

  tft.fillRect(
    120, 100,
    80, 60,
    ILI9341_GREEN
  );

  tft.fillRect(
    220, 100,
    80, 60,
    ILI9341_BLUE
  );

  // --------------------------
  // TEST CIRCLE
  // --------------------------

  tft.drawCircle(
    160, 210,
    40,
    ILI9341_YELLOW
  );

  Serial.println("TFT Test Complete");
}

void loop()
{
}
