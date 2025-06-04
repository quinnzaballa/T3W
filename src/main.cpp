#include <Arduino.h>
#include "T3W.h"

void setup() {
  T3W_CONFIG_INIT(5, 6, 7);
  T3W_WRS(0x11, 0x22);
}

void loop() {
  delay(100);
}