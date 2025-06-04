#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define boardLED 0
#define DHTPIN 12
#define DHTTYPE DHT22
#define POTPIN 34
#define LDRPIN 35 


#define TEMP_CRITICA_MIN 8.0
#define TEMP_CRITICA_MAX 38.0


const char* ID = "Thermo-Guard";
const char* moduleID = "ESP32_THERMO_V2";

const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

const char* THINGSPEAK_API_KEY = "XOG2SSLK4XDJURDG";
const char* THINGSPEAK_URL = "http://api.thingspeak.com/update";

DHT dht(DHTPIN, DHTTYPE);
float temperatura;
float umidade;
int valorPot;
int valorLDR;

void initWiFi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  pinMode(boardLED, OUTPUT);
  digitalWrite(boardLED, HIGH); 
  dht.begin();
  initWiFi();
}

void loop() {
  valorPot = analogRead(POTPIN);
  valorLDR = analogRead(LDRPIN);



  temperatura = map(valorPot, 0, 4095, 0, 50);
  umidade = map(valorPot, 0, 4095, 0, 100);

  Serial.print("Potenciômetro: ");
  Serial.print(valorPot);
  Serial.print(" -> Temp: ");
  Serial.print(temperatura, 2);
  Serial.print(" °C | Umi: ");
  Serial.print(umidade, 2);
  Serial.println(" %");
  Serial.print("Luminosidade (LDR): ");
  Serial.println(valorLDR);
  

  if (temperatura < TEMP_CRITICA_MIN) {
    Serial.println("!!! ALERTA: TEMPERATURA EXTREMAMENTE BAIXA !!!");
    digitalWrite(boardLED, HIGH);
  } else if (temperatura > TEMP_CRITICA_MAX) {
    Serial.println("!!! ALERTA: TEMPERATURA EXTREMAMENTE ALTA !!!");
    digitalWrite(boardLED, HIGH);
  } else {
    digitalWrite(boardLED, LOW);
  }


  String url = String(THINGSPEAK_URL) + "?api_key=" + THINGSPEAK_API_KEY +
                "&field1=" + String(temperatura, 2) +
                "&field2=" + String(umidade, 2) +
                "&field3=" + String(valorPot) +
                "&field4=" + String(valorLDR);

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.print("Dados enviados. Código HTTP: ");
    Serial.println(httpCode);
  } else {
    Serial.print("Erro ao enviar dados. Código: ");
    Serial.println(http.errorToString(httpCode));
  }


  http.end();

  delay(10000);
}