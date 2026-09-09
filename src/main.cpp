#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <DHT.h>
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

#define DHT_PIN   13
#define DHT_TYPE  DHT11

DHT dht(
  DHT_PIN,
  DHT_TYPE
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

  // -------------------------------
  // TFT
  // -------------------------------

  tft.begin();

  // Landscape
  tft.setRotation(3);

  tft.fillScreen(
    ILI9341_BLACK
  );


  // -------------------------------
  // DHT11
  // -------------------------------

  dht.begin();


  // -------------------------------
  // Start Screen
  // -------------------------------

  tft.setTextColor(
    ILI9341_WHITE
  );

  tft.setTextSize(2);

  tft.setCursor(
    55,
    100
  );

  tft.println(
    "DHT11 SENSOR"
  );

  delay(2000);

  tft.fillScreen(
    ILI9341_BLACK
  );
}



// =====================================================
// DISPLAY SENSOR DATA
// =====================================================

void showSensorData(
  float temperature,
  float humidity
)
{
  // ล้างจอ
  tft.fillScreen(
    ILI9341_BLACK
  );


  // ===================================================
  // HEADER
  // ===================================================

  tft.fillRect(
    0,
    0,
    320,
    40,
    ILI9341_BLUE
  );


  tft.setTextColor(
    ILI9341_WHITE
  );

  tft.setTextSize(2);

  tft.setCursor(
    60,
    10
  );

  tft.println(
    "ENVIRONMENT"
  );


  // ===================================================
  // TEMPERATURE
  // ===================================================

  tft.setTextColor(
    ILI9341_YELLOW
  );

  tft.setTextSize(2);

  tft.setCursor(
    20,
    65
  );

  tft.println(
    "TEMPERATURE"
  );


  tft.setTextColor(
    ILI9341_WHITE
  );

  tft.setTextSize(4);

  tft.setCursor(
    45,
    95
  );

  tft.print(
    temperature,
    1
  );


  tft.setTextSize(2);

  tft.print(
    " C"
  );


  // ===================================================
  // HUMIDITY
  // ===================================================

  tft.setTextColor(
    ILI9341_CYAN
  );

  tft.setTextSize(2);

  tft.setCursor(
    20,
    145
  );

  tft.println(
    "HUMIDITY"
  );


  tft.setTextColor(
    ILI9341_WHITE
  );

  tft.setTextSize(4);

  tft.setCursor(
    45,
    175
  );

  tft.print(
    humidity,
    1
  );


  tft.setTextSize(2);

  tft.print(
    " %"
  );


  // ===================================================
  // HUMIDITY BAR
  // ===================================================

  int barWidth =
    map(
      (int)humidity,0,100,0,280);


  // จำกัดค่า
  if (barWidth < 0)
    barWidth = 0;

  if (barWidth > 280)
    barWidth = 280;


  tft.drawRect(
    20,
    225,
    280,
    10,
    ILI9341_WHITE
  );


  if (barWidth > 0)
  {
    tft.fillRect(
      20,
      225,
      barWidth,
      10,
      ILI9341_CYAN
    );
  }
}


// =====================================================
// ERROR DISPLAY
// =====================================================

void showError()
{
  tft.fillScreen(
    ILI9341_BLACK
  );


  tft.setTextColor(
    ILI9341_RED
  );

  tft.setTextSize(2);

  tft.setCursor(
    65,
    80
  );

  tft.println(
    "DHT11 ERROR"
  );


  tft.setTextColor(
    ILI9341_WHITE
  );

  tft.setCursor(
    35,
    120
  );

  tft.println(
    "Check sensor"
  );

  tft.setCursor(
    35,
    150
  );

  tft.println(
    "and wiring"
  );
}

void loop()
{
// อ่านค่า DHT11
  float humidity =
    dht.readHumidity();

  float temperature =
    dht.readTemperature();


  // ตรวจสอบค่าผิดพลาด
  if (
    isnan(humidity) ||
    isnan(temperature)
  )
  {
    Serial.println(
      "DHT11 Read Error!"
    );

    showError();

    delay(2000);

    return;
  }


  // Serial Monitor
  Serial.print(
    "Temperature: "
  );

  Serial.print(
    temperature,
    1
  );

  Serial.print(
    " C   Humidity: "
  );

  Serial.print(
    humidity,
    1
  );

  Serial.println(
    " %"
  );


  // แสดงบน TFT
  showSensorData(
    temperature,
    humidity
  );


  // DHT11 ไม่ควรอ่านเร็วเกินไป
  delay(2000);
}
