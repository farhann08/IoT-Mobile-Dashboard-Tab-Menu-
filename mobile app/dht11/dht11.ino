#include "secrets.h"
#include <Firebase.h>
#include "DHT.h"

// Pin untuk sensor DHT
#define DHTPIN 13
#define DHTTYPE DHT22  // Menggunakan DHT11 sebagai sensor
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi Firebase
Firebase fb(FIREBASE_HOST, FIREBASE_AUTH);

void setup() {
  Serial.begin(115200);

  // Koneksi ke Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Terhubung ke WiFi");

  // Inisialisasi sensor DHT
  dht.begin();
}

void loop() {
  // Membaca kelembapan dan suhu
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  // Validasi pembacaan sensor
  if (isnan(humi) || isnan(temp)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  // Menampilkan data di Serial Monitor
  Serial.println("Kelembapan: " + String(humi, 2) + " | Suhu: " + String(temp, 2));

  // Mengirim data kelembaban ke Firebase
  if (fb.setFloat("Sensor/Humidity", humi)) { 
    Serial.println("Data kelembaban terkirim ke Firebase!");
  } else {
    Serial.println("Gagal kirim kelembaban!");
  }

  // Mengirim data suhu ke Firebase
  if (fb.setFloat("Sensor/Temeperature", temp)) {
    Serial.println("Data suhu terkirim ke Firebase!");
  } else {
    Serial.println("Gagal kirim suhu!");
  }

  delay(1000);  // Kirim data setiap 1 detik
}
