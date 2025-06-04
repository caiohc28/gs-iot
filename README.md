# Projeto IoT - Monitoramento de Temperatura, Umidade e Luminosidade com ESP32, DHT11 e LDR 🌡️💧☀️

Este projeto utiliza um **ESP32** com os sensores **DHT11** (temperatura e umidade), LED para alertas de temperaturas extremas e **LDR** para monitoramento da luminosidade ambiental, além de um potenciômetro para ajuste de frequência. Os dados são enviados via Wi-Fi para a plataforma **ThingSpeak**, onde podem ser visualizados em tempo real.

---

## 🚀 Objetivo

Monitorar o ambiente com os seguintes sensores:
- **Temperatura e Umidade** com DHT11
- **Luminosidade** com LDR (Light Dependent Resistor)
- **Alertas** com LED
- **Frequência** com potenciômetro
  
Todos os dados são enviados à nuvem via ThingSpeak, permitindo visualização remota e análise gráfica.

---

## 🛠️ Tecnologias Utilizadas

- ESP32 DevKit
- Sensor DHT11
- Sensor LDR (com resistor de pull-down)
- Potenciômetro
- LED
- Arduino IDE
- Bibliotecas `DHT.h`, `ThingSpeak.h`, `WiFi.h`
- Plataforma ThingSpeak

---

## 📷 Imagens do Projeto

### Montagem física:
![image](https://github.com/user-attachments/assets/7dbf8d19-5569-46fe-a422-8c09e63807ae)



### Dashboard no ThingSpeak:
![image](https://github.com/user-attachments/assets/95ff24a5-1e57-4e9f-87e5-0b16fc97cf0f)



---

## 🧠 Funcionamento do Projeto

1. O ESP32 conecta-se à rede Wi-Fi.
2. Lê os dados:
   - Temperatura e umidade via sensor DHT11
   - Nível de luminosidade via LDR (valor analógico)
   - A frequência utilizada com o potenciômetro
   - Alertas de temperaturas extremas com o LED
3. Envia os dados para o ThingSpeak utilizando a API Key do canal.
4. O ThingSpeak armazena e exibe os dados em tempo real.

---

## 🧪 Como Executar

### 1.1 Clonagem do repositório (Caso não rode pelo VSCode, teste por aqui: https://wokwi.com/projects/432777992511432705)

``
git clone https://github.com/caiohc28/gs-iot.git
``

``
cd gs-iot
``

### 1.2 Acessar ThingSpeak
``
https://thingspeak.com/channels/2980081
``



### 2. Bibliotecas necessárias

- `DHT sensor library` (Adafruit)
- `Adafruit Unified Sensor`
- `ThingSpeak`
- `WiFi.h`


### 3. Configurar o código `.ino`

No código, altere:

```cpp
const char* writeAPIKey = "SUA_WRITE_API_KEY"; --Caso queira a resposta indo para sua própria API
const char* ID = "ID_DO_GRUPO";
const char* moduleID = "ID_ESP32";
