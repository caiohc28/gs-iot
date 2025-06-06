
#include <WiFi.h>            // Biblioteca de WiFi
#include <ThingSpeak.h>      // Biblioteca do ThingSpeak
#include <DHT.h>             // Biblioteca do sensor DHT

// Pinos e sensores
#define DHTPIN 12
#define DHTTYPE DHT22
#define LEDPIN 2
#define POTPIN 34
#define LDRPIN 35

DHT dht(DHTPIN, DHTTYPE);

// Configurações de WiFi
const char* SECRET_SSID = "Wokwi-GUEST";
const char* SECRET_PW = "";

// Configurações do ThingSpeak
WiFiClient client;
unsigned long channelID = 2980081; // Substitua pelo seu Channel ID
const char* writeAPIKey = "XOG2SSLK4XDJURDG"; // Substitua pela sua Write API Key

// Variáveis Globais
float temperatura;
float umidade;
int valorPot;
int valorLDR;
float limite_calor_extremo;
const float limite_frio_extremo = 10.0; // Valor fixo para frio extremo

// Configuração inicial
void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH); // LED apagado
  dht.begin();
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Serial.println("Iniciando...");
  delay(2000);
}

// Loop principal
void loop() {
  // Conexão Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Conectando a rede SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(SECRET_SSID, SECRET_PW);
      Serial.print(".");
      delay(2000);
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.println("");
  }

  // Leitura de sensores
  valorPot = analogRead(POTPIN);
  valorLDR = analogRead(LDRPIN);
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  // Define limite de calor extremo com o potenciômetro (25°C a 40°C)
  limite_calor_extremo = map(valorPot, 0, 4095, 250, 400) / 10.0;

  // Exibição no monitor serial
  Serial.println("========== Leitura dos Sensores ==========");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  Serial.print("Luminosidade (LDR - valor bruto): ");
  Serial.println(valorLDR);

  Serial.print("Limite de calor extremo (potenciômetro): ");
  Serial.print(limite_calor_extremo);
  Serial.println(" °C");

  Serial.print("Limite de frio extremo (fixo): ");
  Serial.print(limite_frio_extremo);
  Serial.println(" °C");

  // Lógica para acionar LED em caso de calor ou frio extremos
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("⚠️ Erro na leitura do sensor DHT.");
    digitalWrite(LEDPIN, HIGH); // LED apagado
  } else if (temperatura > limite_calor_extremo) {
    Serial.println("⚠️ Alerta: CALOR EXTREMO!");
    digitalWrite(LEDPIN, LOW); // LED aceso
  } else if (temperatura < limite_frio_extremo) {
    Serial.println("⚠️ Alerta: FRIO EXTREMO!");
    digitalWrite(LEDPIN, LOW); // LED aceso
  } else {
    digitalWrite(LEDPIN, HIGH); // LED apagado
  }

  // Envio para o ThingSpeak
  ThingSpeak.setField(1, temperatura);
  ThingSpeak.setField(2, umidade);
  ThingSpeak.setField(3, valorPot);
  ThingSpeak.setField(4, valorLDR);
  ThingSpeak.setField(5, limite_calor_extremo);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (status == 200) {
    Serial.println("✅ Dados enviados com sucesso para o ThingSpeak!");
  } else {
    Serial.print("❌ Erro ao enviar: ");
    Serial.println(status);
  }

  Serial.println("===========================================");
  Serial.println();
  delay(20000); // 20 segundos para respeitar limite do ThingSpeak
}
