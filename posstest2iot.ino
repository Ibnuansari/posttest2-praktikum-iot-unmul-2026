// Import Libary yang Dibutuhkan
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

// Konfigurasi WIFI
#define WIFI_SSID "2309106082"
#define WIFI_PASSWORD "ibnuibnu2004"

// Konfigurasi Token Bot Telegram
#define BOT_TOKEN "8048484142:AAHdxK967uwALedOFJbIJwBK56sXHMRLqoI"

// User ID dari akun telegram
#define CHAT_ID_ARIF "5641722971"
#define CHAT_ID_IBNU "6214138686"
#define CHAT_ID_RIZKY "6327197829"

// ID dari Grup Chat Telegram
#define GROUP_CHAT_ID "-5288176995"

// Konfigurasi Sensor
#define DHTPIN 32
#define DHTTYPE DHT22
#define MQ2PIN 34

// Pin LED
#define LED_ARIF 13
#define LED_IBNU 12
#define LED_RIZKY 14
#define LED_RUANG_TAMU 27

// Mentepapkan Nilai Ambang Gas
#define AMBANG_GAS 1000

// Memastikan koneksi secure
WiFiClientSecure secured_client;

// Membuat Objek telegram untuk mengirim dan menerima pesan
UniversalTelegramBot bot(BOT_TOKEN, secured_client);


unsigned long bot_lasttime;
const unsigned long BOT_MTBS = 1000;

DHT dht(DHTPIN, DHTTYPE);

int statusArif = 0;
int statusIbnu = 0;
int statusRizky = 0;
int statusRuang = 0;

bool peringatanGas = false;

// fungsi untuk mengambil nama user berdasarkan user id
String getNamaUser(String user_id) {
  if (user_id == CHAT_ID_ARIF) return "Arif";
  if (user_id == CHAT_ID_IBNU) return "Ibnu";
  if (user_id == CHAT_ID_RIZKY) return "Rizky";
  return "User Tidak Dikenal";
}

// fungsi untuk memproses pesan dari telegram
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {

    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String user_id = bot.messages[i].from_id;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (text == "/led_arif_on") {
      if (user_id == CHAT_ID_ARIF) {
        digitalWrite(LED_ARIF, HIGH);
        statusArif = 1;
        bot.sendMessage(chat_id, "💡 Lampu Arif berhasil dinyalakan", "");
      } else {
        String msg = "⛔ AKSES DITOLAK!\n";
        msg += "👤 " + getNamaUser(user_id) + " mencoba akses lampu Arif\n";
        msg += "🔒 Lampu ini milik Arif";
        bot.sendMessage(chat_id, msg, "");
      }
    }

    if (text == "/led_arif_off") {
      if (user_id == CHAT_ID_ARIF) {
        digitalWrite(LED_ARIF, LOW);
        statusArif = 0;
        bot.sendMessage(chat_id, "💡 Lampu Arif dimatikan", "");
      } else {
        String msg = "⛔ AKSES DITOLAK!\n";
        msg += "👤 " + getNamaUser(user_id) + " mencoba akses lampu Arif\n";
        msg += "🔒 Lampu ini milik Arif";
        bot.sendMessage(chat_id, msg, "");
      }
    }

    if (text == "/led_ibnu_on") {
      if (user_id == CHAT_ID_IBNU) {
        digitalWrite(LED_IBNU, HIGH);
        statusIbnu = 1;
        bot.sendMessage(chat_id, "💡 Lampu Ibnu berhasil dinyalakan", "");
      } else {
        String msg = "⛔ AKSES DITOLAK!\n";
        msg += "👤 " + getNamaUser(user_id) + " mencoba akses lampu Ibnu\n";
        msg += "🔒 Lampu ini milik Ibnu";
        bot.sendMessage(chat_id, msg, "");
      }
    }

    if (text == "/led_ibnu_off") {
      if (user_id == CHAT_ID_IBNU) {
        digitalWrite(LED_IBNU, LOW);
        statusIbnu = 0;
        bot.sendMessage(chat_id, "💡 Lampu Ibnu dimatikan", "");
      } else {
        String msg = "⛔ AKSES DITOLAK!\n";
        msg += "👤 " + getNamaUser(user_id) + " mencoba akses lampu Ibnu\n";
        msg += "🔒 Lampu ini milik Ibnu";
        bot.sendMessage(chat_id, msg, "");
      }
    }

    if (text == "/led_rizky_on") {
      if (user_id == CHAT_ID_RIZKY) {
        digitalWrite(LED_RIZKY, HIGH);
        statusRizky = 1;
        bot.sendMessage(chat_id, "💡 Lampu Rizky berhasil dinyalakan", "");
      } else {
        String msg = "⛔ AKSES DITOLAK!\n";
        msg += "👤 " + getNamaUser(user_id) + " mencoba akses lampu Rizky\n";
        msg += "🔒 Lampu ini milik Rizky";
        bot.sendMessage(chat_id, msg, "");
      }
    }

    if (text == "/led_rizky_off") {
      if (user_id == CHAT_ID_RIZKY) {
        digitalWrite(LED_RIZKY, LOW);
        statusRizky = 0;
        bot.sendMessage(chat_id, "💡 Lampu Rizky dimatikan", "");
      } else {
        String msg = "⛔ AKSES DITOLAK!\n";
        msg += "👤 " + getNamaUser(user_id) + " mencoba akses lampu Rizky\n";
        msg += "🔒 Lampu ini milik Rizky";
        bot.sendMessage(chat_id, msg, "");
      }
    }

    if (text == "/rumah_on") {
      digitalWrite(LED_RUANG_TAMU, HIGH);
      statusRuang = 1;
      bot.sendMessage(chat_id, "🏠 Lampu ruang tamu dinyalakan", "");
    }

    if (text == "/rumah_off") {
      digitalWrite(LED_RUANG_TAMU, LOW);
      statusRuang = 0;
      bot.sendMessage(chat_id, "🏠 Lampu ruang tamu dimatikan", "");
    }


    if (text == "/dht") {
      String msg = "🌡 SUHU & KELEMBAPAN\n\n";
      msg += "Suhu: " + String(t) + "°C\n";
      msg += "Kelembapan: " + String(h) + "%";
      bot.sendMessage(chat_id, msg, "");
    }

    if (text == "/gas") {
      int gas = analogRead(MQ2PIN);
      String msg = "🧪 STATUS GAS\n\n";
      msg += "Nilai: " + String(gas) + "\n";
      if (gas > AMBANG_GAS) msg += "🔴 BAHAYA!";
      else msg += "🟢 AMAN";
      bot.sendMessage(chat_id, msg, "");
    }

    if (text == "/start") {
      String msg = "🏠 SMART HOUSE SYSTEM\n\n";
      msg += "💡 Kontrol Lampu:\n";
      msg += "/led_arif_on /led_arif_off\n";
      msg += "/led_ibnu_on /led_ibnu_off\n";
      msg += "/led_rizky_on /led_rizky_off\n";
      msg += "/rumah_on /rumah_off\n\n";
      msg += "📊 Monitoring:\n/dht\n\n";
      msg += "🚨 Auto warning gas aktif";
      bot.sendMessage(chat_id, msg, "");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_ARIF, OUTPUT);
  pinMode(LED_IBNU, OUTPUT);
  pinMode(LED_RIZKY, OUTPUT);
  pinMode(LED_RUANG_TAMU, OUTPUT);

  dht.begin();

  secured_client.setInsecure();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void loop() {

  // mengecek pesan telegram secara berkala
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    if (numNewMessages > 0) handleNewMessages(numNewMessages);
    bot_lasttime = millis();
  }

  int gas = analogRead(MQ2PIN);

  if (gas > AMBANG_GAS && !peringatanGas) {
    String msg = "🚨 WARNING GAS TERDETEKSI!\n\n";
    msg += "Nilai: " + String(gas) + "\n";
    msg += "Segera cek rumah!";
    bot.sendMessage(GROUP_CHAT_ID, msg, "");
    peringatanGas = true;
  }

  if (gas <= AMBANG_GAS && peringatanGas) {
    String msg = "🟢 KONDISI AMAN\n\n";
    msg += "Gas normal\nNilai: " + String(gas);
    bot.sendMessage(GROUP_CHAT_ID, msg, "");
    peringatanGas = false;
  }
}