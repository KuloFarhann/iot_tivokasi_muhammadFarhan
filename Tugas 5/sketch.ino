#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>          // Ganti dengan ESP8266WiFi.h jika menggunakan ESP8266
#include <HTTPClient.h>

const char* ssid = "IRUL WIFI";      // Pastikan sama dengan nama WiFi
const char* password = "gampang123"; // Pastikan password benar
String apiKey = "e07c53c6084de0ec216d7de200fde473";       // API Key dari OpenWeatherMap
String city = "Malang";              // Kota yang ingin ditampilkan
String units = "metric";              // Untuk Celsius gunakan "metric", untuk Fahrenheit "imperial"
String server = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&units=" + units + "&appid=" + apiKey;
//String server= "https://api.openweathermap.org/data/2.5/weather?q=Malang&appid=20ca0ff523294dcdeb424dfc5802e21b";

LiquidCrystal_I2C lcd(0x27, 16, 2);   // Inisialisasi LCD dengan alamat I2C 0x27

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi...");

  // Mulai koneksi WiFi
  WiFi.begin(ssid, password);
  Serial.println("\nMencoba terhubung ke WiFi...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  // Tambahkan timeout 15 detik
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {
    delay(500);
    Serial.print(".");
  }

  // Cek hasil koneksi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nGAGAL TERHUBUNG!");
    Serial.print("Status WiFi: ");
    Serial.println(WiFi.status()); // Kode error WiFi
    lcd.clear();
    lcd.print("WiFi FAILED!");
    lcd.setCursor(0, 1);
    lcd.print("Code: " + String(WiFi.status()));
    return; // Stop program
  }

  // Jika berhasil
  Serial.println("\nTERHUBUNG!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  lcd.clear();
  lcd.print("WiFi OK!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP().toString());
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {  // Check WiFi connection status
    
    HTTPClient http;
    http.begin(server);     // Specify the URL
    int httpCode = http.GET();  // Make the request
    
    if (httpCode > 0) { // Check for the returning code
      
      String payload = http.getString();
      Serial.println(payload);   // Print the response payload
      
      // Parse data (extract temperature)
      int tempIndex = payload.indexOf("temp");
      String temp = payload.substring(tempIndex + 6, payload.indexOf(",", tempIndex));
      
      // Display temperature on LCD
      lcd.setCursor(0, 0);
      lcd.print("Temp:");
      lcd.setCursor(6, 0);
      lcd.print(temp);
      lcd.print(" C");
      
      // Extract weather description
      int descIndex = payload.indexOf("description");
      String desc = payload.substring(descIndex + 14, payload.indexOf("\"", descIndex + 14));
      
      // Display description on LCD
      lcd.setCursor(0, 1);
      lcd.print(desc);
      
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end();  // Free the resources
  }
  
  delay(60000);  // Update every minute
}