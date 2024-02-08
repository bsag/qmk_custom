
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "layout.h"
#include "g/keymap_combo.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [ALPHA] = LAYOUT_REDOX(REDOX(_RHODIUM)),
 [NUM] = LAYOUT_REDOX(REDOX(_NUM)),
 [SYM] = LAYOUT_REDOX(REDOX(_SYM)),
 [UTIL] = LAYOUT_REDOX(REDOX(_UTIL)),
 [WINNAV] = LAYOUT_REDOX(REDOX(_WINNAV)),
 [ALWAYS] = LAYOUT_REDOX(REDOX(_ALWAYS_ACC))
};

// NEEDS TO BE HERE. :/
uint16_t get_combo_term(uint16_t index, combo_t* combo) {
  switch (index) {
    default:
      return COMBO_TERM;
  }
}