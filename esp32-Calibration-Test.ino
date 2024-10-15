#include <TFT_eSPI.h>  // Knižnica pre ILI9341 s dotykovým ovládaním

TFT_eSPI tft = TFT_eSPI();       // Inicializácia displeja
uint16_t calData[5] = { 185, 3452, 292, 3540, 1 };

void setup() {
  Serial.begin(115200);          // Spustenie sériovej komunikácie pre ladenie
  tft.init();                    // Inicializácia displeja
  tft.setRotation(1);            // Nastavenie rotácie displeja

  // Nastavenie kalibrácie dotykového panela
  tft.setTouch(calData);

  tft.fillScreen(TFT_BLACK);     // Vymazanie obrazovky po nastavení kalibrácie
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 150);
  tft.println("Touch the screen...");
}

void loop() {
  uint16_t x = 0, y = 0;         // Premenné pre súradnice dotyku

  // Skontroluje, či je dotykový panel dotknutý
  if (tft.getTouch(&x, &y)) {
    tft.fillScreen(TFT_BLACK);   // Vyčistenie obrazovky

    // Zobrazenie krížika na mieste dotyku
    drawCrosshair(x, y);

    Serial.print("Dotyk na: X = ");
    Serial.print(x);
    Serial.print(", Y = ");
    Serial.println(y);

    delay(500);                  // Počkajte, aby sa zabránilo rýchlemu opakovaniu
  }
}

// Funkcia na vykreslenie krížika
void drawCrosshair(uint16_t x, uint16_t y) {
  int size = 10;                         // Veľkosť krížika
  tft.drawLine(x - size, y, x + size, y, TFT_RED);  // Vodorovná čiara
  tft.drawLine(x, y - size, x, y + size, TFT_RED);  // Zvislá čiara
}
