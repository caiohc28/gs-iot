#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define boardLED 2
#define DHTPIN 12     // Pino conectado ao sensor DHT
#define DHTTYPE DHT22   // Tipo do sensor DHT (DHT22 ou DHT11)
#define POTPIN 34     // Pino conectado ao potenciômetro
#define LDRPIN 35     // Pino conectado ao LDR

// Limites de temperatura para alerta
#define TEMP_CRITICA_MIN 8.0
#define TEMP_CRITICA_MAX 38.0

// Identificadores (não utilizados neste código, mas mantidos)
const char* ID = "Thermo-Guard";
const char* moduleID = "ESP32_THERMO_V2";

// Credenciais Wi-Fi (para Wokwi)
const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

// Configurações do ThingSpeak
const char* THINGSPEAK_API_KEY = "XOG2SSLK4XDJURDG"; // Substitua pela sua API Key
const char* THINGSPEAK_URL = "http://api.thingspeak.com/update";

// Inicializa o sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Variáveis globais para armazenar as leituras
float temperatura = 0.0; // Inicializa com valor padrão
float umidade = 0.0;     // Inicializa com valor padrão
int valorPot;
int valorLDR;

// Função para inicializar a conexão Wi-Fi
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

// Função de configuração executada uma vez no início
void setup() {
  Serial.begin(115200);       // Inicializa a comunicação serial
  pinMode(boardLED, OUTPUT);  // Configura o pino do LED como saída
  digitalWrite(boardLED, HIGH); // Garante que o LED comece desligado
  dht.begin();                // Inicializa o sensor DHT
  initWiFi();                 // Conecta ao Wi-Fi
  Serial.println("Setup concluído. Iniciando leituras...");
}

// Função principal executada repetidamente
void loop() {
  // Lê os valores do potenciômetro e do LDR
  valorPot = analogRead(POTPIN);
  valorLDR = analogRead(LDRPIN);

  // Tenta ler a temperatura e a umidade do sensor DHT
  float temp_lida = dht.readTemperature(); // Lê temperatura em Celsius
  float umid_lida = dht.readHumidity();    // Lê umidade

  // Verifica se a leitura do DHT foi bem-sucedida (não NaN - Not a Number)
  if (isnan(temp_lida) || isnan(umid_lida)) {
    Serial.println("Falha ao ler do sensor DHT!");
    // Mantém os valores anteriores ou usa 0.0 se for a primeira leitura falha
    // Por segurança, desliga o LED de alerta se a leitura falhar
    digitalWrite(boardLED, HIGH);
  } else {
    // Atualiza as variáveis globais com as leituras válidas
    temperatura = temp_lida;
    umidade = umid_lida;

    // Imprime os valores lidos do DHT no monitor serial
    Serial.print("Umidade: ");
    Serial.print(umidade, 1); // Imprime com 1 casa decimal
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(temperatura, 1); // Imprime com 1 casa decimal
    Serial.println(" °C");

    // Verifica se a temperatura está fora dos limites críticos e controla o LED
    if (temperatura < TEMP_CRITICA_MIN) {
      Serial.println("!!! ALERTA: TEMPERATURA EXTREMAMENTE BAIXA !!!");
      digitalWrite(boardLED, LOW); // Acende o LED
    } else if (temperatura > TEMP_CRITICA_MAX) {
      Serial.println("!!! ALERTA: TEMPERATURA EXTREMAMENTE ALTA !!!");
      digitalWrite(boardLED, LOW); // Acende o LED
    } else {
      digitalWrite(boardLED, HIGH); // Mantém o LED desligado
    }
  }

  // Imprime os valores do potenciômetro e LDR no monitor serial
  Serial.print("Potenciômetro: ");
  Serial.println(valorPot);
  Serial.print("Luminosidade (LDR): ");
  Serial.println(valorLDR);

  // Monta a URL para enviar os dados ao ThingSpeak
  // Envia os últimos valores válidos de T/H (ou 0.0 se a leitura falhou e nunca foi válida)
  // Envia sempre os valores atuais de Pot e LDR
  String url = String(THINGSPEAK_URL) + "?api_key=" + THINGSPEAK_API_KEY +
                "&field1=" + String(temperatura, 2) +  // Envia temperatura com 2 casas decimais
                "&field2=" + String(umidade, 2) +    // Envia umidade com 2 casas decimais
                "&field3=" + String(valorPot) +      // Envia valor bruto do potenciômetro
                "&field4=" + String(valorLDR);       // Envia valor bruto do LDR



  // Envia a requisição HTTP GET para o ThingSpeak
  HTTPClient http;
  http.begin(url); // Inicia a conexão HTTP
  int httpCode = http.GET(); // Envia a requisição GET

  // Verifica o código de resposta HTTP
  if (httpCode > 0) {
    Serial.print("Dados enviados para ThingSpeak. Código HTTP: ");
    Serial.println(httpCode);
  } else {
    Serial.print("Erro ao enviar dados para ThingSpeak. Código: ");
    Serial.println(http.errorToString(httpCode)); // Imprime o erro
  }

  http.end(); // Fecha a conexão HTTP

  // Aguarda 10 segundos antes da próxima leitura/envio
  delay(10000);
}

