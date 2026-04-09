#include "button.h"
#include "../app/pins.h"          // usa PIN_BUTTON e DEBOUNCE_MS

// Regra elétrica do botão:
// false = ativo em HIGH (pressionado => HIGH), típico com pulldown externo.
// true  = ativo em LOW (pressionado => LOW), típico com INPUT_PULLUP.
static constexpr bool BUTTON_ACTIVE_LOW = false;

// Lê o pino e converte para semântica:
// retorna true quando "está pressionado", independente de HIGH/LOW elétrico.
static inline bool readButtonPressedRaw() {
  const int raw = digitalRead(PIN_BUTTON);      // leitura elétrica do GPIO
  return BUTTON_ACTIVE_LOW ? (raw == LOW)       // se ativo em LOW, LOW = pressionado
                           : (raw == HIGH);     // se ativo em HIGH, HIGH = pressionado
}

void buttonInit(Button& b) {
  b.lastRawPressed = readButtonPressedRaw();    // captura estado inicial cru
  b.stablePressed = b.lastRawPressed;           // inicia estável igual ao cru
  b.lastChangeMs = millis();                    // marca referência de tempo
}

ButtonEvent buttonUpdate(Button& b, uint32_t now) {
  const bool rawPressed = readButtonPressedRaw(); // leitura instantânea deste ciclo

  // 1) Se o raw mudou, reinicia janela de debounce.
  // Ainda não confirma evento, só marca "mudou agora".
  if (rawPressed != b.lastRawPressed) {
    b.lastRawPressed = rawPressed;
    b.lastChangeMs = now;
  }

  // 2) Se ficou sem mudar por DEBOUNCE_MS, então é estado estável.
  // Só gera evento quando o estado estável realmente muda.
  if ((now - b.lastChangeMs) >= DEBOUNCE_MS &&
      b.stablePressed != b.lastRawPressed) {
    b.stablePressed = b.lastRawPressed;             // confirma novo estado estável
    return b.stablePressed ? ButtonEvent::Pressed   // se ficou true, evento Pressed
                           : ButtonEvent::Released; // se ficou false, evento Released
  }

  return ButtonEvent::None; // nada mudou de forma estável neste ciclo
}

bool buttonIsPressedStable(const Button& b) {
  return b.stablePressed; // acesso de leitura ao estado debounced
}