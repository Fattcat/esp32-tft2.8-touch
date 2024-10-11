#include <TFT_eSPI.h>   // Knižnica pre TFT displej
#include <WiFi.h>       // Knižnica pre WiFi

TFT_eSPI tft = TFT_eSPI(); // Iniciácia TFT displeja

void setup() {
  Serial.begin(115200);
  
  // Iniciácia TFT displeja
  tft.init();
  tft.setRotation(2); // Nastavenie orientácie displeja
  tft.fillScreen(TFT_BLACK); // Vyplnenie obrazovky čiernou farbou
  tft.setTextColor(TFT_GREEN, TFT_BLACK); // Nastavenie textovej farby

  // Iniciácia WiFi (v režime STA, bez pripojenia)
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();  // Zastavenie predchádzajúceho pripojenia
  delay(100);
}

void loop() {
  // Skenovanie dostupných WiFi sietí
  int n = WiFi.scanNetworks();
  tft.fillScreen(TFT_BLACK); // Vyčistenie obrazovky pred zobrazením nových dát

  if (n == 0) {
    tft.setCursor(0, 0);
    tft.println("Ziadne WiFi siete nenajdene");
  } else {
    for (int i = 0; i < n; ++i) {
      // Vypočítanie Y pozície pre každý riadok
      int yPosition = i * 40; // Výška jedného bloku textu

      // Zobrazenie SSID
      tft.setCursor(0, yPosition);
      tft.print("SSID: ");
      tft.println(WiFi.SSID(i));

      // Zobrazenie MAC adresy
      tft.setCursor(0, yPosition + 10);
      tft.print("MAC: ");
      tft.println(WiFi.BSSIDstr(i));

      // Zobrazenie kanála
      tft.setCursor(0, yPosition + 20);
      tft.print("CH: ");
      tft.println(WiFi.channel(i));

      // Zobrazenie typu zabezpečenia
      tft.setCursor(0, yPosition + 30);
      tft.print("Security: ");
      String encryptionType = getEncryptionType(WiFi.encryptionType(i));
      tft.println(encryptionType);

      // Zobrazenie sily signálu
      tft.setCursor(0, yPosition + 40);
      tft.print("Sila: ");
      tft.print(WiFi.RSSI(i));
      tft.println(" dBm");

      // Odsadenie medzi jednotlivými sieťami
      tft.println();
    }
  }

  // Čakaj 3 sekundy pred ďalším skenovaním
  delay(3000);
}

// Funkcia na konverziu typu šifrovania na čitateľný formát
String getEncryptionType(int encryptionType) {
  switch (encryptionType) {
    case WIFI_AUTH_OPEN:
      return "Open";
    case WIFI_AUTH_WEP:
      return "WEP";
    case WIFI_AUTH_WPA_PSK:
      return "WPA_PSK";
    case WIFI_AUTH_WPA2_PSK:
      return "WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:
      return "WPA_WPA2_PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE:
      return "WPA2_Enterprise";
    case WIFI_AUTH_WPA3_PSK:
      return "WPA3_PSK";
    default:
      return "Other";
  }
}
