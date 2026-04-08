#include <Arduino.h>

#define PIN_LED 2
#define PIN_BUTTON 4

bool ledState = LOW;        // Estado atual do LED
bool lastState = LOW;       // Estado anterior do botão
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;  // ms (ajuste se necessário)

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(115200);     // Inicializa serial para prints
  digitalWrite(PIN_LED, ledState);  // Inicializa LED
}

void loop() {
  bool currentButtonState = digitalRead(PIN_BUTTON);
  unsigned long currentTime = millis();

  // Detecta a borda de descida (HIGH → LOW: quando solta o botão)
  if (!currentButtonState && lastState && (currentTime - lastDebounceTime > debounceDelay)) {
    ledState = !ledState;
    digitalWrite(PIN_LED, ledState);
    Serial.printf("Botao solto! LED: %s\n", ledState ? "ON" : "OFF");
    lastDebounceTime = currentTime;  // Atualiza tempo
  }
  
  lastState = currentButtonState;
}