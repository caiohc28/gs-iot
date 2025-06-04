# 🌡️ Sistema de Monitoramento de Calor Extremo para Populações Vulneráveis

Este projeto tem como objetivo **monitorar remotamente a temperatura, umidade, luminosidade e valores de um potenciômetro** utilizando um ESP32. Os dados são enviados para o **ThingSpeak**, permitindo a geração de **alertas de calor extremo**, especialmente voltados à proteção de populações vulneráveis.

---

## 📁 Estrutura do Projeto

├── src/

│ └── main.cpp # Código principal do ESP32

├── docs/

│ └── dashboard-thingspeak.png 

├── .gitignore

├── README.md


---

## ✅ Funcionalidades

- 📡 Leitura de sensores (temperatura, umidade, luminosidade e potenciômetro)
- ☁️ Envio de dados via Wi-Fi para o ThingSpeak
- 📊 Visualização gráfica em tempo real no ThingSpeak
- 🚨 Geração de alertas de temperatura crítica (baixa ou alta)

---

## ⚙️ Requisitos

- ESP32 DevKit
- Sensor DHT22 (ou DHT11)
- Sensor LDR (fotoresistor)
- Potenciômetro
- Plataforma [ThingSpeak](https://thingspeak.com/)
- IDE Arduino com as bibliotecas:
  - `WiFi.h`
  - `HTTPClient.h`
  - `DHT.h`

---

## 🔌 Ligações dos Componentes

| Componente      | Pino ESP32 |
|------------------|------------|
| DHT22            | GPIO 12    |
| Potenciômetro    | GPIO 34    |
| LDR              | GPIO 35    |
| LED onboard      | GPIO 0     |

---

## 🚀 Instalação e Execução

### 1. Clone o repositório

```bash
git clone https://github.com/caiohc28/gs-iot.git
cd GS - THERMOGUARD
