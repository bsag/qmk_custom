#include QMK_KEYBOARD_H

// Callum swapper
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "oneshot.h"
#include "swapper.h"
#include "keycodes.h"
#include "layer_lock.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Colemak Mod-DH layout
  [_CDH] = LAYOUT_split_3x5_2(
                              KC_Q, KC_W, KC_F, KC_P, KC_B,                KC_J, KC_L, KC_U,    KC_Y,   KC_QUOT,
                              KC_A, KC_R, KC_S, KC_T, KC_G,                KC_M, KC_N, KC_E,    KC_I,   KC_O,
                              KC_Z, KC_X, KC_C, KC_D, KC_V,                KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,
                                                 NAV, OSM(MOD_LSFT),       KC_SPC, NUM
                              ),


  [_NUM] = LAYOUT_split_3x5_2(
                           KC_LBRC,  KC_7, KC_8, KC_9, KC_RBRC,        KC_NO,   GBPD,    PMIN,    KC_NO,   KC_BSPC,
                           KC_SCLN,  KC_4, KC_5, KC_6, KC_EQL,         KC_NO,   OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL,
                           KC_GRV,   KC_1, KC_2, KC_3, KC_MINS,        KC_NO,   LLOCK,   KC_NO,   KC_BSLS, KC_SLSH,
                                                 KC_DOT,  KC_0,        KC_SPC,  KC_TRNS
                              ),

  [_NAV] = LAYOUT_split_3x5_2(
                              SW_APP,  KC_NO,   TAB_L,  TAB_R,   KC_TAB,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_BSPC,
                              OS_CTRL, OS_ALT,  OS_CMD, OS_SHFT, M_SAVE,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TAB,
                              M_UNDO,  M_CUT,   M_COPY,  LLOCK,  M_PSTE,      WS_L,    W_L,     W_R,     WS_R,    KC_DEL,
                                                        KC_TRNS, KC_TRNS,     LAU, KC_TRNS
                              ),

  [_FUN] = LAYOUT_split_3x5_2(
                              RESET,   KC_VOLD,  KC_MUTE,  KC_VOLU,   KC_CAPS,      KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
                              OS_CTRL, OS_ALT,   OS_CMD,   OS_SHFT,   KC_NO,        KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
                              KC_NO,   KC_MPRV,  KC_MPLY,  KC_MNXT,   KC_NO,        KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
                                                           KC_TRNS,   KC_TRNS,      KC_SPC, KC_TRNS
                              )
};

enum combo_events {
   // punctuation combos
   MINS_COMBO, // C+D
   USCR_COMBO, // H+,,
   SCLN_COMBO, // .+/
   // braces
   LCBR_COMBO, // F+S
   LPRN_COMBO, // P+T
   LBRC_COMBO, // B+G
   RCBR_COMBO, // U+E
   RPRN_COMBO, // L+N
   RBRC_COMBO, // J+M
   // Other combos...
   COMBO_LENGTH
 };
 uint16_t COMBO_LEN = COMBO_LENGTH;
// punctuation combos
 const uint16_t PROGMEM mins_combo[] = {KC_C, KC_D, COMBO_END};
 const uint16_t PROGMEM uscr_combo[] = {KC_H, KC_COMM, COMBO_END};
 const uint16_t PROGMEM scln_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
 // braces - vertical combos
 const uint16_t PROGMEM lcbr_combo[] = {KC_F, KC_S, COMBO_END};
 const uint16_t PROGMEM lprn_combo[] = {KC_P, KC_T, COMBO_END};
 const uint16_t PROGMEM lbrc_combo[] = {KC_B, KC_G, COMBO_END};
 const uint16_t PROGMEM rbrc_combo[] = {KC_J, KC_M, COMBO_END};
 const uint16_t PROGMEM rprn_combo[] = {KC_L, KC_N, COMBO_END};
 const uint16_t PROGMEM rcbr_combo[] = {KC_U, KC_E, COMBO_END};

 combo_t key_combos[] = {
   [MINS_COMBO] = COMBO(mins_combo, KC_MINS),
   [USCR_COMBO] = COMBO(uscr_combo, LSFT(KC_MINS)),
   [SCLN_COMBO] = COMBO(scln_combo, KC_SCLN),
   [LCBR_COMBO] = COMBO(lcbr_combo, KC_LCBR),
   [LPRN_COMBO] = COMBO(lprn_combo, KC_LPRN),
   [LBRC_COMBO] = COMBO(lbrc_combo, KC_LBRC),
   [RCBR_COMBO] = COMBO(rcbr_combo, KC_RCBR),
   [RPRN_COMBO] = COMBO(rprn_combo, KC_RPRN),
   [RBRC_COMBO] = COMBO(rbrc_combo, KC_RBRC),
 };

// caps word setup
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_MINS:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case NAV:
    case NUM:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case NAV:
    case NUM:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}


bool sw_app_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

  update_swapper(
                 &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
                 keycode, record
                 );

  update_oneshot(
                 &os_shft_state, KC_LSFT, OS_SHFT,
                 keycode, record
                 );

  update_oneshot(
                 &os_ctrl_state, KC_LCTL, OS_CTRL,
                 keycode, record
                 );

  update_oneshot(
                 &os_alt_state, KC_LALT, OS_ALT,
                 keycode, record
                 );

  update_oneshot(
                 &os_cmd_state, KC_LCMD, OS_CMD,
                 keycode, record
                 );

  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUM, _NAV, _FUN);
}
