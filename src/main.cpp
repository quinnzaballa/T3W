#include <Arduino.h>
#include "T3W.h"

void setup() {
}

void loop() {
  T3W_CONFIG_INIT(5, 6, 7);
  T3W_WRS(0x00, 0x00);
  delay(50);
}