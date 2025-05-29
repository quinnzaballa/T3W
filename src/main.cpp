#include <Arduino.h>
#include "T3W.h"

void setup() {
}

void loop() {
  T3W_CONFIG_INIT(37, 6, 7);
  delay(50);
}