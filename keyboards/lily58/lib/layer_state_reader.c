
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define _QWERTY 0
#define _SYMBOL (1 << 1)
#define _MOVING (1 << 2)
#define _TENKEY (1 << 3)
#define L_ADJUST_TRI (_TENKEY | _MOVING | _SYMBOL)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case _QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
    break;
  case _MOVING:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Moving");
    break;
  case _SYMBOL:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symbols");
    break;
  case _TENKEY:
  case L_ADJUST_TRI:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: 10Key");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
