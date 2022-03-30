#include QMK_KEYBOARD_H

// Callum oneshot mods and swapper
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "caps_word.h"
#include "swapper.h"
#include "keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BKL] = LAYOUT_split_3x5_2(
			KC_Q,   KC_Y,    KC_O,    KC_U,   KC_X,        KC_G, KC_C,   KC_M,   KC_R,   KC_Z,
      HOME_H, HOME_I,  HOME_E,  HOME_A, KC_DOT,      KC_D, HOME_S, HOME_T, HOME_N, HOME_B,
			KC_J,  KC_SLSH,  KC_COMM, KC_K,   KC_QUOT,     KC_W, KC_F,   KC_L,   KC_P,   KC_V,
					                     NUM,   NAV_SPC,       KC_BSPC, SYM
							   ),

	[_DEF] = LAYOUT_split_3x5_2(
			KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y, KC_U, KC_I,    KC_O,   KC_P,
			QHOME_A, QHOME_S, QHOME_D, QHOME_F, KC_G,    KC_H, QHOME_J, QHOME_K, QHOME_L, QHOME_QUOT,
			KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
					           NUM, NAV_SPC,                 KC_BSPC, SYM
							   ),

	[_NUM] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_PERC,   KC_PLUS, KC_7, KC_8, KC_9, KC_MINS,
			KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,   KC_EQL,    KC_DOT,  KC_4, KC_5, KC_6, KC_COLN,
			KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_UNDS,   KC_ASTR, KC_1, KC_2, KC_3, KC_SLSH,
			                        KC_TRNS,    KC_TRNS,   KC_0, FUN
								),

	[_SYM] = LAYOUT_split_3x5_2(
			KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     GBPD,  KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS,
			KC_PIPE, KC_SCLN, KC_EQL, KC_COLN,  KC_TILD,     KC_NO, KC_LGUI,  KC_LALT,  KC_LCTL, KC_LSFT,
			KC_LT,   KC_GT,   KC_NO,  KC_NO,    KC_GRV,      KC_NO, PMIN,    KC_CIRC, KC_PLUS, KC_BSLS,
			                           FUN,     KC_TRNS,     KC_TRNS, KC_TRNS
								),


	[_NAV] = LAYOUT_split_3x5_2(
			SW_APP,  KC_NO,   TAB_L,  TAB_R,  KC_TAB,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,
			KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_ESC,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
			M_UNDO,  M_CUT,   M_COPY, M_PSTE, M_SAVE,    KC_NO,   ALF,     KC_NO,   KC_NO,   KC_BSPC,
			                          KC_TRNS, KC_TRNS,  WNAV, KC_TRNS
							   ),

	[_WNAV] = LAYOUT_split_3x5_2(
      RESET,    KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,     HOOK,   LHLF,  FULL,  RHLF,  KC_NO,
			KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,  W4,    W5,    W6,    KC_NO,
			TG_QWTY,  KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,     KC_NO,  W1,    W2,    W3,    KC_NO,
			                          KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS
								),

	[_FUN] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_CAPS,      KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
			KC_LSFT, KC_LCTL,  KC_LALT,   KC_LGUI,   KC_ESC,       KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
			KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,        KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
			                             KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS
								)
};

enum combo_events {
  // qwerty layer combos
  TAB_COMBO_Q,
  DEL_COMBO_Q,
  // beakl layer combos
  TAB_COMBO_B,
  DEL_COMBO_B,
  // braces
  LCBR_COMBO_B,
  LPRN_COMBO_B,
  LBRC_COMBO_B,
  RCBR_COMBO_B,
  RPRN_COMBO_B,
  RBRC_COMBO_B,
  // Other combos...
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
// qwerty combos
const uint16_t PROGMEM tab_combo_q[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM del_combo_q[] = {KC_M, KC_COMM, COMBO_END};
// beakl combos
const uint16_t PROGMEM tab_combo_b[] = {KC_COMM, KC_K, COMBO_END};
const uint16_t PROGMEM del_combo_b[] = {KC_F, KC_L, COMBO_END};
// braces - vertical combos
const uint16_t PROGMEM lcbr_combo_b[] = {KC_O, HOME_E, COMBO_END};
const uint16_t PROGMEM lprn_combo_b[] = {KC_U, HOME_A, COMBO_END};
const uint16_t PROGMEM lbrc_combo_b[] = {KC_X, KC_DOT, COMBO_END};
const uint16_t PROGMEM rcbr_combo_b[] = {KC_M, HOME_T, COMBO_END};
const uint16_t PROGMEM rprn_combo_b[] = {KC_C, HOME_S, COMBO_END};
const uint16_t PROGMEM rbrc_combo_b[] = {KC_G, KC_D, COMBO_END};

combo_t key_combos[] = {
  [TAB_COMBO_Q] = COMBO(tab_combo_q, KC_TAB),
  [DEL_COMBO_Q] = COMBO(del_combo_q, KC_DEL),
  [TAB_COMBO_B] = COMBO(tab_combo_b, KC_TAB),
  [DEL_COMBO_B] = COMBO(del_combo_b, KC_DEL),
  [LCBR_COMBO_B] = COMBO(lcbr_combo_b, KC_LCBR),
  [LPRN_COMBO_B] = COMBO(lprn_combo_b, KC_LPRN),
  [LBRC_COMBO_B] = COMBO(lbrc_combo_b, KC_LBRC),
  [RCBR_COMBO_B] = COMBO(rcbr_combo_b, KC_RCBR),
  [RPRN_COMBO_B] = COMBO(rprn_combo_b, KC_RPRN),
  [RBRC_COMBO_B] = COMBO(rbrc_combo_b, KC_RBRC),
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
