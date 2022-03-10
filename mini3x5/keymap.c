#include QMK_KEYBOARD_H

// Callum oneshot mods and swapper
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "caps_word.h"
#include "oneshot.h"
#include "swapper.h"
#include "keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BKL] = LAYOUT_split_3x5_2(
			KC_Q,  KC_H,    KC_O,    KC_U, KC_X,         KC_G, KC_C, KC_R,    KC_F,   KC_Z,
			KC_Y,  KC_I,    KC_E,    KC_A, KC_DOT,       KC_D, KC_S, KC_T,    KC_N,   KC_B,
			KC_J,  KC_SLSH, KC_COMM, KC_K, KC_QUOT,      KC_W, KC_M, KC_L,    KC_P,   KC_V,
					                     NUM, NAV_SPC,       KC_LSFT, SYM
							   ),

	[_DEF] = LAYOUT_split_3x5_2(
			KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,   KC_P,
			KC_A, KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   KC_QUOT,
			KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
					           NUM, NAV_SPC,     KC_LSFT, SYM
							   ),

	[_NUM] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,   KC_NO,  KC_COLN,  KC_PERC,   KC_PLUS, KC_7, KC_8, KC_9, KC_MINS,
			OS_SHFT, OS_CTRL, OS_ALT, OS_CMD,   KC_EQL,    KC_DOT,  KC_4, KC_5, KC_6, KC_0,
			KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_UNDS,   KC_ASTR, KC_1, KC_2, KC_3, KC_SLSH,
			                        KC_TRNS,    KC_TRNS,   KC_TRNS, FUN
								),

	[_SYM] = LAYOUT_split_3x5_2(
			KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     GBPD,  KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS,
			KC_PIPE, KC_SCLN, KC_EQL, KC_COLN,  KC_TILD,     KC_NO, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
			KC_LT,   KC_GT,   KC_NO,  KC_NO,    KC_GRV,      KC_NO, PMIN,    KC_CIRC, KC_PLUS, KC_BSLS,
			                           FUN,     KC_TRNS,     CLEAR, KC_TRNS
								),


	[_NAV] = LAYOUT_split_3x5_2(
			SW_APP,  KC_NO,   TAB_L,  TAB_R,  KC_TAB,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,
			OS_SHFT, OS_CTRL, OS_ALT, OS_CMD, KC_ESC,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
			M_UNDO,  M_CUT,   M_COPY, M_PSTE, M_SAVE,    KC_NO,   ALF,     KC_NO,   KC_NO,   KC_BSPC,
			                          KC_TRNS, KC_TRNS,  WNAV, KC_TRNS
							   ),

	[_WNAV] = LAYOUT_split_3x5_2(
			RESET,    KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,     HOOK,   LHLF,       FULL,       RHLF,       KC_NO,
			KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,  HYPR(KC_4), HYPR(KC_5), HYPR(KC_6), KC_NO,
			TG(_DEF), KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,     KC_NO,  HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), KC_NO,
			                          KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS
								),

	[_FUN] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_CAPS,      KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
			OS_SHFT, OS_CTRL,  OS_ALT,   OS_CMD,   KC_ESC,       KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
			KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,        KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
			                             KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS
								)
};

enum combo_events {
  // qwerty layer combos
  CAPS_COMBO_Q,
  ENTER_COMBO_Q,
  TAB_COMBO_Q,
  BSP_COMBO_Q,
  DEL_COMBO_Q,
  CTRLC_COMBO_Q,
  ESC_COMBO_Q,
  // beakl layer combos
  CAPS_COMBO_B,
  ENTER_COMBO_B,
  TAB_COMBO_B,
  BSP_COMBO_B,
  DEL_COMBO_B,
  CTRLC_COMBO_B,
  ESC_COMBO_B,
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
const uint16_t PROGMEM caps_combo_q[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM enter_combo_q[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM tab_combo_q[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM bsp_combo_q[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM del_combo_q[] = {KC_J, KC_L, COMBO_END};
// Ctrl-c combo mostly for Emacs
const uint16_t PROGMEM ctrlc_combo_q[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM esc_combo_q[] = {KC_F, KC_D, KC_S, COMBO_END};
// beakl combos
const uint16_t PROGMEM caps_combo_b[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM enter_combo_b[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM tab_combo_b[] = {KC_E, KC_A, COMBO_END};
const uint16_t PROGMEM bsp_combo_b[] = {KC_I, KC_A, COMBO_END};
const uint16_t PROGMEM del_combo_b[] = {KC_S, KC_N, COMBO_END};
// braces - vertical combos
const uint16_t PROGMEM lcbr_combo_b[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM lprn_combo_b[] = {KC_U, KC_A, COMBO_END};
const uint16_t PROGMEM lbrc_combo_b[] = {KC_X, KC_DOT, COMBO_END};
const uint16_t PROGMEM rcbr_combo_b[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM rprn_combo_b[] = {KC_C, KC_S, COMBO_END};
const uint16_t PROGMEM rbrc_combo_b[] = {KC_G, KC_D, COMBO_END};
// Ctrl-c combo mostly for Emacs
const uint16_t PROGMEM ctrlc_combo_b[] = {KC_S, KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM esc_combo_b[] = {KC_I, KC_E, KC_A, COMBO_END};

combo_t key_combos[] = {
  [CAPS_COMBO_Q] = COMBO_ACTION(caps_combo_q),
  [ENTER_COMBO_Q] = COMBO(enter_combo_q, KC_ENT),
  [TAB_COMBO_Q] = COMBO(tab_combo_q, KC_TAB),
  [BSP_COMBO_Q] = COMBO(bsp_combo_q, KC_BSPC),
  [DEL_COMBO_Q] = COMBO(del_combo_q, KC_DEL),
  [CTRLC_COMBO_Q] = COMBO(ctrlc_combo_q, LCTL(KC_C)),
  [ESC_COMBO_Q] = COMBO(esc_combo_q, KC_ESC),
  // Other combos...
  [CAPS_COMBO_B] = COMBO_ACTION(caps_combo_b),
  [ENTER_COMBO_B] = COMBO(enter_combo_b, KC_ENT),
  [TAB_COMBO_B] = COMBO(tab_combo_b, KC_TAB),
  [BSP_COMBO_B] = COMBO(bsp_combo_b, KC_BSPC),
  [DEL_COMBO_B] = COMBO(del_combo_b, KC_DEL),
  [CTRLC_COMBO_B] = COMBO(ctrlc_combo_b, LCTL(KC_C)),
  [ESC_COMBO_B] = COMBO(esc_combo_b, KC_ESC),
  [LCBR_COMBO_B] = COMBO(lcbr_combo_b, KC_LCBR),
  [LPRN_COMBO_B] = COMBO(lprn_combo_b, KC_LPRN),
  [LBRC_COMBO_B] = COMBO(lbrc_combo_b, KC_LBRC),
  [RCBR_COMBO_B] = COMBO(rcbr_combo_b, KC_RCBR),
  [RPRN_COMBO_B] = COMBO(rprn_combo_b, KC_RPRN),
  [RBRC_COMBO_B] = COMBO(rbrc_combo_b, KC_RBRC),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CAPS_COMBO_Q:
    case CAPS_COMBO_B:
      if (pressed) {
        caps_word_set(true);  // Activate Caps Word!
      }
      break;

    // Other combos...
  }
}


bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
	case CLEAR:
    case NUM:
    case SYM:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
	case CLEAR:
    case NUM:
    case SYM:
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
	if (!process_caps_word(keycode, record)) { return false; }

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

	switch (keycode) {

		case CLEAR:
			clear_oneshot_mods();
			if (get_oneshot_layer() != 0) {
				clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
			}
			layer_move(_DEF);
			return false;


	}

	return true;
}

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     return update_tri_layer_state(state, _LMOD, _RMOD, _NUM); */
/* } */
