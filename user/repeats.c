#include "layout.h"
#include "features/achordion.h"

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  if ((mods & ~MOD_MASK_SHIFT) == 0) {
    switch (keycode) {
      case ___A___:
        return KC_O;
      case ___B___:
        return KC_N;  // TODO BEFORE
      case ___C___: // C
        return KC_Y;
      case ___D___:
        return KC_Y;
      case ___E___:
        return KC_U;
      case ___F___:
        return KC_Y;
      case ___N___:
        return KC_F;  // Fuenf!
      case ___G___:
        return KC_Y;
      case ___H___:
        return KC_Y;
      case ___I___:
        return MG_ION;
      case ___J___:
        return MG_UST;
      case ___K___:
        return KC_S;
      case ___L___:
        return KC_K;
      case ___M___:
        return KC_T; // AMT and co in Germann ;)
      case ___O___:
        return KC_A;
      case ___P___:
        return KC_Y;
      case ___R___:
        return KC_L;
      case ___S___:
        return KC_K;
      case ___T___:
        return KC_M; //ment does not work that well with german
      case ___U___:
        return KC_E;
      case ___V___:
        return MG_VER;
      case ___W___:
        return KC_Y;
      case ___Y___:
        return KC_P;
      case KC_EQL:
        return KC_GT;
      case KC_LPRN:
        return KC_RPRN;
      case KC_MINS:
        return KC_GT;
      case NAV_SPC:
        return MG_THE;
      case KC_ESC:
        return KC_COLON;
      case KC_COMM:
      case KC_DOT:
        return M_SENTENCE; // ODO does not work!
      case KC_1 ... KC_0:
        return KC_DOT;      
  
      case KC_GT:
        return KC_MINS;
      case KC_PIPE:
        return KC_GT;
      case KC_PAST:
        return KC_GT;
      default:
        return KC_N;
    }
  } else if ((mods & MOD_MASK_CTRL)) {
    switch (keycode) {
      case KC_A:  // Ctrl+A -> Ctrl+K
        return C(KC_K);
      case KC_C:  // Ctrl+C -> Ctrl+C
        return C(KC_C);
    }
  }
  return KC_TRNS;
}


// reeat
bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
        case REP_SFT:
            return false;
        case KC_A ... KC_Y:
              if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
                *remembered_mods &= ~MOD_MASK_SHIFT;
              }
          break;
         
    }
    return true;
}

bool get_repeat_key_eligible_user(uint16_t keycode, keyrecord_t *record,
                                  uint8_t *remembered_mods) {
  switch (keycode) {
    case REP_SFT:
      return false;
    // Forget Shift on letter keys A-Y when Shift or AltGr are the only mods.
    // Exceptionally, I want to remember Shift on Z for "ZZ" in Vim.
    case KC_A ... KC_Y:
      if ((*remembered_mods & ~(MOD_MASK_SHIFT | MOD_BIT(KC_RALT))) == 0) {
        *remembered_mods &= ~MOD_MASK_SHIFT;
      }
      break;
  }

  return true;
}


