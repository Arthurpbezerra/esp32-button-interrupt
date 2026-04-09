#include <Arduino.h>               // base Arduino: setup/loop, millis, pinMode...
#include "app/pins.h"              // PIN_LED, PIN_BUTTON, DEBOUNCE_MS
#include "button/button.h"         // Button, ButtonEvent, buttonInit, buttonUpdate

// Regra elétrica do LED.
// true  = LED liga com HIGH (ativo alto)
// false = LED liga com LOW  (ativo baixo)
static constexpr bool LED_ACTIVE_HIGH = true;

// Estado do LED em nível lógico (intenção), não em nível elétrico.
static bool ledOn = false;

// Instância do botão (guarda estado interno do debounce/FSM)
static Button btn;

// Função pequena para escrever no pino considerando LED ativo alto/baixo.
static void writeLed(bool on) {
  // Se LED é ativo alto: on -> HIGH, off -> LOW
  // Se LED é ativo baixo: on -> LOW,  off -> HIGH
  const uint8_t level = LED_ACTIVE_HIGH
    ? (on ? HIGH : LOW)
    : (on ? LOW  : HIGH);

  digitalWrite(PIN_LED, level);
}

void setup() {
  // Configura o pino do LED como saída.
  pinMode(PIN_LED, OUTPUT);

  // Configura o pino do botão.
  // Se você usa pulldown externo (seu caso no Wokwi anterior), fica INPUT.
  // Se você for usar pull-up interno com botão no GND, seria INPUT_PULLUP.
  pinMode(PIN_BUTTON, INPUT);

  // Abre UART para logs.
  Serial.begin(115200);

  // Estado inicial determinístico.
  ledOn = false;
  writeLed(ledOn);

  // Inicializa o módulo do botão (captura estado inicial e tempos).
  buttonInit(btn);
}

void loop() {
  // Pega tempo uma vez por ciclo (boa prática).
  const uint32_t now = millis();

  // Atualiza máquina de estados do botão e recebe evento, se houver.
  const ButtonEvent ev = buttonUpdate(btn, now);

  // Para "toggle" profissional, escolha uma borda:
  // - Pressed: alterna quando pressiona (recomendado).
  // - Released: alterna quando solta (menos comum).
  if (ev == ButtonEvent::Pressed) {
    ledOn = !ledOn;                // alterna estado lógico
    writeLed(ledOn);               // aplica ao hardware

    // Log com timestamp e estado.
    Serial.printf("[%lu] Pressed -> LED: %s\r\n",
                  (unsigned long)now,
                  ledOn ? "ON" : "OFF");
  }

  // Se você quiser logar soltura também (sem alterar LED), pode:
  // if (ev == ButtonEvent::Released) { Serial.printf(...); }
}