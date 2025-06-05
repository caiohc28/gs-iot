# Projeto IoT - Monitoramento de Temperatura, Umidade e Luminosidade com ESP32, DHT11 e LDR 🌡️💧☀️

Este projeto utiliza um **ESP32** com os sensores **DHT11** (temperatura e umidade), LED para alertas de temperaturas extremas e **LDR** para monitoramento da luminosidade ambiental, além de um potenciômetro para definir o limite de temperatura sem necessidade de alerta. Os dados são enviados via Wi-Fi para a plataforma **ThingSpeak**, onde podem ser visualizados em tempo real.

---

## 🚀 Objetivo

Monitorar o ambiente com os seguintes sensores:
- **Temperatura e Umidade** com DHT11
- **Luminosidade** com LDR (Light Dependent Resistor)
- **Alertas** com LED
- **Limite de temperatura** com potenciômetro
  
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
![image](https://github.com/user-attachments/assets/bb7f3ead-b214-4766-84c3-8d05875de7d8)

## Fluxo de Dados
ESP32 → Sensores → Processamento → ThingSpeak → Dashboard

## Exemplo de Dados Coletados
| Timestamp | Temp(°C) | Umidade(%) | Luminosidade | Status |
|-----------|----------|------------|--------------|---------|
| 14:30:25  | 28.5     | 65         | 450          | Normal  |
| 14:31:25  | 35.2     | 58         | 480          | Alerta  |

## Troubleshooting
- **WiFi não conecta**: Verificar SSID/senha
- **Sensor não responde**: Verificar conexões DHT11
- **ThingSpeak erro**: Validar API Key


### Dashboard no ThingSpeak:
![image](https://github.com/user-attachments/assets/6c66d260-83c2-4517-b3dc-592efb64537c)




---

## 🧠 Funcionamento do Projeto

1. O ESP32 conecta-se à rede Wi-Fi.
2. Lê os dados:
   - Temperatura e umidade via sensor DHT11
   - Nível de luminosidade via LDR (valor analógico)
   - O limite de temperatura antes de ser necessário um alerta via potenciômetro
   - Alertas de temperaturas extremas com o LED
3. Envia os dados para o ThingSpeak utilizando a API Key do canal.
4. O ThingSpeak armazena e exibe os dados em tempo real.

---

## 🧪 Como Executar

### 1.1 Clonagem do repositório 
(Caso não rode pelo VSCode, teste por aqui: https://wokwi.com/projects/432777992511432705)

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

Caso queira testar no seu próprio ThingSpeak, no código, altere:

```cpp
unsigned long channelID = 2980081; // Substitua pelo seu Channel ID
const char* writeAPIKey = "SUA_WRITE_API_KEY";
