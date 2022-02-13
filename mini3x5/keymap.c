#include QMK_KEYBOARD_H

// Callum oneshot mods and swapper
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "caps_word.h"
#include "oneshot.h"
#include "swapper.h"
#include "keycodes.h"
#include "layermodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEF] = LAYOUT_split_3x5_2(
			KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,   KC_P,
			KC_A, KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   KC_QUOT,
			KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
					          LMOD, NAV_SPC,  KC_BSPC, RMOD
							   ),

	[_NUM] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_PERC,   KC_PLUS, KC_7, KC_8, KC_9, KC_MINS,
			OS_SHFT, OS_CTRL, OS_ALT, OS_CMD, KC_EQL,    KC_DOT,  KC_4, KC_5, KC_6, KC_0,
			KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_UNDS,   KC_ASTR, KC_1, KC_2, KC_3, KC_SLSH,
			                        KC_TRNS,  KC_TRNS,   CANCEL,  KC_TRNS
								),

	[_NAV] = LAYOUT_split_3x5_2(
			SW_APP,  KC_NO,   TAB_L,  TAB_R,  KC_TAB,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,
			OS_SHFT, OS_CTRL, OS_ALT, OS_CMD, KC_ESC,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
			M_UNDO,  M_CUT,   M_COPY, M_PSTE, M_SAVE,    KC_NO,   ALF,     KC_NO,   KC_NO,   KC_BSPC,
			                          KC_TRNS, KC_TRNS,  WNAV, KC_TRNS
							   ),

	[_LMOD] = LAYOUT_split_3x5_2(
			KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,     GBPD, KC_AMPR, KC_ASTR, KC_UNDS, KC_NO,
			OS_SHFT, OS_CTRL, OS_ALT, OS_CMD, KC_NO,     PMIN,   KC_COLN, KC_EQL,  KC_SCLN, KC_NO,
			KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,     KC_PIPE, KC_MINS, KC_CIRC, KC_PLUS, KC_BSLS,
			                         KC_TRNS, KC_TRNS,   CLEAR,   FUN
								),

	[_RMOD] = LAYOUT_split_3x5_2(
			KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
			KC_GRV,  KC_TILD, KC_LCBR, KC_LPRN, KC_LBRC,     KC_NO, OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
			KC_LT,   KC_GT,   KC_RCBR, KC_RPRN, KC_RBRC,     KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
			                           FUN,     KC_TRNS,     CLEAR, KC_TRNS
								),

	[_WNAV] = LAYOUT_split_3x5_2(
			KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,     HOOK,   LHLF,       FULL,       RHLF,       KC_NO,
			KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,     KC_NO,  HYPR(KC_4), HYPR(KC_5), HYPR(KC_6), KC_NO,
			KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,     KC_NO,  HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), KC_NO,
			                     KC_TRNS,  KC_TRNS,   CLEAR,  KC_TRNS
								),

	[_FUN] = LAYOUT_split_3x5_2(
			RESET,   KC_VOLD,  KC_MUTE,  KC_VOLU,  KC_CAPS,      KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
			OS_SHFT, OS_CTRL,  OS_ALT,   OS_CMD,   KC_ESC,       KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
			KC_TRNS, KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_NO,        KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
			                             KC_TRNS,  KC_TRNS,      KC_TRNS, CLEAR
								)
};

enum combo_events {
  CAPS_COMBO,
  ENTER_COMBO,
  TAB_COMBO,
  DQUO_COMBO,
  QUES_COMBO,
  CTRLC_COMBO,
  ESC_COMBO,
  NUM_COMBO,
  // Other combos...
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM caps_combo[] = {KC_F, KC_J, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM dquo_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM ques_combo[] = {KC_J, KC_L, COMBO_END};
// Ctrl-c combo mostly for Emacs
const uint16_t PROGMEM ctrlc_combo[] = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_F, KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM num_combo[] = {NAV_SPC, KC_BSPC, COMBO_END};


combo_t key_combos[] = {
  [CAPS_COMBO] = COMBO_ACTION(caps_combo),
  [ENTER_COMBO] = COMBO(enter_combo, KC_ENT),
  [TAB_COMBO] = COMBO(tab_combo, KC_TAB),
  [DQUO_COMBO] = COMBO(dquo_combo, KC_DQUO),
  [QUES_COMBO] = COMBO(ques_combo, KC_QUES),
  [CTRLC_COMBO] = COMBO(ctrlc_combo, LCTL(KC_C)),
  [ESC_COMBO] = COMBO(esc_combo, KC_ESC),
  [NUM_COMBO] = COMBO(num_combo, NUMWORD)
  // Other combos...
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CAPS_COMBO:
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
    case LMOD:
    case RMOD:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
	case CLEAR:
    case LMOD:
    case RMOD:
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

    if (!process_num_word(keycode, record)) { return false; }

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


		case CANCEL:
			layer_off(_NUM);
			layer_off(_LMOD);
			layer_off(_RMOD);
			return false;

		case NUMWORD:
            process_num_word_activation(record);
            return false;
	}

	return true;
}

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     return update_tri_layer_state(state, _LMOD, _RMOD, _NUM); */
/* } */
