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
      int yPosition = i * 60; // Výška jedného bloku textu

      // Zobrazenie SSID
      tft.setCursor(0, yPosition);
      tft.print("SSID: ");
      tft.println(WiFi.SSID(i));

      // Zobrazenie MAC adresy
      tft.setCursor(0, yPosition + 10);
      tft.print("MAC: ");
      tft.println(WiFi.BSSIDstr(i));

      // Zobrazenie kanála
      int channel = WiFi.channel(i);
      tft.setCursor(0, yPosition + 20);
      tft.print("CH: ");
      tft.println(channel);

      // Zobrazenie frekvencie na základe kanála
      float frequency = getWiFiFrequency(channel);
      tft.setCursor(0, yPosition + 30);
      tft.print("Frekvencia: ");
      tft.print(frequency);
      tft.println(" MHz");

      // Zobrazenie typu zabezpečenia
      tft.setCursor(0, yPosition + 40);
      tft.print("Security: ");
      String encryptionType = getEncryptionType(WiFi.encryptionType(i));
      tft.println(encryptionType);

      // Zobrazenie sily signálu
      tft.setCursor(0, yPosition + 50);
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

// Funkcia na prepočet WiFi kanálu na frekvenciu v MHz
float getWiFiFrequency(int channel) {
  if (channel >= 1 && channel <= 14) {
    // 2,4 GHz pásmo
    return 2407 + channel * 5; // Frekvencia sa počíta z 2407 MHz + (kanál * 5)
  } else if (channel >= 32 && channel <= 177) {
    // 5 GHz pásmo (bežné kanály medzi 36 a 165)
    return 5000 + (channel * 5);
  } else {
    return 0; // Neplatný kanál
  }
}
