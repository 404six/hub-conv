# 🏠 Hub de Conveniência - Automação Residencial de Baixo Custo

Projeto de extensão da disciplina "Programação de Microcontroladores" do curso de Ciência da Computação.

**Autor:** Lucas Morais

---

## 🎯 Sobre o Projeto

Este projeto é um recurso educacional aberto (guiado pelo Objetivo 2 da atividade de extensão) que demonstra como construir um "Hub de Conveniência" simples. O objetivo é permitir que outros estudantes e entusiastas possam replicar um sistema básico de automação residencial para controlar dispositivos (como lâmpadas ou ventiladores) pelo celular, usando um microcontrolador ESP32 e uma interface web simples.

A situação-problema identificada foi a falta de guias completos, seguros e "passo a passo" para quem está começando e quer controlar cargas de energia do mundo real (110V/220V) de forma segura.

## 🛠️ Materiais Necessários

1.  **Microcontrolador:** 1x ESP32 (ou ESP8266 NodeMCU)
2.  **Atuador:** 1x Módulo Relé de 1, 2 ou 4 canais (que aceite 3.3V/5V)
3.  **Fios:** Jumpers (Macho-Fêmea e Macho-Macho)
4.  **Carga:** Um abajur, ventilador ou lâmpada (para o teste real)
5.  **Fonte:** Fonte de alimentação USB para o ESP32.

## 🚀 Como Usar (Guia de Replicação)

1.  **Montar o Circuito:** Conecte o Módulo Relé ao ESP32 conforme o diagrama abaixo.
2.  **Configurar a IDE:** Abra o arquivo `.ino` na sua IDE do Arduino (com o *board* do ESP32 instalado).
3.  **Alterar Credenciais:** No topo do código, altere as variáveis `ssid` e `password` para o nome e senha da **sua rede Wi-Fi**.
4.  **Carregar o Código:** Faça o upload do código para o seu ESP32.
5.  **Descobrir o IP:** Abra o **Serial Monitor** na IDE do Arduino (velocidade 115200). Após conectar ao Wi-Fi, ele mostrará o IP do servidor (ex: `Acesse o servidor em: http://192.168.1.10`).
6.  **Controlar:** Abra um navegador (no celular ou PC na *mesma rede Wi-Fi*) e digite o IP que apareceu no Serial Monitor. A página de controle será carregada.

## 🔌 Diagrama de Conexão e Simulação (Evidência)

A parte mais crítica é a conexão do Módulo Relé. O ESP32 controla o relé (baixa tensão), e o relé funciona como um interruptor para a energia da tomada (alta tensão).

* **Pino 4 (ESP32)** -> **IN** (Pino de sinal do Relé)
* **GND (ESP32)** -> **GND** (do Relé)
* **5V (ESP32)** -> **VCC** (do Relé)

**Para a parte de Alta Tensão (CUIDADO):** O relé "corta" um dos fios que vai para a tomada. Veja o diagrama no simulador.

### 💡 Simulação no Wokwi

Para provar o conceito e testar o código sem o hardware físico (e sem risco de choque), você pode usar este simulador online. Ele já está com o código e o circuito montado:

**[Clique aqui para ver a simulação do projeto no Wokwi](https://wokwi.com/projects/381530216165175297)**
