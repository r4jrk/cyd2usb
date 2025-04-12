#include <TFT_eTouch.h>
#include <TFT_eSPI.h>
#include <SPI.h>

SPIClass hspi(HSPI);                                           // SPI bus for display controller
TFT_eSPI tft = TFT_eSPI();                                     // TFT display object
TFT_eTouch<TFT_eSPI> eTouch(tft, ETOUCH_CS, ETOUCH_IRQ, hspi); // A display controller object with touch controller pins

int tftWidth;
int tftHeight;

//-------------------------------------------------------------------
// Utils
//-------------------------------------------------------------------

void displayCenteredText(const char *text) {
  int16_t x = (tftWidth - tft.textWidth(text)) / 2;
  int16_t y = (tftHeight - tft.fontHeight()) / 2;
  tft.setCursor(x, y);
  tft.print(text);
}

//-------------------------------------------------------------------
// Controller methods
//-------------------------------------------------------------------

void setup() {
  Serial.begin(115200);

  tft.init();
  hspi.begin(ETOUCH_SCK, ETOUCH_MISO, ETOUCH_MOSI, ETOUCH_CS); // Touch controller pins
  eTouch.init();

  pinMode(TFT_BL, OUTPUT);    // Backlight pin
  digitalWrite(TFT_BL, HIGH); // Backlight on

  tft.setRotation(1);

  tftWidth = tft.width();
  tftHeight = tft.height();

  tft.fillScreen(TFT_BLACK);

  tft.setFreeFont();
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);

  displayCenteredText("Touch to test");

  eTouch.setCalibration({272, 3783, 3897, 299, 0}); // This is an example calibration. Proper calibration method(s) to be added.
}

void loop() {
  static bool isTouched = false;
  int16_t x, y;

  if (eTouch.getXY(x, y)) { // This condition to prevent from continuously updating the screen
    if (!isTouched) {
      isTouched = true;
      tft.fillScreen(TFT_DARKGREY);
      tft.fillCircle(tftWidth / 2, tftHeight / 2, 20, TFT_GREEN);
    } else {
      isTouched = false;
      tft.fillScreen(TFT_LIGHTGREY);
      tft.fillRect(tftWidth / 2 - 10, tftHeight / 2 - 10, 20, 20, TFT_BLUE);
    }
    delay(100); // To prevent flickering
    Serial.print("Touch at: ");
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);
  }
}
