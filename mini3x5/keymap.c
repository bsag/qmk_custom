#include QMK_KEYBOARD_H

// Callum oneshot mods and swapper
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "caps_word.h"
#include "swapper.h"
#include "keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // PHD = Platinum Hands Down layout
   [_PHD] = LAYOUT_split_3x5_2(
                              KC_J,    KC_G,    KC_H,    KC_P,    KC_V,      KC_MINS, KC_DOT,  KC_COMM, KC_QUOT, KC_DQUO,
                              HHOME_R, HHOME_S, HHOME_N, HHOME_T, KC_B,      KC_SLSH, HHOME_A, HHOME_E, HHOME_C, HHOME_I,
                              KC_X,    KC_F,    KC_M,    KC_D,    KC_K,      KC_BSPC, KC_U,    KC_O,    KC_W,    KC_Y,
                                                         NUM,   NAV_L,       KC_SPC, SYM
                              ),
  // QWERTY layout
  [_DEF] = LAYOUT_split_3x5_2(
                              KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y, KC_U, KC_I,    KC_O,   KC_P,
                              QHOME_A, QHOME_S, QHOME_D, QHOME_F, KC_G,    KC_H, QHOME_J, QHOME_K, QHOME_L, QHOME_QUOT,
                              KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                              NUM, NAV_SPC,                 KC_BSPC, SYM
                              ),

  [_NUM] = LAYOUT_split_3x5_2(
                              KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_PERC,   KC_MINS, KC_7, KC_8, KC_9, KC_PLUS,
                              KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_EQL,    KC_SLSH,  KC_4, KC_5, KC_6, KC_ASTR,
                              KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_UNDS,   KC_DOT, KC_1, KC_2, KC_3, KC_COLN,
                              KC_TRNS,    KC_TRNS,   KC_0, FUN
                              ),

  [_SYM] = LAYOUT_split_3x5_2(
                              KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     GBPD,  KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS,
                              KC_PIPE, KC_SCLN, KC_EQL, KC_COLN,  KC_TILD,     KC_NO, KC_LSFT,  KC_LGUI,  KC_LALT, KC_LCTL,
                              KC_LT,   KC_GT,   KC_NO,  KC_NO,    KC_GRV,      KC_NO, PMIN,    KC_CIRC, KC_PLUS, KC_BSLS,
                              FUN,     KC_TRNS,     KC_TRNS, KC_TRNS
                              ),


  [_NAV] = LAYOUT_split_3x5_2(
                              SW_APP,  KC_NO,   TAB_L,  TAB_R,  KC_TAB,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,
                              KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_ESC,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
                              M_UNDO,  M_CUT,   M_COPY, M_PSTE, M_SAVE,     C(KC_BSPC),   ALF, C(KC_C), KC_NO, A(KC_DEL),
                              KC_TRNS, KC_TRNS,  WNAV, KC_TRNS
                              ),

  [_WNAV] = LAYOUT_split_3x5_2(
                               RESET,    KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,     HOOK,   LHLF,  FULL,  RHLF,  KC_NO,
                               TG_PHD,    KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,  W4,    W5,    W6,    KC_NO,
                               TG_QWTY,  KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,     KC_NO,  W1,    W2,    W3,    KC_NO,
                               KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS
                               ),

  [_FUN] = LAYOUT_split_3x5_2(
                              KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_CAPS,      KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
                              KC_LCTL, KC_LALT,  KC_LGUI,   KC_LSFT,   KC_ESC,       KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
                              KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,        KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
                              KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS
                              )
};

enum combo_events {
  // qwerty layer combos
  TAB_COMBO_Q,
  DEL_COMBO_Q,
  // hands down combos
  TAB_COMBO_P,
  Q_COMBO_P,
  Z_COMBO_P,
  // braces
  LCBR_COMBO_P,
  LPRN_COMBO_P,
  LBRC_COMBO_P,
  RCBR_COMBO_P,
  RPRN_COMBO_P,
  RBRC_COMBO_P,
  // Other combos...
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
// qwerty combos
const uint16_t PROGMEM tab_combo_q[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM del_combo_q[] = {KC_M, KC_COMM, COMBO_END};
// hands down combos
const uint16_t PROGMEM tab_combo_p[] = {KC_M, KC_D, COMBO_END};
const uint16_t PROGMEM q_combo_p[] = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM z_combo_p[] = {KC_W, KC_Y, COMBO_END};
// braces - vertical combos
const uint16_t PROGMEM lcbr_combo_p[] = {KC_H, HHOME_N, COMBO_END};
const uint16_t PROGMEM lprn_combo_p[] = {KC_P, HHOME_T, COMBO_END};
const uint16_t PROGMEM lbrc_combo_p[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM rbrc_combo_p[] = {KC_MINS, KC_SLSH, COMBO_END};
const uint16_t PROGMEM rprn_combo_p[] = {KC_DOT, HHOME_A, COMBO_END};
const uint16_t PROGMEM rcbr_combo_p[] = {KC_COMM, HHOME_E, COMBO_END};

combo_t key_combos[] = {
  [TAB_COMBO_Q] = COMBO(tab_combo_q, KC_TAB),
  [DEL_COMBO_Q] = COMBO(del_combo_q, KC_DEL),
  [TAB_COMBO_P] = COMBO(tab_combo_p, KC_TAB),
  [Q_COMBO_P] = COMBO(q_combo_p, KC_Q),
  [Z_COMBO_P] = COMBO(z_combo_p, KC_Z),
  [LCBR_COMBO_P] = COMBO(lcbr_combo_p, KC_LCBR),
  [LPRN_COMBO_P] = COMBO(lprn_combo_p, KC_LPRN),
  [LBRC_COMBO_P] = COMBO(lbrc_combo_p, KC_LBRC),
  [RCBR_COMBO_P] = COMBO(rcbr_combo_p, KC_RCBR),
  [RPRN_COMBO_P] = COMBO(rprn_combo_p, KC_RPRN),
  [RBRC_COMBO_P] = COMBO(rbrc_combo_p, KC_RBRC),

};

bool sw_app_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_caps_word(keycode, record)) { return false; }

  update_swapper(
                 &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
                 keycode, record
                 );

  return true;
}

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     return update_tri_layer_state(state, _LMOD, _RMOD, _NUM); */
/* } */
