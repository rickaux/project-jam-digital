/* =============================================================
// ESP8266 RTC + NTP Clock with LCD and Web Server
// Features:
// 1. Menggunakan WiFiManager untuk koneksi WiFi tanpa hardcode SSID & Password.
// 2. Menggunakan RTC DS1307 sebagai backup waktu jika WiFi tidak tersedia.
// 3. Menggunakan NTP Client untuk sinkronisasi waktu dari server.
// 4. Menampilkan waktu di LCD 16x2 I2C.
// 5. Menyediakan web server yang menampilkan waktu real-time.
// 6. Web server menggunakan JavaScript fetch() untuk update waktu tanpa refresh halaman.
// 7. Format waktu: HH:MM:SS DD-MM-YYYY.
// 8. Auto update RTC dari NTP saat WiFi tersedia.

ini kalau kalian tidak memiliki lcd 16x2 tidak apa apa, dara masih di tampilkan ke dalam serial monitor
dan webserver browser dengan akses lewat ip port defaultnya 80  tidak perlu memasukkan port

note: kode ini jika si esp belum sama sekali konek ke wifi maka dia akan membuat ssid ESP8266-Clock no password,
di code ini masih ada tantangan besar menurut saya yaitu
saat mau forget masih belum bisa karena belum saya buat, kalimat bisa menghapus semua ssid/ke wifi yang pernah terhubung di esp
lewat script yang ada di github saya

=============================================================*/


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_PCF8574.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// Inisialisasi WiFiManager
WiFiManager wifiManager;

// Inisialisasi RTC DS1307
RTC_DS1307 rtc;

// Inisialisasi LCD 16x2 I2C
LiquidCrystal_PCF8574 lcd(0x26);

// Inisialisasi Web Server
ESP8266WebServer server(80);

// Inisialisasi NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", 25200, 60000); // GMT+7 (25200 detik)

void handleRoot() {
    String html = "<html><head><title>ESP8266 Clock</title>";
    html += "<script>setInterval(function() {fetch('/time').then(res => res.text()).then(time => document.getElementById('time').innerText = time);}, 1000);</script>";
    html += "</head><body>";
    html += "<h1>Waktu Saat Ini</h1><p id='time'>Loading...</p></body></html>";
    
    server.send(200, "text/html", html);
}

void handleTime() {
    DateTime now = rtc.now();
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d %02d-%02d-%04d",
             now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());
    server.send(200, "text/plain", buffer);
}

void setup() {
    Serial.begin(115200);
    
    // WiFiManager untuk koneksi WiFi
    wifiManager.autoConnect("ESP8266-Clock");
    Serial.println("Terhubung ke WiFi");
    
    timeClient.begin();
    
    // Inisialisasi RTC
    if (!rtc.begin()) {
        Serial.println("RTC tidak terdeteksi!");
        while (1);
    }
    if (!rtc.isrunning()) {
        Serial.println("RTC belum berjalan, mengatur waktu sekarang!");
    }
    
    // Inisialisasi LCD
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.setCursor(0, 0);
    lcd.print("Waktu: ");
    
    // Setup Web Server
    server.on("/", handleRoot);
    server.on("/time", handleTime);
    server.begin();
    Serial.println("Server Web berjalan");
}

void loop() {
    server.handleClient();
    
    if (WiFi.status() == WL_CONNECTED) {
        timeClient.update();
        DateTime now(timeClient.getEpochTime());
        rtc.adjust(now);
    } else {
        Serial.println("WiFi terputus, menggunakan waktu RTC.");
    }
    
    // Baca waktu RTC
    DateTime now = rtc.now();
    char buffer[17];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d %02d-%02d-%04d",
             now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());
    Serial.println(buffer);
    
    // Tampilkan waktu di LCD
    lcd.setCursor(0, 1);
    lcd.print(buffer);
    
    delay(1000);
}