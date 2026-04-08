# ESP32 Button Interrupt

Um projeto simples para ESP32 que demonstra como alternar o estado de um LED usando um botão com debouncing não-bloqueante. O LED muda de estado apenas quando o botão é solto, evitando alternâncias indesejadas durante o pressionamento.

## Escopo do Projeto

Este projeto foi desenvolvido para fins educacionais e demonstra conceitos fundamentais de programação embarcada no ESP32:
- **Detecção de botão**: Leitura digital com pull-down externo.
- **Debouncing**: Técnica não-bloqueante para lidar com oscilações do botão (bouncing).
- **Controle de LED**: Alternância de estado (ON/OFF) por clique.
- **Debugging**: Saída serial para monitoramento.
- **Simulação**: Compatível com Wokwi para testes virtuais.

O código é otimizado para ser eficiente, legível e escalável, seguindo boas práticas do Arduino Framework.

## Funcionalidades

- Alterna o LED (GPIO 2) ao soltar o botão (GPIO 4).
- Debouncing ajustável (padrão: 200ms) para evitar detecções falsas.
- Inicialização serial para logs de debug.
- Compatível com simulação no Wokwi e upload físico no ESP32.

## Hardware Necessário

- **ESP32 DevKit C V4** (ou similar).
- **Botão pushbutton** (conectado a GPIO 4 com resistor pull-down de 1kΩ).
- **LED vermelho** (conectado a GPIO 2 com resistor limitador de corrente de 1kΩ).
- **Protoboard** e jumpers para conexões.

Veja o diagrama em `diagram.json` para o esquema completo.

## Software Necessário

- **VS Code** com extensão PlatformIO.
- **Arduino Framework** (incluído no PlatformIO).
- **Wokwi** (para simulação online, opcional).

## Como Instalar e Configurar

1. **Clone o repositório**: