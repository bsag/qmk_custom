#include "layermodes.h"
#include "layout.h"

static uint16_t num_word_timer;
static bool _num_word_enabled = false;

bool num_word_enabled(void) { return _num_word_enabled; }

void enable_num_word(void) {
  _num_word_enabled = true;
  layer_on(NUM);
}

void disable_num_word(void) {
  _num_word_enabled = false;
  layer_off(NUM);
}

void process_num_word_activation(const keyrecord_t *record) {
  if (record->event.pressed) {
    layer_on(NUM);
    num_word_timer = timer_read();
  } else {
    if (timer_elapsed(num_word_timer) < TAPPING_TERM) {
      // Tapping enables NUMWORD
      _num_word_enabled = true;
    } else {
      // Holding turns off NUM when released
      layer_off(NUM);
    }
  }
}

void process_num_word(uint16_t keycode, const keyrecord_t *record) {
  if (_num_word_enabled) {
  // keycode = keycode & 0xFF;
    switch (keycode) {
      // Don't disable for those keycodes
      case ___1___:
      case ___2___:
      case ___3___:
      case ___4___:
      case ___5___:
      case ___6___:
      case ___7___:
      case ___8___:
      case ___9___:
      case ___0___:
      case KC_PERC:      
      case KC_COMM:
      case KC_DOT:  // still a . stops!?
      case KC_SLSH:
      case KC_MINS:
      case KC_ASTR:
      case KC_PLUS:
      case KC_EQL:
      case KC_F18:
      case KC_F19:
      case KC_ENT:
      case KC_MEH:
      case KC_UNDS:
      case KC_BSPC:
      case OS_LSFT:
      case OS_LALT:
      case OS_LCTL:
      case OS_LGUI:
        break;
      default:
        // All other keys disable the layer mode on keyup.      
        if (!record->event.pressed) {
          disable_num_word();
        }
    }
  }
}
