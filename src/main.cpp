#include <Arduino.h>


// static
static constexpr uint8_t PIN_LED = 2;
static constexpr uint8_t PIN_BUTTON = 4;
static constexpr bool BUTTON_ACTIVE_LOW = false;
static constexpr bool LED_ACTIVE_HIGH = true; // o led liga se for HIGH, caso for false entao o led liga se entrada for LOW
static constexpr uint32_t DEBOUNCE_MS = 100;

static bool ledState = false;        // Estado atual do LED     


// functions
static inline bool readButtonPressed();
static void writeLed(bool on); // digitalWrite mas considera


void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(115200);     // Inicializa serial para prints
  writeLed(false);  // Inicializa LED
}

void loop() {
  bool isPressed = readButtonPressed();
  static bool handledPress = false;
  unsigned long currentTime = millis();
  static unsigned long lastDebounceTime = 0;

  // Detecta mudança (debounce)
  static bool lastReading = false;

  if (isPressed != lastReading) {
    lastDebounceTime = currentTime;
  }

  if ((currentTime - lastDebounceTime) > DEBOUNCE_MS) {

    // Só executa UMA vez enquanto estiver pressionado
    if (isPressed && !handledPress) {
      ledState = !ledState;
      writeLed(ledState);
      Serial.printf("[%lu] Pressed! LED: %s\n",currentTime,ledState ? "ON" : "OFF");
      handledPress = true;
      
    }

    // Quando solta o botão, libera para próximo clique
    if (!isPressed) {
      handledPress = false;
    }
  }

  lastReading = isPressed;
}




static inline bool readButtonPressed(){
  bool raw = digitalRead(PIN_BUTTON);
  return BUTTON_ACTIVE_LOW ? (raw == LOW): (raw == HIGH);
}

static void writeLed(bool on) {
  if (LED_ACTIVE_HIGH) {
    digitalWrite(PIN_LED, on ? HIGH : LOW);
  } else {
    digitalWrite(PIN_LED, on ? LOW : HIGH);
  }
}
/*

Tabela-verdade (exemplos)
Vamos testar 4 cenários:

Caso 1: LED_ACTIVE_HIGH = true e on = true
cai no primeiro ramo: (on ? HIGH : LOW) = HIGH
Resultado: digitalWrite(PIN_LED, HIGH) (liga)

Caso 2: LED_ACTIVE_HIGH = true e on = false
(on ? HIGH : LOW) = LOW
Resultado: digitalWrite(PIN_LED, LOW) (desliga)

Caso 3: LED_ACTIVE_HIGH = false e on = true
cai no segundo ramo: (on ? LOW : HIGH) = LOW
Resultado: digitalWrite(PIN_LED, LOW) (liga, porque é ativo em LOW)

Caso 4: LED_ACTIVE_HIGH = false e on = false
(on ? LOW : HIGH) = HIGH
Resultado: digitalWrite(PIN_LED, HIGH) (desliga)


*/