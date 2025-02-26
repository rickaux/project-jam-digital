# RTC LCD I2C Multi-Microcontroller Project

Proyek ini merupakan implementasi **RTC DS1307** dengan **LCD 16x2 I2C**, yang mendukung berbagai mikrokontroler seperti **Arduino Uno, ESP8266**, dan lainnya. Proyek ini menampilkan waktu real-time di **Serial Monitor & LCD**.

## 🚀 Fitur
- ✅ Menampilkan waktu dari **RTC DS1307** ke **LCD 16x2 I2C**
- ✅ Kompatibel dengan **Arduino Uno, ESP8266**, dan lainnya
- ✅ Mendukung **Serial Monitor** untuk debugging
- ✅ Mudah dikembangkan dengan tambahan fitur lain

## 📌 Wiring Diagram
### **ESP8266 + RTC DS1307 + LCD I2C**
![Wiring Diagram](https://raw.githubusercontent.com/rickaux/project-rtc-ds1307-lcd-16x2-i2c/refs/heads/main/wiring%20diagram%20rtc%20ds1307%20lcd%20i2c%2016x2%20esp8266.jpg)

| Komponen        | ESP8266 | Keterangan |
|---------------|--------|------------|
| **RTC DS1307** |        |            |
| VCC           | VIN    | 5V dari ESP8266 |
| GND           | GND    | Ground |
| SDA           | D2     | GPIO4 |
| SCL           | D1     | GPIO5 |
| **LCD 16x2 I2C** |        |            |
| VCC           | VIN    | 5V dari ESP8266 |
| GND           | GND    | Ground |
| SDA           | D2     | GPIO4 |
| SCL           | D1     | GPIO5 |

## 🔧 Instalasi & Library
Pastikan Anda telah menginstal library berikut di **Arduino IDE**:
- `Wire.h` (built-in)
- `RTClib.h` (RTC DS1307)
- `LiquidCrystal_I2C.h` (untuk LCD, gunakan versi kompatibel dengan ESP8266)

Jika menggunakan **ESP8266**, pastikan library **LiquidCrystal_I2C** yang digunakan kompatibel dengan **ESP8266**.

## 🛠️ Cara Penggunaan
1. **Koneksi hardware** sesuai tabel wiring.
2. **Upload kode** sesuai dengan mikrokontroler yang digunakan (**Arduino atau ESP8266**).
3. **Buka Serial Monitor** untuk melihat output waktu dari RTC.
4. **Periksa LCD** untuk memastikan waktu ditampilkan dengan benar.

## 📝 Changelog
### **v1.0.0 - [selasa, 25 Feb 2025]**
- ✅ Implementasi awal untuk **Arduino Uno**
- ✅ Menampilkan waktu RTC di **Serial Monitor & LCD**

### **v1.1.0 - [selasa, 25 Feb 2025]**
- 🔄 **Migrasi ke ESP8266**
- 🛠 **Mengganti library LCD agar kompatibel dengan ESP8266**
- 🔌 **Menyesuaikan pin I2C (SDA = D2, SCL = D1)**

## 🔗 Lisensi
Proyek ini menggunakan lisensi **MIT**. Silakan digunakan dan dikembangkan lebih lanjut.

---
**Kontributor**: [Nama Anda]  
📌 *Project Open Source - Feel free to contribute!* 🚀
