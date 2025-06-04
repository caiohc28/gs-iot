# Projeto IoT - Monitoramento de Temperatura, Umidade e Luminosidade com ESP32, DHT11 e LDR 🌡️💧☀️

Este projeto utiliza um **ESP32** com os sensores **DHT11** (temperatura e umidade) e **LDR** (luminosidade) para monitoramento ambiental. Os dados são enviados via Wi-Fi para a plataforma **ThingSpeak**, onde podem ser visualizados em tempo real.

---

## 🚀 Objetivo

Monitorar o ambiente com os seguintes sensores:
- **Temperatura e Umidade** com DHT11
- **Luminosidade** com LDR (Light Dependent Resistor)

Todos os dados são enviados à nuvem via ThingSpeak, permitindo visualização remota e análise gráfica.

---

## 🛠️ Tecnologias Utilizadas

- ESP32 DevKit
- Sensor DHT11
- Sensor LDR (com resistor de pull-down)
- Arduino IDE
- Bibliotecas `DHT.h`, `ThingSpeak.h`, `WiFi.h`
- Plataforma ThingSpeak

---

## 📷 Imagens do Projeto

### Montagem física:
![image](https://github.com/user-attachments/assets/1ff1ad90-5645-454c-bf6a-41732cc30ef0)


### Dashboard no ThingSpeak:
![image](https://github.com/user-attachments/assets/c44ce70e-685a-4725-bca2-1093800f5f32)


---

## 🧠 Funcionamento do Projeto

1. O ESP32 conecta-se à rede Wi-Fi.
2. Lê os dados:
   - Temperatura e umidade via sensor DHT11
   - Nível de luminosidade via LDR (valor analógico)
3. Envia os dados para o ThingSpeak utilizando a API Key do canal.
4. O ThingSpeak armazena e exibe os dados em tempo real.

---

## 🧪 Como Executar

### 1. Instalação do Arduino IDE

Baixe o Arduino IDE: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

### 2. Bibliotecas necessárias

- `DHT sensor library` (Adafruit)
- `Adafruit Unified Sensor`
- `ThingSpeak`
- `WiFi.h`


### 3. Configurar o código `.ino`

No código, altere:

```cpp
const char* writeAPIKey = "SUA_WRITE_API_KEY";
const char* ID = "ID_DO_GRUPO";
const char* moduleID = "ID_ESP32";
