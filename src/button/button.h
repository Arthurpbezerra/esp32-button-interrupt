#pragma once
#include <Arduino.h>

enum class ButtonEvent : uint8_t {
    None = 0, // nada aconteceu
    Pressed, // transicao para pressionado 
    Released, // transicao para solto
};

struct Button {
    bool lastRawPressed = false; // ultima leitura do botao (raw)
    bool stablePressed = false; // estado ja debounced 
    uint32_t lastChangeMs = 0; // instante da ultima mudança do raw
};

void buttonInit(Button& b); // inicializa o botao no setup

// Atualiza o estado com base no tempo atual 
// Retorna evento somente quando ocorre transição estável
ButtonEvent buttonUpdate(Button& b, uint32_t now); 

// Consulta opcional do estado estável atual
bool buttonIsPressedStable (const Button& b);