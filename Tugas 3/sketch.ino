#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define DHTPIN 19
#define DHTTYPE DHT22
#define LDR_PIN 35  // Pin untuk sensor cahaya (LDR)
#define TIMEDHT 1000

// Inisialisasi variabel
float humidity, celsius, fahrenheit;
int lightIntensity;
uint32_t timerDHT = TIMEDHT;
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi LCD (16x2 dengan I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Fungsi untuk membaca suhu dan kelembapan
void getTemperature() {
  if ((millis() - timerDHT) > TIMEDHT) {
    timerDHT = millis();
    humidity = dht.readHumidity();
    celsius = dht.readTemperature();
    fahrenheit = dht.readTemperature(true);

    if (isnan(humidity) || isnan(celsius) || isnan(fahrenheit)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}

// Fungsi untuk membaca intensitas cahaya
void getLightIntensity() {
  lightIntensity = analogRead(LDR_PIN);  // Membaca nilai analog dari LDR
}

void setup() {
  Serial.begin(115200);
  lcd.begin();  // Inisialisasi LCD
  lcd.backlight();  // Nyalakan backlight LCD
  dht.begin();  // Inisialisasi sensor DHT

  Serial.println("Hello, farhan");
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(500);  // Delay untuk memperlambat loop
  getTemperature();
  getLightIntensity();

  // Tampilkan data di Serial Monitor
  Serial.print("Temp: ");
  Serial.print(celsius);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Light: ");
  Serial.println(lightIntensity);

  // Tampilkan data di LCD
  lcd.setCursor(0, 0);  // Baris pertama
  lcd.print("Temp: ");
  lcd.print(celsius);
  lcd.print(" C");

  lcd.setCursor(0, 1);  // Baris kedua
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" % Light: ");
  lcd.print(lightIntensity);
}